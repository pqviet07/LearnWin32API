#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG  msg;
    WNDCLASSW wc = { 0 };
    wc.lpszClassName = L"Static Control";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Introduce myself", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 420, 270, 0, 0, hInstance, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console window
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static const wchar_t* lyrics = L"Hi all.\n\
                                My name's Viet\n\
                                I come from Thai Nguyen City\n\
                                I graduated from HN University of Technology \n\
                                I came to Fsoft";
    switch(msg)
    {
    case WM_CREATE:
        CreateWindowW(L"STATIC", lyrics, WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 20, 400, 230, hwnd, (HMENU)1, NULL, NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}