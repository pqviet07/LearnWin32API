#include <Windows.h>
#include <strsafe.h>

#define IDC_LIST 1
#define IDC_STATIC 2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hinst;

typedef struct
{
    TCHAR name[30];
    TCHAR role[20];
} Friends;

Friends friends[] =
{
    {TEXT("vncoding"), TEXT("Admin")},
    {TEXT("vhnhan01"), TEXT("member")},
    {TEXT("thanhx175"), TEXT("member")},
    {TEXT("tienle"), TEXT("member")},
    {TEXT("hoanghoa"), TEXT("member")},
};

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
    CreateWindow(wc.lpszClassName, TEXT("List Box"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 340, 200, 0, 0, hInstance, 0);
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
    static HWND hwndList, hwndStatic;
    int i, sel;
    TCHAR buff[100];

    switch(msg)
    {
    case WM_CREATE:
        hwndList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, 10, 10, 150, 120, hwnd, (HMENU)IDC_LIST, g_hinst, NULL);

        hwndStatic = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE, 200, 10, 120, 45, hwnd, (HMENU)IDC_STATIC, g_hinst, NULL);

        for(i = 0; i < sizeof(friends) / sizeof(friends[0]); i++)
        {
            SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)friends[i].name);
        }
        break;
    case WM_COMMAND:
        if(LOWORD(wParam) == IDC_LIST)
        {
            if(HIWORD(wParam) == LBN_SELCHANGE)
            {
                sel = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
                StringCbPrintf(buff, sizeof(buff) / sizeof(buff[0]), TEXT("Role: %s"), friends[sel].role);
                SetWindowText(hwndStatic, buff);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, msg, wParam, lParam));
}