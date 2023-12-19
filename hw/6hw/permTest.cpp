#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using std::cout; using std::endl; using std::vector; using std::string; using std::cerr; using std::ifstream; using std::ofstream;
// purpose: generate all permutations of one combination (starts with empty already and string is in remaining)
// parameters: all (vector of all permutations), already (string of letters recursed through), remaining (string of letters not yet considered in that recursion)
// returns: nothing --> all perms are stored in all

void permGen(vector<string>& all, const string& already, const string& remaining) {
    if (remaining.size() <= 1) { // base case
        string whole = already + remaining;
        cout << whole << endl;
        all.push_back(whole); // add the permutation to the all vector
        return;
    }

    for (int i = 0; i < remaining.size(); i++) { // for each position remaining in remaining
        string whole = already + remaining[i]; // add the letter to already
        string rem = remaining.substr(0,i) + remaining.substr(i+1, remaining.size() - i); // create a remining without that letter
        permGen(all, whole, rem); // recurse with new strings
    }
}




int main() {
    
    vector<string> valid = {};
    vector<string> wants = {"arts", "arid", "east", "rest"};
    vector<string> donts = {"ear", "at", "sit"};
    int row = 4;
    int col = 4;
    string r_type = "all_solutions";
//    permGen(valid, "", "artsarideastrest");
    permGen(valid, "", "123456789");

    for (int i = 0; i < valid.size(); i++) {
        cout << "Board: " << endl;
        for (int j = 0; j < valid[i].size(); j+= col) {
            cout << valid[i].substr(j, col) << endl;
        }
    }

}
