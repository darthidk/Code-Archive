#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <fstream>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Postcodes";

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
    static HWND SubTextBox;
    static HWND PostTextBox;
    static HWND RadBtnArr[15];
    static bool BtnActive[15];
    switch (uMsg)
    {
    case WM_CREATE:
    {
        SubTextBox = CreateWindow(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            450, 125,
            160, 25,
            hwnd, NULL,
            NULL,
            NULL);
        PostTextBox = CreateWindow(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            620, 125,
            150, 25,
            hwnd, NULL,
            NULL,
            NULL);
        CreateWindow(L"BUTTON", L"Edit",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            560, 175,
            100, 50,
            hwnd, (HMENU)1,
            NULL,
            NULL);
        CreateWindow(L"BUTTON", L"Delete",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            670, 175,
            100, 50,
            hwnd, (HMENU)2,
            NULL,
            NULL);
        CreateWindow(L"BUTTON", L"Add New",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            450, 175,
            100, 50,
            hwnd, (HMENU)3,
            NULL,
            NULL);
        CreateWindow(L"BUTTON", L"Quit",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            860, 370,
            75, 75,
            hwnd, (HMENU)4,
            NULL,
            NULL);
        for (int i = 5; i < 20; i++) {
            RadBtnArr[i - 5] = CreateWindow(L"BUTTON", NULL,
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, ((i - 5) * 30),
                150, 25,
                hwnd, NULL,
                NULL,
                NULL);
        }
        for (int i = 0; i < 15; i++) {
            BtnActive[i] = false;
        }

        std::string line;
        int numofline = 0;
        std::fstream file;
        file.open("Postcodes.txt");
        while (getline(file, line)) {
            std::wstring wstr = std::wstring(line.begin(), line.end());
            const wchar_t* widestr = wstr.c_str();
            SendMessage(RadBtnArr[numofline], WM_SETTEXT, 0, (LPARAM)widestr);
            BtnActive[numofline] = true;
            numofline++;
        }
        file.close();
        return 0;
    }
    case WM_DESTROY:
    {
        // get window text and save to text file
        std::fstream file;
        file.open("Postcodes.txt", std::ios::trunc | std::ios::out);
        for (int i = 0; i < 15; i++) {
            wchar_t buffer[30];
            GetWindowText(RadBtnArr[i], buffer, 30);
            std::wstring ws(buffer);
            std::string str(ws.begin(), ws.end());
            file << str << "\n";
        }
        file.close();
        PostQuitMessage(0);
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rect;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255))));
        HFONT hFont = CreateFont(
            50, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT(" ")
        );

        GetClientRect(hwnd, &rect);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, TRANSPARENT);

        rect.left = 475;
        rect.top = 50;
        LPCWSTR titletxt = L"Postcodes";
        DrawText(hdc, titletxt, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        hFont = CreateFont(
            20, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH,
            TEXT(" ")
        );
        SelectObject(hdc, hFont);

        rect.left = 450;
        rect.top = 370;
        LPCWSTR numsubtxt = L"Number of suburbs: ";
        DrawText(hdc, numsubtxt, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        rect.left = 600;
        int numofsub = 0;
        for (int i = 0; i < 15; i++) {
            if (BtnActive[i] == true) {
                numofsub++;
            }
        }
        std::wstring ws = std::to_wstring(numofsub);
        const wchar_t* numofsubstr = ws.c_str();
        DrawText(hdc, numofsubstr, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

        EndPaint(hwnd, &ps);
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            int SubTextLen = GetWindowTextLength(SubTextBox) + 1;
            wchar_t Subbuf[30];
            GetWindowText(SubTextBox, Subbuf, SubTextLen);
            wcscat_s(Subbuf, L", ");
            ;
            wchar_t Postbuf[5];
            GetWindowText(PostTextBox, Postbuf, 5);

            wcscat_s(Subbuf, Postbuf);

            for (int i = 0; i < 15; i++) {
                if (SendMessage(RadBtnArr[i], BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    SendMessage(RadBtnArr[i], WM_SETTEXT, 0, (LPARAM)Subbuf);
                    BtnActive[i] = true;
                    break;
                }
            }
            return 0;
        }
        else if (LOWORD(wParam) == 2) {
            for (int i = 0; i < 15; i++) {
                if (SendMessage(RadBtnArr[i], BM_GETCHECK,0, 0) == BST_CHECKED) {
                    SendMessage(RadBtnArr[i], WM_SETTEXT, 0, (LPARAM)L"");
                    BtnActive[i] = false;
                    break;
                }
            }
            return 0;
        }
        else if (LOWORD(wParam) == 3) {
            int SubTextLen = GetWindowTextLength(SubTextBox) + 1;
            wchar_t Subbuf[30];
            GetWindowText(SubTextBox, Subbuf, SubTextLen);
            wcscat_s(Subbuf, L", ");
;
            wchar_t Postbuf[5];
            GetWindowText(PostTextBox, Postbuf, 5);

            wcscat_s(Subbuf, Postbuf);

            for (int i = 0; i < 15; i++) {
                if (BtnActive[i] == false) {
                    SendMessage(RadBtnArr[i], WM_SETTEXT, 0, (LPARAM)Subbuf);
                    BtnActive[i] = true;
                    break;
                }
            }
            return 0;
        }
        else if (LOWORD(wParam) == 4) {
            DestroyWindow(hwnd);
            return 0;
        }
        return 0;
    return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}