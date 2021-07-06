#include "windows.h"
#include "commctrl.h"

#define ID_TABCTRL 1
#define EDIT 2
#define BTN_ADD 3
#define BTN_DEL 4
#define BTN_DELALL 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND hTab, hEdit;
HINSTANCE g_hinst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASS wc = { 0 };
    wc.lpszClassName = TEXT("Application");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    g_hinst = hInstance;

    RegisterClass(&wc);
    CreateWindow(wc.lpszClassName, TEXT("Tab Control"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 380, 230, 0, 0, hInstance, 0);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    TCITEM tie;
    TCHAR text[250];
    LRESULT count, id;
    INITCOMMONCONTROLSEX icex;

    switch(msg)
    {
    case WM_CREATE:
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_TAB_CLASSES;
        InitCommonControlsEx(&icex);
        hTab = CreateWindow(WC_TABCONTROL, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 200, 150, hwnd, (HMENU)ID_TABCTRL, g_hinst, NULL);
        hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 20, 100, 25, hwnd, (HMENU)EDIT, g_hinst, NULL);

        CreateWindow("button", "Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 50, 100, 25, hwnd, (HMENU)BTN_ADD, g_hinst, NULL);

        CreateWindow("button", "Del", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 80, 100, 25, hwnd, (HMENU)BTN_DEL, g_hinst, NULL);

        CreateWindow("button", "Delall", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 110, 100, 25, hwnd, (HMENU)BTN_DELALL, g_hinst, NULL);
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case BTN_ADD:
            GetWindowText(hEdit, text, 250);
            if(lstrlen(text) != 0)
            {
                tie.mask = TCIF_TEXT;
                tie.pszText = text;
                count = SendMessage(hTab, TCM_GETITEMCOUNT, 0, 0);
                SendMessage(hTab, TCM_INSERTITEM, count, (LPARAM)(LPTCITEM)&tie);
            }
            break;
        case BTN_DEL:
            id = SendMessage(hTab, TCM_GETCURSEL, 0, 0);
            if(id != -1)
            {
                SendMessage(hTab, TCM_DELETEITEM, 0, id);
            }
            break;
        case BTN_DELALL:
            SendMessage(hTab, TCM_DELETEALLITEMS, 0, 0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return(DefWindowProc(hwnd, msg, wParam, lParam));
}