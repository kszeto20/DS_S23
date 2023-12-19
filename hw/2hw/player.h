#ifndef __player_h
#define __player_h
#include <iostream>
#include <vector>
#include <string>

using std::string;

class Player {
    public:
    // constructor
    Player(); // default
    Player(const string & n, const string & t);

    // accessor methods
    string p_getName() const;
    string p_getTeam() const;
    int p_getGoals() const;
    int p_getAssists() const;
    int p_getPens() const;

    // modifier methods
    void p_addGoals();
    void p_addAssists();
    void p_addPens();
    
    // attributes
    private:
    string name;
    string team;

    int goals;
    int assists; 
    int penalties;
};

bool p_IsGreaterThan(const Player& pe1, const Player& pe2);
#endif

