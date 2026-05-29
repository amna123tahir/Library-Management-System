#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book {
public:
int id;
char title[50], author[50];
bool issued;

void input() {
    cout << "--enter book id: ";
    cin >> id;
    cin.ignore();
    cout << "--enter title: ";
    cin.getline(title, 50);
    cout << "--enter author: ";
    cin.getline(author, 50);
    issued = false;
}

void display() {
    cout << endl;
    cout << "ID: " << id << endl;
    cout << "TITLE: " << title << endl;
    cout << "AUTHOR: " << author << endl;
    cout << "STATUS: " << (issued ? "Issued" : "Available") << endl;
}
};

void add_book() {

Book b;
ofstream file("library.txt", ios::binary | ios::app);
b.input();
file.write((char*)&b, sizeof(b));
file.close();
cout << endl;
cout << "book added successfully!" << endl;
}

void display_all_books() {

Book b;
ifstream file("library.txt", ios::binary);
if (!file) {
    cout << "No records found.\n";
    return;
}
while (file.read((char*)&b, sizeof(b))) {
    b.display();
    cout << "-------------------";
}
file.close();
}

void search_book() {

int searchId;
Book b;
bool found = false;
cout << "enter book ID to search: ";
cin >> searchId;
ifstream file("library.txt", ios::binary);
while (file.read((char*)&b, sizeof(b))) {
    if (b.id == searchId) {
        b.display();
        found = true;
        break;
    }
}
file.close();
if (!found) { cout << "book not found!" << endl; }
}

void issue_book() {

int searchId;
Book b;
bool found = false;

cout << "enter book ID to issue: ";
cin >> searchId;
fstream file("library.txt", ios::binary | ios::in | ios::out);
while (file.read((char*)&b, sizeof(b))) {
    if (b.id == searchId) {
        if (!b.issued) {
            b.issued = true;

            int pos = -1 * sizeof(b);
            file.seekp(pos, ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "book issued successfully!" << endl;
        }
        else {
            cout << "book already issued!" << endl;
        }
        found = true;
        break;
    }
}

file.close();

if (!found) { cout << "book not found!" << endl; }
}

void return_book() {
int searchId;
Book b;
bool found = false;

cout << "enter book ID to return: ";
cin >> searchId;

fstream file("library.txt", ios::binary | ios::in | ios::out);

while (file.read((char*)&b, sizeof(b))) {
    if (b.id == searchId) {
        if (b.issued) {
            b.issued = false;

            int pos = -1 * sizeof(b);
            file.seekp(pos, ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "book returned successfully!" << endl;
        }
        else {
            cout << "book was not issued!" << endl;
        }
        found = true;
        break;
    }
}

file.close();
if (!found) { cout << "book not found!" << endl; }

}

int main() {
    int choice;
    do {
        cout << "-- NATIONAL LIBRARY --" << endl;
        cout << "1. ADD BOOK" << endl;
        cout << "2. DISPLAY ALL BOOKS" << endl;
        cout << "3. SEARCH BOOK" << endl;
        cout << "4. ISSUE BOOK" << endl;
        cout << "5. RETURN BOOK" << endl;
        cout << "0. EXIT" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: add_book(); 
            break;
        case 2: display_all_books(); 
            break;
        case 3: search_book(); 
            break;
        case 4: issue_book(); 
            break;
        case 5: return_book(); 
            break;
        case 0: cout << "exiting library portal" << endl;
            break;
        default: cout << "invalid choice" << endl;
        }

    } while (choice != 0);

    return 0;
}