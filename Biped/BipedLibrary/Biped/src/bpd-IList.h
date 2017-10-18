// ################################################################## //
// ##							IList							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Jul 15 - AIE			   ## //
// ################################################################## //
#pragma once

_BPD_BEGIN
namespace containers {
/* ---- LIST ---- */
template<class _Type> class IList {
public:
	typedef _Type value_type;
	typedef const _Type* const_ptr;
	typedef _Type* value_ptr;
public:
	template<size_t N>
	_BPD_CONST_FUN IList(const value_type(&a)[N])
		: p(a), size(N) {
	} // Create Initializer List with params
	_BPD_CONST_FUN IList()
		: p(nullptr), size(0) {
	} // Create Empty Initializer List

	// Overloaded operator []
	_BPD_CONST_FUN value_type operator[](size_t n)
		const {
		return n < size ? p[n] : -1;
	}
	// Get start of sequence
	_BPD_CONST_FUN const_ptr begin()
		const _BPD_NOEXCEPT {
		return (&p[0]);
	}
	// Get end of sequence
	_BPD_CONST_FUN const_ptr end()
		const _BPD_NOEXCEPT {
		return (&p[size]);
	}
	// Get the size of the sequence
	_BPD_CONST_FUN size_t length()
		const _BPD_NOEXCEPT {
		return (size);
	}
	// Get the data in the IList
	_BPD_CONST_FUN const_ptr data()
		const _BPD_NOEXCEPT {
		return (p);
	}
	// Sets the agr to the data
	void editable(value_type * a)
		_BPD_NOEXCEPT {
		_BPD_SAFE_DELETE(a);
		a = new value_type[size];
		for(u_int i = 0; i < size; i++) a[i] = p[i];
	}
	// Returns the data in an non const format
	value_type * editable()
		_BPD_NOEXCEPT {
		value_type * temp = new value_type[size];
		for(u_int i = 0; i < size; i++) temp[i] = p[i];
		return temp;
	}
	// Operator ==
	bool operator==(value_type* other) {
		if (strlen(other)+1 != size) return false;
		size_t i = 0; for (; i < size; i++) {
			if (p[i] != other[i]) break;
		} if (i == size) {
			return true;
		} return false;
	}
private:
	const_ptr p;
	size_t size;
};

template <class _Type> inline
	constexpr const _Type *begin(IList<_Type> _Ilist) {
	return (_list.begin());
}; // Get start of sequence

template <class _Type> inline
	constexpr const _Type *end(IList<_Type> _list) {
	return (_list.end());
}; // Get end of sequence

template <class _Type> inline
	constexpr const int length(IList<_Type> _Ilist) {
	return (_list.length());
}; // Get end of sequence

template <class _Type> inline
	constexpr const _Type *data(IList<_Type> _Ilist) {
	return (_list.data());
}; // Get the data in the IList
typedef IList<char> const_string;
}
_BPD_END
