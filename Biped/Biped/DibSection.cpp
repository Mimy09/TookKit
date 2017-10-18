#include "DibSection.h"
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <sstream>


#define DIB_THROW(stream_)                  \
{                                           \
    std::ostringstream oss;                 \
    oss << stream_;                         \
    throw std::string(oss.str());           \
}

#define DIB_ASSERT(condition_)                                      \
{                                                                   \
    if (!(condition_)) DIB_THROW("Assertion failure at line ");     \
}


std::string getLastErrorString() {
	int e = GetLastError();
	switch(e) {
	case 2:
	case 3: return "File not found";
	case 5: return "Access denied";
	case 8: return "Not enough memory";
	default:
		char error[101];
		_snprintf_s(error, 100, 100, "GetLastError = %ld", e);
		return error;
	}
}



/***************************************************************************************************
****************************************************************************************************/
DibSection::DibSection() {
	m_hBitmap = NULL;
	m_prevBitmap = NULL;
	m_hdc = NULL;
	m_pixels = NULL;
}

/***************************************************************************************************
****************************************************************************************************/
DibSection::~DibSection() {
	try {
		destroy();
	} catch(...) {
	}
}

/***************************************************************************************************
****************************************************************************************************/
DibSection::DibSection(const DibSection& other) {
	m_hBitmap = NULL;
	m_prevBitmap = NULL;
	m_hdc = NULL;
	m_pixels = NULL;

	if(!other.m_pixels) {
		throw std::string("A DIB with no pixels (not created or loaded) cannot be an R-Value");
	}

	create(HWND_DESKTOP, other.m_width, other.m_height);

	DIB_ASSERT(m_pixels);
	DIB_ASSERT(other.m_pixels);

	memcpy(m_pixels, other.m_pixels, m_height * m_stride);
}

/***************************************************************************************************
****************************************************************************************************/
const DibSection& DibSection::operator =(const DibSection& other) {
	if(&other != this) {
		if(!other.m_pixels) {
			DIB_THROW("A DIB with no pixels (not created or loaded) cannot be an R-Value");
		}

		destroy();

		create(HWND_DESKTOP, other.m_width, other.m_height);

		DIB_ASSERT(m_pixels);
		DIB_ASSERT(other.m_pixels);

		memcpy(m_pixels, other.m_pixels, m_height * m_stride);
	}
	return *this;
}

/***************************************************************************************************
Returns the stride that a particular width bitmap will occupy in memory (in bytes). This will vary
according to no. of the bits per pixel.
****************************************************************************************************/
static unsigned stride(unsigned width, unsigned bpp) {
	unsigned num = width * bpp / 8;
	unsigned alignment = sizeof(DWORD);
	return (((num - 1) / alignment) + 1) * alignment;
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::add(
	HWND hwnd,
	int xDest, int yDest,
	const DibSection& other,
	int xOther, int yOther, int widthOther, int heightOther,
	const DibColor& defaultColor) {
	if(widthOther <= 0) DIB_THROW("widthOther must be greater than zero");
	if(heightOther <= 0) DIB_THROW("heightOther must be greater than zero");
	if(xOther < 0) DIB_THROW("xOther cannot be less than zero");
	if(yOther < 0) DIB_THROW("yOther cannot be less than zero");

	// Compute the size and position of new area that will include both 
	// the current dib and the other dib
	int xNew, yNew, widthNew, heightNew;
	if(xDest < 0) {
		xNew = xDest;
	} else {
		xNew = 0;
	}
	if(yDest < 0) {
		yNew = yDest;
	} else {
		yNew = 0;
	}

	// The new width will be the sum of the existing width plus the amount by
	// which the other dib overlaps the existing width on the left and the right
	int leftOverlap = -xNew;
	int rightOverlap;
	if(xDest + widthOther > m_width) {
		rightOverlap = xDest + widthOther - m_width;
	} else {
		rightOverlap = 0;
	}
	DIB_ASSERT(leftOverlap >= 0);
	DIB_ASSERT(rightOverlap >= 0);
	widthNew = m_width + leftOverlap + rightOverlap;

	// The new height will be the sum of the existing height plus the amount by
	// which the other dib overlaps the existing height on the top and the bottom
	int bottomOverlap = -yNew;
	int topOverlap;
	if(yDest + heightOther > m_height) {
		topOverlap = yDest + heightOther - m_height;
	} else {
		topOverlap = 0;
	}
	DIB_ASSERT(bottomOverlap >= 0);
	DIB_ASSERT(topOverlap >= 0);
	heightNew = m_height + bottomOverlap + topOverlap;

	// Create a new dib to cover the new area
	DibSection newDib;
	newDib.create(hwnd, widthNew, heightNew, defaultColor);

	int y;
	DibColor *pxlSource,
		*pxlDest;
	int bytesToCopy;
	int xOrigin, yOrigin;

	// Copy the existing pixels to the appropriate (possibly shifted) location
	// in the new dib.
	xOrigin = xDest < 0 ? abs(xDest) : 0;
	yOrigin = yDest < 0 ? abs(yDest) : 0;
	bytesToCopy = m_stride;
	if(bytesToCopy > 0) {
		for(y = 0; y < m_height; y++) {
			pxlDest = newDib.getPixel(xOrigin, yOrigin + y);
			pxlSource = getPixel(0, y);
			memcpy(pxlDest, pxlSource, bytesToCopy);
		}
	}

	// Clip the other dib's area to its valid area
	if(xOther + widthOther > other.m_width) {
		widthOther = other.m_width - xOther;
	}
	if(yOther + heightOther > other.m_height) {
		heightOther = other.m_height - yOther;
	}

	// Copy the other dib's pixels to the appropriate location in the new dib
	xOrigin = xDest >= 0 ? xDest : 0;
	yOrigin = yDest >= 0 ? yDest : 0;
	if(other.m_bpp != 24) {
		DIB_THROW("Only 24-bit bitmaps supported");
	}
	bytesToCopy = widthOther * 3;
	if(bytesToCopy > 0) {
		for(y = 0; y < heightOther; y++) {
			pxlDest = newDib.getPixel(xOrigin, yOrigin + y);
			pxlSource = other.getPixel(xOther, yOther + y);
			memcpy(pxlDest, pxlSource, bytesToCopy);
		}
	}


	// Assign the new dib over the top of the current dib
	*this = newDib;
}

/***************************************************************************************************
****************************************************************************************************/
static HBITMAP createDIB(
	HDC hdc, int nWidth, int nHeight, int bitCount, void **ppDIBBits) {
	// Validate input parameters
	if(NULL == hdc)
		return NULL;
	if(0 == nWidth || 0 == nHeight)
		return NULL;

	unsigned bytesPerPixel = bitCount / 8;

	// Allocate memory for DIB header & colour table
	LPBITMAPINFOHEADER pbih = (LPBITMAPINFOHEADER)malloc(
		sizeof(BITMAPINFOHEADER) + nWidth * nHeight * bytesPerPixel);
	if(NULL == pbih)
		return NULL;

	ZeroMemory(pbih, sizeof(BITMAPINFOHEADER) + nWidth * nHeight * bytesPerPixel);

	// Initialise bitmap header
	pbih->biSize = sizeof(BITMAPINFOHEADER);
	pbih->biWidth = nWidth;
	pbih->biHeight = nHeight;
	pbih->biPlanes = 1;
	pbih->biBitCount = bitCount;
	pbih->biCompression = BI_RGB;
	pbih->biSizeImage = 0;
	pbih->biXPelsPerMeter = 0;
	pbih->biYPelsPerMeter = 0;
	pbih->biClrUsed = 0;
	pbih->biClrImportant = 0;

	// Create the DIB and return it to caller
	HBITMAP hbmp = CreateDIBSection(hdc, (LPBITMAPINFO)pbih, DIB_RGB_COLORS,
		ppDIBBits, 0, 0L);
	free(pbih);
	return hbmp;
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::create(
	HWND hwnd, unsigned width, unsigned height, const DibColor& defaultColor) {
	if(width == 0 || height == 0)
		DIB_THROW("Cannot create a DibSection with zero height or width");

	// Delete any existing DIB and hdc
	if(m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
	if(m_hdc) {
		DeleteDC(m_hdc);
		m_hdc = NULL;
	}

	m_bpp = 24;

	m_width = width;
	m_height = height;
	m_stride = stride(m_width, m_bpp);
	m_bottomUp = true;

	unsigned numDataBytes = m_stride * m_height;
	unsigned totalSize =
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + numDataBytes;

	ZeroMemory(&m_bmfh, sizeof(BITMAPFILEHEADER));
	m_bmfh.bfType = 19778; // "BM"
	m_bmfh.bfSize = totalSize;
	m_bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// Allocate memory for DIB header & colour table
	char *buffer = (char *)malloc(totalSize);
	if(!buffer) {
		DIB_THROW("Memory failure");
	}
	ZeroMemory(buffer, totalSize);

	// Initialise bitmap header
	ZeroMemory(&m_bmih, sizeof(BITMAPINFOHEADER));
	m_bmih.biSize = sizeof(BITMAPINFOHEADER);
	m_bmih.biWidth = width;
	m_bmih.biHeight = height;
	m_bmih.biPlanes = 1;
	m_bmih.biBitCount = m_bpp;
	m_bmih.biCompression = BI_RGB;

	// ...and copy it into the buffer
	memcpy(buffer + sizeof(BITMAPFILEHEADER),
		&m_bmih, sizeof(BITMAPINFOHEADER));

	// Create a memory dc and associated DIB
	HDC hdc = GetDC(hwnd);

	m_hdc = CreateCompatibleDC(hdc);
	if(!m_hdc)
		DIB_THROW("Failed to create compatible DC");

	LPBITMAPINFOHEADER pbih =
		(LPBITMAPINFOHEADER)(buffer + sizeof(BITMAPFILEHEADER));

	// Create the DIB and return it to caller
	m_hBitmap = CreateDIBSection(hdc, (LPBITMAPINFO)pbih, DIB_RGB_COLORS,
		(void **)&m_pixels, 0, 0L);
	if(0 == m_hBitmap)
		DIB_THROW("Failed loading dib section - " << getLastErrorString());

	// Read the default color into the DIB pixels
	BYTE *pBits;
	for(long y = 0; y < m_height; y++) {
		pBits = (BYTE *)m_pixels + y * m_stride;

		for(long x = 0; x < m_width; x++) {
			pBits[0] = defaultColor.b;
			pBits[1] = defaultColor.g;
			pBits[2] = defaultColor.r;

			pBits += 3;
		}
	}

	ReleaseDC(hwnd, hdc);

	m_prevBitmap = SelectBitmap(m_hdc, m_hBitmap);

	free(buffer);
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::destroy() {
	if(m_hBitmap) {
		if(m_prevBitmap) {
			SelectObject(m_hdc, m_prevBitmap);
		}
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
	if(m_hdc) {
		DeleteDC(m_hdc);
		m_hdc = NULL;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::fill(const DibColor& color) {
	if(!m_pixels) {
		DIB_THROW("DIB has no pixels - it has not yet been created or loaded");
	}
	BYTE *pBits;
	int destStride = stride(m_width, m_bmih.biBitCount);

	for(long y = 0; y < m_height; y++) {
		pBits = (BYTE *)m_pixels + y * destStride;

		for(long x = 0; x < m_width; x++) {
			pBits[0] = color.b;
			pBits[1] = color.g;
			pBits[2] = color.r;

			pBits += 3;
		}
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::fill(
	const DibColor& color, int x, int y, unsigned width, unsigned height) {
	if(!m_pixels) {
		DIB_THROW("DIB has no pixels - it has not yet been created or loaded");
	}

	// Clip the caller's area specification to the DIB's area
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x + width > m_width) width = m_width - x;
	if(y + height > m_height) height = m_height - y;

	BYTE *pBits;
	int destStride = stride(m_width, m_bmih.biBitCount);

	for(long yPxl = y; yPxl < (long)height; yPxl++) {
		pBits = (BYTE *)m_pixels + yPxl * destStride;

		for(long xPxl = 0; xPxl < (long)width; xPxl++) {
			pBits[0] = color.b;
			pBits[1] = color.g;
			pBits[2] = color.r;

			pBits += 3;
		}
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::fillGradient(
	GradientTypes gradientType, const DibColor & startColor, const DibColor & endColor) {
	if(!m_pixels) {
		DIB_THROW("DIB has no pixels - it has not yet been created or loaded");
	}

	double rStart = startColor.r;
	double rEnd = endColor.r;
	double gStart = startColor.g;
	double gEnd = endColor.g;
	double bStart = startColor.b;
	double bEnd = endColor.b;

	BYTE *pBits;
	DibColor *pColor;

	int destStride = stride(m_width, m_bmih.biBitCount);

	switch(gradientType) {
	case GradientTypes::Horizontal:
	{
		double rStep = (rEnd - rStart) / m_width;
		double gStep = (gEnd - gStart) / m_width;
		double bStep = (bEnd - bStart) / m_width;

		for(long y = 0; y < m_height; y++) {
			pBits = (BYTE *)m_pixels + y * destStride;

			for(long x = 0; x < m_width; x++) {
				pBits[0] = (BYTE)(bStart + bStep * x);
				pBits[1] = (BYTE)(gStart + gStep * x);
				pBits[2] = (BYTE)(rStart + rStep * x);

				pBits += 3;
			}
		}

	}
	break;

	case GradientTypes::Vertical:
	{
		double rStep = (rEnd - rStart) / m_height;
		double gStep = (gEnd - gStart) / m_height;
		double bStep = (bEnd - bStart) / m_height;

		for(long x = 0; x < m_width; x++) {
			for(long y = 0; y < m_height; y++) {
				pColor = getPixel(x, y);

				pColor->b = (BYTE)(bStart + bStep * y);
				pColor->g = (BYTE)(gStart + gStep * y);
				pColor->r = (BYTE)(rStart + rStep * y);
			}
		}
	}
	break;

	case GradientTypes::Radial:
	{
		double rxStep = (rEnd - rStart) / m_width;
		double gxStep = (gEnd - gStart) / m_width;
		double bxStep = (bEnd - bStart) / m_width;

		double ryStep = (rEnd - rStart) / m_height;
		double gyStep = (gEnd - gStart) / m_height;
		double byStep = (bEnd - bStart) / m_height;

		double rRange = rEnd - rStart;
		double gRange = gEnd - gStart;
		double bRange = bEnd - bStart;

		double halfWidth = m_width / 2.0;
		double halfHeight = m_height / 2.0;
		double rx, ry;
		double xCtr = m_width / 2.0;
		double yCtr = m_height / 2.0;

		double distance;
		for(long x = 0; x < m_width; x++) {
			for(long y = 0; y < m_height; y++) {
				pColor = getPixel(x, y);

				rx = (x - xCtr) / halfWidth;
				ry = (y - yCtr) / halfHeight;

				distance = sqrt(rx * rx / 1.0 + ry * ry);
				if(distance > 1.0) {
					distance = 1.0;
				}

				pColor->b = (BYTE)(bStart + distance * bRange);
				pColor->g = (BYTE)(gStart + distance * gRange);
				pColor->r = (BYTE)(rStart + distance * rRange);
			}
		}
	}
	break;
	}

}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::getInfo(const char *fileName, Info *info) const {
	DIB_ASSERT(fileName);
	DIB_ASSERT(info);

	FILE *f;
	if(fopen_s(&f, fileName, "rb") == 0) {
		fclose(f);
	} else {
		DIB_THROW("File \"" << fileName << "\" does not exist");
	}

	static char drive[5000];
	static char dir[5000];
	static char name[5000];
	static char extension[5000];

	_splitpath_s(fileName, drive, dir, name, extension);

	if(_stricmp(extension, ".bmp") == 0) {
		getInfo_BMP(fileName, info);
	} else {
		DIB_THROW("Unsupported file extension for file \"" << fileName << "\"");
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::getInfo_BMP(const char *fileName, Info *info) const {
	DIB_ASSERT(fileName);
	DIB_ASSERT(info);

	FILE *file = NULL;
	HDC hdc = NULL;

	DIB_ASSERT(fileName);

	// Open the file
	if(fopen_s(&file, fileName, "rb") != 0) {
		DIB_THROW("Error opening file " << fileName);
	}

	// Create a buffer big enough to hold the two header stuctures
	unsigned bufferSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 10;
	char *buffer = (char *)malloc(bufferSize);
	DIB_ASSERT(buffer);

	// Read the headers
	if(fseek(file, 0, SEEK_SET) != 0)
		DIB_THROW("Seek failure");
	if(fread(buffer, bufferSize, 1, file) != 1)
		DIB_THROW("Read failure");

	// Close the file
	if(file) {
		fclose(file);
	}

	// Point to the headers
	BITMAPFILEHEADER *pbmf = (BITMAPFILEHEADER *)buffer;
	BITMAPINFOHEADER *pbmi =
		(BITMAPINFOHEADER *)(buffer + sizeof(BITMAPFILEHEADER));

	// Copy the data of interest to the caller
	info->width = pbmi->biWidth;
	if(pbmi->biHeight < 0) {
		info->bottomUp = false;
	} else {
		info->bottomUp = true;
	}
	info->height = abs(pbmi->biHeight);
	info->bitCount = pbmi->biBitCount;

	// Clean up
	if(buffer) {
		free(buffer);
	}
}

/***************************************************************************************************
****************************************************************************************************/
unsigned DibSection::getNumPixels() {
	return m_width * m_height;
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::load(HWND hwnd, const char *fileName) {
	DIB_ASSERT(fileName);

	static char drive[5000];
	static char dir[5000];
	static char name[5000];
	static char extension[5000];

	_splitpath_s(fileName, drive, sizeof(drive), dir, sizeof(dir), name, sizeof(name), extension, sizeof(extension));

	if(_stricmp(extension, ".bmp") == 0) {
		loadFile_BMP(hwnd, fileName);
	} else {
		DIB_THROW("Unsupported file extension for file \"" << fileName << "\"");
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::loadFile_BMP(HWND hwnd, const char *fileName) {
	BYTE *pFileBits = NULL;
	FILE *file = NULL;
	HDC hdc = NULL;

	try {
		DIB_ASSERT(fileName);

		// Open the file
		if(fopen_s(&file, fileName, "rb") != 0) {
			DIB_THROW("Error opening file " << fileName);
		}

		// Determine the size of the data file
		if(fseek(file, 0, SEEK_END) != 0)
			DIB_THROW("Seek failure");
		int nFileBytes = ftell(file);
		if(nFileBytes == -1)
			DIB_THROW("File failure");

		// Allocate memory for entire file
		pFileBits = (BYTE *)malloc(nFileBytes);
		if(!pFileBits)
			DIB_THROW("Memory failure");

		// Read the entire file into memory
		if(fseek(file, 0, SEEK_SET) != 0)
			DIB_THROW("Seek failure");
		if(fread(pFileBits, nFileBytes, 1, file) != 1)
			DIB_THROW("Read failure");

		// Point to the bitmap header structures
		BITMAPFILEHEADER *pbmf = (BITMAPFILEHEADER *)pFileBits;
		BITMAPINFOHEADER *pbmi =
			(BITMAPINFOHEADER *)(pFileBits + sizeof(BITMAPFILEHEADER));

		if(pbmi->biBitCount != 24 && pbmi->biBitCount != 32)
			DIB_THROW("Only 24-bit and 32-bit bitmaps supported");
		m_bpp = pbmi->biBitCount;

		// Save the header structures
		m_bmfh = *pbmf;
		m_bmih = *pbmi;

		// Set the height of the DIB (in bytes) to the same height as the 
		// image (in pixels)
		BOOL bTopDown = (pbmi->biHeight < 0);
		if(bTopDown)
			m_height = WORD(-pbmi->biHeight);
		else
			m_height = (WORD)pbmi->biHeight;

		m_bottomUp = !bTopDown;

		// Each line of a DIB starts on an even 4-byte boundary
		m_width = WORD(pbmi->biWidth);
		m_stride = stride(pbmi->biWidth, pbmi->biBitCount);

		// Delete any existing DIB and hdc
		destroy();

		// Create a memory dc and associated DIB
		hdc = GetDC(hwnd);

		m_hdc = CreateCompatibleDC(hdc);
		if(!m_hdc)
			DIB_THROW("Failed to create compatible DC");

		m_hBitmap = createDIB(
			hdc, m_width, m_height, m_bpp, (void **)&m_pixels);
		if(0 == m_hBitmap)
			DIB_THROW("Failed loading dib section - " << getLastErrorString());
		ReleaseDC(hwnd, hdc);

		m_prevBitmap = SelectBitmap(m_hdc, m_hBitmap);

		// Read the pixels into the DIB
		BYTE *pBits;
		BYTE *pColors;
		unsigned bytesPerPixel = m_bpp / 8;
		for(long y = 0; y < m_height; y++) {
			pBits = (BYTE *)m_pixels + y * (m_stride);
			pColors = pFileBits + pbmf->bfOffBits + (y * m_stride);

			for(long x = 0; x < m_width; x++) {
				pBits[0] = pColors[0];
				pBits[1] = pColors[1];
				pBits[2] = pColors[2];

				pBits += bytesPerPixel;
				pColors += bytesPerPixel;
			}
		}

		if(pFileBits)
			free(pFileBits);

		if(file != NULL)
			fclose(file);
	}

	catch(...) {
		if(hdc)
			ReleaseDC(hwnd, hdc);

		if(pFileBits)
			free(pFileBits);

		if(file != NULL)
			fclose(file);

		throw;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::load(HWND hwnd, FILE *file, unsigned numBytes) {
	DIB_ASSERT(file);
	DIB_ASSERT(numBytes > 0);

	BYTE *pFileBits = NULL;
	HDC hdc = NULL;

	try {
		// Allocate memory for entire bitmap
		pFileBits = (BYTE *)malloc(numBytes);
		if(!pFileBits)
			DIB_THROW("Memory failure");

		// ...and read entire bitmnap into memory
		if(fread(pFileBits, numBytes, 1, file) != 1) {
			DIB_THROW("Read failure");
		}

		// Point to the bitmap header structures
		BITMAPFILEHEADER *pbmf = (BITMAPFILEHEADER *)pFileBits;
		BITMAPINFOHEADER *pbmi =
			(BITMAPINFOHEADER *)(pFileBits + sizeof(BITMAPFILEHEADER));

		if(pbmi->biBitCount != 24 && pbmi->biBitCount != 32)
			DIB_THROW("Only 24-bit and 32-bit bitmaps supported");
		m_bpp = pbmi->biBitCount;

		// Save the header structures
		m_bmfh = *pbmf;
		m_bmih = *pbmi;

		// Set the height of the DIB (in bytes) to the same height as the 
		// image (in pixels)
		BOOL bTopDown = (pbmi->biHeight < 0);
		if(bTopDown)
			m_height = WORD(-pbmi->biHeight);
		else
			m_height = (WORD)pbmi->biHeight;

		m_bottomUp = !bTopDown;

		// Each line of a DIB starts on an even 4-byte boundary
		m_width = WORD(pbmi->biWidth);
		m_stride = stride(pbmi->biWidth, pbmi->biBitCount);

		// Delete any existing DIB and hdc
		destroy();

		// Create a memory dc and associated DIB
		hdc = GetDC(hwnd);

		m_hdc = CreateCompatibleDC(hdc);
		if(!m_hdc)
			DIB_THROW("Failed to create compatible DC");

		m_hBitmap = createDIB(
			hdc, m_width, m_height, m_bpp, (void **)&m_pixels);
		if(0 == m_hBitmap)
			DIB_THROW("Failed loading dib section - " << getLastErrorString());
		ReleaseDC(hwnd, hdc);

		m_prevBitmap = SelectBitmap(m_hdc, m_hBitmap);

		// Read the pixels into the DIB
		BYTE *pBits;
		BYTE *pColors;
		unsigned bytesPerPixel = m_bpp / 8;
		for(long y = 0; y < m_height; y++) {
			pBits = (BYTE *)m_pixels + y * (m_stride);
			pColors = pFileBits + pbmf->bfOffBits + (y * m_stride);

			for(long x = 0; x < m_width; x++) {
				pBits[0] = pColors[0];
				pBits[1] = pColors[1];
				pBits[2] = pColors[2];

				pBits += bytesPerPixel;
				pColors += bytesPerPixel;
			}
		}

		if(pFileBits)
			free(pFileBits);
	}

	catch(...) {
		if(hdc)
			ReleaseDC(hwnd, hdc);

		if(pFileBits)
			free(pFileBits);

		throw;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::load(HWND hwnd, void *buffer) {
	DIB_ASSERT(buffer);

	BYTE *pFileBits = (BYTE *)buffer;
	HDC hdc = NULL;

	try {
		// Point to the bitmap header structures
		BITMAPFILEHEADER *pbmf = (BITMAPFILEHEADER *)pFileBits;
		BITMAPINFOHEADER *pbmi =
			(BITMAPINFOHEADER *)(pFileBits + sizeof(BITMAPFILEHEADER));

		if(pbmi->biBitCount != 24 && pbmi->biBitCount != 32)
			DIB_THROW("Only 24-bit and 32-bit bitmaps supported");
		m_bpp = pbmi->biBitCount;

		// Save the header structures
		m_bmfh = *pbmf;
		m_bmih = *pbmi;

		// Set the height of the DIB (in bytes) to the same height as the 
		// image (in pixels)
		BOOL bTopDown = (pbmi->biHeight < 0);
		if(bTopDown)
			m_height = WORD(-pbmi->biHeight);
		else
			m_height = (WORD)pbmi->biHeight;

		m_bottomUp = !bTopDown;

		// Each line of a DIB starts on an even 4-byte boundary
		m_width = WORD(pbmi->biWidth);
		m_stride = stride(pbmi->biWidth, pbmi->biBitCount);

		// Delete any existing DIB and hdc
		destroy();

		// Create a memory dc and associated DIB
		hdc = GetDC(hwnd);

		m_hdc = CreateCompatibleDC(hdc);
		if(!m_hdc)
			DIB_THROW("Failed to create compatible DC");

		m_hBitmap = createDIB(hdc, m_width, m_height, m_bpp, (void **)&m_pixels);
		if(0 == m_hBitmap)
			DIB_THROW("Failed loading dib section - " << getLastErrorString());
		ReleaseDC(hwnd, hdc);

		m_prevBitmap = SelectBitmap(m_hdc, m_hBitmap);

		// Read the pixels into the DIB
		BYTE *pBits;
		BYTE *pColors;
		unsigned bytesPerPixel = m_bpp / 8;
		for(long y = 0; y < m_height; y++) {
			pBits = (BYTE *)m_pixels + y * (m_stride);
			pColors = pFileBits + pbmf->bfOffBits + (y * m_stride);

			for(long x = 0; x < m_width; x++) {
				pBits[0] = pColors[0];
				pBits[1] = pColors[1];
				pBits[2] = pColors[2];

				pBits += bytesPerPixel;
				pColors += bytesPerPixel;
			}
		}
	}

	catch(...) {
		if(hdc)
			ReleaseDC(hwnd, hdc);
		throw;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::load(
	HWND hwnd, const char *fileName,
	int xOrigin, int yOrigin, int width, int height,
	const DibColor& defaultColor) {
	BYTE *pFileBits = NULL;
	FILE *file = NULL;
	HDC hdc = NULL;

	if(width <= 0) DIB_THROW("Width must be greater than zero");
	if(height <= 0) DIB_THROW("Height must be greater than zero");

	try {
		DIB_ASSERT(fileName);

		// Open the file
		if(fopen_s(&file, fileName, "rb") != 0) {
			DIB_THROW("Error opening file " << fileName);
		}

		// Create a buffer big enough to hold the two header stuctures
		unsigned bufferSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 10;
		char *buffer = (char *)malloc(bufferSize);
		DIB_ASSERT(buffer);

		// Read the headers
		if(fseek(file, 0, SEEK_SET) != 0)
			DIB_THROW("Seek failure");
		if(fread(buffer, bufferSize, 1, file) != 1)
			DIB_THROW("Read failure");

		// Determine the total size of the bitmap file
		if(fseek(file, 0, SEEK_END) != 0)
			DIB_THROW("Seek failure");
		int totalSourceBytes = ftell(file);
		if(totalSourceBytes == -1)
			DIB_THROW("File failure");
		if(fseek(file, 0, SEEK_SET) != 0)
			DIB_THROW("Seek failure");

		// Point to the bitmap header structures
		BITMAPFILEHEADER *pbmf = (BITMAPFILEHEADER *)buffer;
		BITMAPINFOHEADER *pbmi =
			(BITMAPINFOHEADER *)(buffer + sizeof(BITMAPFILEHEADER));

		if(pbmi->biBitCount != 24 && pbmi->biBitCount != 32)
			DIB_THROW("Only 24-bit and 32-bit bitmaps supported");

		m_bpp = pbmi->biBitCount;

		// Save the header structures
		m_bmfh = *pbmf;
		m_bmih = *pbmi;

		// Free the buffer
		free(buffer);
		buffer = 0;
		pbmf = 0;
		pbmi = 0;

		// Determine the dimensions of the source file
		int sourceWidth, sourceHeight, sourceStride;
		BOOL bTopDown = (m_bmih.biHeight < 0);
		if(bTopDown)
			sourceHeight = WORD(-m_bmih.biHeight);
		else
			sourceHeight = (WORD)m_bmih.biHeight;
		sourceWidth = WORD(m_bmih.biWidth); // Each line starts on an even 4-byte boundary
		sourceStride = stride(sourceWidth, m_bmih.biBitCount);

		// Dimensions of the destination DIB
		int destWidth = width;
		int destHeight = height;
		int destStride = stride(destWidth, m_bmih.biBitCount);

		m_bottomUp = !bTopDown;

		// Delete any existing DIB and hdc
		destroy();

		// Create a memory dc and associated DIB
		hdc = GetDC(hwnd);

		m_hdc = CreateCompatibleDC(hdc);
		if(!m_hdc)
			DIB_THROW("Failed to create compatible DC");

		// Make the bitmap the requested width and height
		m_hBitmap = createDIB(hdc, width, height, m_bpp, (void **)&m_pixels);
		if(0 == m_hBitmap)
			DIB_THROW("Failed loading dib section - " << getLastErrorString());
		ReleaseDC(hwnd, hdc);

		m_prevBitmap = SelectBitmap(m_hdc, m_hBitmap);

		// Fill the dib with the default color
		BYTE *pBits;
		unsigned bytesPerPixel = m_bpp / 8;
		for(long y = 0; y < height; y++) {
			pBits = (BYTE *)m_pixels + y * destStride;

			for(long x = 0; x < width; x++) {
				pBits[0] = defaultColor.b;
				pBits[1] = defaultColor.g;
				pBits[2] = defaultColor.r;

				pBits += bytesPerPixel;
			}
		}

		// Read the pixels from the source bitmap file into the DIB
		unsigned fileOffset, bytesToRead;
		int xFile, yFile;
		int cxFile, cyFile;
		int xDib, yDib;
		bool intersection = true;

		if(xOrigin < 0) {
			xFile = 0;
			xDib = -xOrigin;
		} else if(xOrigin >= sourceWidth) {
			intersection = false;
		} else {
			xFile = xOrigin;
			xDib = 0;
		}
		if(intersection && xDib >= width) {
			intersection = false;
		}

		if(intersection) {
			DIB_ASSERT(xFile >= 0);
			cxFile = width;
			if(xFile + cxFile > sourceWidth) {
				cxFile = sourceWidth - xFile;
			}
			if(xDib + cxFile > destWidth) {
				cxFile = destWidth - xDib;
			}
			if(cxFile <= 0) {
				intersection = false;
			}

			if(intersection && yOrigin < 0) {
				yFile = 0;
				yDib = -yOrigin;
			} else if(yOrigin >= sourceHeight) {
				intersection = false;
			} else {
				yFile = yOrigin;
				yDib = 0;
			}
			if(intersection && yDib >= height) {
				intersection = false;
			}

			if(intersection) {
				DIB_ASSERT(yFile >= 0);
				cyFile = height;
				if(yFile + cyFile > sourceHeight) {
					cyFile = sourceHeight - yFile;
				}
				if(yDib + cyFile > destHeight) {
					cyFile = destHeight - yDib;
				}
				if(cyFile <= 0) {
					intersection = false;
				}
			}
		}

		if(intersection) {
			DIB_ASSERT(xFile >= 0);
			DIB_ASSERT(xDib >= 0);
			DIB_ASSERT(cxFile > 0);
			DIB_ASSERT(yFile >= 0);
			DIB_ASSERT(yDib >= 0);
			DIB_ASSERT(cyFile > 0);

			for(int y = yDib; y < (int)yDib + cyFile; y++) {
				// Point to the current line in the dest DIB
				if(m_bottomUp) {
					pBits = (BYTE *)m_pixels + (destHeight - y - 1) * destStride + xDib * bytesPerPixel;
				} else {
					pBits = (BYTE *)m_pixels + y * (destStride)+xDib * bytesPerPixel;
				}

				// Calculate the file offset in the source file
				if(m_bottomUp) {
					fileOffset = m_bmfh.bfOffBits + ((sourceHeight - yFile - 1) * sourceStride + (xFile * bytesPerPixel));
				} else {
					fileOffset = m_bmfh.bfOffBits + (yFile * sourceStride + (xFile * bytesPerPixel));
				}
				yFile++;

				bytesToRead = cxFile * bytesPerPixel;

				if(fileOffset + bytesToRead <= (unsigned)totalSourceBytes) {
					// Read the line from the file
					if(fseek(file, fileOffset, SEEK_SET) != 0)
						DIB_THROW("Seek failure");
					if(fread(pBits, bytesToRead, 1, file) != 1)
						DIB_THROW("Read failure");
				}
			}
		}

		if(file != NULL)
			fclose(file);

		// Finally, update the DIB's dimensions
		m_width = destWidth;
		m_height = destHeight;
		if(bTopDown) {
			m_bmih.biHeight = -destHeight;
		} else {
			m_bmih.biHeight = destHeight;
		}
		m_stride = destStride;
		m_bmfh.bfSize = m_bmfh.bfOffBits + destHeight * destStride;
		m_bmih.biWidth = m_width;

	}

	catch(...) {
		if(hdc)
			ReleaseDC(hwnd, hdc);

		if(pFileBits)
			free(pFileBits);

		if(file != NULL)
			fclose(file);

		throw;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::save(const char *szFileName) const {
	if(!m_pixels) {
		DIB_THROW("DIB has no pixels - it has not yet been created or loaded");
	}

	BYTE *pFileBits = NULL;
	FILE *file = NULL;
	HDC hdc = NULL;

	try {
		DIB_ASSERT(szFileName);

		// Open the file
		if(fopen_s(&file, szFileName, "wb") != 0) {
			DIB_THROW("Error opening file");
		}

		if(fwrite(&m_bmfh, sizeof(m_bmfh), 1, file) != 1)
			DIB_THROW("Error writing file");

		if(fwrite(&m_bmih, sizeof(m_bmih), 1, file) != 1)
			DIB_THROW("Error writing file");

		// Write the pixels into the file
		if(fwrite(m_pixels, m_height * m_stride, 1, file) != 1)
			DIB_THROW("Error writing file pixels");

		if(file != NULL)
			fclose(file);
	}

	catch(...) {
		if(file != NULL)
			fclose(file);

		throw;
	}
}

/***************************************************************************************************
****************************************************************************************************/
void DibSection::saveToBuffer(void **bufferOut, unsigned *numBytes) const {
	if(!m_pixels) {
		DIB_THROW("DIB has no pixels - it has not yet been created or loaded");
	}

	DIB_ASSERT(bufferOut);

	BYTE *pFileBits = NULL;
	FILE *file = NULL;
	HDC hdc = NULL;

	unsigned numDataBytes = m_stride * m_height;
	unsigned totalSize = sizeof(m_bmfh) + sizeof(m_bmih) + numDataBytes;

	char *buffer = (char *)malloc(totalSize);
	if(!buffer) {
		DIB_THROW("Memory fail");
	}

	memcpy(buffer, &m_bmfh, sizeof(m_bmfh));
	memcpy(buffer + sizeof(m_bmfh), &m_bmih, sizeof(m_bmih));
	memcpy(buffer + sizeof(m_bmfh) + sizeof(m_bmih),
		m_pixels, numDataBytes);

	*bufferOut = buffer;
	if(numBytes) {
		*numBytes = totalSize;
	}
}

