#include "tkString.h"

namespace tk {
	// -------------------------------------------------------------------------------------------------- //
	// ------------------------------------------ STRING_START ------------------------------------------ //

	// ---- COPY ---- //
	void String::strCopy(char** dest, const char* str) {
		SAFE_ARRAY_DELETE(*dest);
		*dest = new char[length(str) + 1];
		for (int i = 0; i < length(str) + 1; i++) {
			(*dest)[i] = str[i];
		}

	}
	void String::strCopy(char* dest, const char* str) {
		SAFE_ARRAY_DELETE(dest);
		dest = new char[length(str) + 1];
		for (int i = 0; i < length(str) + 1; i++) {
			dest[i] = str[i];
		}
	}

	void String::strCopy(char** dest, const char str) {
		SAFE_ARRAY_DELETE(*dest);
		*dest = new char[3];
		(*dest)[0] = str;
		(*dest)[1] = '\0';
	}

	// ---- ADD ---- //
	void String::strAdd(char** dest, const char* str) {
		char* strTemp = new char[2];
		strCopy(&strTemp, *dest);
		SAFE_ARRAY_DELETE(*dest);
		*dest = new char[length(strTemp) + length(str) + 1];
		for (int i = 0; i < length(strTemp); i++) {
			(*dest)[i] = strTemp[i];
		}
		for (int i = length(strTemp); i < length(strTemp) + length(str) + 1; i++) {
			(*dest)[i] = str[i - length(strTemp)];
		}
		SAFE_ARRAY_DELETE(strTemp);
	}
	String String::strAddS(const char* dest, const char* str) {
		String stringData;
		stringData.data = new char[length(dest) + length(str) + 1];
		for (int i = 0; i < length(dest); i++) {
			stringData.data[i] = dest[i];
		}
		for (int i = length(dest); i < length(dest) + length(str) + 1; i++) {
			stringData.data[i] = str[i - length(dest)];
		}
		return stringData;
	}

	// ---- LENGTH ---- //
	int String::length(const char* str) {
		int i = 0;
		while (true) {
			if (str[i] == '\0') break;
			i++;
		} return i;
	}
	int String::length(const String& str) {
		int i = 0;
		while (true) {
			if (str.data[i] == '\0') break;
			i++;
		} return i;
	}
	int String::length() {
		int i = 0;
		while (true) {
			if (data[i] == '\0') break;
			i++;
		} return i;
	}

	// ---- PRINT ---- //
	void String::print_tk() {
		printf("%s", data);

	}
	void String::println_tk() {
		printf("%s\n", data);
	}

	// ---- operator ---- //
	void String::operator=(const char* str) {
		strCopy(&data, str);
	}
	void String::operator=(const String& other) {
		strCopy(&data, other.data);
	}
	void String::operator=(const int other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%d", other);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	void String::operator=(const float other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", other);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	void String::operator=(const double other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", other);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	void String::operator+=(const char* str) {
		strAdd(&data, str);
	}
	void String::operator+=(const String& other) {
		strAdd(&data, other.data);
	}
	void String::operator+=(const int other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%d", other);
		strAdd(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	void String::operator+=(const float other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", other);
		strAdd(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	void String::operator+=(const double other) {
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", other);
		strAdd(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	String String::operator+(const char* str) {
		return strAddS(data, str);
	}
	String String::operator+(const String& other) {
		return strAddS(data, other.data);
	}

	// ---- CONSTRUCTOR ---- //
	String::String() {
		SAFE_ARRAY_DELETE(data);
	}

	String::String(const String & str) {
		SAFE_ARRAY_DELETE(data);
		strCopy(&data, str.data);
	}
	String::String(const char* str) {
		SAFE_ARRAY_DELETE(data);
		strCopy(&data, str);
	}
	String::String(const char str) {
		strCopy(&data, str);
	}
	String::String(const int value) {
		SAFE_ARRAY_DELETE(data);
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%d", value);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	String::String(const float value) {
		SAFE_ARRAY_DELETE(data);
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", value);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}
	String::String(const double value) {
		SAFE_ARRAY_DELETE(data);
		char* buffer = new char[tk_BIT_LIMIT];
		sprintf(buffer, "%f", value);
		strCopy(&data, buffer);
		SAFE_ARRAY_DELETE(buffer);
	}

	// ---- DECONSTRUCTOR ---- //
	String::~String() {
		SAFE_ARRAY_DELETE(data);
	}

	// ---- TO CHAR ---- //
	char* String::toChar() {
		return data;
	}

	// ---- TO INT ---- //
	int String::toInt() {
		return 0;
	}

	// ---- SPLIT ---- //
	char* String::cSplit(char stopChar, int position) {
		char* tempStr = new char[length(data)];
		char* itrTempStr;
		int charPos = 0;

		if (position == 0) {
			charPos = 0;
		}
		else {
			position--;
			for (; charPos < length(data); charPos++) {
				if (data[charPos] == stopChar) {
					if (position <= 0) {
						charPos++;
						break;
					}
					else {
						position--;
					}
				}
			}
		}
		itrTempStr = tempStr;

		for (int i = charPos; i < length(data) + 1; i++) {
			if (data[i] == stopChar) {
				*itrTempStr = '\0';
				break;
			}
			else {
				*itrTempStr = data[i];
				itrTempStr++;
			}
		}
		return tempStr;
	}

	String String::sSplit(char stopChar, int position) {
		String tempStr;
		tempStr.data = new char[length(data)];

		char* itrTempStr;
		int charPos = 0;

		if (position == 0) {
			charPos = 0;
		}
		else {
			position--;
			for (; charPos < length(data); charPos++) {
				if (data[charPos] == stopChar) {
					if (position <= 0) {
						charPos++;
						break;
					}
					else {
						position--;
					}
				}
			}
		}
		itrTempStr = tempStr.data;

		for (int i = charPos; i < length(data) + 1; i++) {
			if (data[i] == stopChar) {
				*itrTempStr = '\0';
				break;
			}
			else {
				*itrTempStr = data[i];
				itrTempStr++;
			}
		}
		return tempStr;
	}

	// ---- REPLACE ---- //
	void String::replace(char splitChar, char* value) {
		char* tempStr = new char[length(data) + length(value)];

		char* str_first = this->cSplit(splitChar, 0);
		char* str_last = this->cSplit(splitChar, 2);


		for (int i = 0; i < length(str_first); i++) {
			tempStr[i] = str_first[i];
		}
		for (int i = 0; i < length(value); i++) {
			tempStr[i + length(str_first)] = value[i];
		}

		for (int i = 0; i < length(str_last) + 1; i++) {
			tempStr[i + length(str_first) + length(value)] = str_last[i];
		}

		data = tempStr;

		SAFE_ARRAY_DELETE(str_first);
		SAFE_ARRAY_DELETE(str_last);
	}

	void String::replace(char splitChar, String& value) {


		String tempStr;
		tempStr.data = new char[length(data) + length(value)];

		char* str_first = this->cSplit(splitChar, 0);
		char* str_last = this->cSplit(splitChar, 2);

		tempStr = str_first;
		tempStr += value;
		tempStr += str_last;

		data = tempStr.data;

		SAFE_ARRAY_DELETE(str_first);
		SAFE_ARRAY_DELETE(str_last);
	}

	int String::countChar(char character) {
		int k = 0;
		for (int i = 0; i < length(data); i++) {
			if (data[i] == character) k++;
		} return k;
	}
	// ------------------------------------------ STRING_END ------------------------------------------ //
	// ------------------------------------------------------------------------------------------------ //
}