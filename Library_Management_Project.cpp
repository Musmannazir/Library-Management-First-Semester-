#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
};

Book library[MAX_BOOKS];
int bookCount = 0;
bool isLoggedIn = false;
bool isAdmin = false;
string currentUser;

const string adminUsername = "admin";
const string adminPassword = "admin123";


void loadBooksFromFile() {
    ifstream file("library.txt");
    if (!file.is_open()) {
        cout << "Error opening library file!\n";
        return;
    }

    bookCount = 0; 
    while (file >> library[bookCount].id) {
        file.ignore(); 
        getline(file, library[bookCount].title);
        getline(file, library[bookCount].author);
        file >> library[bookCount].issued;
        file.ignore(); 
        bookCount++;
    }
    file.close();
}


void saveBookToFile(const Book& book) {
    ofstream file("library.txt", ios::app); 
    if (file.is_open()) {
        file << book.id << endl;
        file << book.title << endl;
        file << book.author << endl;
        file << book.issued << endl;
        file.close();
    } else {
        cout << "Error opening library file!\n";
    }
}

void registerUser() {
    string username, password;

    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << endl;
        userFile.close();
        cout << "Registration successful!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

bool loginUser() {
    string username, password, storedUsername, storedPassword;
    bool loginSuccess = false;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        isAdmin = true;
        loginSuccess = true;
        currentUser = username;
        cout << "Admin login successful!\n";
        return true;
    }

    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        while (userFile >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                loginSuccess = true;
                currentUser = username;
                break;
            }
        }
        userFile.close();

        if (loginSuccess) {
            cout << "Login successful!\n";
        } else {
            cout << "Invalid credentials!\n";
        }
    } else {
        cout << "Error opening file!\n";
    }

    return loginSuccess;
}

void addBook() {
    if (!isAdmin) {
        cout << "Only admins can add books.\n";
        return;
    }

    if (bookCount >= MAX_BOOKS) {
        cout << "Library is full! Cannot add more books.\n";
        return;
    }

    cout << "Enter book ID: ";
    cin >> library[bookCount].id;
    cin.ignore(); 
    cout << "Enter book title: ";
    getline(cin, library[bookCount].title);
    cout << "Enter book author: ";
    getline(cin, library[bookCount].author);
    library[bookCount].issued = false; 
    saveBookToFile(library[bookCount]); 
    bookCount++;

    cout << "Book added successfully!\n";
}

void viewBooks() {
    loadBooksFromFile(); 

    if (bookCount == 0) {
        cout << "No books in the library!\n";
        return;
    }

    cout << "ID\tTitle\tAuthor\tStatus\n";
    for (int i = 0; i < bookCount; i++) {
        cout << library[i].id << "\t" << library[i].title << "\t" << library[i].author << "\t"
             << (library[i].issued ? "Issued" : "Available") << "\n";
    }
}

void issueBook() {
    loadBooksFromFile(); 

    int id;
    cout << "Enter book ID to issue: ";
    cin >> id;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].issued) {
                cout << "Book is already issued!\n";
            } else {
                library[i].issued = true;
                cout << "Book issued successfully!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            cout << "Debug: Book found. Issued status = " << library[i].issued << "\n";
            if (library[i].issued) {
                library[i].issued = false;
                cout << "Book returned successfully!\n";
            } else {
                cout << "Book was not issued!\n";
            }
            return;
        }
    }
    cout << "Book not found!\n";
}


int main() {
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        if (isAdmin) {
            cout << "3. Add Book (Admin Only)\n";
        }
        cout << "4. View Books\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            isLoggedIn = loginUser();
            break;
        case 3:
            if (isAdmin) addBook();
            else cout << "Invalid option!\n";
            break;
        case 4:
            if (isLoggedIn) viewBooks();
            else cout << "Please log in first.\n";
            break;
        case 5:
            if (isLoggedIn) issueBook();
            else cout << "Please log in first.\n";
            break;
        case 6:
            if (isLoggedIn) returnBook();
            else cout << "Please log in first.\n";
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
