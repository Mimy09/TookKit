#pragma once
#include <stdlib.h>
#include "tkException.h"

namespace tk {
	class IO {
	public:
		static enum Mode { ReadOnly, ReadWrite, Empty };

		IO(String Path) : m_path(Path) {}
		IO() { m_path = nullptr; }
		~IO() { if (m_file != NULL) fclose(m_file); }
		void SetPath(String Path) { m_path = Path; }

		void Open(Mode mode) {
			if (m_path.data == nullptr) TK_EXCEPTION("Path is null");

			switch (mode) {
			case tk::IO::ReadOnly:
				m_file = fopen(m_path.data, "rb");
				break;
			case tk::IO::ReadWrite:
				m_file = fopen(m_path.data, "rb");
				if (m_file == NULL) {
					fclose(m_file);
					m_file = fopen(m_path.data, "wb");
				} fclose(m_file);
				m_file = fopen(m_path.data, "r+b");
				break;
			case tk::IO::Empty:
				m_file = fopen(m_path.data, "wb");
				break;
			default:
				m_file = fopen(m_path.data, "rb");
				if (m_file == NULL) {
					fclose(m_file);
					m_file = fopen(m_path.data, "wb");
				} fclose(m_file);
				m_file = fopen(m_path.data, "r+b");
				break;
			} if (m_file == NULL) TK_EXCEPTION("Open error");
		}

		template<typename T> void Write(T data) {
			if (fseek(m_file, 0, SEEK_END) != 0) TK_EXCEPTION("Seek error");
			if (fwrite((char*)&data, sizeof(T), 1, m_file) != 1) TK_EXCEPTION("Write error");
		}
		template<typename T> void Write(T data, int Offset) {
			if (fseek(m_file, Offset, SEEK_SET) != 0) TK_EXCEPTION("Seek error");
			if (fwrite((char*)&data, sizeof(T), 1, m_file) != 1) TK_EXCEPTION("Write error");
		}
		template<> void Write<String>(String data, int Offset) {
			if (fseek(m_file, Offset, SEEK_SET) != 0) TK_EXCEPTION("Seek error");
			int dataSize = data.length();
			if (fwrite((char*)&dataSize, sizeof(dataSize), 1, m_file) != 1) TK_EXCEPTION("Write error");
			if (dataSize != 0) {
				if (fwrite(data.data, dataSize, 1, m_file) != 1) TK_EXCEPTION("Write error");
			}
		}
		template<typename T> void Read(T& data, int Offset) {
			if (fseek(m_file, Offset, SEEK_SET) != 0) TK_EXCEPTION("Seek error");
			if (fread((char*)&data, sizeof(T), 1, m_file) != 1) TK_EXCEPTION("Raed error");
		}
		template<> void Read<String>(String& data, int Offset) {
			if (fseek(m_file, Offset, SEEK_SET) != 0) TK_EXCEPTION("Seek error");
			int dataSize = 0;
			if (fread((char*)&dataSize, sizeof(dataSize), 1, m_file) != 1) TK_EXCEPTION("Raed error");
			if (dataSize == 0) {
				data = "";
			}
			else {
				char* buffer = new char[dataSize + 1];
				if (fread(buffer, dataSize, 1, m_file) != 1) TK_EXCEPTION("Raed error");
				buffer[dataSize] = 0;
				data = buffer;
				delete[] buffer;
			}
		}
		int Size() {
			if (m_path.data == nullptr) TK_EXCEPTION("Path is null");
			m_file = fopen(m_path.data, "rb");
			if (m_file == NULL) TK_EXCEPTION("Open error");
			int cur = ftell(m_file);
			if (fseek(m_file, 0, SEEK_END) != 0) TK_EXCEPTION("Seek error");
			int end = ftell(m_file);
			if (fseek(m_file, 0, cur) != 0) TK_EXCEPTION("Seek error");
			return end;
		}
		void Close() { fclose(m_file); }
	private:
		String m_path;
		FILE* m_file;
	};
}