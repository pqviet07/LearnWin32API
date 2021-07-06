#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Pixels";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Pixels", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 250, 150, NULL, NULL, hInstance, NULL);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_PAINT:
        DrawPixels(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void DrawPixels(HWND hwnd)
{
    PAINTSTRUCT ps;
    RECT r;

    HDC hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &r);
    for(int i = 0; i < 1000; i++)
    {
        int x = (rand() % r.right - r.left);
        int y = (rand() % r.bottom - r.top);
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }
    EndPaint(hwnd, &ps);
}