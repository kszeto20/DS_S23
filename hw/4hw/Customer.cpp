#include "Inventory.h"
#include "Customer.h"

void Customer::c_addRent(Inventory& tool) {
    list<Inventory>::iterator ritr = c_rent.begin();
    while (ritr != c_rent.end()) {
        Inventory t = *ritr;
        if (tool.t_getId() < t.t_getId()) {
            c_quantity += tool.t_getQuant();
            c_rent.insert(ritr, tool);
            return;
        }
        ritr++;
    }
    c_rent.push_back(tool);
    c_quantity += tool.t_getQuant();
    return;
}

void Customer::c_addPend(Inventory& tool) {
    list<Inventory>::iterator pitr = c_pend.begin();
    while (pitr != c_pend.end()) {
        Inventory t = *pitr;
        if (tool.t_getId() < t.t_getId()) {
            c_pend.insert(pitr, tool);
            return;
        }
        pitr++;
    }
    c_pend.push_back(tool);
    return;

}

void Customer::c_removeRent(Inventory& tool) {
    list<Inventory>::iterator ritr = c_rent.begin();
    while (ritr != c_rent.end()) {
        Inventory t = *ritr;
        if (tool.t_getId() == t.t_getId()) {
            c_quantity -= tool.t_getQuant();
            c_rent.erase(ritr);
            return;
        }
        ritr++;
    }
    cerr << "Customer " << c_id << " attempted to return item " << tool.t_getId() << " which she/he did not rent." << endl;
    return;
}

void Customer::c_removePend(Inventory& tool) {
    list<Inventory>::iterator pitr = c_pend.begin();
    while (pitr != c_pend.end()) {
        Inventory t = *pitr;
        if (tool.t_getId() == t.t_getId()) {
            c_pend.erase(pitr);
            return;
        }
        pitr++;
    }
    return;

}