// ################################################################## //
// ##						INPUT / OUTPUT						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "Core\bpddef.h"
#include <stdlib.h>
#include "Exception.h"

BPD_BEGIN
class IO {
public:
		
	enum Mode { ReadOnlyBinary, ReadWriteBinary, ReadWrite, ReadOnly, Empty };

	IO(String Path);
	IO();
	~IO();
	void SetPath(String Path);

	void Open(Mode mode);

	template<typename T> void Write(T data);
	template<typename T> void Write(T data, int Offset);
	template<> void Write<String>(String data, int Offset);
	template<typename T> void Read(T& data, int Offset);
	template<> void Read<String>(String& data, int Offset);
	int Size();
	void Close();
private:
	String m_path;
	FILE* m_file;
};
BPD_END