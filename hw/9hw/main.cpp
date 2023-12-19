#include <iostream>
#include <fstream>
#include "ds_hashset.h"

using std::string; using std::ostream; using std::cout; using std::endl; using std::list; using std::vector; using std::cin;

// Wrapping a class around a function turns a function into a functor
// (We'll talk about this more in Lecture 22.  You can just ignore
// this wrapper part for now.)
class hash_string_obj {
public:

  // ----------------------------------------------------------
  // EXPERIMENT WITH THE HASH FUNCTION FOR CHECKPOINT 1, PART 2

  unsigned int operator() ( const std::string& key ) const {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    //
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
  
};

typedef ds_hashset<hash_string_obj> ds_hashset_type;

int main() {
    ds_hashset_type hash_table;
    string genome_in;
    int kmer;
    
    string temp;
    while (cin >> temp) {
        if (temp == "genome") { // read in the genome to compare to
            cin >> temp; // get the input name
            std::ifstream genfile(temp);
            if(!genfile){
                std::cerr << "Failed to open genome file " << temp << " for reading." << std::endl;
                exit(1);
            }
            while (genfile >> temp) {
                genome_in += temp;
            }
        }
        else if (temp == "table_size") {
            cin >> temp; // get size to set
            int n_size = stoi(temp);
            hash_table.setSize(n_size);
        }
        else if (temp == "occupancy") {
            cin >> temp; // get occupancy ratio
            float n_occ = stof(temp);
            if (n_occ < 0 || n_occ > 1) {
                std::cerr << "occupancy ratio not allowed please try again" << endl;
                continue;
            }
            hash_table.setOcc(n_occ);
        }
        else if (temp == "kmer") {
            cin >> temp; // get kmer value
            kmer = stoi(temp);
            
            for (int i = 0; i < genome_in.size() - kmer; i++) { // populate hash table
                // fragments of kmer size, increasing first by one letter
                string to_add = genome_in.substr(i, kmer);
                hash_table.insert(to_add, i);
            }
        }
        else if (temp == "query") {
            cin >> temp; // get allowed mismatches
            int mismatch_max = stoi(temp);
            cin >> temp; // get query sequence

            cout << "Query: " << temp << endl;

            list<int> potential_pos = list<int>(); // to store 
            hash_table.find(temp, kmer, potential_pos);

            

            if (potential_pos.size() == 0) {
                cout << "No Match" << endl;
            }
            else {
                std::vector<Qresult> results;
                list<int>::iterator pitr = potential_pos.begin();
                while (pitr != potential_pos.end() && *pitr <= genome_in.size() - temp.size()) {
                    string to_check = genome_in.substr(*pitr, temp.size()); // grab substring from index in the list

                    // check between each letter
                    int missed = 0;
                    for (int i = 0; i < temp.size(); i++) {
                        if (temp[i] != to_check[i]) {
                            missed++;
                        }
                    }
                    // if too many not allowed
                    if (missed <= mismatch_max) {
                        results.push_back(Qresult(*pitr, missed, to_check));
                    }
                    pitr++;
                }

                if (results.size() == 0) {
                    cout << "No Match" << endl;
                }
                else {
                    // for each result print out
                    for (int i = 0; i < results.size(); i++) {
                        results[i].print_out(cout);
                    }
                }
            }
        }
        else if (temp == "quit") {
            break;
        }
        else {
            std::cerr << "command not recognized please try again" << endl;
        }
    }
    return 0;
}