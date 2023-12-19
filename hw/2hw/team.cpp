#include "team.h"

using std::string; using std::vector;

// constructors

Team::Team() {
    team_name = "not set";

    wins = 0;
    loss = 0;
    ties = 0;

    total_goals = 0;
    total_penalties = 0;
    days_played = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
}

Team::Team(string tname) {
    team_name = tname;

    wins = 0;
    loss = 0;
    ties = 0;

    total_goals = 0;
    total_penalties = 0;
    days_played = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
}

// accessors 
string Team::t_getName() const {
    return team_name;
}


int Team::t_getWins() const {
    return wins;
}

int Team::t_getLosses() const {
    return loss;
}

int Team::t_getTies() const {
    return ties;
}

int Team::t_getGoals() const {
    return total_goals;
}

int Team::t_getPens() const {
    return total_penalties;
}

vector<float> Team::t_getDays() const {
    return days_played;
}

// modifiers

void Team::t_addWins() {
    wins++;
}

void Team::t_addLosses() {
    loss++;
}

void Team::t_addTies() {
    ties++;
}

void Team::t_addGoals() {
    total_goals++;
}

void Team::t_addPens() {
    total_penalties++;
}

void Team::t_addDays(int ind) {
    days_played.at(ind) += 1;
}
