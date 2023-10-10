/* creatures and creature_society implementation */
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "creature.h"

using namespace std;

/* Default good creature names */
string good[8] = {"John", "Johnnie", "Jonny", "Janni", "Gianni",
                        "Iani", "JohnJohn", "Janos"};

/* Default bad creature names */
string bad[8] = {"Karras", "Billis", "Petaloudas", "Xtenas", "Kagelarios",
                        "Pergolas", "Xasapotavernas", "Volanis"};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* creature Implementation */
creature::creature() {
    /* Default Constructor */
    cout << "[creature::creature] Making a Creature\n";
    is_zobie = false;
}

creature::creature(int L, int Index) {
    /* Parameterized Constructor */
    cout << "[creature::creature] Making a Creature\n";
    is_zobie = false;
    life = L;
    homeAddress = Index;
}

/*
creature::creature(const creature &tar) {
    // Copy Constructor
    cout << "[creature::creature] Copy Constructor\n";
    life        = tar.life;
    name        = tar.name;
    home        = tar.home;
    homeAddress = tar.homeAddress;
    Thr         = tar.Thr;
    is_zobie    = tar.is_zobie;
}
*/

creature::~creature() {
    cout << "[creature::~creature] Destroying a creature\n";
    //delete this;
}

void creature::bless() {
    /* if not zobie, increase life */
    if ( !is_a_zobie() ) {
        cout << "[creature::bless] Blessing creature " << this->name << "\n";
        this->life += 1;
    }
    else return;
}

void creature::beat() {
    /* if not zobie, decrease life */
    if ( !is_a_zobie() ) {
        cout << "[creature::beat] Beating creature " << this->name << "\n";
        this->life -= 1;

        /* zobie check */
        if (this->life == 0) {
            this->is_zobie = true;
            cout << "\t Creature became a ZOBIE\n";
        }
    }
    else return;
}

bool creature::is_a_zobie() {
    return is_zobie;
}

void creature::clone(creature *Target) {
    cout << "[creature::clone] Cloning creature " << name
    << (Target->is_a_good() ? " bad" : " good") << "!\n";

    //delete Target; //sigsegv careful

    int index = Target->homeAddress;

    if (Target->is_a_good()) {
        *Target = *(good_creature *)this;
    }
    else {
        *Target = *(bad_creature *)this;
    }

    Target->homeAddress = index;
}

void creature::print() {
    cout << "[PRINT] CREATURE STATS\n\t" << "Name:\t\t" << name << "\n\t"
        << "Life:\t\t" << life << "\n\t" << "Community Index:\t"
        << homeAddress << "\n";
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* good_creature Implementation */
good_creature::good_creature() {
    /*
    if (is_a_good()) {
        name = good[rand() % 8];
    }
    else
        name = bad[rand() % 8];

    cout << "[good_creature::good_creature] Its a-good un named " << name << "!\n";
    */
}

good_creature::good_creature(int L, int Index, int goodThr, void *home)
                        : creature(L, Index)
{
    this->name = string(good[ rand() % 8 ]) + to_string(Index);
    this->Thr = goodThr;
    this->home = home;
    cout << "[good_creature::good_creature] Its a-good un named " << name << "!\n";
}

/*
good_creature::good_creature(const good_creature &tar)
            : creature(tar)
{
    cout << "Constructing a copy of creature named: " << this->name << endl;
}


good_creature& good_creature::operator=(const good_creature& tar)
{
    creature::operator=(tar);
    return *this;
};
*/

bool good_creature::is_a_good() {
    return true;
}

void good_creature::bless() {
    /* augments base class bless() functionality with cloning */

    creature::bless();
    if (this->is_a_zobie())
        return;
    else {
        cout << "\t\t It's a good creature!\n";
        if (this->life > this->Thr) {
            creature_society *Sauce = (creature_society *)home;
            Sauce->clone_next(homeAddress);
        }
        return;
    }
}

good_creature::~good_creature() {
    //delete this;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* bad_creature Implementation */
bad_creature::bad_creature() {
    //cout << "[bad_creature::bad_creature] Its a-bad un named " << name << "!\n";
}

bad_creature::bad_creature(int L, int Index, int badThr, void *home)
                        : creature(L, Index)
{
    this->name = string(bad[ rand() % 8 ]) + to_string(Index);
    this->Thr = badThr;
    this->home = home;
    cout << "[bad_creature::bad_creature] Its a-bad un named " << name << "!\n";
}

bool bad_creature::is_a_good() {
    return false;
}

void bad_creature::bless() {
    /* Extends Base and adds cloning functionality */
    creature::bless();
    if (this->is_a_zobie())
        return;
    else {
        cout << "\t\t It's a bad creature!\n";
        if (this->life > this->Thr) {
            creature_society *Sauce = (creature_society *)home;
            Sauce->clone_zobies(homeAddress);
            return;
        }
    }
}

bad_creature::~bad_creature() {
    //delete this;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* creature_society Implementation */

creature_society::creature_society(int N, int L, int goodThr, int badThr) {
    /* Requires number of creatures to contain and their Life expectancy */
    cout << "[creature_society] Making a Society!\n";
    numberOfCreatures = N;
    life = L;
    for (int creat = 0; creat < N; ++creat) {
        if (rand() % 2 == 0) {
            // good
            Plasmata.emplace_back(new good_creature(life, creat, goodThr, this));
        }
        else {
            // bad
            Plasmata.emplace_back(new bad_creature(life, creat, badThr, this));
        }
        // no ugly
    }
}

creature_society::~creature_society() {
    cout << "[creature_society::~creature_society] Destroying the Society\n";
    delete this;
}

void creature_society::beat_i(int i) {
    /* beats creature at i index */
    Plasmata[i]->beat();
}

void creature_society::bless_i(int i) {
    /* blesses creature at i index */
    Plasmata[i]->bless();
}

int creature_society::no_of_good() {
    /* returns number of good creatures in the society */
    int count = 0;
    for (int i = 0; i < numberOfCreatures; ++i) {
        if(Plasmata[i]->is_a_good())
            count++;
    }
    return count;
}

int creature_society::no_of_zobies() {
    /* returns number of zobie creatures in the society */
    int count = 0;
    for (int i = 0; i < this->numberOfCreatures; ++i) {
        if(Plasmata[i]->is_a_zobie())
            count++;
    }
    return count;
}

void creature_society::check() {
    // case 1: all creatures are good
    if (no_of_good() == numberOfCreatures) {
        cout << "[CHECK] Good Dominates in the World!\n";
        return;
    }
    // case 2: all creatures are zobies
    else if (no_of_zobies() == numberOfCreatures) {
        cout << "[CHECK] This is a dead society\n";
        return;
    }
    //case 3: gl next
    else {
        cout << "[CHECK] Try again to improve the world\n";
        return;
    }

}

void creature_society::clone_next(int i) {
    /* clones ith creature to i+1 (cyclical) */

    // get unique_ptr object
    creature *target = Plasmata[ ((i+1) % numberOfCreatures) ].get();
    Plasmata[i].get()->clone(target);

    Plasmata[i]->print();
    target->print();

}

void creature_society::clone_zobies(int i) {
    /* clones ith creature to all continouus occuring zobie creatures */

    //check that i is not the last creature
    if ( (i % numberOfCreatures != 0) ) {
        for (int pivot = i+1; pivot < numberOfCreatures; ++pivot) {
            //if zobie, clone i to it
            if (Plasmata[pivot]->is_a_zobie()) {
                Plasmata[i]->clone(Plasmata[pivot].get());
            }
            else //else break the loop
                break;
        }
    }
    return;
}