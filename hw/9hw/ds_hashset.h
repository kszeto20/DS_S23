#ifndef ds_hashset_h_
#define ds_hashset_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using std::string; using std::ostream; using std::cout; using std::endl; using std::list; using std::vector; using std::pair;

class Qresult {
    public: 
    Qresult(int pos, int err, string& keys) { position = pos; error = err; key = keys;}

    void print_out(ostream& ostr) { // helper so we don't need accessor functions for print
        ostr << position << " " << error << " " << key << endl;
    }

    private:
    int position;
    int error;
    string key;
};


// ds_set structure from class material
template <class HashFunc>
class ds_hashset {
    public:    
    // CONSTRUCTORS

    // Constructor for the table accepts the size of the table.  Default
    // constructor for the hash function object is implicitly used.
    ds_hashset(unsigned int init_size = 100, float init_occ = 0.5) : m_table(init_size), m_size(0), m_occ(init_occ) {}
    
    // Copy constructor just uses the member function copy constructors.
    ds_hashset(const ds_hashset<HashFunc>& old) 
        : m_table(old.m_table), m_size(old.m_size), m_occ(old.m_occ) {}

    ~ds_hashset() {} // destructor

    // = assignment operator
    ds_hashset& operator=(const ds_hashset<HashFunc>& old) {
        if (&old != this) { // if it isn't already the same thing
        this->m_table = old.m_table;
        this->m_size = old.m_size;
        this->m_hash = old.m_hash;
        this->m_occ = old.m_occ;
        }
        return *this;
    }
    
    // modifiers
    void setSize(int n_size) { m_size = n_size; resize_table(n_size); } // replace with new size
    void setOcc(float n_occ) { m_occ = n_occ; } // replace with new occupancy

    // purpose: get list of indexes that represent the first letter of a similar pattern to the query
    // parameters: (key) query, (kmer) size, (positioins) list to hold - fed in as an empty list
    // returns: void - list is directly reassigned to positions parameter
    void find(const string& key, int kmer, list<int>& positions) {
        // get key fragment
        string key_frag = key.substr(0, kmer);
        //  Compute the hash value and then the table index
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();

        for (int i = index + 1; i < m_table.size(); i++) { // go through existing values in table
            if (m_table[i].first == key_frag) { index = i; break; } // if found, update ind
            if (i == m_table.size() - 1) { i = -1; } // if at end, loop back to front and keep looking
            else if (i == index) { return; } // if never found, return immediately;
        }
        positions = m_table[index].second; // reassign positions to the corresponding list
        return;
    }

    // given a position to insert, insert key at position
    // purpose: given a string, insert into 
    // returns: void - nothing to return 
    void insert(const string& key, int position) {
        // check if too populated
        int max_allowed = (int)floor(m_occ*m_table.size());
        if (m_size >= max_allowed) { this->resize_table(2*m_table.size() + 1); }


        //  Compute the hash value and then the table index
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();
        bool found = true;

        while (m_table[index].first != key && index != m_table.size()) { // while the key has not been found
            index++;                
            // if at end, loop back to the front
            if (index == m_table.size()) { index = 0; }
            // if back to same position; break out of loop
            if (index == hash_value % m_table.size()) { found = false; break; }
        }
        
        // if never found
        if (found == false) {
            // loop to the first empty space
            while (m_table[index].first != "" && index != m_table.size()) {
                index++;
                if (index == m_table.size()) { index = 0; } // if at end loop back to front
            }
            // at first empty space, make entry
            m_table[index] = std::make_pair(key, list<int>()); 
            m_size++; // update size
        }

        m_table[index].second.push_back(position); // add position to the correspoding list

    }


    private:
    // resize the table with the same values but twice as many buckets
    void resize_table(unsigned int new_size) {

        vector< pair<string, list<int> > > new_table(new_size); // create new table
        for (int i = 0; i < m_table.size(); i++) { // for each value in the old table
            if (m_table[i].first.size() == 0) { continue; }
            else { // if not empty
                // Calculate the hash again
                string new_key = m_table[i].first;
                unsigned int hash_value = m_hash(new_key);
                unsigned int index = hash_value % m_table.size();

                while (index < new_table.size()) {
                    if (new_table[index].first.size() == 0) {
                        new_table[index] = m_table[i];
                        break;
                    }
                    index++;
                    if (index == new_table.size()) { index = 0; }
                }                    
            }
        }

        this->m_table = new_table; // reasssign table
    }

    // =================================================================
    // HASH SET REPRESENTATION
    vector< pair<string, list<int> > > m_table;  // actual table
    HashFunc m_hash;                            // hash function
    unsigned int m_size;                        // number of keys
    float m_occ;

};

#endif