#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

/* Creature desc */
class creature {
    public:
        int life;
        int homeAddress;
        string name;
        void *home;
        int Thr;
        bool is_zobie;

        //default
        creature();
        //parameterized
        creature(int, int);
        //copy constructor
        //creature(const creature&);
        //op overload
        //creature& operator=(const creature&);
        //destructor
        virtual ~creature();


        void clone(creature *);
        virtual void bless();
        void beat();

        bool is_a_zobie();
        virtual bool is_a_good()=0;

        void print();
};

class good_creature: public creature {
    public:
        //default
        good_creature();
        //parameterized
        good_creature(int, int, int, void *);
        //copy constuctor
        //good_creature(const good_creature&);
        // copy operator
        //good_creature& operator=(const good_creature&);
        //destructor
        ~good_creature();

        bool is_a_good();
        void bless();

};

class bad_creature: public creature {
    public:
        //default
        bad_creature();
        //parameterized
        bad_creature(int, int, int, void *);
        //copy constructor
        //bad_creature(const bad_creature&);
        //destructor
        ~bad_creature();

        bool is_a_good();
        void bless();
};

class creature_society {
    public:
        int numberOfCreatures;
        int life;
        // hacky way using std::c++14 feature to overload deriveds on base
        vector<std::unique_ptr<creature>> Plasmata;

        creature_society(int, int, int, int);
        ~creature_society();

        void beat_i(int);
        void bless_i(int);

        void clone_next(int);
        void clone_zobies(int);

        int no_of_good();
        int no_of_zobies();

        void check();
};