// ################################################################## //
// ##							Biped Macro						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#pragma once

#define _BPD_SAFE_ARRAY_DELETE(pObj) \
{ if(pObj != nullptr) {delete[] pObj; pObj = nullptr;}}
#define _BPD_SAFE_DELETE(pObj) \
{ if(pObj != nullptr) {delete pObj; pObj = nullptr;}}
#define _BPD_DEF_HANDLE(name) typedef struct name##_bpd* name

#define _BPD_BEGIN namespace bpd {
#define _BPD_END }

#define _BPD_NOEXCEPT noexcept
#define _BPD_CONST_FUN constexpr

#define BPD_SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define BPD_SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)

#define BPD_BEGIN_DRAW	\
bpdApplication::Draw(hdc);

#define BPD_UPDATE_WINDOW				\
InvalidateRect(*m_hwnd, NULL, true);	\
UpdateWindow(*m_hwnd);

// ------------ Results --------------------
enum class BPD_RESULT { SUCCESS, FAILURE };