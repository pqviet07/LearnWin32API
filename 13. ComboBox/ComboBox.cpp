#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hinst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wc = { 0 };
    wc.lpszClassName = TEXT("Application");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    g_hinst = hInstance;

    RegisterClass(&wc);
    hwnd = CreateWindow(wc.lpszClassName, TEXT("Combo Box"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 270, 170, 0, 0, hInstance, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console window

    while(GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndCombo, hwndStatic;
    const TCHAR* items[] = { TEXT("C/C++"), TEXT("C#"), TEXT("Java"), TEXT("Python") };
    int i;
    LRESULT sel = 0;

    switch(msg)
    {
    case WM_CREATE:
        hwndCombo = CreateWindow(TEXT("combobox"), NULL,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
            10, 10, 120, 110, hwnd, NULL, g_hinst, NULL);

        CreateWindow(TEXT("button"), TEXT("Drop down"),
            WS_CHILD | WS_VISIBLE,
            150, 10, 90, 25, hwnd, (HMENU)1, g_hinst, NULL);

        hwndStatic = CreateWindow(TEXT("static"), TEXT(""),
            WS_CHILD | WS_VISIBLE,
            150, 80, 90, 25, hwnd, NULL, g_hinst, NULL);

        for(i = 0; i < 4; i++)
        {
            SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)items[i]);
        }
        break;
    case WM_COMMAND:
        if(HIWORD(wParam) == BN_CLICKED)
        {
            SendMessage(hwndCombo, CB_SHOWDROPDOWN, (WPARAM)TRUE, 0);
        }
        if(HIWORD(wParam) == CBN_SELCHANGE)
        {
            sel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
            SetWindowText(hwndStatic, items[sel]);
            SetFocus(hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}