#include <string>

using namespace std;

#define CASHIERS 5

class Tameio {
    private:
        /* True = Yes, False = No */
        bool open_flag, serving_flag;
        int customers_served;
    public:
        int Tameio_Limit;

        /* Build/destroy the tameio */
        Tameio();
        ~Tameio();

        /* Tameio methods */
        void open();
        void close();
        bool is_open();
        bool is_free();

        /* autaaaa */
        void serve();
        void free(int);
};

class Trapeza {
    private:
        int last_customer, curr_serving;
        Tameio cashiers[CASHIERS];
    public:
        int Trapeza_Limit;
        int Tameio_Limit;
        int last_served; //helper for serve()

        /* Constr/Destr */
        Trapeza();
        ~Trapeza();

        /* Customer behavior */
        bool enter();
        void serve();
        void exit();

        /* Cashier modus operandi */
        void open(int);
        void close(int);
        bool check_to_open();
        bool check_to_close();
        void open_cashiers();

        /* helper methods */
        int get_open();
        int get_next_closed();
        int get_next_open();
        int get_next_open(int);

};