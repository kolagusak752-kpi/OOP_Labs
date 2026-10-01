#include "module1.h"
#include "Resource.h"
static INT_PTR CALLBACK OnMsgDialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
    {
        SetWindowLongPtr(hDlg, DWLP_USER, lParam);
        HWND Slider = GetDlgItem(hDlg, IDC_SLIDER1);
        SetScrollRange(Slider, SB_CTL, 0, 100, TRUE);
        return (INT_PTR)TRUE;
    }
    case WM_HSCROLL:
    {
        int action = LOWORD(wParam);
        if (action == SB_THUMBTRACK) {
            int scrollPos = HIWORD(wParam);
            int* scrollPos_ptr = (int*)GetWindowLongPtr(hDlg, DWLP_USER);
            *scrollPos_ptr = scrollPos;
            HWND Slider = (HWND)lParam;
            SetScrollPos(Slider, SB_CTL, scrollPos, TRUE);
        }
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDC_BUTTON_YES: {
            EndDialog(hDlg, IDC_BUTTON_YES);
            return (INT_PTR)TRUE;
        }
        case IDC_BUTTON_NO:
        case IDCANCEL:
            EndDialog(hDlg, IDC_BUTTON_NO);
            return (INT_PTR)TRUE;
        }
         break;
    }
   
    }
    return (INT_PTR)FALSE;
}
int ShowSliderDialog(HINSTANCE hInst, HWND hParent) {
    int result = NO_VALUE_SELECTED;
     int endCommand = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hParent, OnMsgDialog1, (LPARAM)&result);
     if (endCommand == IDC_BUTTON_NO) {
         result = NO_VALUE_SELECTED;
     }
     return result;
}