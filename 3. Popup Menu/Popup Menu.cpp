#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

    LPSTR lpCmdLine, int nCmdShow)
{
    MSG  msg;
    WNDCLASS wc = { 0 };
    wc.lpszClassName = TEXT("Application");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClass(&wc);

    CreateWindow(wc.lpszClassName, TEXT("Popup Menu"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 200, 150, 0, 0, hInstance, 0);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HMENU hMenu;
    POINT point;

    switch(msg)
    {
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDM_FILE_NEW:
        case IDM_FILE_OPEN:
            Beep(50, 100);
            break;
        case IDM_FILE_QUIT:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }
        break;

    case WM_RBUTTONUP:
        point.x = LOWORD(lParam);
        point.y = HIWORD(lParam);
        hMenu = CreatePopupMenu();
        ClientToScreen(hwnd, &point);

        AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("&New"));
        AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, TEXT("&Open"));
        AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
        AppendMenu(hMenu, MF_STRING, IDM_FILE_QUIT, TEXT("&Quit"));

        TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
        DestroyMenu(hMenu);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}