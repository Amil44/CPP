#include <iostream>
#include <string>
using namespace std;

enum Genre { Romantik = 1, Detektiv, Romance, Mystery, Thriller, Fantasy, Historical, Biography };
enum Language { German, Russian, English, Spanish, Turkish };

class Book {
    char* name;
    char* author;
    short int release;
    short int date;
    short int id;
    Language language;
    Genre* genre;

public:
    Book() {
        name = nullptr;
        author = nullptr;
        release = 0;
        date = 0;
        id = 0;
        language = German;
        genre = new Genre[3]{ Romantik , Romance , Fantasy };
    }

    Book(const Book& other) {
        name = new char[strlen(other.name) + 1];
        strcpy_s(this->name, strlen(other.name) + 1, other.name);
        author = new char[strlen(other.author) + 1];
        strcpy_s(this->author, strlen(other.author) + 1, other.author);
        release = other.release;
        date = other.date;
        id = other.id;
        language = other.language;
        genre = new Genre[3];
        for (int i = 0; i < 3; i++)
            genre[i] = other.genre[i];
    }

    void setInfo(const char* name, const char* author, short int release, short int date, short int id, Language language, Genre* genre) {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
        this->author = new char[strlen(author) + 1];
        strcpy_s(this->author, strlen(author) + 1, author);
        this->release = release;
        this->date = date;
        this->id = id;
        this->language = language;
        this->genre = new Genre[3];
        for (int i = 0; i < 3; i++) {
            this->genre[i] = genre[i];
        }
    }

    void getInfo(Language lan) {
        cout << "Id: " << id << " | "
            << "Name: " << name << " | "        
            << "Author: " << author << " | "
            << "Release: " << release << " | "
            << "Date: " << date << " | "
            << "Language: " << LanguageToString(lan) << " | ";

        for (int i = 0; i < 3; i++) {
            cout << GenreToString(genre[i]) << " ";
        }
        cout << endl << endl;
        cout << "================================================================================================================================" << endl << endl;
    }

    const char* LanguageToString(Language lan) {
        switch (lan) {
        case German: return "German";
        case Russian: return "Russian";
        case English: return "English";
        case Spanish: return "Spanish";
        case Turkish: return "Turkish";
        default: return "Unknown";
        }
    }

    const char* GenreToString(Genre g) {
        switch (g) {
        case Romantik: return "Romantik";
        case Detektiv: return "Detektiv";
        case Romance: return "Romance";
        case Mystery: return "Mystery";
        case Thriller: return "Thriller";
        case Fantasy: return "Fantasy";
        case Historical: return "Historical";
        case Biography: return "Biography";
        default: return "Unknown";
        }
    }

    void showBooksByAuthor(const char* author) {
        cout << "\n── Books by \"" << author << "\" ──\n";
    }

    void removeBook(const char* name) {
        name = nullptr;
        author = nullptr;
        release = 0;
        date = 0;
        id = 0;
        cout << "Book removed successfully." << endl;
    }

    Genre* getGenre() const { return genre; }
    char* getBookName() const { return name; }
    char* getAuthor() const { return author; }
    Language getLanguage() const { return language; }

    ~Book() {
        delete[] this->name;
        delete[] this->author;
        delete[] genre;
    }
};

class Library {
    Book* books[10];
    int count = 0;

public:
    void addBook(const Book& book) {
        books[count++] = new Book(book);
    }

    void showAllBooks() {
        for (int i = 0; i < count; i++) {
            cout << books[i]->getBookName() << "\n"; 
        }
    }
    void showBooksByAuthor(const std::string& author) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (std::string(books[i]->getAuthor()) == author) {
                books[i]->getInfo(books[i]->getLanguage());
                found = true;
            }
        }
        if (!found)
            cout << "No books found\n";
    }

    void removeBook(const char* name) {
        for (int i = 0; i < count; i++) {
            if (std::string(books[i]->getBookName()) == std::string(name)) {
                delete books[i];

                for (int j = i; j < count - 1; j++)
                    books[j] = books[j + 1];

                count--;
                cout << "Deleted\n";
                return;
            }
        }
        cout << "Not found\n";
    }

    ~Library() {
        for (int i = 0; i < count; i++)
            delete books[i];
    }
};

int main() {
    Library library;

    Book* b1 = new Book();
    Book* b2 = new Book();
    Book* b3 = new Book();
    Book* b4 = new Book();

    Language lang1;
    Language lang2;
    Language lang3;
    Language lang4;

    lang1 = Spanish;
    lang2 = English;
    lang3 = Russian;
    lang4 = English;

    Genre* genre1 = new Genre[3];
    genre1[0] = Fantasy;
    genre1[1] = Thriller;
    genre1[2] = Mystery;

    Genre* genre2 = new Genre[3];
    genre2[0] = Fantasy;
    genre2[1] = Historical;
    genre2[2] = Biography;

    Genre* genre3 = new Genre[3];
    genre3[0] = Romance;
    genre3[1] = Historical;
    genre3[2] = Biography;

    Genre* genre4 = new Genre[3];
    genre4[0] = Historical;
    genre4[1] = Mystery;
    genre4[2] = Thriller;

    b1->setInfo("1984", "George Orwell", 1949, 2024, 1, lang1, genre1);
    b1->getInfo(lang1);

    b2->setInfo("Animal Farm", "George Orwell", 1945, 2024, 2, lang2, genre2);
    b2->getInfo(lang2);

    b3->setInfo("The Great Gatsby", "F. Scott Fitzgerald", 1925, 2022, 3, lang3, genre3);
    b3->getInfo(lang3);

    b4->setInfo("Crime and Punishment", "Fyodor Dostoevsky", 1866, 2023, 4, lang4, genre4);
    b4->getInfo(lang4);

    library.addBook(*b1);
    library.addBook(*b2);
    library.addBook(*b3);
    library.addBook(*b4);

    cout << "\nAll books:\n";
    library.showAllBooks();

    cout << "\nBy author:\n";
    library.showBooksByAuthor("George Orwell");

    library.removeBook("1984");

    cout << "\nAfter delete:\n";
    library.showAllBooks();

    delete b1;
    delete b2;
    delete b3;
    delete b4;

    b1 = nullptr;
    b2 = nullptr;
    b3 = nullptr;
    b4 = nullptr;

    delete[] genre1;
    delete[] genre2;
    delete[] genre3;
    delete[] genre4;

    return 0;
}