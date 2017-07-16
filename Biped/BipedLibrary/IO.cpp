#include "Biped\bpd\IO.h"

BPD_BEGIN
IO::IO(String Path) : m_path(Path){}
IO::IO(){ m_path = ""; }
IO::~IO(){ if(m_file != NULL) fclose(m_file); }
void IO::SetPath(String Path){ m_path = Path; }

void IO::Open(Mode mode){
	if(m_path.data == "") BPD_EXCEPTION("Path is null");

	switch(mode){
	case bpd::IO::ReadOnly:
		m_file = fopen(m_path.data, "rb");
		break;
	case bpd::IO::ReadWrite:
		m_file = fopen(m_path.data, "rb");
		if(m_file == NULL){
			fclose(m_file);
			m_file = fopen(m_path.data, "wb");
		} fclose(m_file);
		m_file = fopen(m_path.data, "r+b");
		break;
	case bpd::IO::ReadOnlyBinary:
		m_file = fopen(m_path.data, "r");
		break;
	case bpd::IO::ReadWriteBinary:
		m_file = fopen(m_path.data, "r");
		if(m_file == NULL){
			fclose(m_file);
			m_file = fopen(m_path.data, "w");
		} fclose(m_file);
		m_file = fopen(m_path.data, "r+");
		break;
	case bpd::IO::Empty:
		m_file = fopen(m_path.data, "wb");
		break;
	default:
		m_file = fopen(m_path.data, "rb");
		if(m_file == NULL){
			fclose(m_file);
			m_file = fopen(m_path.data, "wb");
		} fclose(m_file);
		m_file = fopen(m_path.data, "r+b");
		break;
	} if(m_file == NULL) BPD_EXCEPTION("Open error");
}

template<typename T> void IO::Write(T data){
	if(fseek(m_file, 0, SEEK_END) != 0) BPD_EXCEPTION("Seek error");
	if(fwrite((char*)&data, sizeof(T), 1, m_file) != 1) BPD_EXCEPTION("Write error");
}
template<typename T> void IO::Write(T data, int Offset){
	if(fseek(m_file, Offset, SEEK_SET) != 0) BPD_EXCEPTION("Seek error");
	if(fwrite((char*)&data, sizeof(T), 1, m_file) != 1) BPD_EXCEPTION("Write error");
}
template<> void IO::Write<String>(String data, int Offset){
	if(fseek(m_file, Offset, SEEK_SET) != 0) BPD_EXCEPTION("Seek error");
	int dataSize = data.length();
	if(fwrite((char*)&dataSize, sizeof(dataSize), 1, m_file) != 1) BPD_EXCEPTION("Write error");
	if(dataSize != 0){
		if(fwrite(data.data, dataSize, 1, m_file) != 1) BPD_EXCEPTION("Write error");
	}
}
template<typename T> void IO::Read(T& data, int Offset){
	if(fseek(m_file, Offset, SEEK_SET) != 0) BPD_EXCEPTION("Seek error");
	if(fread((char*)&data, sizeof(T), 1, m_file) != 1) BPD_EXCEPTION("Read error");
}
template<> void IO::Read<String>(String& data, int Offset){
	if(fseek(m_file, Offset, SEEK_SET) != 0) BPD_EXCEPTION("Seek error");
	int dataSize = 0;
	if(fread((char*)&dataSize, sizeof(dataSize), 1, m_file) != 1) BPD_EXCEPTION("Read error");
	if(dataSize == 0){
		data = "";
	} else{
		char* buffer = new char[dataSize + 1];
		if(fread(buffer, dataSize, 1, m_file) != 1) BPD_EXCEPTION("Read error");
		buffer[dataSize] = 0;
		data = buffer;
		delete[] buffer;
	}
}
int IO::Size(){
	if(m_path.data == "") BPD_EXCEPTION("Path is null");
	m_file = fopen(m_path.data, "rb");
	if(m_file == NULL) BPD_EXCEPTION("Open error");
	int cur = ftell(m_file);
	if(fseek(m_file, 0, SEEK_END) != 0) BPD_EXCEPTION("Seek error");
	int end = ftell(m_file);
	if(fseek(m_file, 0, cur) != 0) BPD_EXCEPTION("Seek error");
	return end;
}
void IO::Close(){ fclose(m_file); }
BPD_END