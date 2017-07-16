#pragma once
#ifndef BPD_DEF_
#define BPD_DEF_

#define BPD_BEGIN namespace bpd {
#define BPD_END }

#define BPD_SAFE_ARRAY_DELETE(pObj) \
{ if(pObj != nullptr) {delete[] pObj; pObj = nullptr;}}
#define BPD_SAFE_DELETE(pObj) \
{ if(pObj != nullptr) {delete pObj; pObj = nullptr;}}
BPD_BEGIN
	typedef const unsigned int size_type;
BPD_END
BPD_BEGIN
template <bpd::size_type N>
	struct type_of_size{ typedef char type[N]; };
template <typename _Type, bpd::size_type Size>
	typename type_of_size<Size>::type& bpdsoah(_Type(&)[Size]){
	} // Size Of Array Helper
#define BPD_SIZEOF(pArray) sizeof(bpd::bpdsoah(pArray))
BPD_END

#define BPD_TEMPLATE_INCLUE(class_) template class class_
#define BPD_TEMPLATE_CLASS template <typename _Type>

#define BPD_NOEXCEPT noexcept
#endif // !BPD_DEF_