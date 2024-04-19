// Main file that contains all the code to display windows and all other objects associated with them

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ShObjIdl.h>
#include "ClassDeclarations.h"
#include "SearchFunctions.h"
#include "MiscFunctions.h"
#include "FileFunctions.h"
#include "Paint.h"

// Proc functions are declared here and defined later on
// Proc functions take a window, a message and 2 other values related to the message
// Output depends on the inputted message 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LogInWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoggedInWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoggedInLibWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AddUserWindowProc(HWND hwnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);
LRESULT CALLBACK AddBookWindowProc(HWND hwnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);
LRESULT CALLBACK DisplayBookProc(HWND hwnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);
LRESULT CALLBACK DisplayUserProc(HWND hwnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);

HWND txtboxSearch;
std::vector<User> UserList;
std::vector<Book> BookList;
std::vector<std::string> UserEmails;
std::vector<std::string> BookNames;

bool LoggedIn = false;
std::vector<std::string> tempuservect = { "null" };
User LoggedInUser("null", "null", "null", false, tempuservect);
tm temptmstruct;
Book SearchBookResult("null", "null", "null", "null", "null", temptmstruct, true, "null", "null");
User SearchUserResult("null", "null", "null", false, tempuservect);

// All functions below create and display the window when called for and call the relevant proc function when messages are recieved
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Library Borrowing System";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Library Borrowing System",
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

int LogInWindow(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Log In";

    WNDCLASS mwc = { };

    mwc.lpfnWndProc = LogInWindowProc;
    mwc.hInstance = mhInstance;
    mwc.lpszClassName = CLASS_NAME;

    RegisterClass(&mwc);

    // Create the window.

    HWND mwnd = CreateWindowEx(
        0, CLASS_NAME, L"Log In",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (mwnd == NULL)
    {
        MessageBox(mwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(mwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int LoggedInWindow(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Home Page";

    WNDCLASS mwc = { };

    mwc.lpfnWndProc = LoggedInWindowProc;
    mwc.hInstance = mhInstance;
    mwc.lpszClassName = CLASS_NAME;

    RegisterClass(&mwc);

    // Create the window.

    HWND mwnd = CreateWindowEx(
        0, CLASS_NAME, L"Home Page",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (mwnd == NULL)
    {
        MessageBox(mwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(mwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int LoggedInLibWindow(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"New Window";

    WNDCLASS lmwc = { };

    lmwc.lpfnWndProc = LoggedInLibWindowProc;
    lmwc.hInstance = mhInstance;
    lmwc.lpszClassName = CLASS_NAME;

    RegisterClass(&lmwc);

    // Create the window.

    HWND lmwnd = CreateWindowEx(
        0, CLASS_NAME, L"Home Page",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (lmwnd == NULL)
    {
        MessageBox(lmwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(lmwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int AddUserWindow(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Add User";

    WNDCLASS lmwc = { };

    lmwc.lpfnWndProc = AddUserWindowProc;
    lmwc.hInstance = mhInstance;
    lmwc.lpszClassName = CLASS_NAME;

    RegisterClass(&lmwc);

    // Create the window.

    HWND lmwnd = CreateWindowEx(
        0, CLASS_NAME, L"Add User",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (lmwnd == NULL)
    {
        MessageBox(lmwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(lmwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int AddBookWindow(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Add Book";

    WNDCLASS lmwc = { };

    lmwc.lpfnWndProc = AddBookWindowProc;
    lmwc.hInstance = mhInstance;
    lmwc.lpszClassName = CLASS_NAME;

    RegisterClass(&lmwc);

    // Create the window.

    HWND lmwnd = CreateWindowEx(
        0, CLASS_NAME, L"Add Book",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (lmwnd == NULL)
    {
        MessageBox(lmwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(lmwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int DisplayBook(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Book Result";

    WNDCLASS lmwc = { };

    lmwc.lpfnWndProc = DisplayBookProc;
    lmwc.hInstance = mhInstance;
    lmwc.lpszClassName = CLASS_NAME;

    RegisterClass(&lmwc);

    // Create the window.

    HWND lmwnd = CreateWindowEx(
        0, CLASS_NAME, L"Book Result",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (lmwnd == NULL)
    {
        MessageBox(lmwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(lmwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int DisplayUser(HINSTANCE mhInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"User Result";

    WNDCLASS lmwc = { };

    lmwc.lpfnWndProc = DisplayUserProc;
    lmwc.hInstance = mhInstance;
    lmwc.lpszClassName = CLASS_NAME;

    RegisterClass(&lmwc);

    // Create the window.

    HWND lmwnd = CreateWindowEx(
        0, CLASS_NAME, L"User Result",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // x axis is roughly 100, y axis is roughly 450
        NULL, NULL,
        mhInstance,
        NULL
    );

    if (lmwnd == NULL)
    {
        MessageBox(lmwnd, L"mwnd fail", NULL, MB_OK);
        return 0;
    }

    ShowWindow(lmwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// All functions below are the definitions for the proc functions declared earlier
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND txtboxEmail;
    static HWND txtboxPassword;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxEmail = CreateWindow(L"EDIT", L"Email",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            200, 75, 250, 50,
            hwnd, NULL,
            NULL, NULL);
        txtboxPassword = CreateWindow(L"EDIT", L"PW",
            WS_BORDER | WS_VISIBLE | WS_CHILD | ES_PASSWORD,
            200, 150, 250, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Log in",
            BS_DEFPUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            275, 225, 100, 100,
            hwnd, (HMENU)3,
            NULL, NULL);
        
        UserList = ReadFromUser();
        BookList = ReadFromBook();

        // Gets the name of every user/book and puts them into another vector at the same index where it originally was
        for (size_t i = 0; i < UserList.size(); i++) {
            UserEmails.push_back(UserList[i].email);
        }

        for (size_t i = 0; i < BookList.size(); i++) {
            BookNames.push_back(BookList[i].name);
        }

        return 0;
    }
    case WM_PAINT:
    {
        OnPaint(hwnd);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 3) {
            // Searches for whether the email that was put into the first tetxtbox exists within the system/vector
            // If it exists, searches for whether the password entered matches the one in the system
            // If they match, user is logged in, if not a message box pops up to promopt the user that the details are wrong
            int bufemaillen = GetWindowTextLength(txtboxEmail) + 1;
            wchar_t bufemail[50];
            GetWindowText(txtboxEmail, bufemail, bufemaillen);
            std::wstring wbufemail = bufemail;
            std::string request = std::string(wbufemail.begin(), wbufemail.end());

            int bufpwlen = GetWindowTextLength(txtboxPassword) + 1;
            wchar_t bufpw[50];
            GetWindowText(txtboxPassword, bufpw, bufpwlen);
            std::wstring wbufpw = bufpw;
            std::string pwstr = std::string(wbufpw.begin(), wbufpw.end());

            if (request.size() == 0) {
                MessageBox(hwnd, L"Email text box is empty", L"Failed to log in", MB_OK | MB_ICONERROR);
                return 0;
            }
            else if (pwstr.size() == 0) {
                MessageBox(hwnd, L"Password text box is empty", L"Failed to log in", MB_OK | MB_ICONERROR);
                return 0;
            }

            int emailindex = EmailSearch(request, UserEmails);

            if (emailindex >= 0) {
                if (UserList[emailindex].pw == pwstr) {
                    LoggedInUser = UserList[emailindex];
                    LoggedIn = true;
                    if (UserList[emailindex].islibrarian == true) {
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
                        DestroyWindow(hwnd);
                        LoggedInLibWindow(hInstance, SW_SHOW);
                    }
                    else {
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
                        DestroyWindow(hwnd);
                        LoggedInWindow(hInstance, SW_SHOW);
                    }
                }
                else if (UserList[emailindex].pw != pwstr) {
                    MessageBox(hwnd, L"Email and Password do not match", L"Failed to log in", MB_OK);
                }
            }
            else {
                MessageBox(hwnd, L"Email does not exist within the system", L"Failed to log in", MB_OK);
            }

        }
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LogInWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND txtboxEmail;
    static HWND txtboxPassword;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxEmail = CreateWindow(L"EDIT", L"Email",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            200, 75, 250, 50,
            hwnd, NULL,
            NULL, NULL);
        txtboxPassword = CreateWindow(L"EDIT", L"PW",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            200, 150, 250, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Log in",
            BS_DEFPUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            275, 225, 100, 100,
            hwnd, (HMENU)3,
            NULL, NULL);
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint(hwnd);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 3) {
            // Searches for whether the email that was put into the first tetxtbox exists within the system/vector
            // If it exists, searches for whether the password entered matches the one in the system
            // If they match, user is logged in, if not a message box pops up to promopt the user that the details are wrong
            int bufemaillen = GetWindowTextLength(txtboxEmail) + 1;
            wchar_t bufemail[50];
            GetWindowText(txtboxEmail, bufemail, bufemaillen);
            std::wstring wbufemail = bufemail;
            std::string request = std::string(wbufemail.begin(), wbufemail.end());

            int bufpwlen = GetWindowTextLength(txtboxPassword) + 1;
            wchar_t bufpw[50];
            GetWindowText(txtboxPassword, bufpw, bufpwlen);
            std::wstring wbufpw = bufpw;
            std::string pwstr = std::string(wbufpw.begin(), wbufpw.end());

            if (request.size() == 0) {
                MessageBox(hwnd, L"Email text box is empty", L"Failed to log in", MB_OK | MB_ICONERROR);
                return 0;
            }
            else if (pwstr.size() == 0) {
                MessageBox(hwnd, L"Password text box is empty", L"Failed to log in", MB_OK | MB_ICONERROR);
                return 0;
            }

            int emailindex = EmailSearch(request, UserEmails);

            if (emailindex >= 0) {
                if (UserList[emailindex].pw == pwstr) {
                    LoggedInUser = UserList[emailindex];
                    LoggedIn = true;
                    if (UserList[emailindex].islibrarian == true) {
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
                        DestroyWindow(hwnd);
                        LoggedInLibWindow(hInstance, SW_SHOW);
                    }
                    else {
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
                        DestroyWindow(hwnd);
                        LoggedInWindow(hInstance, SW_SHOW);
                    }
                }
                else if (UserList[emailindex].pw != pwstr) {
                    MessageBox(hwnd, L"Email and Password do not match", L"Failed to log in", MB_OK);
                }
            }
            else {
                MessageBox(hwnd, L"Email does not exist within the system", L"Failed to log in", MB_OK);
            }

        }
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LoggedInWindowProc(HWND mwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 20, 550, 50,
            mwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 20, 50, 50,
            mwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Log out",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 20, 60, 50,
            mwnd, (HMENU)2,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Your Books",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            250, 100, 150, 50,
            mwnd, (HMENU)3,
            NULL, NULL);
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint(mwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Searches if the book is in the system, if it is not found a message box pops up to inform the user
            // If the search result is found, displays the window that displays the book and information about it
            int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
            wchar_t bufsearch[50];
            GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
            std::wstring wbufsearch = bufsearch;
            std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
            int index = BookSearch(searchstr, BookNames);
            if (index < 0) {
                MessageBox(mwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
            }
            else {
                SearchBookResult = BookList[index];
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
                DestroyWindow(mwnd);
                DisplayBook(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Logs out the user and takes them back to the home screen
            User nulluser("null", "null", "null", false, { "null" });
            LoggedInUser = nulluser;
            LoggedIn = false;
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
            DestroyWindow(mwnd);
            LogInWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 3) {
            // Opens the window that displays information about the user
            SearchUserResult = LoggedInUser;
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
            DestroyWindow(mwnd);
            DisplayUser(hInstance, SW_SHOW);
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(mwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LoggedInLibWindowProc(HWND mwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND RadBtnBook;
    static HWND RadBtnUser;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book/User Name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 20, 550, 50,
            mwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 20, 50, 50,
            mwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Add Book",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            300, 100, 150, 50,
            mwnd, (HMENU)2,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Add User",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            300, 175, 150, 50,
            mwnd, (HMENU)3,
            NULL, NULL);
        RadBtnBook = CreateWindow(L"BUTTON", L"Book Search",
            WS_BORDER | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            100, 85, 110, 25,
            mwnd, (HMENU)4,
            NULL, NULL);
        RadBtnUser = CreateWindow(L"BUTTON", L"User Search",
            WS_BORDER | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            100, 120, 110, 25,
            mwnd, (HMENU)5,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Log out",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 20, 60, 50,
            mwnd, (HMENU)6,
            NULL, NULL);
        SendMessage(RadBtnBook, BM_SETCHECK, BST_CHECKED, 1);
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint(mwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Checks which radio button has been selected
            if (SendMessage(RadBtnUser, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                // Searches if the user is in the system, if it is not found a message box pops up to inform the user
                // If the search result is found, displays the window that displays the user and information about it
                int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
                wchar_t bufsearch[50];
                GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
                std::wstring wbufsearch = bufsearch;
                std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
                int index = EmailSearch(searchstr, UserEmails);
                if (index < 0) {
                    MessageBox(mwnd, L"User was not found", L"User Search", MB_OK | MB_ICONINFORMATION);
                }
                else {
                    SearchUserResult = UserList[index];
                    HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
                    DestroyWindow(mwnd);
                    DisplayUser(hInstance, SW_SHOW);
                }
            }
            else {
                // Searches if the book is in the system, if it is not found a message box pops up to inform the user
                // If the search result is found, displays the window that displays the book and information about it
                int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
                wchar_t bufsearch[50];
                GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
                std::wstring wbufsearch = bufsearch;
                std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
                int index = BookSearch(searchstr, BookNames);
                if (index < 0) {
                    MessageBox(mwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
                }
                else {
                    SearchBookResult = BookList[index];
                    HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
                    DestroyWindow(mwnd);
                    DisplayBook(hInstance, SW_SHOW);
                }
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Opens the Add Book Window
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
            DestroyWindow(mwnd);
            AddBookWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 3) {
            // Opens the Addd User Window
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
            DestroyWindow(mwnd);
            AddUserWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 6) {
            // Logs out the user and displays the Log In Window
            User nulluser("null", "null", "null", false, { "null" });
            LoggedInUser = nulluser;
            LoggedIn = false;
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mwnd, GWLP_HINSTANCE);
            DestroyWindow(mwnd);
            LogInWindow(hInstance, SW_SHOW);
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(mwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK AddUserWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND txtboxName;
    static HWND txtboxEmail;
    static HWND txtboxPassword;
    static HWND cbxIsLib;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 20, 550, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 20, 50, 50,
            hwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Back",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 10, 50, 50,
            hwnd, (HMENU)2,
            NULL, NULL);
        txtboxName = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            225, 100, 500, 50,
            hwnd, NULL,
            NULL, NULL);
        txtboxEmail = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            225, 175, 500, 50,
            hwnd, (HMENU)3,
            NULL, NULL);
        txtboxPassword = CreateWindow(L"EDIT", L"",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            225, 250, 500, 50,
            hwnd, (HMENU)4,
            NULL, NULL);
        cbxIsLib = CreateWindow(L"COMBOBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS,
            225, 325, 100, 75,
            hwnd, (HMENU)5,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Add User",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            375, 375, 150, 50,
            hwnd, (HMENU)6,
            NULL, NULL);

        SendMessage(cbxIsLib, CB_ADDSTRING, NULL, (LPARAM)L"True");
        SendMessage(cbxIsLib, CB_ADDSTRING, NULL, (LPARAM)L"False");
        SendMessage(cbxIsLib, CB_SETCURSEL, (WPARAM)1, NULL);
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint2(hwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Searches if the book is in the system, if it is not found a message box pops up to inform the user
            // If the search result is found, displays the window that displays the book and information about it
            int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
            wchar_t bufsearch[50];
            GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
            std::wstring wbufsearch = bufsearch;
            std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
            int index = BookSearch(searchstr, BookNames);
            if (index < 0) {
                MessageBox(hwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
            }
            else {
                SearchBookResult = BookList[index];
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                DisplayBook(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Goes back to the last window
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
            DestroyWindow(hwnd);
            LoggedInLibWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 6) {
            // Takes the text from each of the text boxes and then checks whether there is text within the text box
            // If there is no text, displays a message box to inform the user that there is no text in the text box
            // If every text box has text, creates a new user and then puts that into the correct place within the vectors
            // Rewrites the text file containing user information
            int bufNameLen = GetWindowTextLength(txtboxName) + 1;
            wchar_t bufName[50];
            GetWindowText(txtboxName, bufName, bufNameLen);
            std::wstring wbufName = bufName;
            std::string strname = std::string(wbufName.begin(), wbufName.end());

            int bufEmailLen = GetWindowTextLength(txtboxEmail) + 1;
            wchar_t bufEmail[50];
            GetWindowText(txtboxEmail, bufEmail, bufEmailLen);
            std::wstring wbufEmail = bufEmail;
            std::string stremail = std::string(wbufEmail.begin(), wbufEmail.end());

            int bufPwlen = GetWindowTextLength(txtboxPassword) + 1;
            wchar_t bufPw[50];
            GetWindowText(txtboxPassword, bufPw, bufPwlen);
            std::wstring wbufPw = bufPw;
            std::string strpw = std::string(wbufPw.begin(), wbufPw.end());

            if (strname.size() > 0) {
                if (stremail.size() > 0) {
                    if (strpw.size() > 0) {
                        if (MessageBox(hwnd, L"Are you sure you want to add the user\nAre you sure all the details are correct?\nUser will be created and added to the system immediately"
                            , L"Confirmation to Add User", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                            if (EmailSearch(stremail, UserEmails) != -1) {
                                MessageBox(hwnd, L"User already exists", L"User Creation", MB_OK | MB_ICONINFORMATION);
                            }
                            else {
                                bool inislibbool;
                                std::string inislib;
                                if (SendMessage(cbxIsLib, CB_GETCURSEL, 0, 0) == 0) {
                                    inislibbool = true;
                                    inislib = "true";
                                }
                                else {
                                    inislibbool = false;
                                    inislib = "false";
                                }
                                User tempuser(strname, stremail, strpw, inislibbool, { "null" });
                                UserEmails.push_back(stremail);
                                std::sort(UserEmails.begin(), UserEmails.end());
                                int newuserindex = EmailSearch(stremail, UserEmails);
                                UserList.insert(UserList.begin() + newuserindex, tempuser);

                                WriteUserFile(UserList);
                            }
                        }
                    }
                    else {
                        MessageBox(hwnd, L"Password text box is empty", L"User Creation", MB_OK | MB_ICONEXCLAMATION);
                    }
                }
                else {
                    MessageBox(hwnd, L"Email text box is empty", L"User Creation", MB_OK | MB_ICONEXCLAMATION);
                }
            }
            else {
                MessageBox(hwnd, L"Name text box is empty", L"User Creation", MB_OK | MB_ICONEXCLAMATION);
            }
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK AddBookWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static std::string strinputimage;
    static HWND txtboxName;
    static HWND txtboxAuthor;
    static HWND txtboxGenre;
    static HWND txtboxDesc;
    static HWND txtboxMoreinfo;
    static HWND btnAddBook;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 15, 550, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 15, 50, 50,
            hwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Back",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 15, 50, 50,
            hwnd, (HMENU)2,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Add Image",
            BS_DEFPUSHBUTTON | BS_BITMAP | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 75, 75, 150,
            hwnd, (HMENU)3,
            NULL, NULL);
        txtboxName = CreateWindow(L"EDIT", NULL,
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            250, 75, 475, 30,
            hwnd, NULL,
            NULL, NULL);
        txtboxAuthor = CreateWindow(L"EDIT", NULL,
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            250, 130, 475, 30,
            hwnd, NULL,
            NULL, NULL);
        txtboxGenre = CreateWindow(L"EDIT", NULL,
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            250, 185, 475, 30,
            hwnd, NULL,
            NULL, NULL);
        txtboxDesc = CreateWindow(L"EDIT", NULL,
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            250, 240, 475, 50,
            hwnd, NULL,
            NULL, NULL);
        txtboxMoreinfo = CreateWindow(L"EDIT", NULL,
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            250, 315, 475, 50,
            hwnd, NULL,
            NULL, NULL);
        btnAddBook = CreateWindow(L"BUTTON", L"Add Book",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            325, 390, 150, 50,
            hwnd, (HMENU)4,
            NULL, NULL);
        strinputimage = "null";
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint3(hwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Searches if the book is in the system, if it is not found a message box pops up to inform the user
            // If the search result is found, displays the window that displays the book and information about it
            int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
            wchar_t bufsearch[50];
            GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
            std::wstring wbufsearch = bufsearch;
            std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
            int index = BookSearch(searchstr, BookNames);
            if (index < 0) {
                MessageBox(hwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
            }
            else {
                SearchBookResult = BookList[index];
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                DisplayBook(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Goes back to the last window
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
            DestroyWindow(hwnd);
            LoggedInLibWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 3) {
            // Creates and displays an open file dialog box which only allows users to select bitmaps
            // The string of the image is then stored inside of a variable that is used when creating the book
            HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                COINIT_DISABLE_OLE1DDE);
            if (SUCCEEDED(hr))
            {
                IFileOpenDialog* pFileOpen;
                hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                    IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

                if (SUCCEEDED(hr))
                {
                    COMDLG_FILTERSPEC rgSpec[] = {{ L"Bitmaps", L"*.bmp"}};
                    hr = pFileOpen->SetFileTypes(1, rgSpec);

                    if(SUCCEEDED(hr)) {
                    hr = pFileOpen->Show(NULL);

                        if (SUCCEEDED(hr)) {
                            IShellItem* pItem;
                            hr = pFileOpen->GetResult(&pItem);

                            if (SUCCEEDED(hr)) {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                if (SUCCEEDED(hr))
                                {
                                    size_t filelength = wcslen(pszFilePath);
                                    char temparr[256];
                                    wcstombs_s(&filelength, temparr, 256, pszFilePath, wcslen(pszFilePath));
                                    strinputimage = temparr;
                                    CoTaskMemFree(pszFilePath);
                                }
                                pItem->Release();
                            }
                        }
                    }
                    pFileOpen->Release();
                }
                CoUninitialize();
            }
        }
        else if (LOWORD(wParam) == 4) {
            // Takes the text from each of the text boxes and then checks whether there is text within the text box
            // If there is no text, displays a message box to inform the user that there is no text in the text box
            // If every text box has text, creates a new book and then puts that into the correct place within the vectors
            // Rewrites the text file containing book information
            int bufNameLen = GetWindowTextLength(txtboxName) + 1;
            wchar_t bufName[50];
            GetWindowText(txtboxName, bufName, bufNameLen);
            std::wstring wbufName = bufName;
            std::string strname = std::string(wbufName.begin(), wbufName.end());

            int bufAuthorLen = GetWindowTextLength(txtboxAuthor) + 1;
            wchar_t bufAuthor[50];
            GetWindowText(txtboxAuthor, bufAuthor, bufAuthorLen);
            std::wstring wbufAuthor = bufAuthor;
            std::string strauthor = std::string(wbufAuthor.begin(), wbufAuthor.end());

            int bufGenreLen = GetWindowTextLength(txtboxGenre) + 1;
            wchar_t bufGenre[50];
            GetWindowText(txtboxGenre, bufGenre, bufGenreLen);
            std::wstring wbufGenre = bufGenre;
            std::string strgenre = std::string(wbufGenre.begin(), wbufGenre.end());

            int bufDescLen = GetWindowTextLength(txtboxDesc) + 1;
            wchar_t bufDesc[50];
            GetWindowText(txtboxDesc, bufDesc, bufDescLen);
            std::wstring wbufDesc = bufDesc;
            std::string strdesc = std::string(wbufDesc.begin(), wbufDesc.end());

            int bufMoreInfoLen = GetWindowTextLength(txtboxMoreinfo) + 1;
            wchar_t bufMoreInfo[50];
            GetWindowText(txtboxMoreinfo, bufMoreInfo, bufMoreInfoLen);
            std::wstring wbufMoreInfo = bufMoreInfo;
            std::string strmoreinfo = std::string(wbufMoreInfo.begin(), wbufMoreInfo.end());

            if (strname.size() > 0) {
                if (strauthor.size() > 0) {
                    if (strgenre.size() > 0) {
                        if (strdesc.size() > 0) {
                            if (strmoreinfo.size() > 0) {
                                if (MessageBox(hwnd, L"Are you sure you want to add the book\nAre you sure all the details are correct?\nBook will be created and added to the system immediately"
                                    , L"Confirmation to Add Book", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                                    if (BookSearch(strname, BookNames) != -1) {
                                        MessageBox(hwnd, L"Book already exists", L"Book Creation", MB_OK | MB_ICONINFORMATION);
                                    }
                                    else {
                                        time_t rawtime;
                                        tm timeinfo;

                                        time(&rawtime);
                                        localtime_s(&timeinfo, &rawtime);

                                        Book tempbook(strname, strauthor, strgenre, strdesc, strmoreinfo, timeinfo, false, "null", strinputimage);
                                        BookNames.push_back(strname);
                                        std::sort(BookNames.begin(), BookNames.end());
                                        int newbookindex = BookSearch(strname, BookNames);
                                        BookList.insert(BookList.begin() + newbookindex, tempbook);

                                        WriteBookFile(BookList);
                                    }
                                }
                            }
                            else {
                                MessageBox(hwnd, L"More info text box is empty", L"Book Creation", MB_OK | MB_ICONEXCLAMATION);
                            }
                        }
                        else {
                            MessageBox(hwnd, L"Description text box is empty", L"Book Creation", MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    else {
                        MessageBox(hwnd, L"Genre text box is empty", L"Book Creation", MB_OK | MB_ICONEXCLAMATION);
                    }
                }
                else {
                    MessageBox(hwnd, L"Author text box is empty", L"Book Creation", MB_OK | MB_ICONEXCLAMATION);
                }
            }
            else {
                MessageBox(hwnd, L"Name text box is empty", L"Book Creation", MB_OK | MB_ICONEXCLAMATION);

            }
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DisplayBookProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND btnimg;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 15, 550, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 15, 50, 50,
            hwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Back",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 15, 50, 50,
            hwnd, (HMENU)2,
            NULL, NULL);
        btnimg = CreateWindow(L"BUTTON", NULL,
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD | BS_BITMAP,
            10, 80, 150, 200,
            hwnd, NULL,
            NULL, 0);
        if (SearchBookResult.borrowed == false && LoggedInUser.islibrarian == false) {
            CreateWindow(L"BUTTON", L"Borrow Book",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                675, 80, 100, 50,
                hwnd, (HMENU)3,
                NULL, NULL);
        }
        else if (LoggedInUser.islibrarian == true) {
            CreateWindow(L"BUTTON", L"Edit Book",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                675, 110, 100, 50,
                hwnd, (HMENU)4,
                NULL, NULL);
            CreateWindow(L"BUTTON", L"Remove Book",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                675, 180, 100, 50,
                hwnd, (HMENU)5,
                NULL, NULL);
        }

        else if (SearchBookResult.borrowed == true) {
            for (size_t i = 0; i < LoggedInUser.books.size(); i++) {
                if(LoggedInUser.books[i] == SearchBookResult.name) {
                    CreateWindow(L"BUTTON", L"Extend Book",
                        BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                        675, 80, 100, 50,
                        hwnd, (HMENU)6,
                        NULL, NULL);  
                    CreateWindow(L"BUTTON", L"Return Book",
                        BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                        675, 80, 100, 50,
                        hwnd, (HMENU)7,
                        NULL, NULL);
                }
            }
        }

        // Checks that the string is the location of a bitmap, if it is a bitmap displays the bitmap on the button
        // If the string does not containi the location of a bitmap, displays a placeholder image
        std::string flippedstr = SearchBookResult.imagepath;
        int n = flippedstr.length();
        for (int i = 0; i < n / 2; i++) {
            std::swap(flippedstr[i], flippedstr[n - i - 1] );
        }
        if (flippedstr[0] == 'p' && flippedstr[1] == 'm' && flippedstr[2] == 'b' && flippedstr[3] == '.') {
            std::wstring tempwstring = std::wstring(SearchBookResult.imagepath.begin(), SearchBookResult.imagepath.end());
            LPCWSTR BitmapFileName = tempwstring.c_str();
            HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SendMessage(btnimg, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
        }
        else {
            LPCWSTR BitmapFileName = L"BookImages\\duckbmp.bmp";
            HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SendMessage(btnimg, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
        }
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint4(hwnd, SearchBookResult, UserEmails, LoggedInUser);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Searches if the book is in the system, if it is not found a message box pops up to inform the user
            // If the search result is found, displays the window that displays the book and information about it
            int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
            wchar_t bufsearch[50];
            GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
            std::wstring wbufsearch = bufsearch;
            std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
            int index = BookSearch(searchstr, BookNames);
            if (index < 0) {
                MessageBox(hwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
            }
            else {
                SearchBookResult = BookList[index];
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                DisplayBook(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Goes back to the last window, checks to see whether they are a librarian to ensure they go to the right place
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            DestroyWindow(hwnd);
            if (LoggedInUser.islibrarian == true) {
                LoggedInLibWindow(hInstance, SW_SHOW);
            }
            else {
                LoggedInWindow(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 3) {
            // Sets that status of the book to being displayed and puts the book into the borrowed books attribute of the user class
            LoggedInUser.books.push_back(SearchBookResult.name);
            int userindex = EmailSearch(LoggedInUser.email, UserEmails);
            UserList[userindex].books.push_back(SearchBookResult.name);
            int bookindex = BookSearch(SearchBookResult.name, BookNames);
            BookList[bookindex].borrowed = true;
            BookList[bookindex].borrowedusers = LoggedInUser.email;
        }
        else if (LOWORD(wParam) == 4) {
            // Deletes the book and then sends the user to the Add Book Window to allow them to edit/fix/create the user
            if (MessageBox(hwnd, L"This will delete the book, are you sure you want to continute?",
                L"Edit Book", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                int bookindex = BookSearch(SearchBookResult.name, BookNames);
                BookNames.erase(BookNames.begin() + bookindex);
                BookList.erase(BookList.begin() + bookindex);
                WriteBookFile(BookList);

                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                AddBookWindow(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 5) {
            // Deletes the book from vectors that contain book information and rewrites the book information file so that it is no longer in the database
            int bookindex = BookSearch(SearchBookResult.name, BookNames);
            BookNames.erase(BookNames.begin() + bookindex);
            BookList.erase(BookList.begin() + bookindex);
            WriteBookFile(BookList);

            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            DestroyWindow(hwnd);
            LoggedInLibWindow(hInstance, SW_SHOW);
        }
        else if (LOWORD(wParam) == 6) {
            // Extends the borrowing duration of the book
            SearchBookResult.duedate.tm_mon++;
            BookList[BookSearch(SearchBookResult.name, BookNames)].duedate.tm_mon++;
            WriteBookFile(BookList);
            MessageBox(hwnd, L"Due date has been extended by a month", L"Extend Book", MB_OK);
        }
        else if (LOWORD(wParam) == 7) {
            // Sets the books status to returned and removes the book from thet user's borrowed books
            SearchBookResult.borrowed = false;
            SearchBookResult.borrowedusers = true;
            int bookindex = BookSearch(SearchBookResult.name, BookNames);
            BookList[bookindex].borrowed = false;
            BookList[bookindex].borrowedusers = "null";
            for (size_t i = 0; i < LoggedInUser.books.size(); i++) {
                if (LoggedInUser.books[i] == SearchBookResult.name) {
                    LoggedInUser.books[i].erase();
                    int userindex = EmailSearch(LoggedInUser.name, UserEmails);
                    UserList[userindex].books[i].erase();
                }
            }
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DisplayUserProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int pagenum = 0;
    static HWND btnimgarr[4];
    switch (uMsg)
    {
    case WM_CREATE:
    {
        txtboxSearch = CreateWindow(L"EDIT", L"Book name",
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            100, 15, 550, 50,
            hwnd, NULL,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Enter",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            675, 15, 50, 50,
            hwnd, (HMENU)1,
            NULL, NULL);
        CreateWindow(L"BUTTON", L"Back",
            BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
            10, 15, 50, 50,
            hwnd, (HMENU)2,
            NULL, NULL);
        if (LoggedInUser.islibrarian == true) {
            CreateWindow(L"BUTTON", L"Remove User",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                600, 100, 125, 25,
                hwnd, (HMENU)11,
                NULL, NULL);
            CreateWindow(L"BUTTON", L"Change Email",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                600, 100, 125, 25,
                hwnd, (HMENU)3,
                NULL, NULL);
            CreateWindow(L"BUTTON", L"Change Password",
                BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                600, 130, 125, 25,
                hwnd, (HMENU)4,
                NULL, NULL);
        }
        if (SearchUserResult.islibrarian == true) {
            return 0;
        }
        else if (SearchUserResult.islibrarian == false) {
            if (SearchUserResult.books.size() == 1) {
                if (SearchUserResult.books[0] == "null") {
                    return 0;
                }
            }
            else if (SearchUserResult.books.size() <= 4) {
                for (size_t i = 0; i < SearchUserResult.books.size(); i++) {
                    btnimgarr[i] = CreateWindow(L"BUTTON", NULL,
                        WS_BORDER | WS_VISIBLE | WS_CHILD | BS_BITMAP,
                        (i * 150) + 100, 200, 125, 175,
                        hwnd, (HMENU)(7 + i),
                        NULL, NULL);
                }
            }
            else if (SearchUserResult.books.size() > 4) {
                CreateWindow(L"BUTTON", L"Previous page",
                    BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                    50, 400, 125, 40,
                    hwnd, (HMENU)5,
                    NULL, NULL);
                CreateWindow(L"BUTTON", L"Next page",
                    BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
                    500, 400, 125, 40,
                    hwnd, (HMENU)6,
                    NULL, NULL);
                for (size_t i = 0; i < 4; i++) {
                    btnimgarr[i] = CreateWindow(L"BUTTON", NULL,
                        WS_BORDER | WS_VISIBLE | WS_CHILD | BS_BITMAP,
                        (i * 150) + 50, 200, 125, 175,
                        hwnd, (HMENU)(7 + i),
                        NULL, NULL);
                }
            }
        }
        
        // Checks that the string is the location of a bitmap, if it is a bitmap displays the bitmap on the button
        // If the string does not containi the location of a bitmap, displays a placeholder image
        int bookindex = -1;
        for (int i = 0; i < SearchUserResult.books.size() && i < 4; i++) {
            bookindex = BookSearch(SearchUserResult.books[i], BookNames);
            std::string flippedstr = BookList[bookindex].imagepath;
            int n = flippedstr.length();
            for (int k = 0; k < n / 2; k++) {
                std::swap(flippedstr[k], flippedstr[n - k - 1]);
            }
            if (flippedstr[0] == 'p' && flippedstr[1] == 'm' && flippedstr[2] == 'b' && flippedstr[3] == '.') {
                std::wstring tempwstring = std::wstring(BookList[bookindex].imagepath.begin(), BookList[bookindex].imagepath.end());
                LPCWSTR BitmapFileName = tempwstring.c_str();
                HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
            }
            else {
                LPCWSTR BitmapFileName = L"BookImages\\duckbmp.bmp";
                HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
            }
        }
        return 0;
    }
    case WM_PAINT:
    {
        OnPaint5(hwnd, SearchUserResult);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) {
            // Searches if the book is in the system, if it is not found a message box pops up to inform the user
            // If the search result is found, displays the window that displays the book and information about it
            int bufsearchlen = GetWindowTextLength(txtboxSearch) + 1;
            wchar_t bufsearch[50];
            GetWindowText(txtboxSearch, bufsearch, bufsearchlen);
            std::wstring wbufsearch = bufsearch;
            std::string searchstr = std::string(wbufsearch.begin(), wbufsearch.end());
            int index = BookSearch(searchstr, BookNames);
            if (index < 0) {
                MessageBox(hwnd, L"Book was not found", L"Book Search", MB_OK | MB_ICONINFORMATION);
            }
            else {
                pagenum = 0;
                SearchBookResult = BookList[index];
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                DisplayBook(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 2) {
            // Goes back to the last window, and checks whether they are a librarian or user to send them to the correct place
            pagenum = 0;
            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            DestroyWindow(hwnd);
            if (LoggedInUser.islibrarian == true) {
                LoggedInLibWindow(hInstance, SW_SHOW);
            }
            else {
                LoggedInWindow(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 3) {
            // Deletes the user and then displays the Add User Window which allows them to  // Takes the text from each of the text boxes and then checks whether there is text within the text box
            // If there is no text, displays a message box to inform the user that there is no text in the text box
            // If every text box has text, creates a new user and then puts that into the correct place within the vectors
            // Rewrites the text file containing user information
            if (MessageBox(hwnd, L"This will delete the user, are you sure you want to continute?",
                L"Edit User", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                int userindex = EmailSearch(SearchUserResult.email, UserEmails);
                UserEmails.erase(UserEmails.begin() + userindex);
                UserList.erase(UserList.begin() + userindex);
                WriteUserFile(UserList);

                pagenum = 0;
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                AddUserWindow(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 4) {
            // Deletes the user and rewrites the user information window and then displays the Add User Window so that they can add/fix the user
            if (MessageBox(hwnd, L"This will delete the user, are you sure you want to continute?",
                L"Edit User", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                int userindex = EmailSearch(SearchUserResult.email, UserEmails);
                UserEmails.erase(UserEmails.begin() + userindex);
                UserList.erase(UserList.begin() + userindex);
                WriteUserFile(UserList);

                pagenum = 0;
                HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                DestroyWindow(hwnd);
                AddUserWindow(hInstance, SW_SHOW);
            }
        }
        else if (LOWORD(wParam) == 5) {
            // Changes the images displayed on all of the buttons to be the previous 4 books in the array
            if (pagenum != 0) {
                pagenum--;
                int bookindex = -1;
                for (int i = 0; i < SearchUserResult.books.size() && i < 4; i++) {
                    bookindex = BookSearch(SearchUserResult.books[i + (pagenum * 4)], BookNames);
                    std::string flippedstr = BookList[bookindex].imagepath;
                    int n = flippedstr.length();
                    for (int k = 0; k < n / 2; k++) {
                        std::swap(flippedstr[k], flippedstr[n - k - 1]);
                    }
                    if (flippedstr[0] == 'p' && flippedstr[1] == 'm' && flippedstr[2] == 'b' && flippedstr[3] == '.') {
                        std::wstring tempwstring = std::wstring(BookList[bookindex].imagepath.begin(), BookList[bookindex].imagepath.end());
                        LPCWSTR BitmapFileName = tempwstring.c_str();
                        HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                        SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
                    }
                    else {
                        LPCWSTR BitmapFileName = L"BookImages\\duckbmp.bmp";
                        HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                        SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
                    }
                }
            }
            RECT rect;
            GetClientRect(hwnd, &rect);
            InvalidateRect(hwnd, &rect, TRUE);
        }
        else if (LOWORD(wParam) == 6) {
            // Changes the images displayed on all of the buttons to be the next 4 books in the array
            if (pagenum < (SearchUserResult.books.size() / 4)) {
                pagenum++;
                int bookindex = -1;
                for (int i = 0; i < SearchUserResult.books.size() && i < 4; i++) {
                    if (i + (pagenum * 4) >= SearchUserResult.books.size()) {
                        LPCWSTR BitmapFileName = L"null\\null.bmp";
                        HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                        SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
                    }
                    else {
                        bookindex = BookSearch(SearchUserResult.books[i + (pagenum * 4)], BookNames);
                        std::string flippedstr = BookList[bookindex].imagepath;
                        int n = flippedstr.length();
                        for (int k = 0; k < n / 2; k++) {
                            std::swap(flippedstr[k], flippedstr[n - k - 1]);
                        }
                        if (flippedstr[0] == 'p' && flippedstr[1] == 'm' && flippedstr[2] == 'b' && flippedstr[3] == '.') {
                            std::wstring tempwstring = std::wstring(BookList[bookindex].imagepath.begin(), BookList[bookindex].imagepath.end());
                            LPCWSTR BitmapFileName = tempwstring.c_str();
                            HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                            SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
                        }
                        else {
                            LPCWSTR BitmapFileName = L"BookImages\\duckbmp.bmp";
                            HANDLE hbitmap = LoadImage(NULL, BitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                            SendMessage(btnimgarr[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
                        }
                    }
                }
            }
            RECT rect;
            GetClientRect(hwnd, &rect);
            InvalidateRect(hwnd, &rect, TRUE);
        }
        else if (LOWORD(wParam) == 11) {
        // Checks whether the user has any books boorrowed, if they do all of them are set to unborrowed
        // Deletes the user from all vectors and rewrites the text file so that it is no longer in the database
            int userindex = EmailSearch(SearchUserResult.email, UserEmails);
            for (size_t i = 0; i < UserList[userindex].books.size(); i++) {
                int bookindex = -1;
                bookindex = BookSearch(UserList[userindex].books[i], BookNames);
                BookList[i].borrowed = false;
                BookList[i].borrowedusers = "null";
            }
            UserEmails.erase(UserEmails.begin() + userindex);
            UserList.erase(UserList.begin() + userindex);
            WriteUserFile(UserList);

            HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            DestroyWindow(hwnd);
            LoggedInLibWindow(hInstance, SW_SHOW);
        }
        else {
        // Checks what page of books are beinng currently displayed and then displays the book
            switch (LOWORD(wParam)) {
            case 7:
            {
                if ((pagenum * 4) < SearchUserResult.books.size()) {
                    int bookindex = BookSearch(SearchUserResult.books[(pagenum * 4)], BookNames);
                    if (bookindex != -1) {
                        SearchBookResult = BookList[bookindex];
                        pagenum = 0;
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                        DestroyWindow(hwnd);
                        DisplayBook(hInstance, SW_SHOW);
                    }
                }
                break;
            }
            case 8:
            {
                if ((pagenum * 4) + 1 < SearchUserResult.books.size()) {
                    int bookindex = BookSearch(SearchUserResult.books[(pagenum * 4) + 1], BookNames);
                    if (bookindex != -1) {
                        SearchBookResult = BookList[bookindex];
                        pagenum = 0;
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                        DestroyWindow(hwnd);
                        DisplayBook(hInstance, SW_SHOW);
                    }
                }
                break;
            }
            case 9:
            {
                if ((pagenum * 4) + 2 < SearchUserResult.books.size()) {
                    int bookindex = BookSearch(SearchUserResult.books[(pagenum * 4) + 2], BookNames);
                    if (bookindex != -1) {
                        SearchBookResult = BookList[bookindex];
                        pagenum = 0;
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                        DestroyWindow(hwnd);
                        DisplayBook(hInstance, SW_SHOW);
                    }
                }
                break;
            }
            case 10:
            {
                if ((pagenum * 4) + 3 < SearchUserResult.books.size()) {
                    int bookindex = BookSearch(SearchUserResult.books[(pagenum * 4) + 3], BookNames);
                    if (bookindex != -1) {
                        SearchBookResult = BookList[bookindex];
                        pagenum = 0;
                        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
                        DestroyWindow(hwnd);
                        DisplayBook(hInstance, SW_SHOW);
                    }
                }
                break;
            }
            }
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}