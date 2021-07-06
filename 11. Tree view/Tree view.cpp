#include <windows.h>
#include <commctrl.h>

#pragma comment( lib, "comctl32.lib" )

#define ID_TREEVIEW 100

HINSTANCE g_hInst;

HWND CreateATreeView(HWND hwndParent);
HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Ham Winmain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HWND hwnd;
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = TEXT("TreeView");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClass(&wc);
    // Create parent window
    hwnd = CreateWindow(wc.lpszClassName, TEXT("Menu"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 250, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd); // Update windows

    while(GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        HWND hwndTreeview;
        hwndTreeview = CreateATreeView(hwnd);
        AddItemToTree(hwndTreeview, "Drink", 1);
        AddItemToTree(hwndTreeview, "Orange juice", 2);
        AddItemToTree(hwndTreeview, "Price: 20K", 3);
        AddItemToTree(hwndTreeview, "Coffee", 2);
        AddItemToTree(hwndTreeview, "Price: 25K", 3);
        AddItemToTree(hwndTreeview, "Tea", 2);
        AddItemToTree(hwndTreeview, "Price: 15K", 3);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Ham tao treeview
HWND CreateATreeView(HWND hwndParent)
{
    RECT rcClient; // dimensions of client area 
    HWND hwndTV; // handle to tree-view control 

    // Ensure that the common control DLL is loaded. 
    InitCommonControls();

    // Get the dimensions of the parent window's client area, and create 
    // the tree-view control. 
    GetClientRect(hwndParent, &rcClient);
    hwndTV = CreateWindowEx(0, WC_TREEVIEW,
        TEXT("Tree View"),
        WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES,
        0,
        0,
        rcClient.right,
        rcClient.bottom,
        hwndParent,
        (HMENU)ID_TREEVIEW,
        g_hInst,
        NULL);
    return hwndTV;
}

HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel)
{
    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST;
    static HTREEITEM hPrevRootItem = NULL;
    static HTREEITEM hPrevLev2Item = NULL;
    HTREEITEM hti;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    // Set the text of the item. 
    tvi.pszText = lpszItem;
    tvi.cchTextMax = sizeof(tvi.pszText) / sizeof(tvi.pszText[0]);

    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = 0;
    tvi.iSelectedImage = 0;

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM)nLevel;
    tvins.item = tvi;
    tvins.hInsertAfter = hPrev;

    // Set the parent item based on the specified level. 
    if(nLevel == 1)
        tvins.hParent = TVI_ROOT;
    else if(nLevel == 2)
        tvins.hParent = hPrevRootItem;
    else
        tvins.hParent = hPrevLev2Item;

    // Add the item to the tree-view control. 
    hPrev = (HTREEITEM)SendMessage(hwndTV, TVM_INSERTITEM,
        0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
    if(hPrev == NULL)
        return NULL;

    // Save the handle to the item. 
    if(nLevel == 1)
        hPrevRootItem = hPrev;
    else if(nLevel == 2)
        hPrevLev2Item = hPrev;

    // The new item is a child item. Give the parent item a 
    // closed folder bitmap to indicate it now has child items. 
    if(nLevel > 1)
    {
        hti = TreeView_GetParent(hwndTV, hPrev);
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        tvi.hItem = hti;
        tvi.iImage = 0;
        tvi.iSelectedImage = 0;
        TreeView_SetItem(hwndTV, &tvi);
    }
    return hPrev;
}