#pragma once
#ifndef BPD_DEF_
#define BPD_DEF_

#define BPD_TEMPLATE_INCLUE(class_) template class class_
#define BPD_TEMPLATE_CLASS template <class T>
#define BPD_TEMPLATE(class_) class_<T>
#define BPD_TEMPLATE_TYPE T

#define BPD_BEGIN namespace bpd {
#define BPD_END }

#define BPD_NULL 0
#define BPD_NULL_P nullptr

#define BPD_SAFE_ARRAY_DELETE(pObj) \
{ if(pObj != nullptr) {delete[] pObj; pObj = nullptr;}}
#define BPD_SAFE_DELETE(pObj) \
{ if(pObj != nullptr) {delete pObj; pObj = nullptr;}}


BPD_BEGIN
	typedef unsigned int size_type;    
template <bpd::size_type N>
	struct type_of_size{ typedef char type[N]; };
template <typename _Type, bpd::size_type Size>
	typename type_of_size<Size>::type& bpdsoah(_Type(&)[Size]){
	} // Size Of Array Helper
BPD_END
#define BPD_SIZEOF_ARRAY(pArray) sizeof(bpd::bpdsoah(pArray))
#define BPD_SIZEOF(v_) sizeof(v_) / sizeof(v_[0])


/* Default Template inclue list */
#define BPD_TEMPLATE_DEFAULT(class_)				\
BPD_TEMPLATE_INCLUE(class_) < unsigned int > ;		\
BPD_TEMPLATE_INCLUE(class_) < unsigned char > ;		\
BPD_TEMPLATE_INCLUE(class_) < char > ;				\
BPD_TEMPLATE_INCLUE(class_) < double > ;			\
BPD_TEMPLATE_INCLUE(class_) < float > ;				\
BPD_TEMPLATE_INCLUE(class_) < short > ;				\
BPD_TEMPLATE_INCLUE(class_) < long > ;				\
BPD_TEMPLATE_INCLUE(class_) < int > ;
#define BPD_TEMPLATE_DEFAULT_P(class_)				\
BPD_TEMPLATE_INCLUE(class_) < unsigned int > ;		\
BPD_TEMPLATE_INCLUE(class_) < unsigned char > ;		\
BPD_TEMPLATE_INCLUE(class_) < char > ;				\
BPD_TEMPLATE_INCLUE(class_) < double > ;			\
BPD_TEMPLATE_INCLUE(class_) < float > ;				\
BPD_TEMPLATE_INCLUE(class_) < short > ;				\
BPD_TEMPLATE_INCLUE(class_) < long > ;				\
BPD_TEMPLATE_INCLUE(class_) < int > ;				\
BPD_TEMPLATE_INCLUE(class_) < unsigned int* > ;		\
BPD_TEMPLATE_INCLUE(class_) < unsigned char* > ;	\
BPD_TEMPLATE_INCLUE(class_) < char* > ;				\
BPD_TEMPLATE_INCLUE(class_) < double* > ;			\
BPD_TEMPLATE_INCLUE(class_) < float* > ;			\
BPD_TEMPLATE_INCLUE(class_) < short* > ;			\
BPD_TEMPLATE_INCLUE(class_) < long* > ;				\
BPD_TEMPLATE_INCLUE(class_) < int* > ;


#define BPD_NOEXCEPT noexcept
#endif // !BPD_DEF_