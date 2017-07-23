#pragma once
#ifndef BPD_LIB_
	#define BPD_LIB_
	#ifndef BPD_NO_STD
		#include "../Exception.h"
		#include "../HashTable.h"
		#include "../IO.h"
		#include "../LinkedList.h"
		#include "../IList.h"
		#include "../ObjectPool.h"
		#include "../String.h"
		#include "../Timer.h"
		#include "../Tree.h"
	#else
		#include "bpddef.h"
	#endif // BPD_NO_STD
#endif // !BPD_LIB_