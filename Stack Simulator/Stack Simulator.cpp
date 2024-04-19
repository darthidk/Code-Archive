#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Stack Simulator";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, CLASS_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND RadBtn1;
    static HWND RadBtn2;
    static HWND RadBtn3;
    static HWND RadBtn4;
    static HWND RadBtn5;
    static HWND RadBtn6;
    static HWND PushBtn;    
    static HWND PopBtn;
    static std::vector<float> coins;
    static int cointype[6] = { 0, 0, 0, 0, 0, 0 };
    static float numint = 0;
    RECT updaterect;
    updaterect.top = 0;
    updaterect.left = 0;
    updaterect.bottom = 500;
    updaterect.right = 1000;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        RadBtn1 = CreateWindow(L"BUTTON", L"5c",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 100,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        RadBtn2 = CreateWindow(L"BUTTON", L"10c",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 150,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        RadBtn3 = CreateWindow(L"BUTTON", L"20c",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 200,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        RadBtn4 = CreateWindow(L"BUTTON", L"50c",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 250,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        RadBtn5 = CreateWindow(L"BUTTON", L"$1",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 300,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        RadBtn6 = CreateWindow(L"BUTTON", L"$2",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
            200, 350,
            75, 50,
            hwnd, NULL,
            NULL,
            NULL);
        PushBtn = CreateWindow(L"BUTTON", L"Push",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
            90, 140,
            100, 100,
            hwnd, (HMENU)1,
            NULL,
            NULL);
        PopBtn = CreateWindow(L"BUTTON", L"Pop",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
            90, 260,
            100, 100,
            hwnd, (HMENU)2,
            NULL,
            NULL);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        RECT greyrect;

        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));

        HFONT hFont = CreateFont(
            25, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, 
            DEFAULT_QUALITY, DEFAULT_PITCH, 
            TEXT("L"));

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(200, 0, 0));
        SetBkMode(hdc, TRANSPARENT);

        rect.left = 100;
        rect.top = 5;
        LPCWSTR titlestr = L"Stack Simulator";
        DrawText(hdc, titlestr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        // total value of coins
        rect.left = 125;
        rect.top = 60;

        wchar_t buffer[256];
        if (numint < 10 && numint > 0) {
            swprintf(buffer, 5, L"%f", numint);
            DrawText(hdc, buffer, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
        }
        else if (numint <= 0) {
            LPCWSTR total0 = L"0";
            DrawText(hdc, total0, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
        }
        else if (numint >= 10) {
            swprintf(buffer, 6, L"%f", numint);
            DrawText(hdc, buffer, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
        }
        rect.left = 65;
        LPCWSTR totalstr = L"Total: ";
        DrawText(hdc, totalstr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        // numbers of each type of coins
        rect.top = 60;
        for (int i = 0; i < 6; i++) {
            rect.top += 50;
            rect.left = 300;
            LPCWSTR coinnamestr = L" ";
            switch (i) {
            case 0:
                coinnamestr = L"5c: ";
                break;
            case 1:
                coinnamestr = L"10c: ";
                break;
            case 2:
                coinnamestr = L"20c: ";
                break;
            case 3:
                coinnamestr = L"50c: ";
                break;
            case 4:
                coinnamestr = L"$1: ";
                break;
            case 5:
                coinnamestr = L"$2: ";
                break;
            }
            DrawText(hdc, coinnamestr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
            rect.left = 350;
            if (cointype[i] == 0) {
                LPCWSTR arr = L"0";
                DrawText(hdc, arr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
                continue;
            }
            wchar_t arr[256];
            wsprintfW(arr, L"%d", cointype[i]);
            DrawText(hdc, arr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
            
        }

        // coin on the top of the stack
        rect.left = 250;
        rect.top = 60;
        LPCWSTR topstr = L"Top: ";
        DrawText(hdc, topstr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        wchar_t buf[256];
        if (coins.size() < 1) {
            EndPaint(hwnd, &ps);
            return 0;
        }
        swprintf(buf, 5, L"%f", coins[coins.size() - 1]);
        rect.left = 310;
        DrawText(hdc, buf, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
        
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            if (coins.size() >= 5) {
                MessageBox(hwnd, L"Maximum Number of Coins Reached", L"Input Denied", MB_OK);
                return 0;
            }
            else if (SendMessage(RadBtn1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[0] += 1;
                coins.push_back(0.05);
                numint += 0.05;
            }
            else if (SendMessage(RadBtn2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[1] += 1;
                coins.push_back(0.1);
                numint += 0.1;
            }
            else if (SendMessage(RadBtn3, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[2] += 1;
                coins.push_back(0.2);
                numint += 0.2;
            }
            else if (SendMessage(RadBtn4, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[3] += 1;
                coins.push_back(0.5);
                numint += 0.5;
            }
            else if (SendMessage(RadBtn5, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[4] += 1;
                coins.push_back(1);
                numint += 1;
            }
            else if (SendMessage(RadBtn6, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                cointype[5] += 1;
                coins.push_back(2);
                numint += 2;
            }
            InvalidateRect(hwnd, &updaterect, TRUE);
            return 0;
        }
        else if (LOWORD(wParam) == 2) {
            if (coins.size() <= 0) {
                return 0;
            }
            float e = coins[coins.size() - 1];
            switch (int(e * 100)) {
            case 5:
                cointype[0] -= 1;
                break;
            case 10:
                cointype[1] -= 1;
                break;
            case 20:
                cointype[2] -= 1;
                break;
            case 50:
                cointype[3] -= 1;
                break;
            case 100:
                cointype[4] -= 1;
                break;
            case 200:
                cointype[5] -= 1;
                break;
            }
            numint -= coins[coins.size() - 1];
            coins.pop_back();
            InvalidateRect(hwnd, &updaterect, TRUE);
            return 0;
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}