#ifndef __customer_h
#define __customer_h

#include <iostream>
#include <list>
#include <iterator>

using std::cout; using std::cerr; using std::endl; using std::string; using std::list;

class Inventory;
#include "Inventory.h"

class Customer {
    public:
    // Constructor
    Customer();
    Customer(string id, string name, int quantity) { c_id = id; c_name = name; c_quantity = quantity;}
    Customer(string id, string name) { c_id = id; c_name = name; c_quantity = 0;}
    Customer(string id, string name, int quantity, string time) {c_id = id; c_name = name; c_quantity = quantity; c_time = time; }
    // accessors
    string c_getId() { return c_id; }
    string c_getName() { return c_name; }
    int c_getQuant() { return c_quantity; }
    string c_getTime() { return c_time; }
    list<Inventory> c_getRent() {return c_rent; }
    list<Inventory> c_getPend() {return c_pend; }
    
    void c_addRent(Inventory& tool);
    void c_addPend(Inventory& tool);

    void c_removeRent(Inventory& tool);
    void c_removePend(Inventory& tool);

    private:
    string c_id;
    string c_name;
    int c_quantity;
    string c_time;

    list<Inventory> c_rent;
    list<Inventory> c_pend;

};


#endif