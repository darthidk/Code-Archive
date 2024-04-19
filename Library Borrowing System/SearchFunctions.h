// Header file containing search binary search functions used to search for an item in an array

// Takes in a vector with the name of books and a string to search for
// If the string is found within the vector, return the index at which it was found at
// If it is not found it returns -1

int BookSearch(std::string request, std::vector<std::string> BookNames) {
    char strfirstletter = request[0];
    int low = 0;
    int high = BookNames.size() - 1;
    int mid = (low + high) / 2;
    bool found = false;
    int i = 0;
    int index = -1;

    while (found == false && low <= high) {
        if (BookNames[low][0] == strfirstletter) {
            if (BookNames[low] == request) {
                found = true;
                index = low;
                break;
            }
            else if (BookNames[low] != request) {
                int i = 0;
                while (BookNames[low + i][0] == strfirstletter) {
                    if (BookNames[low + i] == request) {
                        found = true;
                        index = low + i;
                        break;
                    }
                    else {
                        i++;
                    }
                }
                low = high + 1;
                break;
            }
        }
        else if (BookNames[high][0] == strfirstletter) {
            if (BookNames[high] == request) {
                found = true;
                index = high;
                break;
            }
            else if (BookNames[high] != request) {
                int i = 0;
                while (BookNames[high - i][0] == strfirstletter) {
                    if (BookNames[high - i] == request) {
                        found = true;
                        index = high - i;
                        break;
                    }
                    else {
                        i++;
                    }
                }
                low = high + 1;
                break;
            }
        }
        else if (BookNames[mid][0] == strfirstletter) {
            if (BookNames[mid] == request) {
                found = true;
                index = mid;
                break;
            }
            else if (BookNames[mid] != request) {
                int i = 0;
                while (BookNames[mid + i][0] == strfirstletter) {
                    if (BookNames[mid + i] == request) {
                        found = true;
                        index = mid + i;
                        break;
                    }
                    else { i++; }
                }
                i = 0;
                while (BookNames[mid - i][0] == strfirstletter) {
                    if (BookNames[mid - i] == request) {
                        found = true;
                        index = mid - i;
                        break;
                    }
                    else { i++; }
                }
                low = high + 1;
                break;
            }
        }
        else {
            if (BookNames[mid][0] < strfirstletter) {
                low = mid + 1;
                mid = (low + high) / 2;
            }
            else if (BookNames[mid][0] > strfirstletter) {
                high = mid - 1;
                mid = (low + high) / 2;
            }
        }
    }
    return index;
}

// Takes in a vector with the name of users and a string to search for
// If the string is found within the vector, return the index at which it was found at
// If it is not found it returns -1

int EmailSearch(std::string request, std::vector<std::string> UserEmails) {
    char strfirstletter = request[0];
    int low = 0;
    int high = UserEmails.size() - 1;
    int mid = (low + high) / 2;
    std::sort(UserEmails.begin(), UserEmails.end());
    bool found = false;
    int emailindex = -1;

    while (found == false && low <= high) {
        if (UserEmails[low][0] >= strfirstletter) {
            if (UserEmails[low][0] == strfirstletter) {
                if (UserEmails[low] == request) {
                    found = true;
                    emailindex = low;
                    return emailindex;
                }
                else if (UserEmails[low] != request) {
                    int i = 0;
                    while (UserEmails[low + i][0] == strfirstletter) {
                        if (UserEmails[low + i] == request) {
                            found = true;
                            emailindex = low + i;
                            return emailindex;
                        }
                        else {
                            i++;
                        }
                    }
                    low = high + 1;
                    return emailindex;
                }
            }
            else if (UserEmails[low][0] > strfirstletter) {
                return emailindex;
            }
        }
        else if (UserEmails[high][0] <= strfirstletter) {
            if (UserEmails[high][0] == strfirstletter) {
                if (UserEmails[high] == request) {
                    found = true;
                    emailindex = high;
                    return emailindex;
                }
                else if (UserEmails[high] != request) {
                    int i = 0;
                    while (UserEmails[high - i][0] == strfirstletter) {
                        if (UserEmails[high - i] == request) {
                            found = true;
                            emailindex = high - i;
                            return emailindex;
                        }
                        else {
                            i++;
                        }
                    }
                    low = high + 1;
                    return emailindex;
                }
            }
            else if (UserEmails[high][0] < strfirstletter) {
                return emailindex;
            }
        }
        else if (UserEmails[mid][0] == strfirstletter) {
            if (UserEmails[mid] == request) {
                found = true;
                emailindex = mid;
                return emailindex;
            }
            else if (UserEmails[mid] != request) {
                int i = 0;
                while (UserEmails[mid + i][0] == strfirstletter) {
                    if (UserEmails[mid + i] == request) {
                        found = true;
                        emailindex = mid + i;
                        return emailindex;
                    }
                    else { i++; }
                }
                i = 0;
                while (UserEmails[mid - i][0] == strfirstletter) {
                    if (UserEmails[mid - i] == request) {
                        found = true;
                        emailindex = mid - i;
                        return emailindex;
                    }
                    else { i++; }
                }
                low = high + 1;
                return emailindex;
            }
        }
        else {
            if (UserEmails[mid][0] < strfirstletter) {
                low = mid + 1;
                mid = (low + high) / 2;
            }
            else if (UserEmails[mid][0] > strfirstletter) {
                high = mid - 1;
                mid = (low + high) / 2;
            }
        }
    }
    }