#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using std::cout; using std::endl; using std::vector; using std::string; using std::cerr; using std::ifstream; using std::ofstream;

enum DIRECTION { UNKNOWN = 0, NW = 1, N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 8};

// purpose: given a "direction" (moveType (enum declared above)) and coordinates, check for the next letter in the direction specified
    // special case - moveType = UNKNOWN --> means that the movement type is not yet determined (EX: only the first letter was found but direction of next letter is unknown)
// parameters: 2D board (toCheck), string to look for (toLook), row, col, number of letters already found (nFound), direction for movement (moveType)
// returns true for found the word, false for word not found

bool checker2(const vector<string>& toCheck, const string& toLook, int row, int col, int nFound, int moveType) {
    if (nFound == toLook.length()) { return true; }
    
    if (moveType == UNKNOWN) { // if direction has not been determined yet
        for (int k = NW; k <= W; k++) { 
            bool found = checker2(toCheck, toLook, row, col, nFound, k); // recurse from point given for each distinct direction
            if (found) { return true; } // if ever found --> return true 
            else { continue; } // else --> check other directions
        }
        return false; // if none of directions are good return false;
    }
    else { // direction is determined
        int newRow = row; // row for next spot in direction
        int newCol = col; // col for next spot in direction

        // logic is same for all directions
        if (moveType == NW) { // given a specific direction
            // update the new coordinates
            newRow--; newCol--;

            // do bounds checking on the new coordinates
            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            // if value at the new coordinate is not correct return false
            if (toLook[nFound] != toCheck[row - 1][col - 1]) { return false; }

        }
        else if (moveType == N) {
            newRow--;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row - 1][col]) { return false; }
        }     
        else if (moveType == NE) {
            newRow--; newCol++;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row - 1][col + 1]) { return false; }
        }
        else if (moveType == E) {
            newCol++;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row][col + 1]) { return false; }
        }
        else if (moveType == SE) {
            newRow++; newCol++;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row + 1][col + 1]) { return false; }
        }
        else if (moveType == S) {
            newRow++;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row + 1][col]) { return false; }
        }
        else if (moveType == SW) {
            newRow++; newCol--;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }
            
            if (toLook[nFound] != toCheck[row + 1][col - 1]) { return false; }
        }
        else if (moveType == W) {
            newCol--;

            if (newRow < 0 || newRow >= toCheck.size()) { return false; }
            if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

            if (toLook[nFound] != toCheck[row][col - 1]) { return false; }
        }

        // after corresponding direction is checked --> if false was not yet returned = this path is still valid + the correct letter was found
        nFound++; // update letters found
        return checker2(toCheck, toLook, newRow, newCol, nFound, moveType); // call recursion on this next point
    }
    
}


// purpose: loop through all possible points in the 2D array; recurse from any point that has a matching letter to the first letter in toLook(word)
// parameters: 2D board (toCheck), string to look for (toLook)
// returns: true for found the word, false for word not found

bool checker1(const vector<string>& toCheck, const string& toLook) {
    if (toLook.length() <= 0) { return true; } // bounds checking?
    // loop through every letter on the board
    for (int i = 0; i < toCheck.size(); i++) {
        for (int j = 0; j < toCheck[0].size(); j++) {
            if (toLook[0] == toCheck[i][j]) { // if the first letter is found
                // recurse from that point 
                // parameters: (toCheck, toLook, i (row), j (col), 1 (because first letter is found), UNKNOWN (direction of movement not set yet))
                bool found = checker2(toCheck, toLook, i, j, 1, UNKNOWN); 
                if (found) { return true; } // if the word is found --> return true for found 
                else { continue; } // else --> keep going through the board
            }
        }
    }
    return false; // if all board positions are looked at and none are found --> word is not in 2D array -- return false
}

// purpose: given a combination find if the combinations has all the wants and none of the dont wants
// parameters: combo (permutation), row, col, wanted words, unwanted words
// returns: boolean (true if both conditions are satisfied || false if conditions are not satisfied)

bool checkerTop (const string & combo, int row, int col, vector<string> & want, vector<string> & dont) {
    // create the 2D array to check from with (row) rows of strings of (col) length
    int at = 0;
    vector<string> toCheck(row, "1");
    for (int i = 0; i < row; i++) {
        toCheck[i] = combo.substr(at, col);
        at += col;
    }


    int wat = 0; // want index
    while (wat < want.size()) { // go through all wanted
        bool found = checker1(toCheck, want[wat]); // check if the word at want[wat] is in the 2D array (RECURSIVE FUNCTION)
        if (!found) { return false; } // if at any pt; the word is not found the whole combo is invalid
        wat++;
    }
    
    int dat = 0; // dont (want) index
    while (dat < dont.size()) { // go through all unwanted
        bool found = checker1(toCheck, dont[dat]); // check if the word at dont[dat] is in the 2D array (RECURSIVE FUNCTION)
        if (found) { return false; } // if at any pt; the word is found the whole combo is invalid
        dat++;
    }
    
    // if no invalid conditions are trippd then the combo must be valid
    return true;
}

bool checkerDonts (const string & combo, int row, int col, vector<string> & dont) {
    // create the 2D array to check from with (row) rows of strings of (col) length
    int at = 0;
    vector<string> toCheck(row, "1");
    for (int i = 0; i < row; i++) {
        toCheck[i] = combo.substr(at, col);
        at += col;
    }

    int dat = 0; // dont (want) index
    while (dat < dont.size()) { // go through all unwanted
        bool found = checker1(toCheck, dont[dat]); // check if the word at dont[dat] is in the 2D array (RECURSIVE FUNCTION)
        if (found) { return false; } // if at any pt; the word is found the whole combo is invalid
        dat++;
    }
    
    // if no invalid conditions are trippd then the combo must be valid
    return true;
}

// purpose: generate all permutations of one combination (starts with empty already and string is in remaining)
// parameters: all (vector of all permutations), already (string of letters recursed through), remaining (string of letters not yet considered in that recursion)
// returns: nothing --> all perms are stored in all

void permGen(vector<string>& all, const string& already, const string& remaining) {
    if (remaining.size() <= 1) { // base case
        string whole = already + remaining;
        all.push_back(whole); // add the permutation to the all vector
        return;
    }

    for (int i = 0; i < remaining.size(); i++) { // for each position remaining in remaining
        string whole = already + remaining[i]; // add the letter to already
        string rem = remaining.substr(0,i) + remaining.substr(i+1, remaining.size() - i); // create a remining without that letter
        permGen(all, whole, rem); // recurse with new strings
    }
}

// purpose: create all permutations from one combination, find valid permutations, add it into vector of all valid permutations
// parameters: all (vector of all valid permutations), already (part of string), remaining (part of string not yet recursed through), row, col, want (words wanted), dont (words not wanted), request_type
// return: nothing --> valid permutations are stored in all;
void permTop(vector<string>& all, const string& already, const string& remaining, int row, int col, vector<string> want, vector<string> dont, const string& request_type) {
    vector<string> all_perms = {};
    permGen(all_perms, "", remaining); // generate all permutations of the given string

    for (int i = 0; i < all_perms.size(); i++) { // for each permutation
        bool valid = checkerTop(all_perms[i], row, col, want, dont); // check if it is a valid permutation
        if (valid) { 
            all.push_back(all_perms[i]); // push permutation onto vector of all valid perms
            if (request_type == "one_solution") { // if only need one --> first instance found returns
                return;
            }
        }
    }
    return; // after all permutations are checked, end the function

}

// purpose: create all the possible combinations of letters from a list of words
// parameters: want (words wanted), dont, (words unwanted), row, column
// returns: vector<string> of unqiue combinations

vector<string> comboGen(const vector<string>& want, int row, int col) {
    vector<string> toRet; // vector of strings with unique combination of letters and their duplicates

    string allLetters = "";
    for (int i = 0; i < want.size(); i++) { // loop through all the wanted words and add them to a huge string
        allLetters += want[i];
    }

    sort(allLetters.begin(), allLetters.end()); // sort the string lexicographically

    string beginning = ""; // string to hold initially one of each distinct letter (whether or not it has duplicates)
    string rest = ""; // string to hold any duplicate letters

    char at = '-';
    for (int i = 0; i < allLetters.size(); i++) {
        if (allLetters[i] != at) { // if the distinct letter has not been added yet, add it to the "beginning" string for first distinct letters
            beginning += allLetters[i]; 
            at = allLetters[i];
        } // else add it to the duplicates
        else { rest += allLetters[i]; }
    }


    int spaces = row * col; // total number of spaces to fill with letters
    spaces = spaces - beginning.length(); // total number of spaces left to fill with duplicates after every distinct letter has at least one in the combination
    if (spaces == 0) {
        toRet.push_back(beginning);
        return toRet;
    }

    vector<string> leftPerm = {}; // permutations of duplicate letters left over
    permGen(leftPerm, "", rest); // generate the permutations using the RECURSIVE function

    vector<string> toAdd = {}; // unique combinations of letters to add to the "beginning" string

    // iterate through the list of returned permutations
    std::vector<string>::iterator itr;
    for (int i = 0; i < leftPerm.size(); i++) { // for each permutation
        sort(leftPerm[i].begin(), leftPerm[i].end()); // sort the perm being checked
        itr = std::find(toAdd.begin(), toAdd.end(), leftPerm[i]); // try to find that combo in the toAdd array
        if (itr != toAdd.end()) { continue; } // if found, do not add it again --> do not do anything with the perm as it has already been accounted for as a combination
        else { // else --> add it to toAdd array
            toAdd.push_back(leftPerm[i]);
            string toSend = beginning + leftPerm[i];
            toRet.push_back(toSend);
        }
    }
    return toRet;  
}

// purpose: generate all the COMBINATIONS of letters to use, of those combinations find the valid ones and add it them all into the common vector (all)
// parameters: vector<string> all (all valid grids are stored here); want (words wanted in the search), dont (words not wanted in the search), row, col, request_type (one/all solutions)
// returns: nothing --> because all valid grids are written directly into "all" parameter

void comboTop(vector<string>& all_valid_grids, const vector<string>& want, const vector<string>& dont, int row, int col, const string& request_type) {
    // generate all the combinations
    vector<string> all_combos = comboGen(want, row, col); 

    if (request_type == "one_solution") { 
        for (int i = 0; i < all_combos.size(); i++) { // for each combination generated 
            permTop(all_valid_grids, "", all_combos[i], row, col, want, dont, request_type); // generate permutations of the letters + find the valid permutations
            if (all_valid_grids.size() > 0) { // if anything has been found from the call return --> dont need to go through anymore combos
                return;
            }
        }
        // if all the combinations of letters is found checked and valid grid is never found
        return;
    }
    else { // want all the solutions
        for (int i = 0; i < all_combos.size(); i++) { // for each combinations
            permTop(all_valid_grids, "", all_combos[i], row, col, want, dont, request_type); // find the permutations of the combo and add the valid ones to all_walid_grids
        }
        return;
    }
} 


/*
int main() {
    
    vector<string> valid = {};
    vector<string> wants = {"arts", "arid", "east", "rest"};
    vector<string> donts = {"ear", "at", "sit"};
    int row = 4;
    int col = 4;
    string r_type = "all_solutions";
    comboTop(valid, wants, donts, row, col, r_type);

    cout << valid.size() << endl;
    for (int i = 0; i < valid.size(); i++) {
        cout << "Board: " << endl;
        for (int j = 0; j < valid[i].size(); j+= col) {
            cout << valid[i].substr(j, col) << endl;
        }
    }

}
*/


int main (int argc, char* argv[]) {

    if (argc != 4) {
        cerr << "insufficient arguments please provide an .exe, input file, output file, and request type" << endl;
        exit(1);
    }

    string all_w;
    // try to open files
    ifstream in_str(argv[1]);
    // check for opening success (read)
    if (!in_str.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n" << endl;
        exit(1);
    }

    // check for opening success (write)
    ofstream out_str(argv[2]);
    if (!out_str.good()) {
        cerr << "Can't open " << argv[1] << " to write.\n" << endl;
        exit(1);
    }

    
    int col = 0;
    int row = 0;
    
    in_str >> all_w;
    col = std::stoi(all_w);
    in_str >> all_w;
    row = std::stoi(all_w);

    vector<string> wants = {};
    vector<string> donts = {};
    
    while (in_str >> all_w) {
        if (all_w == "+") {
            in_str >> all_w;
            wants.push_back(all_w);
        }
        else if (all_w == "-") {
            in_str >> all_w;
            donts.push_back(all_w);
        }    
    }

    vector<string> valid = {};
    string r_type = argv[3];
    
    if (r_type == "one_solution" || r_type == "all_solutions") {
        comboTop(valid, wants, donts, row, col, r_type);
    }
    else {
        cerr << "incorrect formating of request type" << endl;
    }
    
    if (valid.size() <= 0) {
        out_str << "no solutions found." << endl;
    }
    else {
        if (r_type != "one_solution") {
            out_str << valid.size() << " solution(s)" << endl;
        }
        for (int i = 0; i < valid.size(); i++) {
            out_str << "Board:" << endl;
            string board = valid[i];
            for (int j = 0; j < valid[i].size(); j += col) {
                out_str << "  " << valid[i].substr(j, col) << endl;
            }
        }

    }
    
    
}
