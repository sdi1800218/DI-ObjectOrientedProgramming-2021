#include <string>

using namespace std;

typedef struct{
    string  title;
    string  author;
    int     ISBN;
    /*friend ostream& operator<<(ostream& os, const Book& book) {
        magic << ;
        return magic;
    }*/
}Book;

const Book nullBook = {string(), string(), 0};

/* nvm it's a struct
class Book {
    private:
        string  title;
        string  author;
        int     ISBN;
    public:
        Book(string);
        Book(string, string);
        Book(string, string, int);
        ~Book();
        //void get(int&, int&, int&);
};
*/

class Shelf {
    /* What's a shelf after all? */
    private:
        int N;
        int MaxN;
        Book* Books;
    public:
        Shelf(int);
        ~Shelf();

        int getN();
        void inc();
        void decr();

        bool addBook(Book);
        bool rmBook();
        void print();
};

class Cabinet {
    /* Could be a parliament */
    private:
        Shelf *Upper, *Bottom;
    public:
        Cabinet(int);
        ~Cabinet();

        bool take_book(short);
        bool place_book(short, Book);
        void print();
};

class Tripodo {
    /* aintnouseforit */
    public:
        Tripodo();
        ~Tripodo();
};

class Bookcase {
    /* Thy Bookcase core */
    private:
        int maxN;
        int counter;
    public:
        Shelf *Upper, *Middle, *Bottom; // 3 shelves
        Cabinet *Main;                  // 1 cabinet
        Tripodo *Stub;                  // amazing price

        Bookcase(int);
        ~Bookcase();

        bool place_book(short, Book);   // Menu
        bool place_book(Shelf *, Book); // Server
        bool take_book(short);  //Menu
        bool take_book(Shelf *);

        void print();
};

void print_book(Book *);
bool isNullBook(Book);