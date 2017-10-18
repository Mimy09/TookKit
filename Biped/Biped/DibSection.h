#pragma once

#include <stdio.h>
#include <windows.h>



//! An RGB color used by class DibSection.
struct DibColor {
	DibColor() : r(0), g(0), b(0) {};
	DibColor(BYTE r_, BYTE g_, BYTE b_) : r(r_), g(g_), b(b_) {};
	BYTE b, g, r;
};

//! Wrapper around the Win32 DibSection. A DibSection is a 24-bit (i.e. RGB) bitmap that allows
//! direct manipulation of its pixels, including loading and saving to disk file.
class DibSection {
public:

	//---------------------------------
	// Creation
	//---------------------------------
	// After construction of a DibSection object, at least one of the functions
	// from this section must be called to load the DibSection with pixels 
	// (empty or otherwise). No other member functions can be called on a 
	// DibSection until this has been done.

	//! Constructs and empty DibSection
	DibSection();

	//! Destroys the DibSection and any internal memory.
	~DibSection();

	//! Creates an empty DIB to a specified width and height (in pixels).
	//! Optionally, a color can be supplied that will be used to fill the DIB
	//! pixels.
	void create(HWND hwnd, unsigned width, unsigned height,
		const DibColor& defaultColor = DibColor(0, 0, 0));

	//! Load the dib from a bitmap. The file must be in BMP (only 24-bit RGB). 
	void load(HWND hwnd, const char *fileName);

	//! Load the dib from a memory buffer that contains the exact image of the 
	//! dib in bitmap (i.e. BMP) format (i.e. as if read directly from a bitmap).
	void load(HWND hwnd, void *buffer);

	//! Load the dib from the current position of a specified file that contains
	//! the exact image of the dib in bitmap (i.e. BMP) format (i.e. as if read 
	//! directly from a BMP file).
	void load(HWND hwnd, FILE *file, unsigned numBytes);

	//! Load a specified area from a bitmap into the dib. This function does NOT
	//! load the source bitmap entirely into memory but only loads the specified
	//! area. This can be useful when handling bitmaps larger than available memory.
	//! It is allowable for the specified area to overlap the bounds of the 
	//! bitmap (including negative x and/or y). In such cases, the overlapping 
	//! areas will be filled with the specified default color. The function only
	//! supports BMP files.
	void load(HWND hwnd, const char *fileName,
		int x, int y, int width, int height,
		const DibColor& defaultColor = DibColor(0, 0, 0));

	//! DibSections have full copy semantics (provided by the copy constructor 
	//! and assignment operator). Note that the DibSection that serves as the 
	//! R-Value MUST contain pixels (i.e. created or loaded), however, the 
	//! L-Value DibSection may or may not contain pixels.
	const DibSection& operator =(const DibSection& other);
	DibSection(const DibSection& other);


	//---------------------------------
	// Operations
	//---------------------------------

	//! Fill the entire DIB with a specified color.
	void fill(const DibColor & color);

	enum class GradientTypes { Horizontal, Vertical, Radial };
	void fillGradient(GradientTypes, const DibColor & startColor, const DibColor & endColor);

	//! Fill a specified area of the DIB with a specified color. The specified
	//! area may overlap the edges of the DIB in any fashion - the function will
	//! clip the fill to the bounds of the DIB.
	void fill(const DibColor& color, int x, int y, unsigned width, unsigned height);

	//! Add a specified area from another DibSection into this DibSection. The 
	//! area of the DibSection will be expanded where necessary to include the 
	//! complete area from the other DibSection. New areas not occupied by pixels 
	//! from either DibSection will be filled with the supplied default color. 
	//! The area from the other DibSection will be placed "on top of" the area 
	//! within this DibSection. WARNING - this function will require enough 
	//! memory to hold two copies of this DibSection plus the other DibSection.
	void add(
		HWND hwnd,
		int xDest, int yDest,            //!< Position within this DibSection at 
										 //!< which the added area is to be placed.
		const DibSection& other,         //!< Other DibSection to add
		int xOther, int yOther,          //!< Origin of the area in the other DibSection
		int widthOther, int heightOther, //!< Size of the area in the other DibSection
		const DibColor& defaultColor = DibColor(0, 0, 0));  //!< Default color to fill new areas not
														  //!< occupied by pixels.

	//! Save the DIB to a new bitmap file (in 24-bit format).
	void save(const char *fileName) const;

	//! Save the DIB to a memory buffer. The function will allocate the buffer
	//! from the heap (via malloc) and fill it with the exact contents of a
	//! file in 24-bit bitmap format. The caller will be responsible for freeing
	//! the buffer. If non-zero, "numBytes" will return the total size of the buffer.
	void saveToBuffer(void **buffer, unsigned *numBytes = 0) const;

	//! HDC to use for blting
	HDC m_hdc;

	//! Array of pixels. This array will be NULL until either "create" or "load"
	//! is called.
	DibColor *m_pixels;

	//! Returns the number of pixels in the dib, i.e. the number of DibColor
	//! structures.
	unsigned getNumPixels();

	//! Points to a specified pixel. Can only be called after dib has been
	//! created or loaded, otherwise an exception will occur.
	inline DibColor *getPixel(unsigned x, unsigned y) const {
		if(m_bottomUp)
			return (DibColor *)((char *)m_pixels + ((m_height - y - 1) * m_stride + x * 3));
		else
			return (DibColor *)((char *)m_pixels + (y * m_stride + x * 3));
	}

	//! Returns true if the DIB is stored in bottom-up format, false if the DIB
	//! is stored in top-down format.
	bool isBottomUp() { return m_bottomUp; };

	//! Returns the width and height of the DIB (in pixels)
	WORD m_width, m_height;

	//! Returns the stride of the DIB. This represents the no. of BYTES that each
	//! row takes up in memory (NOT necessarily the no. of pixels multiplied by 3).
	//! Usually, each row is aligned on 4-bute boundaries.
	WORD m_stride;

	//! Read information about the specified bitmap without actually loading
	//! the entire file into memory. This is the only function that can be 
	//! called before the DibSection has been created or loaded. The function
	//! supports BMP format only.
	struct Info {
		unsigned width,     // Width and height (pixels)
			height;
		bool     bottomUp;  // true = bottom up, false = top down
		unsigned bitCount;  // Bits per pixel
	};
	void getInfo(const char *fileName, Info *info) const;


private:

	HBITMAP m_hBitmap;
	HBITMAP m_prevBitmap;
	BITMAPFILEHEADER m_bmfh;
	BITMAPINFOHEADER m_bmih;
	bool m_bottomUp;
	unsigned m_bpp;

	void destroy();
	void getInfo_BMP(const char *fileName, Info *info) const;
	void loadFile_BMP(HWND hwnd, const char *fileName);
};


