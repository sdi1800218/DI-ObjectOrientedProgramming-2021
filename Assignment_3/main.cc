/* Makes a creature society and initializes, plays with it and checks it */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "creature.h"

using namespace std;

void usage(char *progName) {
    /*
        Print command line usage parameters
    */
    cout << "Wrong number of arguments provided\n"
        << "Usage:\t\"froutopia <N> <M> <L> <GT> <BT>\"\n";
}


int main(int argc, char **argv) {

    int M, N, L, good_thr, bad_thr;

    if (argc != 6) {
        usage(argv[0]);
        exit(-1);
    }

    // seed pseudorandom gen
    srand(time(0));

    /* Parse the arguments */
    N = atoi(argv[1]);
    assert(N > 0);

    /* Sanitize inputs */
    M = atoi(argv[2]);
    assert(M > 0);

    L = atoi(argv[3]);
    assert(L > 0);

    good_thr = atoi(argv[4]);
    assert(good_thr > 0);

    bad_thr = atoi(argv[4]);
    assert(bad_thr > 0);

    /* Objective #1, Make a society */
    creature_society *MySpace = new creature_society(N, L, good_thr, bad_thr);

    /* Objective #2, Do tricks */
    for (int times = 0; times < M; ++times) {
        // Choose a randoms
        int rand_creature = rand() % N;
        int rand_action = rand() % 2;

        /* 0: bless(), 1: beat() */
        if (rand_action == 0)
            MySpace->bless_i(rand_creature);
        else
            MySpace->beat_i(rand_creature);
    }

    /* Objective #3, Check society */
    MySpace->check();

    return 0;
}