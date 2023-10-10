#include <iostream>
#include <cassert>
#include "trapeza.h"

using namespace std;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Tameio Implementation */

Tameio::Tameio() {
    /* Initiliaze as closed and empty */
    //cout << "[Tameio::Tameio] I am making a Tameio\n";
    open_flag = false;
    serving_flag = false;
}

Tameio::~Tameio() {
    cout << "[Tameio::~Tameio] Destroying a Tameio\n";
}

void Tameio::open() {
    /* Reset **served** and let me know */
    cout << "[Tameio::open] Opening a new Tameio\n";
    customers_served = 0;
    open_flag = true;
    serving_flag = false;
}

void Tameio::close() {
    cout << "[Tameio::close] Closing a Tameio\n";
    open_flag = false;
}

bool Tameio::is_open() {
    return open_flag;
}

bool Tameio::is_free() {
    /* return the natural language negation of free, given that free = !busy */ 
    return !(serving_flag);
}

void Tameio::serve() {
    cout << "[Tameio::serve] Serving a customer\n";
    serving_flag = true;
}

void Tameio::free(int Tameio_Limit) {
    cout << "[Tameio::free] Freeing Tameiooo\n";
    ++customers_served;

    // Check if its lunch break time
    if(customers_served == Tameio_Limit) {
        cout << "[IMPORTANT] This Tameio reached the maximum number of serves!\n";
        close();
    }
    serving_flag = false;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Trapeza Implementation */

Trapeza::Trapeza() {
    /* Open the doors, initliaze xartaki, open one cashier */
    cout << "[Trapeza::Trapeza] I am creating a bank\n";

    last_customer = 1;
    curr_serving = 1;

    cashiers[0].open();
    last_served = -1;
}

Trapeza::~Trapeza() {
    cout << "[Trapeza::~Trapeza] The bank is CLOSING\n";
}

bool Trapeza::enter() {

    // announce thre number of open cashiers
    open_cashiers();

    // checks whether the open ones are enough
    if ( check_to_open() ) {
        cout << "\nhelp\n";
        ++last_customer;
        return true;
    }
    else if ( get_next_closed() != -1) {
        cashiers[get_next_closed()].open();
        ++last_customer;
        return true;
    }
    else {
        cout << "[Trapeza::enter] Sorry you cannot enter until some customers are served!\n";
        return false;
    }
}

void Trapeza::serve() {
    /*
    1) Ελέγχεται μήπως όλα τα ταμεία είναι κλειστά οπότε ανοίγει το πρώτο ταμείο και το επιλέγει.

    2) Αλλιώς, επιλέγεται το επόμενο ταμείο που είναι ανοικτό και ελεύθερο, έστω το ith . Η
    επιλογή γίνεται κυκλικά. (Δηλαδή, το ith ταμείο είναι το επόμενο ανοικτό ταμείο από αυτό
    που εξυπηρέτησε την προηγούμενη φορά. Αν αυτό ήταν το τελευταίο, επιλέγεται το πρώτο
    ανοικτό.)(Υπόδειξη: μήπως χρειάζεστε κάποιο επιπλέον μέλος-δεδομένο για την υλοποίηση
    αυτή;).

    3) Κατόπιν, τυπώνονται τα εξής: το μήνυμα "Customer no:", ακολουθεί η τιμή της ένδειξης
    curr serving, ακολουθεί το μήνυμα "by cashier no:" και τέλος εκτυπώνεται η τιμή i.

    4) Στη συνέχεια, το επιλεγμένο ταμείο εξυπηρετεί τον πελάτη και κατόπιν ελευθερώνεται.

    CASHIERS) Στη συνέχεια πραγματοποιείται έξοδος πελάτη.
    */

    int selection;

    if (get_next_open() == -1) {    //ola kleista
        cout << "HELLO 1\t" << last_customer << '\t' << curr_serving << endl;
        selection = 0;              //select the first one
        cashiers[selection].open();
    }
    else {
        cout << "HELLO 2\t" << last_served << endl;
        selection = get_next_open(last_served);
    }

    cout << "[Trapeza:serve] Custoner no: " << curr_serving
        << "\n\t\tby cashier no: " << (selection+1) << endl;

    cashiers[selection].serve();
    last_served = selection;
    cashiers[selection].free(Tameio_Limit);
    exit();
}

void Trapeza::exit() {
    // check whether we have too many open
    if (check_to_close()) {
        // close the next open
        close(get_next_open());
    }
    ++curr_serving;
}

void Trapeza::open(int tameio_id) {
    cashiers[tameio_id].open();
    cout << "[Trapeza]::open Opened Cashier with number: " << tameio_id+1 << "\n";
}

void Trapeza::close(int tameio_id) {
    cashiers[tameio_id].close();
    cout << "[Trapeza]::close Closed Cashier with number: " << tameio_id+1 << "\n";
}

bool Trapeza::check_to_open() {
    /*  Checks if the open cashiers are enough,
        essentially it checks whether the waiting between the number of 
        customers in the bank and number of customers being served is bigger
        than the number of open cashiers times K (ti einai to kappa?)
    */

    int waiting = last_customer - curr_serving;

    if (waiting > (get_open() * Trapeza_Limit))
        return true;
    else return false;

    //return (waiting > (get_open() * Trapeza_Limit)) ? true : false;
}

bool Trapeza::check_to_close() {
    /* Checks if open cashiers are too many */

    int waiting = last_customer - curr_serving;

    if (waiting <= ((get_open() - 1) * Trapeza_Limit)) {
        cout << "[Trapeza::check_to_close] " << waiting << endl;
        return true;
    }
    else return false;

    //return (waiting <= ((get_open() - 1) * Trapeza_Limit)) ? true : false;
}

void Trapeza::open_cashiers() {
    cout << "[Trapeza::open_cashiers] The number of open Cashiers is: " << get_open() << "\n";
}

int Trapeza::get_open() {
    /* Helper function that counts how many cashiers are open */
    int counter = 0;
    for (int i = 0; i < CASHIERS; ++i) {
        if ( cashiers[i].is_open() )
            counter++;
    }
    return counter;
}

int Trapeza::get_next_closed() {
    /* Returns the index of the next Cashier that is closed */
    for (int i = 0; i < CASHIERS; ++i) {
        if ( !(cashiers[i].is_open() ) ) // if cashier at i is closed
            return i;
    }
    // if all are open return error
    return -1;
}

int Trapeza::get_next_open(int cyclic) {
    /* Returns the index of the next Cashier that is open and free
        it has a cyclic property that if an argument is present
        it will iterate with that as first index. Also it's overloaded
    */
    // go to the next one from the last
    ++cyclic;
    assert(cyclic >= 0 && cyclic < CASHIERS);

    // run for 5 times
    for (int i = 0; i < CASHIERS; ++i) {
        // if cashier at i is open and free
        if ( cashiers[(cyclic % CASHIERS)].is_open()
                    && cashiers[(cyclic % CASHIERS)].is_free() )
            return (cyclic % CASHIERS);
        else
            ++cyclic;
    }
    return -1;
}

int Trapeza::get_next_open() {
    /* Returns the index of the next Cashier that is open and free
    */
    for (int i = 0; i < CASHIERS; ++i) {
        // if cashier at i is open and free
        if ( cashiers[i].is_open() && cashiers[i].is_free() )
            return i;
    }
    return -1;
}