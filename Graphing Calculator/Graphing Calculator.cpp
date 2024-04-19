#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <cmath>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool graphing = false;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Graphing Calculator";

    WNDCLASS wc = { };

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, CLASS_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 945, y axis is roughly 450
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        MessageBox(hwnd, L"hwnd fail", NULL, MB_OK);
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

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND ComboBoxsqr;
    static HWND ComboBoxlin;
    static HWND ComboBoxcon;
    static HWND TextBoxsquare;
    static HWND TextBoxlinear;
    static HWND TextBoxconst;
    static Gdiplus::Point graphpoints[31];
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CreateWindow(L"BUTTON", L"Calculate",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            300, 55, 75, 20,
            hwnd, (HMENU)1,
            NULL,
            NULL);

        TextBoxsquare = CreateWindow(L"EDIT", L"0",
            WS_BORDER | WS_VISIBLE | WS_CHILD | ES_NUMBER,
            80, 55, 20, 25,
            hwnd, NULL,
            NULL,
            NULL);
        TextBoxlinear = CreateWindow(L"EDIT", L"1",
            WS_BORDER | WS_VISIBLE | WS_CHILD | ES_NUMBER,
            190, 55, 20, 25,
            hwnd, NULL,
            NULL,
            NULL);
        TextBoxconst = CreateWindow(L"EDIT", L"0",
            WS_BORDER | WS_VISIBLE | WS_CHILD | ES_NUMBER,
            270, 55, 20, 25,
            hwnd, NULL,
            NULL,
            NULL);

        TCHAR combostring[2] = { L'+', L'-' };

        ComboBoxsqr = CreateWindow(L"COMBOBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
            45, 55, 35, 75,
            hwnd, (HMENU)4,
            NULL,
            NULL);
        for (int i = 0; i < 2; i++) {
            TCHAR str = combostring[i];
            SendMessage(ComboBoxsqr, CB_ADDSTRING, NULL, (LPARAM)&str);
        }
        SendMessage(ComboBoxsqr, CB_SETCURSEL, (WPARAM)0, NULL);

        ComboBoxlin = CreateWindow(L"COMBOBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
            150, 55, 35, 75,
            hwnd, (HMENU)5,
            NULL,
            NULL);
        for (int i = 0; i < 2; i++) {
            TCHAR str = combostring[i];
            SendMessage(ComboBoxlin, CB_ADDSTRING, NULL, (LPARAM)&str);
        }
        SendMessage(ComboBoxlin, CB_SETCURSEL, (WPARAM)0, NULL);

        ComboBoxcon = CreateWindow(L"COMBOBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
            230, 55, 35, 75,
            hwnd, (HMENU)6,
            NULL,
            NULL);
        for (int i = 0; i < 2; i++) {
            TCHAR str = combostring[i];
            SendMessage(ComboBoxcon, CB_ADDSTRING, NULL, (LPARAM)&str);
        }
        SendMessage(ComboBoxcon, CB_SETCURSEL, (WPARAM)0, NULL);

        graphpoints[0] = Gdiplus::Point(50, 100);
        graphpoints[1] = Gdiplus::Point(175, 225);
        graphpoints[2] = Gdiplus::Point(300, 350);
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
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200))));

        HFONT hFont = CreateFont(
            25, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT("hi")
        );

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(200, 0, 0));
        SetBkMode(hdc, TRANSPARENT);

        rect.left = 10;
        rect.top = 50;
        LPCWSTR hi = L"y =           x^2             x  ";
        DrawText(hdc, hi, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        using namespace Gdiplus;
        Graphics graphics(hdc);

        // cartesian plane
        Pen penplane(Color(255, 150, 150, 150), 2.0f); 
        graphics.DrawLine(&penplane, 50, 225, 300, 225); // x axis
        graphics.DrawLine(&penplane, 175, 100, 175, 350); // y axis

        // box around the graphing area
        Pen penbox(Color(255, 0, 0, 0), 0.5f); 
        graphics.DrawLine(&penbox, 50, 100, 300, 100); // top line
        graphics.DrawLine(&penbox, 50, 350, 300, 350); // bottom line
        graphics.DrawLine(&penbox, 50, 100, 50, 350); // left line
        graphics.DrawLine(&penbox, 300, 100, 300, 350); // right line
      
        // drawing graph
        // origin is at 175, 225
        Pen graphpen(Color(255, 0, 0, 200), 1.0f);
        if (graphing == false) {
            graphics.DrawCurve(&graphpen, graphpoints, 3);
            EndPaint(hwnd, &ps);
            return 0;
        }
        graphics.DrawCurve(&graphpen, graphpoints, 31);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // get textbox values
            int WinTextsquareLen = GetWindowTextLength(TextBoxsquare) + 1;
            wchar_t buf;
            GetWindowText(TextBoxsquare, &buf, WinTextsquareLen);

            int WinTextlinearLen = GetWindowTextLength(TextBoxlinear) + 1;
            wchar_t buflin;
            GetWindowText(TextBoxlinear, &buflin, WinTextlinearLen);

            int WinTextconstLen = GetWindowTextLength(TextBoxconst) + 1;
            wchar_t bufcon;
            GetWindowText(TextBoxconst, &bufcon, WinTextconstLen);


            // convert textbox values to int
            wchar_t* bufconptr = &bufcon;
            std::wstring wsc(bufconptr);    
            std::string constr(wsc.begin(), wsc.end());
            int constnum = std::stoi(constr);

            wchar_t* buflinptr = &buflin;
            std::wstring wsl(buflinptr);
            std::string linstr(wsl.begin(), wsl.end());
            int linnum = std::stoi(linstr);

            wchar_t* bufsqrptr = &buf;
            std::wstring wss(bufsqrptr);
            std::string bufstr(wss.begin(), wss.end());
            int squarenum = std::stoi(bufstr);

            if (SendMessage(ComboBoxsqr, CB_GETCURSEL, NULL, NULL) == 1) {
                squarenum = -1 * squarenum;
            }
            if (SendMessage(ComboBoxlin, CB_GETCURSEL, NULL, NULL) == 1) {
                linnum = -1 * linnum;
            }
            if (SendMessage(ComboBoxcon, CB_GETCURSEL, NULL, NULL) == 1) {
                constnum = -1 * constnum;
            }
            
            // calculating y values based on x values from -15 to 15
            for(int i = 1; i < 16; i++) { // negatives on x axis
                int ni = i * -1;
                int y = pow(squarenum * ni, 2) + (linnum * ni) + constnum;
                int j = i - 1;
                j = 8 - i + 7;
                if (SendMessage(ComboBoxsqr, CB_GETCURSEL, NULL, NULL) == 1) {
                    y = y * -1;
                }
                graphpoints[j] = Gdiplus::Point(ni*10 + 175, 225 - y);
            }
            for (int i = 0; i < 16; i++) { // positives on x axis
                int y = pow(squarenum * i, 2) + (linnum * i) + constnum;
                if (SendMessage(ComboBoxsqr, CB_GETCURSEL, NULL, NULL) == 1) {
                    y = y * -1;
                }
                graphpoints[i + 15] = Gdiplus::Point(i*10 + 175, 225 - y);
            }
            graphing = true;

            // update graph area
            RECT updaterect;
            updaterect.top = 100;
            updaterect.left = 50;
            updaterect.right = 300;
            updaterect.bottom = 350;
            InvalidateRect(hwnd, &updaterect, TRUE);
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}