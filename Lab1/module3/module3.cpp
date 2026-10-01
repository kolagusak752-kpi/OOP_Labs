#include "module3.h"
#include "Resource.h"
static INT_PTR CALLBACK OnMsgDialogBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		switch (wmId) {
		case IDC_BUTTON_BACK: {
			EndDialog(hDlg, IDC_BUTTON_BACK);
			return (INT_PTR)TRUE;
		}
		case IDC_BUTTON_CANCEL2: {
			EndDialog(hDlg, IDC_BUTTON_CANCEL2);
			return (INT_PTR)TRUE;
		}
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}
int ShowDialogBack(HINSTANCE hInst, HWND hParent) {
	int result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hParent, OnMsgDialogBack);
	return result;
}