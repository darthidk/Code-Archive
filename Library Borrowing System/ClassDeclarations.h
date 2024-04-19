// Header file containg the declarations and defitions of the User and Book class used throughout the solution

// User Class, used to effectively store information about users
// Constructor takes an input for each attribute of the class
class User
{
public:
    std::string name;
    std::string email;
    std::string pw;
    bool islibrarian;
    std::vector<std::string> books;
    User(std::string inname, std::string inemail, std::string inpw, bool inislib, std::vector<std::string>inbooks) {
        name = inname;
        email = inemail;
        pw = inpw;
        islibrarian = inislib;
        books = inbooks;
    }
};

// Book class, stores book information
// Constructur takes in a value for each attribute of the class
class Book
{
public:
    std::string name;
    std::string author;
    std::string genre;
    std::string description;
    std::string moreinfo;
    tm duedate;
    bool borrowed;
    std::string borrowedusers;
    std::string imagepath;
    Book(std::string inname, std::string inauthor, std::string ingenre, std::string indescr,
        std::string inmoreinfo, tm induedate, bool inborrowed, std::string inborrowedusers, std::string inimagepath) {
        name = inname;
        author = inauthor;
        genre = ingenre;
        description = indescr;
        moreinfo = inmoreinfo;
        duedate = induedate;
        borrowed = inborrowed;
        borrowedusers = inborrowedusers;
        imagepath = inimagepath;
    }
};