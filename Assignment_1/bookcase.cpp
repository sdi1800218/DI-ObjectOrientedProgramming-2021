#include <iostream>
#include <ctime>
#include <cstdlib>
#include "bookcase.h"

using namespace std;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Vasi Implementation */

Tripodo::Tripodo() {
    /* Vasi Constructor */
    cout << "\t[Tripodo::Tripodo] Constructing Vasi\n";
}

Tripodo::~Tripodo() {
    /* Vasi Dectructeur */
    cout << "\t[Tripodo::~Tripodo] Bye bye Vasi object\n";
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Shelf Implementation */

Shelf::Shelf(int max) {
    /* Shelf Contructor */
    cout << "\t[Shelf::Shelf] Making a Shelf\n";
    N = 0;
    MaxN = max;
    Books = new Book[MaxN];
}

Shelf::~Shelf() {
    /* Self-Destructor */
    cout << "\t[Shelf::~Shelf] Breaking a Shelf\n";
    delete[] Books;
}

int Shelf::getN() {
    return N;
}

void Shelf::inc() {
    /* Increment the private part */
    ++N;
}

void Shelf::decr() {
    /* Decrease the private part */
    --N;
}

bool Shelf::addBook(Book book) {

    /* Checks whether it's possible to add a new book on the shelf.
        Then adds it to the first free place (null Book object).
        Returns true or false.
    */
    if (N < MaxN) {
        // iterate until N and see if we have any empty objects
        for (int i = 0; i <= N; ++i) {
            if (isNullBook(Books[i]))
                Books[i] = book;
        }
        inc();
        print_book(&book);
        return true;
    }
    else {
        cout << "[Shelf::addBook] Requested Shelf is FULL. Aborting..\n";
        return false;
    }
    //cout << "Added at position: " << N << endl;
}

bool Shelf::rmBook() {
    /* Removes a random Book from the Shelf in the range(N) */

    srand(time(0));

    // Check that shelf is not empty
    if(N > 0) {
        int randomBook = rand() % N;
        Books[randomBook] = nullBook;
        decr();
        return true;
    }
    else {
        cout << "[Shelf::take_book] Requested Shelf is EMPTY. Aborting..\n";  
        return false;
    }
}

void Shelf::print() {

    /* Print books if they exist on the (this), using 2 pointers for iteration */

    //check if first book is null book, which means the shelf is empty
    if(isNullBook(Books[0])) {
        cout << "[Shelf::print] The Shelf is empty!\n";
    }
    else {
        // make the 2 pointers
        Book* end = Books + N;
        Book* start = Books;

        while (start < end) {
            cout << "[Shelf::print]";
            print_book(start);
            ++start;
        }
        // TODO: Delete the pointers
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Cabinet Implementation */

Cabinet::Cabinet(int Max) {
    /* Init the Cabinet's Shelves */
    cout << "\t[Cabinet::Cabinet] Cabineting Up\n\t";
    Upper = new Shelf(Max);
    cout << "\t";
    Bottom = new Shelf(Max);
}

Cabinet::~Cabinet() {
     /* Init the Cabinet's Shelves */
    cout << "\t[Cabinet::~Cabinet] Cabineting Down\n\t";
    delete Upper;
    cout << "\t";
    delete Bottom;
}

bool Cabinet::place_book(short where, Book book) {
    /* Same name, different scope; as the assignment mentions */

    // Handle Upper
    if(where == 1) {
        if(Upper->addBook(book)) {
            return true;
        }
        else {
            return false;
        }
    }
    // Handle Lower
    else if (where == 2) {
        if(Bottom->addBook(book)) {
            return true;
        }
        else {
            return false;
        }
    }
    // Panic
    else {
        exit(1337);
    }
}

bool Cabinet::take_book(short where) {
    if(where == 1) {
        if(Upper->rmBook()) {
            return true;
        }
        else {
            return false;
        }
    }
    // Handle Lower
    else if (where == 2) {
        if(Bottom->rmBook()) {
            return true;
        }
        else {
            return false;
        }
    }
    // Panic
    else {
        exit(1337);
    }
}

void Cabinet::print() {

    cout << "\t\t\t ~~UPPER CABINET SHELF~~\n";
    cout << string(79, '+') << "\n";
    Upper->print();

    cout << "\t\t\t ~~BOTTOM CABINET SHELF~~\n";
    cout << string(79, '+') << "\n";
    Bottom->print();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Bookcase Implementation */

Bookcase::Bookcase(int Max) {
    /* Print Various messages */
    maxN = Max;
    counter = 0;

    cout << string(36, '~') << "CREATION" << string(35, '~') << endl;
    cout << "[Bookcase::Bookcase] Contructing a very strong Bookcase\n";

    Upper   = new Shelf(Max);
    Middle  = new Shelf(Max);
    Bottom  = new Shelf(Max);
    Main    = new Cabinet(Max);
    Stub    = new Tripodo();

    cout << "[Bookcase::Bookcase] All ready!!\n";
    cout << string(79, '~') << endl;
}

Bookcase::~Bookcase() {
    cout << endl << string(35, '~') << "INFERNO" << string(36, '~') << endl;
    cout << "[Bookcase::~Bookcase] Breaking the very strong Bookcase\n";

    delete Upper;
    delete Middle;
    delete Bottom;
    delete Main;
    delete Stub;

    cout << "[Bookcase::~Bookcase] Successfully made everything vides\n";
}

bool Bookcase::place_book(Shelf *target, Book book) {
    /* Intermediate and overloaded function that handles the choice of the menu */

    if(target->addBook(book)) {
        return true;
    }
    else {
        return false;
    }
}

bool Bookcase::place_book(short where, Book book) {
    /* Description */

    bool flag = false;

    /* Hacky way that works. Matces the appropriate location to place the book,
        prints the message and then calls again it's overloaded friend that
        does the work either in the Bookcase object or in the Cabinet object.
    */ // Dont show this to anyone!
    switch(where) {
        case 1: cout << "[Bookcase::place_book] Placing book in Upper Bookcase shelf\n";
                flag = place_book(Upper, book);
                break;
        case 2: cout << "[Bookcase::place_book] Placing book in Middle Bookcase shelf\n";
                flag = place_book(Middle, book);
                break;
        case 3: cout << "[Bookcase::place_book] Placing book in Bottom Bookcase shelf\n";
                flag = place_book(Bottom, book);
                break;
        case 4: cout << "[Bookcase::place_book] Placing book in Upper Cabinet shelf\n";
                flag = Main->place_book(1, book);
                break;
        case 5: cout << "[Bookcase::place_book] Placing book in Bottom Cabinet shelf\n";
                flag = Main->place_book(2, book);
                break;
        default: break;
    }
    //^^ Idea: enumerate the symbols and make the call via index to the enum'd array

    // If book successfully placed, increase the total counter
    if (flag) counter++;
    //else cout << "ERROR: Something wicked this way comes\n";

    return flag;
}

bool Bookcase::take_book(Shelf *target) {
    /* Intermediate and overloaded function that handles the choice of the menu */

    // Check if shelf is empty
    if(target->rmBook()) {
        return true;
    }
    else {
        return false;
    }
}

bool Bookcase::take_book(short where) {
    bool flag = false;

    /* Same hacky approach with overloading like place_book*/ 
    switch(where) {
        case 1: cout << "[Bookcase::take_book] Taking book from Upper Bookcase shelf\n";
                flag = take_book(Upper);
                break;
        case 2: cout << "[Bookcase::take_book] Taking book from Middle Bookcase shelf\n";
                flag = take_book(Middle);
                break;
        case 3: cout << "[Bookcase::take_book] Taking book from Bottom Bookcase shelf\n";
                flag = take_book(Bottom);
                break;
        case 4: cout << "[Bookcase::take_book] Taking book from Upper Cabinet shelf\n";
                flag = Main->take_book(1);
                break;
        case 5: cout << "[Bookcase::take_book] Taking book from Bottom Cabinet shelf\n";
                flag = Main->take_book(2);
                break;
        default: break;
    }

    // If book successfully removed, decrease the total counter
    if (flag) counter--;
    //else cout << "ERROR: Something wicked this way comes\n";

    return flag;
}

void Bookcase::print() {

    cout << "[Bookcase::print] PRINTING BOOKCASE\n";

    cout << string(79, '+') << "\n";
    cout << "\t\t\t ~~UPPER SHELF~~\n";
    Upper->print();

    cout << string(79, '+') << "\n";
    cout << "\t\t\t ~~MIDDLE SHELF~~\n";
    Middle->print();

    cout << string(79, '+') << "\n";
    cout << "\t\t\t ~~BOTTOM SHELF~~\n";
    Bottom->print();

    cout << string(79, '+') << "\n";
    cout << "\t\t\t\t ~~CABINET~~\n";
    Main->print();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Helper functions */

void print_book(Book *book) {
    cout << "Book {\n" << "\tTitle:\t" << book->title << "\n\tAuthor:\t"
        << book->author << "\n\tISBN:\t" << book->ISBN << "\n}\n";
}

bool isNullBook(Book book) {
    /* Check if the given book is equal to the nullBook */
    if ( (nullBook.title == book.title) \
        && (nullBook.author == book.author) \
        && (nullBook.ISBN == book.ISBN) )
        return true;
    else return false;
}