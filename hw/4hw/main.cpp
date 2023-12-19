#include "Customer.h"
#include "Inventory.h"

#include <iostream>
#include <list>
#include <iterator>
#include <fstream>

using std::cout; using std::cerr; using std::endl; using std::list; using std::ifstream; using std::ofstream;

/*
function to insert new customers into the list of customers according to id
parameters: custees --> list of existing customers, toIn --> customer to push into list

psuedocode -
loop through list
if customer id of toIn is ever less than customer id of customer at iterator -- insert at that iterator and break out of loop
else -- increment iterator and keep checking

if never inserted - just add toIn to the back of the list
*/

void c_listInsert(list<Customer>& custees, Customer& toIn) {
    typename list<Customer>::iterator citr = custees.begin();
    while (citr != custees.end()) {
        Customer c = *citr;
        if (toIn.c_getId() < c.c_getId()) {
            custees.insert(citr, toIn);
            return;
        }
        citr++;
    }
    custees.push_back(toIn);
    return;
}

/*
function to insert new inventory into the list of inventory (tools) according to id
parameters: invnetory --> list of existing inventory(tool), toIn --> inventory to push into list

psuedocode -
loop through list
if inventory id of toIn is ever less than inventory id of inventory at iterator -- insert at that iterator and break out of loop
else -- increment iterator and keep checking

if never inserted - just add toIn to the back of the list
*/
void t_listInsert(list<Inventory>& inventory, Inventory& toIn) {
    typename list<Inventory>::iterator iitr = inventory.begin();
    while (iitr != inventory.end()) {
        Inventory i = *iitr;
        if (toIn.t_getId() < i.t_getId()) {
            inventory.insert(iitr, toIn);
            return;
        }
        iitr++;
    }
    inventory.push_back(toIn);
    return;
}

/*
function: to read and populate a list representing the inventory
parameters: inF --> instream from a file to read from

psuedocode -
while there are words to read in:
    according to count: --> assign the values read in to their corresponding holder variables
    count = 0 --> check for valid inventory id - if valid store into id variable
    count = 1 --> check for valid id - if valid store into quant variable
    count = 2 --> ASSUMED NAME INPUT WILL ALWAYS BE VALID - store into name variable

    once all names are read in properly (count == 3) 
        --> create inventory object with corresponding attributes
        --> add the inventory object into the list

*/
list<Inventory> readInv (ifstream& inF) {
    list<Inventory> toRet; // list of tools (inventory) to return and keep track of

    // attributes of tool to add
    string id;
    string name;
    int quant;
    
    string all_w;
    int count = 0;
    while (inF >> all_w) {
        if (count == 0) { // ID of next item
            if (all_w[0] != 'T') {
                cerr << "Invalid inventory ID " << all_w << " found in the inventory file." << endl;
            }
            else {
                int numID = stoi(all_w.substr(1, all_w.length() - 1));
                if (numID <= 0) {
                    cerr << "Invalid inventory ID " << all_w << " found in the inventory file." << endl;
                }
                else {
                    id = all_w;
                }
            }
        }
        else if (count == 1) { // number of new item
            int numIN = stoi(all_w);
            if (numIN <= 0) {
                cerr << "Invalid inventory ID " << all_w << " found in the inventory file." << endl;
            }
            else {
                quant = numIN;
            }
        }
        else if (count == 2) { // tool name
            name = all_w;
        }
        count++;
        if (count == 3) { // if all 3 attributes have been created ...
            // create the object
            Inventory toAdd = Inventory(id, name, quant);
            t_listInsert(toRet, toAdd);
            count = 0;
        }
    }
    return toRet;
}

/*
function: to read and populate a list of customers
parameters: toolies --> list of inventory, inF --> instream with words to read in

psuedo code:
while there are words to read in:
    according to counter --> assign values to corresponding holder values
    counter == 0 --> check for valid inventory, assign to id if valid
    counter == 1 --> ASSUMMED it will always be rent or return --> change toRent boolean = true if rent, false if return
    counter == 2 --> ASSUMMED time is always valid --> assign to time variable
    counter == 3 --> if # > 0 --> assigned to quantity 
    counter == 4 --> check if given tool ID is inventory --> if in tool, store in toolId
    coutner == 5 --> ASSUMMED name will always be in valid input --> store in name

    when counter == 6:
        process the request


to process the request:
    if rent:
        check if tool exists
        if tool exist:
            check is quantity is sufficient for request
            if sufficient:
                check to see if Customer is new or existing
                if existing:
                    add tool to renting list

                    add customer to tool's renters list
                else:
                    create new customer
                    add tool to renting list
                    add to customer list

                    add customer to tools renters list

            if not sufficient:
                check to see if Customer is new or existing
                if existing:
                    add tool to pending list

                    add customer to tool's pending list
                else:
                    create new customer
                    add tool to pending list
                    add to customer list

                    add customer to tool's pending list
        else:
            throw error because that tool doesnt exist
    else: (return case)
        check if tool exists
        if tool exists:
            if customer exists:
                if tool is in customer's renting list:
                    remove tool from customer's renting list

                    remove customer from tool's renting list
                else:
                    throw error (tool wasn't rented by this customer)
            else:
                throw error
        else:
            throw error (tool doesnt exist)
        
        check waitlist:
            take off any pendings available
    
*/

list<Customer> readCust(list<Inventory>& toolies, ifstream& inF) {
    list<Customer> custees;


    string id;
    string name;
    int quantity;
    string time;
    string toolId; 

    bool toRent = false;
    
    list<Inventory>::iterator titr;
    list<Customer>::iterator citr;

    int counter = 0;
    string all_w;
    while (inF >> all_w) {
        if (counter == 0) {
            if (all_w[0] != 'C') {
                cerr << "Invalid customer information found for ID " << all_w << " int the customer file." << endl;
            }
            else {
                string digits = all_w.substr(1, all_w.length() - 1);
                int n = stoi(digits);
                if (n <= 0) {
                    cerr << "Invalid customer information found for ID " << all_w << " int the customer file." << endl;
                }
                else {
                    id = all_w;
                }

            }
            
        }
        else if (counter == 1) {
            if (all_w == "rent") {
                toRent = true;
            }
            else if (all_w == "return") {
                toRent = false;
            }
        }
        else if (counter == 2) {
            time = all_w;
        }
        else if (counter == 3) {
            int q = stoi(all_w);
            if (q < 0) {
                cerr << "Invalid customer information found for ID " << all_w << " int the customer file." << endl;
            } 
            else {
                quantity = q;

            }
        }
        else if (counter == 4) {
            bool found = false;
            list<Inventory>::iterator tNames = toolies.begin();
            while (tNames != toolies.end()) {
                Inventory t = *tNames;
                if (t.t_getId() == all_w) {
                    found = true;
                    break;
                }
                tNames++;
            }
            if (!found) {
                cerr << "Invalid customer information found for ID " << all_w << " int the customer file." << endl;
            }
            else {
                toolId = all_w;
            }
        }
        else if (counter == 5) {
            name = all_w;
        }
        counter++;

        if (counter == 6) { // time to process request
            if (toRent) {
                titr = toolies.begin();
                bool foundTool = false;
                while (titr != toolies.end() && foundTool == false) {
                    Inventory t = *titr;
                    if (t.t_getId() == toolId) { // tool exists
                        foundTool = true;
                        if (quantity <= t.t_getQuant()) { // sufficient quantity for request
                            citr = custees.begin();
                            bool foundCust = false;
                            while (citr != custees.end() && foundCust == false) {
                                Customer c = *citr;
                                if (c.c_getId() == id) { // customer exists

                                    // update customer stats
                                    foundCust = true;
                                    Inventory newT = Inventory(toolId, quantity);
                                    c.c_addRent(newT);
                                    *citr = c;

                                    // update tool stats
                                    Customer newC = Customer(id, name, quantity);
                                    t.t_addRent(newC);
                                    *titr = t;
                                }
                                else {
                                    citr++;
                                }
                            }
                            if (foundCust == false) { // customer does not exist yet

                                Customer c = Customer(id, name);
                                Inventory newT = Inventory(toolId, quantity);
                                c.c_addRent(newT); // add tool to customer rented list
                                c_listInsert(custees, c); // add customer into list

                                // update tool stats
                                Customer newC = Customer(id, name, quantity);
                                t.t_addRent(newC);
                                *titr = t;
                            }
                        }
                        else  { // insufficient quantity --> waitlist
                            citr = custees.begin();
                            bool foundCust = false;
                            while (citr != custees.end() && foundCust == false) {
                                Customer c = *citr;
                                if (c.c_getId() == id) { 

                                    // customer exists
                                    foundCust = true;
                                    Inventory newT = Inventory(toolId, quantity);
                                    c.c_addPend(newT); // update customer
                                    *citr = c;

                                    // update tool stats
                                    Customer newC = Customer(id, name, quantity, time);
                                    t.t_addPend(newC);
                                    *titr = t;                                 
                                }
                                else {
                                    citr++;
                                }
                            }
                            if (foundCust == false) { 
                                // customer does not exist
                                Customer c = Customer(id, name);
                                Inventory newT = Inventory(toolId, quantity);
                                c.c_addPend(newT); // add tool to customer pending list
                                c_listInsert(custees, c); // add customer into list

                                // update tool stats
                                Customer newC = Customer(id, name, quantity, time);
                                t.t_addPend(newC);
                                *titr = t;   
                            }                                        
                        }
                    } 
                    else {
                        titr++;
                    }
                }
                if (foundTool == false) {
                    cerr << "Customer " << id << " requested item " << toolId << " which is not in the inventory." << endl;
                }
            }
            else {
                titr = toolies.begin();
                bool foundTool = false;
                while (titr != toolies.end() && foundTool == false) {
                    Inventory t = *titr;
                    if (t.t_getId() == toolId) { // tool exists
                        foundTool = true;
                        citr = custees.begin();
                        bool fCust = false;
                        while (citr != custees.end() && fCust == false) { 
                            Customer c = *citr;
                            if (c.c_getId() == id) { // customer exists
                                // update customer
                                fCust = true;
                                Inventory newT = Inventory(toolId, quantity);
                                c.c_removeRent(newT);
                                *citr = c;

                                // update tool attributes
                                Customer newC = Customer(id, name, quantity);
                                t.t_removeRent(newC);
                                *titr = t;

                                // check waitlist
                                string changed = t.t_updatePend();
                                *titr = t;
                                bool ced = false;
                                if (changed != "not_init") { // if pending was changed
                                    list<Customer>::iterator wcitr = custees.begin();
                                    while (wcitr != custees.end() && ced == false) {
                                        Customer nwc = *wcitr;
                                        if (nwc.c_getId() == changed) {
                                            ced = true;
                                            Inventory i = Inventory(t.t_getId(), t.t_getWaitlistQ());
                                            // update customer info as well
                                            nwc.c_removePend(i);
                                            nwc.c_addRent(i);
                                            *wcitr = nwc;

                                        }
                                        wcitr++;
                                    }
                                    
                                }
                            }
                            else {
                                citr++;
                            }
                        }
                        if (fCust == false) { // never a customer
                            cerr << "1Customer " << id << " attempted to return item " << toolId << " which she/he did not rent." << endl;                            
                        }
                    }
                    else {
                        titr++;
                    }
                }
                if (foundTool == false) {
                    cerr << "2Customer " << id << " attempted to return item " << toolId << " which is not in the inventory." << endl; 
                }
            }
            counter = 0;
            
        }
    }
    return custees;
}

/*
function: write info to outfile
parameters: custees --> list of customers, outc --> outfile

psuedocode:
for each customer:
    check if there is any pending/ rented tools
    if there are:
        write out  any rented tools
        write out any pending tools
    else: 
        don't write out anything
*/

void c_print(list<Customer>& custees, ofstream& outc) {
    // customers
    list<Customer>::iterator co = custees.begin();
    while (co != custees.end()) {
        Customer a = *co;
        list<Inventory> cR = a.c_getRent();
        list<Inventory> cP = a.c_getPend();

        if (cR.size() > 0 || cP.size() > 0) {
            outc << a.c_getId() << " " << a.c_getName() << endl;
            if (cR.size() > 0) {
                list<Inventory>::iterator renters = cR.begin();
                outc << "Rentals: ";
                while (renters != cR.end()) {
                    Inventory test = *renters;
                    outc << test.t_getId() << " (" << test.t_getQuant() << ") ";
                    renters++;
                }
                outc << endl;
            }
            if (cP.size() > 0) {
                list<Inventory>::iterator penders = cP.begin();
                outc << "Pending: ";
                while (penders != cP.end()) {
                    Inventory test = *penders;
                    outc << test.t_getId() << " (" << test.t_getQuant() << ") ";
                    penders++;
                }
                outc << endl;
            }
            outc << endl;
        }
        co++;
    }
}

/*
function: write info to outfile
parameters: toolies --> list of inventory, outc --> outfile

psuedocode:
for each inventory:
    check if there is any pending/ renter customers
    if there are:
        write out any rented customers
        write out any pending customers
    else: 
        don't write out anything
*/

void t_print(list<Inventory> & toolies, ofstream& outc) {
    // tools
    list<Inventory>::iterator to = toolies.begin(); 
    while (to != toolies.end()) {
        Inventory a = *to;
        list<Customer> tR = a.t_getRent();
        list<Customer> tP = a.t_getPend();

        outc << a.t_getId() << " " << a.t_getQuant() << " available " << a.t_getName() << endl;
        if (tR.size() > 0) {
            list<Customer>::iterator renters = tR.begin();
            outc << "Rental Customers: ";
            while (renters != tR.end()) {
                Customer test = *renters;
                outc << test.c_getId() << " " << test.c_getName() << " " << "(" << test.c_getQuant() << ") ";
                renters++;
            }
            outc << endl;
        }
        if (tP.size() > 0) {
            list<Customer>::iterator penders = tP.begin();
            outc << "Pending Customers: ";
            while (penders != tP.end()) {
                Customer test = *penders;
                outc << test.c_getId() << " " << test.c_getName() << " " << "(" << test.c_getQuant() << ") ";
                penders++;
            }
            outc << endl;
        }       
        outc << endl;
        to++;
    }

}



int main(int argc, char* argv[]) {

    if (argc != 5) { // check for correct # of args
        cerr << "Incorrect amount of arguments supplied" << endl;
        exit(1);
    }

    // try to open files

    // inventory file (read)
    ifstream in_inv(argv[1]);
    if (!in_inv.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n" << endl;
        exit(1);
    }

    // customer file (read)
    ifstream in_cust(argv[2]);
    if (!in_cust.good()) {
        cerr << "Can't open " << argv[2] << " to read.\n" << endl;
        exit(1);
    }

    // inventory outfile (write)
    ofstream out_inv(argv[3]);
    if (!out_inv.good()) {
        cerr << "Can't open " << argv[3] << " to write.\n" << endl;
        exit(1);
    }

    // inventory outfile (write)
    ofstream out_cust(argv[4]);
    if (!out_cust.good()) {
        cerr << "Can't open " << argv[4] << " to write.\n" << endl;
        exit(1);
    }

    // read in inventory
    list<Inventory> toolies = readInv(in_inv);
    // process the customer
    list<Customer> custees = readCust(toolies, in_cust);

    // write out info
    c_print(custees, out_cust);
    t_print(toolies, out_inv);
}