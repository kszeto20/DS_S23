#include "Inventory.h"
#include "Customer.h"

using std::cout; using std::cerr; using std::endl; using std::string; using std::list; 

void Inventory::t_addRent(Customer& custee) {
    list<Customer>::iterator ritr = t_rent.begin();
    while (ritr != t_rent.end()) {
        Customer c = *ritr;
        if (custee.c_getId() < c.c_getId()) {
            t_quantity -= custee.c_getQuant();
            t_rent.insert(ritr, custee);
            return;
        }
        ritr++;
    }
    t_quantity -= custee.c_getQuant();
    t_rent.push_back(custee);
    return;
}

void Inventory::t_addPend(Customer& custee) {
    list<Customer>::iterator pitr = t_pend.begin();
    while (pitr != t_pend.end()) {
        Customer c = *pitr;
        if (custee.c_getTime() < c.c_getTime()) {
            t_pend.insert(pitr, custee);
            return;
        }
        pitr++;
    }
    t_pend.push_back(custee);
    return;
}

void Inventory::t_removeRent(Customer& custee) {
    list<Customer>::iterator ritr = t_rent.begin();
    while (ritr != t_rent.end()) {
        Customer c = *ritr;
        if (custee.c_getId() == c.c_getId()) {
            t_quantity += custee.c_getQuant();
            t_rent.erase(ritr);
            return;
        }
        ritr++;
    }
    return;
}

void Inventory::t_removePend(Customer& custee) {
    list<Customer>::iterator pitr = t_pend.begin();
    while (pitr != t_pend.end()) {
        Customer c = *pitr;
        if (custee.c_getId() == c.c_getId()) {
            t_pend.erase(pitr);
            return;
        }
        pitr++;
    }
    // not actually on pending? 
    return;
}

string Inventory::t_updatePend() {
    list<Customer>::iterator pitr = t_pend.begin();
    while (pitr != t_pend.end()) {
        Customer c = *pitr;
        if (c.c_getQuant() <= t_quantity) {
            t_removePend(c);
            t_addRent(c);
            t_waitlistQ = c.c_getQuant();
            string toRet = c.c_getId();
            return toRet;
        }
        pitr++;
    }
    return "not_init";
}