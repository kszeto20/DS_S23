#ifndef __team_h
#define __team_h
#include <iostream>
#include <vector>
#include <string>

#include "player.h"

using std::string; using std::vector;

class Team {
    public:
    Team(); // default constructor
    Team(string tname);
    
    // accessors
    string t_getName() const;
    int t_getWins() const;
    int t_getLosses() const;
    int t_getTies() const;

    int t_getGoals() const;
    int t_getPens() const;

    vector<float> t_getDays() const;

    // modifiers methods
    void t_addWins();
    void t_addLosses();
    void t_addTies();

    void t_addGoals();
    void t_addPens();

    void t_addDays(int ind);

    // attributes
    private:
    string team_name;
    int wins;
    int loss;
    int ties;

    int total_goals;
    int total_penalties;

    vector<float> days_played;
};

bool t_IsGreaterThan(const Team& te1, const Team& te2);
#endif