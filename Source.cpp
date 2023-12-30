#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>
#include <iterator>

using namespace std;

struct Book {
    string title;
    string author;
    string publisher;
    int year;
    double price;
};

void printBook(const Book& book, int number) {
    cout << number << ". " << book.title << "\t" << book.author << "\t" << book.publisher << "\t" << book.year << "\t" << book.price << endl;
}

void printBooks(const vector<Book>& books) {
    for (size_t i = 0; i < books.size(); ++i) {
        printBook(books[i], i + 1);
    }
}

void printBooksWithNumbers(const vector<Book>& books) {
    for (size_t i = 0; i < books.size(); ++i) {
        cout << i + 1 << ". ";
        printBook(books[i], i + 1);
    }
}

void addBook(ofstream& file, vector<Book>& books, const Book& book) {
    books.push_back(book);
    file << book.title << "\t" << book.author << "\t" << book.publisher << "\t" << book.year << "\t" << book.price << endl;
}

void removeBook(const string& filePath, vector<Book>& books) {
    ifstream inputFile(filePath);
    ofstream tempFile("temp.txt", ios::out);

    vector<string> numbersToRemove;
    cout << "������� ������ ���� ��� �������� (����� ������): ";
    string input;
    getline(cin, input);
    istringstream iss(input);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(numbersToRemove));

    bool bookFound = false;

    for (size_t i = 0; i < numbersToRemove.size(); ++i) {
        int bookIndex = stoi(numbersToRemove[i]) - 1;
        if (bookIndex >= 0 && static_cast<size_t>(bookIndex) < books.size()) {
            books.erase(books.begin() + bookIndex);
            bookFound = true;
        }
    }

    if (!bookFound) {
        cout << "����� �� �������." << endl;
    }

    for (const Book& book : books) {
        tempFile << book.title << "\t" << book.author << "\t" << book.publisher << "\t" << book.year << "\t" << book.price << endl;
    }

    tempFile.close();
    inputFile.close();

    remove(filePath.c_str());
    rename("temp.txt", filePath.c_str());

    if (bookFound) {
        cout << "����� ������� �������." << endl;
    }
}

void addBooksFromFile(ofstream& file, vector<Book>& books, const string& filePath) {
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "������ �������� ����� ��� ������." << endl;
        return;
    }

    string line;
    int lineNum = 0;
    while (getline(inputFile, line)) {
        ++lineNum;
        stringstream ss(line);

        Book book;
        if (getline(ss, book.title, '\t') && getline(ss, book.author, '\t') &&
            getline(ss, book.publisher, '\t') && (ss >> book.year >> book.price)) {
            addBook(file, books, book);
        }
        else {
            cerr << "������ � ������ " << lineNum << ": ������������ ������ ������." << endl;
        }
    }

    inputFile.close();
    cout << "����� ������� ��������� �� ������� �����." << endl;
}

vector<Book> readBooksFromFile(ifstream& file) {
    vector<Book> books;
    Book book;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        if (getline(ss, book.title, '\t') && getline(ss, book.author, '\t') &&
            getline(ss, book.publisher, '\t') && (ss >> book.year >> book.price)) {
            books.push_back(book);
        }
    }

    return books;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    string filePath;

    cout << "������� ������ ���� � �����: ";
    getline(cin, filePath);

    ifstream inputFile(filePath);

    while (!inputFile.is_open()) {
        cout << "������ �������� �����, ���������� ��� ���: ";
        getline(cin, filePath);
        inputFile.open(filePath);
    }

    vector<Book> books = readBooksFromFile(inputFile);
    inputFile.close();

    while (true) {
        cout << "�����:" << endl;
        cout << "1. ������� �����" << endl;
        cout << "2. ������� ����� �� ��������� ���" << endl;
        cout << "3. �������� ����� �����" << endl;
        cout << "4. ������� �����" << endl;
        cout << "5. �������� ����� �� ������� �����" << endl;
        cout << "6. �����" << endl;

        string option;
        cout << "������� ���� �������: ";
        getline(cin, option);

        if (option == "1") {
            cout << "�����, ����������� � �����:" << endl;
            printBooks(books);
        }
        else if (option == "2") {
            cout << "������� �������� ��� (���. ����.): ";
            double minPrice, maxPrice;

            // �������� �� ���������� ���� ����������� ����
            while (!(cin >> minPrice) || minPrice <= 0) {
                cout << "������ �����. ������� ���������� ������������� �������� ��� ����������� ����, �� ������������ � ����: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // �������� �� ���������� ���� ������������ ����
            while (!(cin >> maxPrice) || maxPrice <= 0 || maxPrice < minPrice) {
                cout << "������ �����. ������� ���������� ������������� �������� ��� ������������ ���� (������ ��� ������ �����������): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            vector<Book> filteredBooks;
            copy_if(books.begin(), books.end(), back_inserter(filteredBooks), [minPrice, maxPrice](const Book& book) {
                return book.price >= minPrice && book.price <= maxPrice;
                });

            cout << "��������������� �����:" << endl;
            printBooks(filteredBooks);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
        else if (option == "3") {
            Book newBook;
            cout << "������� ��������: ";
            getline(cin, newBook.title);
            cout << "������� ������: ";
            getline(cin, newBook.author);
            cout << "������� ������������: ";
            getline(cin, newBook.publisher);

            cout << "������� ���: ";
            while (!(cin >> newBook.year) || newBook.year < 1) {
                cout << "������ ����� ����. ���������� �����:" << endl;
                clearInputBuffer();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������ ����� ������

            cout << "������� ����: ";
            while (!(cin >> newBook.price) || newBook.year < 0) {
                cerr << "������ ����� ����. ���������� �����." << endl;
                clearInputBuffer();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������ ����� ������

            ofstream outputFile(filePath, ios::app);
            addBook(outputFile, books, newBook);
            outputFile.close();

            cout << "����� ����� ������� ���������." << endl;

        }
        else if (option == "4") {
            printBooks(books);
            removeBook(filePath, books);

        }
        else if (option == "5") {
            string otherFilePath;
            cout << "������� ���� � ������� �����: ";
            getline(cin, otherFilePath);
            ofstream outputFile(filePath, ios::app);
            addBooksFromFile(outputFile, books, otherFilePath);
            outputFile.close();

        }
        else if (option == "6") {
            cout << "�����...." << endl;
            break;
        }
        else {
            cerr << "������������ �������." << endl;
        }
    }

    return 0;
}
