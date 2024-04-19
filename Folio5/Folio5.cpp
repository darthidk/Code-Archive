#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Learn to Program Windows",
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
    static HWND RadBtnArr[6];
    static HWND txtboxEnter;
    static std::string endresult = "0";
    switch (uMsg)
    {
    case WM_CREATE:
    {
        RadBtnArr[0] = CreateWindow(L"BUTTON", L"Faranheit to Celsius",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 100,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        RadBtnArr[1] = CreateWindow(L"BUTTON", L"Celsius to Faranheit",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 135,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        RadBtnArr[2] = CreateWindow(L"BUTTON", L"Inches to centimeter",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 170,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        RadBtnArr[3] = CreateWindow(L"BUTTON", L"Centimetres to inches",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 205,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        RadBtnArr[4] = CreateWindow(L"BUTTON", L"Ounces to Grams",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 240,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        RadBtnArr[5] = CreateWindow(L"BUTTON", L"Grams to Ounces",
            BS_AUTORADIOBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 275,
            200, 25,
            hwnd, NULL,
            NULL, NULL);
        txtboxEnter = CreateWindow(L"EDIT", NULL,
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_NUMBER,
            50, 150,
            100, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Convert",
            BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
            300, 330,
            100, 100,
            hwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Quit",
            BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
            625, 330,
            100, 100,
            hwnd, (HMENU)2,
            NULL, NULL);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rect;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint
        FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));

        HFONT hFont = CreateFont(
            50, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT("hi")
        );

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, TRANSPARENT);

        rect.left = 220;
        rect.top = 25;
        LPCWSTR text = L"Unit convertor";
        DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        rect.left = 650;
        rect.right = 807;
        rect.top = 150;
        std::wstring tempwstr = std::wstring(endresult.begin(), endresult.end());
        DrawText(hdc, tempwstr.c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            int WinTextLen = GetWindowTextLength(txtboxEnter) + 1;
            if (WinTextLen <= 1) {
                MessageBox(hwnd, L"Text Box is empty", L"Validation", MB_OK | MB_ICONEXCLAMATION);
                break;
            }
            wchar_t buf[5];
            GetWindowText(txtboxEnter, buf, WinTextLen);
            int intinputnum = _wtoi(buf);
            double inputnum = intinputnum;
            double tempendresult;
            for (int i = 0; i < 6; i++) {
                if (SendMessage(RadBtnArr[i], BM_GETCHECK, NULL, NULL) == BST_CHECKED) {
                    if (i == 0) {
                        tempendresult = (inputnum * 9) / 5 + 32;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " C\0";
                        endresult = tempstr;
                    }
                    else if (i == 1) {
                        tempendresult = ((inputnum - 32) * 5) / 9;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " F\0";
                        endresult = tempstr;
                    }
                    else if (i == 2) {
                        tempendresult = inputnum * 2.54;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " cm\0";
                        endresult = tempstr;
                    }
                    else if (i == 3) {
                        tempendresult = inputnum / 2.54;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " inches\0";
                        endresult = tempstr;
                    }
                    else if (i == 4) {
                        tempendresult = inputnum * 28.35;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " g\0";
                        endresult = tempstr;
                    }
                    else if (i == 5) {
                        tempendresult = inputnum / 28.35;
                        char str[40];
                        sprintf_s(str, "%.2f", tempendresult);
                        sscanf_s(str, "%f", &tempendresult);
                        std::string tempstr = str;
                        tempstr = tempstr + " ounces\0";
                        endresult = tempstr;
                    }
                    RECT rect;
                    GetClientRect(hwnd, &rect);
                    InvalidateRect(hwnd, &rect, TRUE);
                    break;
                }
            }
            
        }
        else if (LOWORD(wParam) == 2) {
            DestroyWindow(hwnd);
        }
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}