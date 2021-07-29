#include <windows.h>

#define ID_BLUE 1
#define ID_YELLOW 2
#define ID_ORANGE 3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hinst;
COLORREF g_color;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG  msg;
    WNDCLASS wc = { 0 };
    wc.lpszClassName = TEXT("GroupBox");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    g_hinst = hInstance;
    RegisterClass(&wc);
    hwnd = CreateWindow(wc.lpszClassName, TEXT("GroupBox"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 170, 0, 0, hInstance, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console window
    while(GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hBrush, holdBrush;
    HPEN hPen, holdPen;

    switch(msg)
    {
    case WM_CREATE:
        CreateWindow(TEXT("button"), TEXT("Choose Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 120, 110, hwnd, (HMENU)0, g_hinst, NULL);

        CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 30, 100, 30, hwnd, (HMENU)ID_BLUE, g_hinst, NULL);

        CreateWindow(TEXT("button"), TEXT("Yellow"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 55, 100, 30, hwnd, (HMENU)ID_YELLOW, g_hinst, NULL);

        CreateWindow(TEXT("button"), TEXT("Orange"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 80, 100, 30, hwnd, (HMENU)ID_ORANGE, g_hinst, NULL);
        break;
    case WM_COMMAND:
        if(HIWORD(wParam) == BN_CLICKED)
        {
            switch(LOWORD(wParam))
            {
            case ID_BLUE:
                g_color = RGB(0, 76, 255);
                break;
            case ID_YELLOW:
                g_color = RGB(255, 255, 0);
                break;
            case ID_ORANGE:
                g_color = RGB(255, 123, 0);
                break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(g_color);
        hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
        holdPen = (HPEN)SelectObject(hdc, hPen);
        holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Rectangle(hdc, 160, 20, 260, 120);
        SelectObject(hdc, holdBrush);
        SelectObject(hdc, holdPen);
        DeleteObject(hPen);
        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}