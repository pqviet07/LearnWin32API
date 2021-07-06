#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

//Define ID
#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG  msg;
    WNDCLASS wc = { 0 };
    wc.lpszClassName = TEXT("Menu");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClass(&wc);

    CreateWindow(wc.lpszClassName, TEXT("Menu"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 200, 150, 0, 0, hInstance, 0);

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
    case WM_CREATE:
        AddMenus(hwnd);
        break;
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
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void AddMenus(HWND hwnd)
{
    HMENU hMenubar;
    HMENU hMenu;
    hMenubar = CreateMenu();
    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("New"));
    AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, TEXT("Open"));
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, IDM_FILE_QUIT, TEXT("Quit"));
    AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, TEXT("File"));
    SetMenu(hwnd, hMenubar);
}