// Header files that contains functions used throughout other header files and the main file

// Splits a string everytime there is a '|' into multiple parts 
/* Split parts are put into a vector with each of these parts in
chronological order of when they appeared in the orginial string */
std::vector<std::string> tokenize(std::string s)
{
    std::string del = "|";
    int start = 0;
    int end = s.find(del);
    std::vector<std::string> vect;
    while (end != -1) {
        vect.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    vect.push_back(s.substr(start, end - start));
    return vect;
}

// Receives a string and returns either true or false based on what the string was
bool strtobool(std::string str) {
    if (str == "true") {
        return true;
    }
    else if (str == "false") {
        return false;
    }
    else {
        return NULL;
    }
}

// Receives a bool and returns either true or false as a string
// Returns null if the string is neither truue or false
std::string booltostr(bool val) {
    if (val == true) {
        return "true";
    }
    else {
        return "false";
    }
}

// Recieves a string and returns a timestructure based on the string
tm strtotm(std::string str) {
    std::string del = "/";
    int start = 0;
    int end = str.find(del);
    std::vector<std::string> vect;
    while (end != -1) {
        vect.push_back(str.substr(start, end - start));
        start = end + del.size();
        end = str.find(del, start);
    }
    vect.push_back(str.substr(start, end - start));
    time_t rawtime = time(NULL);
    struct tm tempstruct;
    localtime_s(&tempstruct, &rawtime);
    tempstruct.tm_year = std::stoi(vect[2]) - 1900;
    tempstruct.tm_mon = std::stoi(vect[1]);
    tempstruct.tm_mday = std::stoi(vect[0]);
    return tempstruct;
}

// Recieves a string and encrypts/modifies the string and returns the encrypted string
std::string encrypt(std::string instring) {
    std::string str = instring;
    for (size_t i = 0; i < str.size(); i += 2) {
        str[i] += 2;
    }
    for (size_t i = 1; i < str.size(); i += 2) {
        str[i] -= 3;
    }
    return str;
}

// Recieves a string and unecrypts/does the opposite of the encrypt function and returns the unencrypted/original string
std::string unencrypt(std::string instring) {
    std::string str = instring;
    for (size_t i = 0; i < str.size(); i += 2) {
        str[i] -= 2;
    }
    for (size_t i = 1; i < str.size(); i += 2) {
        str[i] += 3;
    }
    return str;
}