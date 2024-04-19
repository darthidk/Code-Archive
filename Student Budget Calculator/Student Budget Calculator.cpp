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
    static HWND TextBoxes[6];
    static HWND ComboBoxes[6];
    static int BudgetTotal = 0;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CreateWindow(L"BUTTON", L"Calculate",
            WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            500, 75,
            75, 75,
            hwnd, (HMENU)15,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Quit",
            WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            500, 225,
            75, 75,
            hwnd, (HMENU)16,
            NULL, NULL);

        for (int i = 0; i < 3; i++) {
            TextBoxes[i] = CreateWindow(L"EDIT", L"0",
                WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER,
                200, 75 + (30 * i),
                100, 25,
                hwnd, (HMENU)(i),
                NULL, NULL);
            ComboBoxes[i] = CreateWindow(L"COMBOBOX", NULL,
                WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
                350, 75 + (30 * i),
                100, 100,
                hwnd, (HMENU)(i + 6),
                NULL, NULL);
        }
        for (int i = 3; i < 6; i++) {
            TextBoxes[i] = CreateWindow(L"EDIT", L"0",
                WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER,
                200, 135 + (30 * i),
                100, 25,
                hwnd, (HMENU)(i),
                NULL, NULL);
            ComboBoxes[i] = CreateWindow(L"COMBOBOX", NULL,
                WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS,
                350, 135 + (30 * i),
                100, 100,
                hwnd, (HMENU)(i + 6),
                NULL, NULL);
        }

        TCHAR ComboBoxStr[4][10] = {L"Daily", L"Weekly", L"Monthly", L"Annually"};

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                SendMessage(ComboBoxes[i], CB_ADDSTRING, NULL, (LPARAM)&ComboBoxStr[j]);
            }
            SendMessage(ComboBoxes[i], CB_SETCURSEL, (WPARAM)1, NULL);
        }
        
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
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0))));


        LPCWSTR IncomeLabels[3] = { L"Allowance", L"Job", L"Other" };
        LPCWSTR ExpenseLabels[3] = { L"School", L"Travel", L"Other" };

        HFONT hFont = CreateFont(
            20, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT("hi")
        );

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);

        for (int i = 0; i < 3; i++) {
            rect.left = 100;
            rect.top = 75 + (i * 30);
            DrawText(hdc, IncomeLabels[i], -1, &rect, DT_SINGLELINE | DT_NOCLIP);
            rect.top = 225 + (i * 30);
            DrawText(hdc, ExpenseLabels[i], -1, &rect, DT_SINGLELINE | DT_NOCLIP);
        }

        rect.left = 250;
        rect.top = 25;
        DrawText(hdc, L"Income", -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        rect.top = 185;
        DrawText(hdc, L"Expenses", -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        rect.top = 350;
        DrawText(hdc, L"Summary", -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        rect.left = 200;
        rect.top = 380;
        std::wstring totalstr = L"Annual Saving: $" + std::to_wstring(BudgetTotal);
        DrawText(hdc, (LPCWSTR)totalstr.c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        MessageBox(hwnd, (LPCWSTR)(std::to_wstring(BudgetTotal)).c_str(), NULL, MB_OK);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 15) {
            int TextBoxVal = 0;
            BudgetTotal = 0;
            for (int i = 0; i < 6; i++) {
                wchar_t buffer;
                if (GetWindowText(TextBoxes[i], &buffer, 10) == 0) {
                    MessageBox(hwnd, L"new thing", NULL, MB_OK);
                    continue;
                }
                wchar_t* bufferptr = &buffer;
                std::wstring wsbuf(bufferptr);
                std::string conbuf(wsbuf.begin(), wsbuf.end());
                TextBoxVal += std::stoi(conbuf);

                if (TextBoxVal == 0) {
                    MessageBox(hwnd, L"0 continue", NULL, MB_OK);
                    continue;
                }

                if (i < 3) {
                    switch (SendMessage(ComboBoxes[i], CB_GETCURSEL, 0, 0)) {
                    case 0:
                        BudgetTotal += TextBoxVal * 365;
                    case 1:
                        BudgetTotal += TextBoxVal * 52;
                    case 2:
                        BudgetTotal += TextBoxVal * 12;
                    case 3:
                        BudgetTotal += TextBoxVal;
                    }
                }
                else if (i >= 3) {
                    switch (SendMessage(ComboBoxes[i], CB_GETCURSEL, 0, 0)) {
                    case 0:
                        BudgetTotal -= TextBoxVal * 365;
                    case 1:
                        BudgetTotal -= TextBoxVal * 52;
                    case 2:
                        BudgetTotal -= TextBoxVal * 12;
                    case 3:
                        BudgetTotal -= TextBoxVal;
                    }
                }
            }

            RECT rect;
            rect.top = 370;
            rect.left = 190;
            rect.bottom = 410;
            rect.right = 400;
            InvalidateRect(hwnd, &rect, TRUE);
            return 0;
        } 
        if (LOWORD(wParam) == 16) {
            DestroyWindow(hwnd);
            return 0;
        }
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}