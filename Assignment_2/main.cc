#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "trapeza.h"

using namespace std;

void usage(char *progName) {
    /*
        Print command line usage parameters
    */
    cout << "Wrong number of arguments provided\n"
        << "Usage:\t\"banking <K> <M> <N> <L>\"\n";
}


int main(int argc, char **argv) {

    int M, N;

    if (argc < 5) {
        usage(argv[0]);
        exit(-1);
    }

    /* Objective #1, Init the Trapeza */
    Trapeza bank;

    /* Parse the arguments */
    bank.Trapeza_Limit = atoi(argv[1]);
    assert(bank.Trapeza_Limit > 0);

    /* Sanitize inputs */
    M  = atoi(argv[2]);
    assert(M > 0);

    N  = atoi(argv[3]);
    assert(N > 0);

    bank.Tameio_Limit  = atoi(argv[4]);
    assert(bank.Tameio_Limit > 0);

    /* Objective #2, Do tricks */
    int waiting = 0;
    for (int times = 0; times < M; ++times) {

        // Serve the Mth wave of N pelates
        for (int pelates = 0; pelates < N; ++pelates) {
            /* Check that customer can enter;
                If so serve() them, else add them to waiting */
            if (bank.enter()){
                bank.serve();
            }
            else waiting++;
        }
        cout << "[MAIN] Customers waiting after wave " << times
                << " are: " << waiting << endl;


        /* Now serve those who were waiting */
        int curr_waiting = waiting;
        for (int pelates = 0; pelates < curr_waiting; ++pelates) {
            if (bank.enter()){
                bank.serve();
                --waiting;
            }
        }
        cout << "[MAIN] Customers after waiting cleanup: " << waiting << endl;
    }

    return 0;
}