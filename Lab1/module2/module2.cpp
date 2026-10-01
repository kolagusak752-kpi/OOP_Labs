#include "module2.h"
#include "Resource.h"
static INT_PTR CALLBACK OnMsgDialogNext(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		switch (wmId) {
		case IDC_BUTTON_NEXT: {
			EndDialog(hDlg, IDC_BUTTON_NEXT);
			return (INT_PTR)TRUE;
		}
		case IDC_BUTTON_CANCEL1: {
			EndDialog(hDlg, IDC_BUTTON_CANCEL1);
			return (INT_PTR)TRUE;
		}
		}
	}
	}
}
int ShowDialogNext(HINSTANCE hInst, HWND hParent) {
	int result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hParent, OnMsgDialogNext);
		
	return result;
}