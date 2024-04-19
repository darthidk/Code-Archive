// Header file that contians all functions related to writing and reading form text files

// Reading from 'Users.txt' and then creating classes based on the information
// Classes are then pushed into a vector which is returned
std::vector<User> ReadFromUser() {
    std::string line;
    std::ifstream file;
    std::vector<User> tempUserList;
    file.open("Users.txt");
    while (getline(file, line)) {
        std::vector<std::string> vectinfo;
        vectinfo = tokenize(line);
        std::vector<std::string> bookvect;
        for (size_t i = 4; i < vectinfo.size(); i++) {
            bookvect.push_back(vectinfo[i]);
        }
        User temp(vectinfo[0], vectinfo[1], unencrypt(vectinfo[2]), strtobool(vectinfo[3]), bookvect);
        tempUserList.push_back(temp);
    }
    file.close();
    return tempUserList;
}

// Reading from 'Books.txt' and then creating Book classes based on the information
// Classes are then pushed into a vector which is returned
std::vector<Book> ReadFromBook() {
    std::string line;
    std::ifstream file;
    std::vector<Book> tempBookList;
    file.open("Books.txt");
    while (getline(file, line)) {
        std::vector<std::string> vectinfo;
        vectinfo = tokenize(line);
        std::vector<std::string> bookvect;
        Book temp(vectinfo[0], vectinfo[1], vectinfo[2], vectinfo[3], vectinfo[4],
            strtotm(vectinfo[5]), strtobool(vectinfo[6]), vectinfo[7], vectinfo[8]);
        tempBookList.push_back(temp);
    }
    file.close();
    return tempBookList;
}

// Takes in the vector and then writes the vector's information to the file which stores user information
void WriteUserFile(std::vector<User> UserList) {
    std::ofstream file("Users.txt", std::ios::trunc);
    for (size_t i = 0; i < UserList.size(); i++) {
        file << UserList[i].name << "|" << UserList[i].email << "|" << encrypt(UserList[i].pw) << "|";
        file << booltostr(UserList[i].islibrarian);
        for (size_t k = 0; k < UserList[i].books.size(); k++) {
            file << "|" << UserList[i].books[k];
        }
        file << "\n";
    }
    file.close();
}

// Takes in the vector and then writes the vector's information to the file which stores book information
void WriteBookFile(std::vector<Book> BookList) {
    std::ofstream file("Books.txt", std::ios::trunc);
    for (size_t i = 0; i < BookList.size(); i++) {
        file << BookList[i].name << "|" << BookList[i].author << "|" << BookList[i].genre << "|";
        file << BookList[i].description << "|" << BookList[i].moreinfo << "|";
        file << BookList[i].duedate.tm_mon << "/" << BookList[i].duedate.tm_mday << "/";
        file << BookList[i].duedate.tm_year + 1900 << "|";
        file << booltostr(BookList[i].borrowed) << "|";
        file << BookList[i].borrowedusers << "|" << BookList[i].imagepath << "\n";
    }
    file.close();
}