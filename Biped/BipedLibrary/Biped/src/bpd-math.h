// ################################################################## //
// ##							IList							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Oct 18 - AIE			   ## //
// ################################################################## //
#pragma once
namespace Maths {
	template<class _Type> struct _X_ {};
	template<class _Type> struct _Y_ {};
	template<class _Type> struct _Z_ {};
	template<class _Type> struct _W_ {};
	/////////////////////////////////////////////////////
	// VECTORS
	template<class _Type>
	class Vector {
	public:
		typedef _Type type_t;
		typedef const _Type* type_tcp;
		typedef _Type* type_tp;
	public:

		template<size_t _Size> Vector(const type_t(&a)[_Size])
			_BPD_NOEXCEPT : pValConst(a), size(_Size) {
			pVal = new type_t[size];
			for(u_int i = 0; i < size; i++) pVal[i] = pValConst[i];
		}

		// Overloaded operator []
		_BPD_CONST_FUN type_t operator[](size_t n)
			const _BPD_NOEXCEPT {
			return n < size ? pVal[n] : -1;
		}
		// Gets the size of the Vectors
		_BPD_CONST_FUN size_t length()
			const _BPD_NOEXCEPT {
			return (size);
		}

		template<typename t> void operator()() {}
		template<> type_t operator()<_X_<type_t> _Val>() { return pVal[0]; }
		template<> type_t operator()<_Y_<type_t> _Val>() { return pVal[1]; }
		template<> type_t operator()<_Z_<type_t> _Val>() { return pVal[2]; }
		template<> type_t operator()<_W_<type_t> _Val>() { return pVal[3]; }

		~Vector() {}

	private:
		type_tcp pValConst;
		type_tp pVal;
		size_t size;
	};
}