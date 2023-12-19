#include <iostream>
#include <string>
#include <fstream> 
#include <map>
#include <set>

#include "Fighter.h"

//You may add additional typedefs, includes, etc. up here
using std::cout; using std::endl; using std::string; using std::ifstream; using std::ofstream; using std::map; using std::pair; using std::set;

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

// custom sort function for slowest frame speed with regular alphabetical sorting
// used in s_process
bool s_sort (const pair<int, string>& a, const pair<int, string>& b) {
    if (a.first != b.first) {
        return a.first > b.first;
    }
    else {
        return a.second < b.second;
    }
}

// function: take input file, read everything into a map of fighters
// parameters: input file (infile), map of fighters (all_fighters)
// returns: void
void read_db(ifstream& dbfile, map<string, Fighter>& all_fighters) {
	string all_w; // string to read into

	int counter = 0; // to keep track of which column code is reading from
	// skip over description row
	map<string, Fighter>::iterator c_fighter_ind;
	int i = 0;
	while (i < 8) {
		dbfile >> all_w;
		i++;
	}
	// while there is more data
	while (dbfile >> all_w) {
		if (counter == 0) { // 0 represents character name
			// make a fighter with that name
			c_fighter_ind = all_fighters.insert(make_pair(all_w, Fighter(all_w))).first;
		}
		else { // anything else is a frame count for a move
			Fighter& curr_fighter = c_fighter_ind->second; // get that fighter
			int frame_c = stoi(all_w); // convert frame data
			curr_fighter.setNewMove(move_names[counter - 1], frame_c); // add move to fighter with correct data	
		}
		counter++;
		if (counter == 8) { counter = 0; } // reset at the end of the row
	}
}

// purpose: handle all "-q" requests accordingly
// parameters: output file (outfile), name of fighter, name of move, map of all fighters (all_fighters)
// returns: void
void q_process (ofstream& outfile, string& fighter_name, string& move_name, map<string, Fighter>& all_fighters) {
	map<string, Fighter>::iterator found = all_fighters.find(fighter_name); // iterator to the string associated to the correct fighter
	if (found == all_fighters.end()) { // if fighter not found, output error message + return
		outfile << "Invalid character name: " << fighter_name << endl;
		return;
	}

	Fighter& curr_fighter = found->second; // get fighter since found
	if (move_name == "all") { // if "all" all moves must be printed
		map<string, int> moves_and_times; // map to hold move name and associated frame values
		for (int i = 0; i < 7; i++) { // for each move add it to moves_and_times
			moves_and_times.insert(std::make_pair(move_names[i], curr_fighter.getMoveFrame(move_names[i])));
		}
		map<string, int>::iterator toOut = moves_and_times.begin();
		while (toOut != moves_and_times.end()) { // for each move, output it to outfile
			outfile << fighter_name << " " << toOut->first << ": " << toOut->second << endl;
			toOut++;
		}
	}
	else { // if one specific move was requested
		// if one of the valid moves, output data to outfile
		if (move_name == "jab" || move_name == "forward-tilt" || move_name == "up-tilt" || move_name == "down-tilt" || move_name == "forward-smash" || move_name == "up-smash" || move_name == "down-smash") {
			outfile << fighter_name << " " << move_name << ": " << curr_fighter.getMoveFrame(move_name) << endl;
		}
		else { // else output error message + return 
			outfile << "Invalid move name: " << move_name << endl;
			return;
		}
	}
}

// purpose: handle "-f" requests
// parameters: output file (outfile), move name (r_name), request number (r_type), map of all fighters (all_fighters)
// returns: void
void f_process(ofstream& outfile, string& r_name, string& r_type, map<string, Fighter>& all_fighters) {
	int wanted_num = stoi(r_type); // convert number requested + make sure it is within bounds - if not return max
	if (wanted_num > all_fighters.size()) {
		wanted_num = all_fighters.size();
	}
	// check to see if the move is valid
	bool found = false;
	for (int i = 0; i < 8; i++) {
		if (r_name == move_names[i]) {
			outfile << "-f " << r_name << " " << r_type << endl;
			found = true;
			break;
		}
	}
	if (found == false) { // if move is not valid, print error message + return
		outfile << "Invalid move name: " << r_name << endl;
		return;
	}
	else { // if valid
		// go through every fighter, add a pair of the frame speed and fighter name to fastest_move
		set<pair<int, string> > fastest_move;
		map<string, Fighter>::iterator found = all_fighters.begin();
		while (found != all_fighters.end()) {
			Fighter& curr_fighter = found->second;
			fastest_move.insert(std::make_pair(curr_fighter.getMoveFrame(r_name), curr_fighter.getName()));
			found++;
		} 
		// for (wanted_num) fastest fighters, print out their name and frame speed for that move
		set<pair<int, string> >::iterator itr = fastest_move.begin();
		for (int i = 0; i < wanted_num; i++) {
			outfile << itr->second << " " << itr->first << endl;
			itr++;
		}
	}
}

// purpose: handle "-s" requests
// parameters: output file (outfile), move name (r_name), number requested (r_type), map of all fighters (all_fighters)
// returns: void
void s_process(ofstream& outfile, string& r_name, string& r_type, map<string, Fighter>& all_fighters) {
	int wanted_num = stoi(r_type); // convert number requested + make sure it is within bounds - if not return max
	if (wanted_num > all_fighters.size()) {
		wanted_num = all_fighters.size();
	}
	// check to see if the move is valid
	bool found = false;
	for (int i = 0; i < 8; i++) {
		if (r_name == move_names[i]) {
			outfile << "-s " << r_name << " " << r_type << endl;
			found = true;
			break;
		}
	}
	if (found == false) { // if move is not valid, print error message + return
		outfile << "Invalid move name: " << r_name << endl;
		return;
	}
	else { // if valid
		// go through every fighter, add a pair of the frame speed and fighter name to fastest_move
		// NOTE: fastest_move has custom sort parameter (s_sort) defined above
		set<pair<int, string>, bool(*)(const pair<int, string> &, const pair<int, string> &) > fastest_move(s_sort);
		map<string, Fighter>::iterator found = all_fighters.begin();
		while (found != all_fighters.end()) {
			Fighter& curr_fighter = found->second;
			fastest_move.insert(std::make_pair(curr_fighter.getMoveFrame(r_name), curr_fighter.getName()));
			found++;
		} 
		// for (wanted_num) fastest fighters, print out their name and frame speed for that move
		set<pair<int, string> >::iterator itr = fastest_move.begin();
		for (int i = 0; i < wanted_num; i++) {
			outfile << itr->second << " " << itr->first << endl;
			itr++;
		}
	}
}

// purpose: handle "-d" requests
// parameters: output file (outfile), move name (r_name), startup frame (r_type), map of all fighters (all_fighters)
// returns: void
void d_process(ofstream& outfile, string& r_name, string& r_type, map<string, Fighter>& all_fighters) {
	int wanted_num = stoi(r_type); // convert number requested
	// check to see if the move is valid
	bool found = false;
	for (int i = 0; i < 8; i++) {
		if (r_name == move_names[i]) {
			outfile << "-d " << r_name << " " << r_type << endl;
			found = true;
			break;
		}
	}
	if (found == false) { // if move is not valid, print error message + return
		outfile << "Invalid move name: " << r_name << endl;
		return;
	}

	set<string> fighters;
	map<string, Fighter>::iterator each_fighter = all_fighters.begin();
	// iterate through each fighter
	while (each_fighter != all_fighters.end()) {
		Fighter& curr_fighter = each_fighter->second;
		if (curr_fighter.getMoveFrame(r_name) == wanted_num) { // if the move has a matching start up frame
			fighters.insert(curr_fighter.getName()); // add it to the set of names
		}
		each_fighter++;
	}
	// output all the names
	set<string>::const_iterator f_names = fighters.begin();
	while (f_names != fighters.end()) {
		outfile << *f_names << endl;
		f_names++;
	} 
}


int main(int argc, char** argv){

	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}
	
	// populate data map
	map<string, Fighter> all_fighters;
	read_db(dbfile, all_fighters);

	// handle all requests
	string all_w;
	while (infile >> all_w) {
		string r_name; infile >> r_name;
		string r_type; infile >> r_type;

		if (all_w == "-q") {
			q_process(outfile, r_name, r_type, all_fighters);
		}
		else if (all_w == "-f") {
			f_process(outfile, r_name, r_type, all_fighters);
		}
		else if (all_w == "-s") {
			s_process(outfile, r_name, r_type, all_fighters);
		}
		else if (all_w == "-d") {
			d_process(outfile, r_name, r_type, all_fighters);
		}
		outfile << endl;
	}

	return 0;
}