// ################################################################## //
// ##							IList							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Jul 15 - AIE			   ## //
// ################################################################## //
#pragma once
#ifndef BPD_INITIALIZER_LIST_
#define BPD_INITIALIZER_LIST_
#include "Core/bpddef.h"
#include "Exception.h"

BPD_BEGIN
/* ---- LIST ---- */
template<class _Type> class IList {
public:
	typedef _Type value_type;
	typedef const _Type* const_ptr;
	typedef _Type* value_ptr;
public:
template<size_type N>
	constexpr IList( const value_type(&a)[N] )
		: p(a), size(N) {
	} // Create Initializer List with params
	constexpr IList()
		: p(nullptr), size(0) {
	} // Create Empty Initializer List

	// Overloaded operator []
	constexpr value_type operator[](size_type n)
		const; 
	// Get start of sequence
	constexpr const_ptr begin()
		const BPD_NOEXCEPT;
	// Get end of sequence
	constexpr const_ptr end()
		const BPD_NOEXCEPT;
	// Get the size of the sequence
	constexpr size_type length()
		const BPD_NOEXCEPT;
	// Get the data in the IList
	constexpr const_ptr data()
		const BPD_NOEXCEPT;
	// Sets the agr to the data
	void editable(value_type * a)
		BPD_NOEXCEPT;
	// Returns the data in an non const format
	value_type * editable()
		BPD_NOEXCEPT;
private:
	const_ptr p;
	size_type size;
};
typedef IList<char> const_string;

template <class _Type> inline
constexpr const _Type *begin(IList<_Type> _Ilist){
	return (_list.begin());
}; // Get start of sequence

template <class _Type> inline
constexpr const _Type *end(IList<_Type> _list){
	return (_list.end());
}; // Get end of sequence

template <class _Type> inline
constexpr const int length(IList<_Type> _Ilist){
	return (_list.length());
}; // Get end of sequence

template <class _Type> inline
constexpr const _Type *data(IList<_Type> _Ilist){
	return (_list.data());
}; // Get the data in the IList
template<class _Type> inline
_Type * editable(IList<_Type> _list){
	return _list.editable();
} // Get the data and return as non const
typedef IList<char> const_string;
BPD_END
#endif // !BPD_INITIALIZER_LIST_