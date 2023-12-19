#ifndef __inventory_h
#define __inventory_h

#include <iostream>
#include <list>
#include <iterator>
#include <string>

using std::cout; using std::cerr; using std::endl; using std::string; using std::list; 

class Customer;

class Inventory {
    public:
    // constructor
    Inventory();
    Inventory(string id, string name, int quantity) { t_id = id; t_name = name; t_quantity = quantity; }
    Inventory(string id, int quantity) { t_id = id; t_quantity = quantity; }

    string t_getId() { return t_id; }
    string t_getName() { return t_name; }
    int t_getQuant() { return t_quantity; }
    list<Customer> t_getRent() { return t_rent; }
    list<Customer> t_getPend() { return t_pend; }
    int t_getWaitlistQ() { return t_waitlistQ; }

    void t_addRent(Customer& custee);
    void t_addPend(Customer& custee);
    
    string t_updatePend();
    int t_getPendQuant(Customer& custee);

    void t_removeRent(Customer& custee);
    void t_removePend(Customer& custee);

    private:
    string t_id;
    string t_name;
    int t_quantity;
    int t_waitlistQ;

    list<Customer> t_rent;
    list<Customer> t_pend;
};

#endif