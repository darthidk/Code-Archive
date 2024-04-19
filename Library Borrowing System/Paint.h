// Paint header file
// Contains all functions related to painting the window

// Input: Window to paint
// Output: Paints the window white
void OnPaint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint
    FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
    EndPaint(hwnd, &ps);
}

// Input: Window to paint
// Output: Paints the window white and displays text for adding users
void OnPaint2(HWND hwnd) {
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint
    FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));

    HFONT hFont = CreateFont(
        25, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );

    GetClientRect(hwnd, &rect);
    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);

    rect.left = 50;
    rect.top = 100;
    LPCWSTR text = L"Name:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 175;
    text = L"Email:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 250;
    text = L"Password:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 325;
    text = L"Librarian:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    EndPaint(hwnd, &ps);
}

// Input: Window to paint
// Output: Paints the window white and displays text for adding books
void OnPaint3(HWND hwnd) {
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint
    FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));

    HFONT hFont = CreateFont(
        25, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );

    GetClientRect(hwnd, &rect);
    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);

    rect.left = 100;
    rect.top = 75;
    LPCWSTR text = L"Title:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 130;
    text = L"Author:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 185;
    text = L"Genre:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 240;
    text = L"Description:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    rect.top = 315;
    text = L"More info:";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    EndPaint(hwnd, &ps);
}

// Input: Window to paint
// Output: Paints the window white and displays text for user/books the user has borrowed
void OnPaint4(HWND hwnd, Book SearchResult, std::vector<std::string> UserEmails, User LoggedInUser) {
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint
    FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));

    HFONT titleFont = CreateFont(
        50, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    HFONT authorFont = CreateFont(
        40, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    HFONT genreFont = CreateFont(
        35, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    HFONT descFont = CreateFont(
        30, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    HFONT moreinfoFont = CreateFont(
        30, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    HFONT duedateFont = CreateFont(
        25, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );
    GetClientRect(hwnd, &rect);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);
    std::wstring wtext;

    SelectObject(hdc, titleFont);
    rect.left = 180;
    rect.right = 650;
    rect.top = 80;
    wtext = std::wstring(SearchResult.name.begin(), SearchResult.name.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP);

    if (SearchResult.borrowed == true) {
        if (EmailSearch(SearchResult.borrowedusers, UserEmails) == -1) {
            // ?
        }
    }
    bool userborrowed = false;
    if (SearchResult.borrowed == true) {
        for (size_t i = 0; i < LoggedInUser.books.size(); i++) {
            if (LoggedInUser.books[i] == SearchResult.name) {
                userborrowed = true;
                break;
            }
        }
        if (userborrowed == false) {
            SelectObject(hdc, duedateFont);
            rect.left = 675;
            rect.right = 1000;
            std::string tempstr;

            tempstr = "Borrowed until ";
            char duedatestr[9];
            strftime(duedatestr, 9, "%D", &SearchResult.duedate);
            tempstr.append(duedatestr);
            wtext = std::wstring(tempstr.begin(), tempstr.end());
            DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);
        }
    }
    

    SelectObject(hdc, authorFont);
    rect.left = 180;
    rect.right = 650;
    rect.top = 150;
    wtext = std::wstring(SearchResult.author.begin(), SearchResult.author.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);

    SelectObject(hdc, genreFont);
    rect.top = 210;
    wtext = std::wstring(SearchResult.genre.begin(), SearchResult.genre.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);

    SelectObject(hdc, descFont);
    rect.top = 275;
    rect.bottom = 365;
    if (SearchResult.description.size() <= 60) {
        wtext = std::wstring(SearchResult.description.begin(), SearchResult.description.end());
        DrawText(hdc, wtext.c_str(), -1, &rect, NULL);
    }
    else {
        std::string temporgstr = SearchResult.description;
        for (size_t i = 1; i < temporgstr.size() / 35; i++) {
            temporgstr.insert(i * 35, "\n");
        }
        wtext = std::wstring(temporgstr.begin(), temporgstr.end());
        DrawText(hdc, wtext.c_str(), -1, &rect, NULL);
    }

    SelectObject(hdc, moreinfoFont);
    rect.top = 385;
    rect.bottom = 445;
    
    if (SearchResult.description.size() <= 60) {
        wtext = std::wstring(SearchResult.moreinfo.begin(), SearchResult.moreinfo.end());
        DrawText(hdc, wtext.c_str(), -1, &rect, NULL);
    }
    else {
        std::string temporgstr = SearchResult.moreinfo;
        for (size_t i = 1; i < temporgstr.size() / 35; i++) {
            temporgstr.insert(i * 35, "\n");
        }
        wtext = std::wstring(temporgstr.begin(), temporgstr.end());
        DrawText(hdc, wtext.c_str(), -1, &rect, NULL);
    }

    EndPaint(hwnd, &ps);
}

// Input: Window to paint
// Output: Paints the window white and displays text to display a book
void OnPaint5(HWND hwnd, User SearchResult) {
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint
    FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
    HFONT nameFont = CreateFont(
        25, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH,
        TEXT(" ")
    );

    GetClientRect(hwnd, &rect);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);
    std::wstring wtext;
    LPCWSTR text;

    SelectObject(hdc, nameFont);
    rect.left = 100;
    rect.right = 650;
    rect.top = 70;
    text = L"Name: ";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE);
    rect.left = 175;
    wtext = std::wstring(SearchResult.name.begin(), SearchResult.name.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);

    rect.left = 100;
    rect.top = 100;
    text = L"Email: ";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE);
    rect.left = 175;
    wtext = std::wstring(SearchResult.email.begin(), SearchResult.email.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);

    rect.top = 135;
    rect.bottom = 365;
    rect.left = 100;
    text = L"Password: ";
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE);
    rect.left = 215;
    wtext = std::wstring(SearchResult.pw.begin(), SearchResult.pw.end());
    DrawText(hdc, wtext.c_str(), -1, &rect, DT_SINGLELINE);

    EndPaint(hwnd, &ps);
}