#include <iostream>
#include <string>
using namespace std;

// Base class
class LibraryItem {
protected:
    int id;
    string title;

public:
    void setID(int i) { id = i; }
    int getID() const { return id; }

    void setTitle(const string &t) { title = t; }
    string getTitle() const { return title; }

    virtual void display() const = 0; // pure virtual
};

// Derived class
class Book : public LibraryItem {
    string author;
    bool isIssued;

public:
    Book() {
        id = 0;
        title = "";
        author = "";
        isIssued = false;
    }

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        do {
            cout << "Enter Title: ";
            getline(cin, title);
            if (title.empty()) {
                cout << "Title cannot be empty! Please enter again.\n";
            }
        } while (title.empty());

        do {
            cout << "Enter Author: ";
            getline(cin, author);
            if (author.empty()) {
                cout << "Author cannot be empty! Please enter again.\n";
            }
        } while (author.empty());

        isIssued = false;
        cout << "Book added successfully.\n";
    }

    void display() const override {
        cout << "Book ID : " << id << endl;
        cout << "Title   : " << title << endl;
        cout << "Author  : " << author << endl;
        cout << "Status  : " << (isIssued ? "Issued" : "Available") << endl;
    }

    void issue() {
        if (isIssued) {
            cout << "Book is already issued.\n";
        } else {
            isIssued = true;
            cout << "Book issued.\n";
        }
    }

    void ret() {
        if (!isIssued) {
            cout << "Book is already available.\n";
        } else {
            isIssued = false;
            cout << "Book returned.\n";
        }
    }

    void update() {
        cin.ignore();
        do {
            cout << "Enter new Title: ";
            getline(cin, title);
            if (title.empty()) {
                cout << "Title cannot be empty! Please enter again.\n";
            }
        } while (title.empty());

        do {
            cout << "Enter new Author: ";
            getline(cin, author);
            if (author.empty()) {
                cout << "Author cannot be empty! Please enter again.\n";
            }
        } while (author.empty());

        cout << "Book updated.\n";
    }

    bool getIssuedStatus() const { return isIssued; }
};

// Library manager
class Library {
    Book books[100];
    int count;

public:
    Library() { count = 0; }

    void addBook() {
        if (count >= 100) {
            cout << "Library full.\n";
            return;
        }
        books[count].input();
        count++;
    }

    void displayAll() const {
        if (count == 0) {
            cout << "No books.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            books[i].display();
            cout << "--------------------\n";
        }
    }

    void searchBook(int id) const {
        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                books[i].display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void issueBookByTitle(const string &title) {
        for (int i = 0; i < count; i++) {
            if (books[i].getTitle() == title) {
                books[i].issue();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBookByTitle(const string &title) {
        for (int i = 0; i < count; i++) {
            if (books[i].getTitle() == title) {
                books[i].ret();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void deleteBook(int id) {
        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                for (int j = i; j < count - 1; j++) {
                    books[j] = books[j + 1];
                }
                count--;
                cout << "Book deleted.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void updateBook(int id) {
        for (int i = 0; i < count; i++) {
            if (books[i].getID() == id) {
                books[i].update();
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library lib;
    int choice, id;
    string title;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book by Title\n";
        cout << "5. Return Book by Title\n";
        cout << "6. Delete Book by ID\n";
        cout << "7. Update Book by ID\n";
        cout << "8. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayAll();
            break;
        case 3:
            cout << "Enter Book ID to search: ";
            cin >> id;
            lib.searchBook(id);
            break;
        case 4:
            cin.ignore();
            cout << "Enter Book Title to issue: ";
            getline(cin, title);
            lib.issueBookByTitle(title);
            break;
        case 5:
            cin.ignore();
            cout << "Enter Book Title to return: ";
            getline(cin, title);
            lib.returnBookByTitle(title);
            break;
        case 6:
            cout << "Enter Book ID to delete: ";
            cin >> id;
            lib.deleteBook(id);
            break;
        case 7:
            cout << "Enter Book ID to update: ";
            cin >> id;
            lib.updateBook(id);
            break;
        case 8:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
