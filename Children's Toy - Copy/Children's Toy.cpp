#ifndef UNICODE
#define UNICODE 
#endif 

#include <windows.h>
#include <gdiplus.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HBITMAP bitmapLetterList[5];
HBITMAP bitmapImageList[5];
HWND buttonLetterList[5];
HWND buttonImageList[5];
bool buttonStatus[10]; // shows whether a button has been pressed or not


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Children's Toy";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME, CLASS_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is 1000, y axis is 450
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

void wmcommand(int num1, int num2, HWND hwnd) {
    if (buttonStatus[num2] == true) { 
        buttonStatus[num1] = false;   
        buttonStatus[num2] = false;
        switch (num1) {
        case 0:
            MessageBox(hwnd, L"0 and 5", L"Match", MB_OK);
            break;
        case 1:
            MessageBox(hwnd, L"1 and 6", L"Match", MB_OK);
            break;
        case 2:
            MessageBox(hwnd, L"2 and 7", L"Match", MB_OK);
            break;
        case 3:
            MessageBox(hwnd, L"3 and 8", L"Match", MB_OK);
            break;
        case 4:
            MessageBox(hwnd, L"4 and 9", L"Match", MB_OK);
            break;
        case 5:
            MessageBox(hwnd, L"0 and 5", L"Match", MB_OK);
            break;
        case 6:
            MessageBox(hwnd, L"1 and 6", L"Match", MB_OK);
            break;
        case 7:
            MessageBox(hwnd, L"2 and 7", L"Match", MB_OK);
            break;
        case 8:
            MessageBox(hwnd, L"3 and 8", L"Match", MB_OK);
            break;
        case 9:
            MessageBox(hwnd, L"4 and 9", L"Match", MB_OK);
            break;
        }
    }
    else {
        for (int i = 0; i < 10; i++) {
            if (buttonStatus[i] == true) { 
                for (int j = 0; j < 10; j++) {
                    buttonStatus[j] = false; 
                }
                MessageBox(hwnd, L"Reset all", L"Reset", MB_OK);
                break;
            }
            else {
                if (i == 9) { 
                    buttonStatus[num1] = true; 
                    break;
                }
            }
        }
    }
}
 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{   
    switch (uMsg)
    {
    case WM_CREATE:
    {   
        for (int i = 0; i < 10; i++) {
            buttonStatus[i] = false;
        }
        for (int i = 0; i < 5; i++) {
            LPCWSTR BitmapFileName = NULL;
            LPCWSTR BitmapFileNameAlt = NULL;
            switch (i) {
            case 0:
                BitmapFileName = L"Letters\\Abmp.bmp";
                break;
            case 1:
                BitmapFileName = L"Letters\\Gbmp.bmp";
                break;
            case 2:
                BitmapFileName = L"Letters\\Lbmp.bmp";
                break;
            case 3:
                BitmapFileName = L"Letters\\Tbmp.bmp";
                break;
            case 4:
                BitmapFileName = L"Letters\\Xbmp.bmp";
                break;
            }
            switch (i) {
            case 0:
                BitmapFileNameAlt = L"Images\\Applebmp.bmp";
                break;
            case 1:
                BitmapFileNameAlt = L"Images\\Goldbmp.bmp";
                break;
            case 2:
                BitmapFileNameAlt = L"Images\\Leafbmp.bmp";
                break;
            case 3:
                BitmapFileNameAlt = L"Images\\Treebmp.bmp";
                break;
            case 4:
                BitmapFileNameAlt = L"Images\\xraybmp.bmp";
                break;
            }

            bitmapLetterList[i] = (HBITMAP)LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            bitmapImageList[i] = (HBITMAP)LoadImage(NULL, BitmapFileNameAlt, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

            buttonLetterList[i] = CreateWindow(L"BUTTON", L"ji",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                i * 150, 160, 100, 30,
                hwnd, (HMENU)i,
                NULL,
                0);
            buttonImageList[i] = CreateWindow(L"BUTTON", L"j",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                i * 150, 310, 100, 30,
                hwnd, (HMENU)(i+5),
                NULL,
                0);
        }
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BITMAP bitmap;
        HDC hdcMem;
        HGDIOBJ oldBitmap;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;

        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(0, 250, 250))));

        HFONT hFont = CreateFont(
            25, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT("hi")
        );

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, TRANSPARENT);

        rect.left = 300;
        rect.top = 10;
        LPCWSTR hi = L"Children's Toy";
        DrawText(hdc, hi, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        for (int i = 0; i < 5; i++) {
            hdcMem = CreateCompatibleDC(hdc);

            GetObject(bitmapLetterList[i], sizeof(BITMAP), &bitmap);
            oldBitmap = SelectObject(hdcMem, bitmapLetterList[i]);
            StretchBlt(hdc, i * 150, 50, 100, 100, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);
        }
        for (int i = 0; i < 5; i++) {
            hdcMem = CreateCompatibleDC(hdc);
            oldBitmap = SelectObject(hdcMem, bitmapImageList[i]);

            GetObject(bitmapImageList[i], sizeof(BITMAP), &bitmap);
            StretchBlt(hdc, i * 150, 200, 100, 100, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);
        }
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        DeleteObject(bitmapLetterList);
        DeleteObject(bitmapImageList);
        DeleteObject(buttonLetterList);
        DeleteObject(buttonImageList);
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        switch (wParam) {
        case 0:
            wmcommand(0, 5, hwnd);
            break;
        case 1:
            wmcommand(1, 6, hwnd);
            break;
        case 2:
            wmcommand(2, 7, hwnd);
            break;
        case 3:
            wmcommand(3, 8, hwnd);
            break;
        case 4:
            wmcommand(4, 9, hwnd);
            break;
        case 5:
            wmcommand(5, 0, hwnd);
            break;
        case 6:
            wmcommand(6, 1, hwnd);
            break;
        case 7:
            wmcommand(7, 2, hwnd);
            break;
        case 8:
            wmcommand(8, 3, hwnd);
            break;
        case 9: 
            wmcommand(9, 4, hwnd);
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}