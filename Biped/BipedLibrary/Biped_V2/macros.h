#ifndef _MACROS_H_
#define _MACROS_H_

#define BPD_DEF_HANDLE(name) typedef struct name##_bpd* name
#define BPD_BEGIN_ namespace bpd {
#define BPD_END_ }
#define BPD_NULL_ 0
#define BPD_NULL_P_ nullptr
#define BPD_NOEXCEPT_ noexcept
#define BPD_CONST_FUN_ constexpr

#define BPD_SAFE_ARRAY_DELETE(pObj) \
{ if(pObj != nullptr) {delete[] pObj; pObj = nullptr;}}
#define BPD_SAFE_DELETE(pObj) \
{ if(pObj != nullptr) {delete pObj; pObj = nullptr;}}

BPD_BEGIN_
typedef unsigned int size_type;
template <bpd::size_type N>
struct type_of_size { typedef char type[N]; };
template <typename _Type, bpd::size_type Size>
typename type_of_size<Size>::type& bpdsoah(_Type(&)[Size]) {
} // Size Of Array Helper
BPD_END_
#define BPD_SIZEOF_ARRAY(pArray) sizeof(bpd::bpdsoah(pArray))
#define BPD_SIZEOF(v_) sizeof(v_) / sizeof(v_[0])

#define BPD_WinMain() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cCmdShow)
#define BPD_WinProc() CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_BtnWinProc() CALLBACK WinProcBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#define BPD_DEFWINPROC DefWindowProc(hwnd, msg, wParam, lParam)
#define BPD_UPDATE_RECT(_hwnd_,_rect_) InvalidateRect(_hwnd_, _rect_, false);UpdateWindow(_hwnd_);

BPD_BEGIN_
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}
BPD_END_

#ifndef BPD_DEBUGMODE
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_DEBUGMODE 
#endif
#endif // !BPD_CONSOLE

#ifndef BPD_ASSERT
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_ASSERT(b) do {if (!(b)){OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define BPD_ASSERT(b)
#endif
#endif // !BPD_ASSERT

#ifndef BPD_CONSOLE
#if defined( DEBUG ) || defined ( _DEBUG )
#define BPD_CONSOLE 1
#else
#define BPD_CONSOLE 0
#endif
#endif // !BPD_CONSOLE

#if defined ( WIN_DIRECT2D )
BPD_BEGIN_
static const bool isDirect2D = true;
BPD_END_
#else
BPD_BEGIN_
static const bool isDirect2D = false;
BPD_END_
#endif
#define BPD_DIRECT2D isDirect2D

#if defined ( WIN_DIRECT2D_FULLSCREEN_WINDOWED )
BPD_BEGIN_
static const bool isFullscreenWindowed = true;
BPD_END_
#else
BPD_BEGIN_
static const bool isFullscreenWindowed = false;
BPD_END_
#endif
#define WIN_DIRECT2D_FULLSCREEN_WINDOWED isFullscreenWindowed

#if defined ( WIN_DIRECT2D_FALLSCREEN_WINDOWED )
BPD_BEGIN_
inline bool isPointInRect(D2D1_POINT_2F point, D2D1_RECT_F rect) {
	if (point.x < (rect.left + (.5*(rect.right - rect.left))) && point.x >(rect.left - (.5*(rect.right - rect.left))) &&
		point.y < (rect.top + (.5*(rect.top - rect.bottom))) && point.y >(rect.top - (.5*(rect.top - rect.bottom))))
		return true;
	else return false;
}
BPD_END_
#endif //  WIN_DIRECT2D_FALLSCREEN_WINDOWED

BPD_BEGIN_
enum bpd_MsgResult {
	MSG_EXIT,
	MSG_UPDATE,
	MSG_DISPATCH
};
enum bpd_Result {
	SUCCESS,
	FAILURE
};
BPD_END_

#endif // !_MACROS_H_