#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Text";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"GDI-Text",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 390, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console window
    while(GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    DWORD color;
    HFONT hFont, holdFont;

    static wchar_t ver1[] = L"Hello everybody,";
    static wchar_t ver2[] = L"This is forum for developer";
    static wchar_t ver3[] = L"Sharing everything";

    switch(msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        color = GetSysColor(COLOR_BTNFACE);
        SetBkColor(hdc, color);
        hFont = CreateFontW(15, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, L"Georgia");
        holdFont = (HFONT)SelectObject(hdc, hFont);

        TextOutW(hdc, 50, 20, ver1, lstrlenW(ver1));
        TextOutW(hdc, 50, 40, ver2, lstrlenW(ver2));
        TextOutW(hdc, 50, 60, ver3, lstrlenW(ver3));

        SelectObject(hdc, holdFont);
        DeleteObject(hFont);

        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}