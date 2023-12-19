#ifndef __fighter_h
#define __fighter_h

#include <iostream>
#include <map>
#include <string>

using std::string; using std::map; using std::pair;

class Fighter {

    public:
    // constructor
    Fighter();
    Fighter(const string& n ) { name = n; }
    
    // accessor
    string getName() const { return name; }
    map<string, int> getMoves() const { return move_frames; }
    int getMoveFrame(string move_name) const;

    // modifiers
    void setNewMove(string move_name, int frames);

    
    private:
    string name;
    map<string, int> move_frames;

};

#endif