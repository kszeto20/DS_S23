#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 

using std::cout; using std::endl; using std::cerr; using std::string; using std::ifstream; using std::ofstream; using std::vector;

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

// purpose: given a combination find if the combinations has none of the dont wants
// parameters: combo (permutation), row, col, wanted words, unwanted words
// returns: boolean (true if both conditions are satisfied || false if conditions are not satisfied)

bool checkerTop (const string & combo, int row, int col, const vector<string> & dont) {
    // create the 2D array to check from with (row) rows of strings of (col) length
    int at = 0;
    vector<string> toCheck(row, "1");
    for (int i = 0; i < row; i++) {
        toCheck[i] = combo.substr(at, col);
        at += col;
    }
    
    int dat = 0; // dont want index
    while (dat < dont.size()) { // go through all unwanted
        bool found = checker1(toCheck, dont[dat]); // check if the word at dont[dat] is in the 2D array (RECURSIVE FUNCTION)
        if (found) { return false; } // if at any pt; the word is found the whole combo is invalid
        dat++;
    }
    
    // if no invalid conditions are trippd then the combo must be valid
    return true;
}

// purpose: generate all the permutations of "boards" with the unused spaces filled with each letter of the alphabet
// parameters: vector of strings (all_combos) -- each string represents a board, string to populate (toFill), index for position (ind_at)
// returns: void function because all permutations are put directly into all_combos
void filler_gen(vector<string>& all_combos, string& toFill, int ind_at) {
    if (ind_at == toFill.size()) { // if at the end of the word push the word into the all_combos
        all_combos.push_back(toFill);
        return;
    }

    while (ind_at != toFill.size()) { // loop until find a "-" or at end of string
        if (toFill[ind_at] != '-') {
            ind_at++;
        }
        else {
            break;
        }
    }

    if (ind_at == toFill.size()) {  // if no "-" found, push toFill into vector
        all_combos.push_back(toFill);
    }
    else { // at the index where "-" found
        for (int i = 0; i < 26; i++) { // for each letter in the alphabet
            string str = toFill.substr(0, ind_at); // take substring to the left of the index
            char letter(97 + i); // add the alphabet letter
            str += letter;
            if (ind_at != (toFill.length() - 1)) { // if not at the end, add everything to the right
                str += toFill.substr(ind_at + 1, (toFill.length() - ind_at - 1));
            }
            filler_gen(all_combos, str, ind_at + 1); // recurse from there
        }

    }
    
}

// purpose: check if a word can be inserted in a direction given a board
// parameters: board to check (toCheck), string to check (toLook), row of index to start at, col of index to start at, direction to move (moveType)
// returns: (bool) if valid direction to insert, true; else false;

// NOTE: logic/set up is very similar to checker
bool valid_check(vector<vector<string>>& toCheck, string &toLook, int row, int col, int nFound, int moveType) {
    if (nFound == toLook.length()) { // if nFound = length of word then stop looking and return true
        return true;
    }

    string letter = toLook.substr(nFound, 1);

    int newRow = row; // row for next spot in direction
    int newCol = col; // col for next spot in direction

    // logic is same for all directions
    if (moveType == NW) { // given a specific direction
        // update the new coordinates
        newRow--; newCol--;

        // do bounds checking on the new coordinates
        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        // if value at the new coordinate is not correct or is not empty ("-") return false
        if (letter != toCheck[row - 1][col - 1] && toCheck[row - 1][col - 1] != "-") { return false; }

    }
    else if (moveType == N) {
        newRow--;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        if (letter != toCheck[row - 1][col] && toCheck[row - 1][col] != "-") { return false; }
    }     
    else if (moveType == NE) {
        newRow--; newCol++;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        if (letter != toCheck[row - 1][col + 1] && toCheck[row - 1][col + 1] != "-") { return false; }
    }
    else if (moveType == E) {
        newCol++;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        if (letter != toCheck[row][col + 1] && toCheck[row][col + 1] != "-") { return false; }
    }
    else if (moveType == SE) {
        newRow++; newCol++;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        if (letter != toCheck[row + 1][col + 1] && toCheck[row + 1][col + 1] != "-") { return false; }
    }
    else if (moveType == S) {
        newRow++;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }


        if (letter != toCheck[row + 1][col] && toCheck[row + 1][col] != "-") { return false; }
    }
    else if (moveType == SW) {
        newRow++; newCol--;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }
            
        if (letter != toCheck[row + 1][col - 1] && toCheck[row + 1][col - 1] != "-") { return false; }
    }
    else if (moveType == W) {
        newCol--;

        if (newRow < 0 || newRow >= toCheck.size()) { return false; }
        if (newCol < 0 || newCol >= toCheck[0].size()) { return false; }

        if (letter != toCheck[row][col - 1] && toCheck[row][col - 1] != "-") { return false; }
    }

    // after corresponding direction is checked --> if false was not yet returned = this path is still valid + a valid space was found
    nFound++; // update letters found
    return valid_check(toCheck, toLook, newRow, newCol, nFound, moveType); // call recursion on this next point
    // NOTE: I do not add to the board yet -- this function is for checking only

}

// purpose: method to determine sorting properties -- to be used in grid gen
bool compLen (const std::string& a, const std::string& b) {
    return (a.size() < b.size());
}

// purpose: add a word to a board in a direction
// parameters: board to add to (board), word to add (word), row of ind to start at, col of ind to start at, direction to insert (moveType)
// returns: nothing, added directly into board
void add_word (vector<vector<string>> & board, string & word, int row, int col, int moveType) {
    int newRow  = row; // row for adding
    int newCol = col; // col for adding
    for (int i = 0; i < word.length(); i++) { // for each letter in the word 
        string str = word.substr(i, 1);
        board[newRow][newCol] = str; // update the board with the letter at that index

        // logic is same for all directions
        if (moveType == NW) { // given a specific direction
            // update the new coordinates
            newRow--; newCol--;
        }
        else if (moveType == N) {
            newRow--;
        }     
        else if (moveType == NE) {
            newRow--; newCol++;
        }
        else if (moveType == E) {
            newCol++;
        }
        else if (moveType == SE) {
            newRow++; newCol++;
        }
        else if (moveType == S) {
            newRow++;
        }
        else if (moveType == SW) {
            newRow++; newCol--;
        }
        else if (moveType == W) {
            newCol--;
        }
    }
}

// purpose: generate all possible grids and add valid ones into all_grids
// parameters: master vector of grids (all_grids), representation of current board state (board), words to add in (want), max rows, max cols, words to check are not in (dont), one_solution/all_solutions (request)
// returns true if by the end, a valid path was added, false if not a single valid path was added

bool gridGen_1 (vector<string> & all_grids, vector<vector<string>>& board, vector<string>& want, int row, int col, const vector<string>& dont, const string& request) {
    if (want.size() == 0) { // base case -- no more words to add
        bool unused = false;
        string str = ""; // create the string representation of the board (from 2D version)
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == "-") {  // update boolean to see if any spaces to generate filler for 
                    unused = true;
                }
                str += board[i][j];
            }
        }
        
        if (unused == false) { // if its a full board 
            bool any_bad = checkerTop(str, row, col, dont);
            if (any_bad) { // if the string doesnt have unwanted words
                all_grids.push_back(str);
                if (request == "one_solution") {
                    return true;
                }
            }
            else { // return false since bad words found; therefore not valid board/ orientation
                return false;
            }
        }
        else { // not a full board
            bool added = false;
            vector<string> combos = {};
            filler_gen(combos, str, 0); // generate all the combos
            for (int i = 0; i < combos.size(); i++) { // for each combo
                bool any_bad = checkerTop(combos[i], row, col, dont); // check if it has any unwanted
                if (any_bad) { // if has no unwanted
                    all_grids.push_back(combos[i]);
                    if (request == "one_solution") {
                        return true;
                    }
                }
            }
            if (added == false) { // if no solution was ever added, return false because it is a bad orientation
                return false;
            }
        }
        return true;
    }
    else { // recursive case
        // grab word from the back of wanted vector
        string word_to_add = want[want.size() - 1];
        want.pop_back();
        vector<string> new_want = want; // create a new vector with just added word not there
        want.push_back(word_to_add); // add that word back to the old vector --
            /*
            Example: if we dont add back to vector
            after we do:
            catone | cateno --> when we try to rotate tac--- there will be no more one in the vector because we are passing by reference
            must add back
            */
        
        string first_letter = word_to_add.substr(0, 1); // get first letter needed
        bool ever_valid = false; // boolean to keep track if a valid path was ever found with this combination of words

        // for every position in the board: 
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                // check if any position can be the start of the word or empty space ("-")
                if (board[i][j] == first_letter || board[i][j] == "-") {
                    for (int k = NW; k <= W; k++) { // for each valid potential position, loop through all directions
                        bool add_able = valid_check(board, word_to_add, i, j, 1, k);
                        if (add_able) { // if a direction is valid
                            vector<vector<string>> board_added = board; // create an identical board and add the word in the specific direction
                            add_word(board_added, word_to_add, i, j, k);
                            // recurse on that grid with the words left (new_want)
                            bool nexts = gridGen_1(all_grids, board_added, new_want, row, col, dont, request);
                            if (nexts) { // a valid grid was found from this orientation
                                ever_valid = true; // signifies that there is at least one valid path here
                                if (request == "one_solution") { // if one sol - return at the first instance of a valid path
                                    return true;
                                }
                            } 
                        } // if not a valid orientation - move onto next orientation
                    }
                }
            } // move onto next possible position in the grid
        }
        if (ever_valid == false) { // if a possible solution was never found for all positions in all directions
            return false; // this grid is not possible with current configurations
        }
    }
    return true;
}

// purpose: generate all the grids
// parameters: master vector of all solutions, vector of wanted rows, max rows, max cols, vector of unwanted words (dont), one_solution/all_solutions (request)
// returns: nothing; valid grids are added directly to all_grids
void gridGen_top (vector<string>& all_grids, vector<string>& want, int row, int col, const vector<string>& dont, const string& request) {
    std::sort(want.begin(), want.end(), compLen); // sort wanted by length
    string filler = "-";
    vector<vector<string>> start_board(row, vector<string>(col, filler)); // create empty board
    gridGen_1(all_grids, start_board, want, row, col, dont, request); // generate boards
}


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
        gridGen_top(valid, wants, row, col, donts, r_type);
    }
    else {
        cerr << "incorrect formating of request type" << endl;
    }
    
    vector<string> no_dups = {};
    for (int i = 0; i < valid.size(); i++) {
        if (std::find(no_dups.begin(), no_dups.end(), valid[i]) == no_dups.end()) {
            no_dups.push_back(valid[i]);            
        }
    }

    if (no_dups.size() <= 0) {
        out_str << "No solutions found" << endl;
    }
    else {
        if (r_type != "one_solution") {
            out_str << no_dups.size() << " solution(s)" << endl;
        }
        for (int i = 0; i < no_dups.size(); i++) {
            out_str << "Board:" << endl;
            string board = no_dups[i];
            for (int j = 0; j < no_dups[i].size(); j += col) {
                out_str << "  " << no_dups[i].substr(j, col) << endl;
            }
        }

    }
    
}
