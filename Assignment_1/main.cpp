#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "bookcase.h"

using namespace std;

string TheBoks[15] = { "Clean Code", "Eating At The East", "Rescue At The Forest",
                        "Theories of Programming Languages", "1984", "CLRS",
                        "Tractatus Logicophilosophicus", "UNIX Bible",
                        "Practical Binary Analysis", "Being and Time",
                        "Askitiki", "Ylysses", "Du Contrat Social", "Catch-22",
                        "The Portrait of the Artist as a Young Man"};

string ThePpls[15] = { "John Cena", "Antonis Remos", "Sakis Rouvas", "Sotis Volanis",
                        "Ksaderfos Saki Rouva", "Valianatos", "Nikos Kafetzis",
                        "Nikos Kalantas", "Kostas Kavourdiris", "Giannis Toras",
                        "Pasxalis Terzis", "Foivos", "Giorgos Lebesis", 
                        "Kelli Kelekidou", "Stamatis Gardelis"};

void usage(char *progName) {
    /*
        Print command line usage parameters
    */
    cout << "Wrong number of arguments provided\n"
        << "Usage:\t\"vivliothiki <N> <L> <K1> <K2>\"\n";
}


int main(int argc, char **argv) {

    int NMax, L, K1, K2;

    // init random time
    srand(time(0));

    // Exit process if wrong arguments given
    if (argc < 5) {
        usage(argv[0]);
        exit(-1);
    }

    /* Parse the arguments */
    NMax = atoi(argv[1]);
    assert(NMax > 0);

    L = atoi(argv[2]);
    assert(L > 0);

    K1 = atoi(argv[3]);
    assert(K1 > 0);

    K2 = atoi(argv[4]);
    assert(K2 > 0);

    /* Objective #1, Init the Bookcase */
    Bookcase exLib = Bookcase(NMax);

    /* Objective #2: mek-L-bok */
    Book helpers[L];
    for (int l = 0; l < L; ++l) {
        string title  = string(TheBoks[rand() % 15]);
        string author = string(ThePpls[rand() % 15]);
        int ISBN      = 1234+(rand() % L);

        helpers[l] = {title, author, ISBN};
    }

    /* Objective #3, Make K1 random place_book() calls */
    for(int insertion = 0; insertion < K1; insertion++) {

        // Random place_book operation
        short operation = (rand() % 5) + 1;

        // Make sure these are indeed books
        //if (insertion % 5 == 2) print_book(&helper);

        /* Put it in the Bookcase */
        exLib.place_book(operation, helpers[rand() % L]);
    }

    /* Objective #4, Make K2 random take_book calls */
    for(int deletion = 0; deletion < K1; deletion++) {

        short operation = (rand() % 5) + 1;
        exLib.take_book(operation);
    }

    /* Objective #5, Print Bookcase */
    exLib.print();

    return 0;
}