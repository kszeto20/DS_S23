#include "player.h"
#include <iostream>

// constructors 
Player::Player() {
    name = "not set";
    team = "not set";

    goals = 0;
    assists = 0;
    penalties = 0;
}

Player::Player(const string & n, const string & t) {
    name = n;
    team = t;

    goals = 0;
    assists = 0;
    penalties = 0;
}

// accessors

string Player::p_getName() const {
    return name;
}

string Player::p_getTeam() const {
    return team;
}

int Player::p_getGoals() const {
    return goals;
}

int Player::p_getAssists() const {
    return assists;
}

int Player::p_getPens() const {
    return penalties;
}

// modifiers

void Player::p_addGoals() {
    goals++;
}

void Player::p_addAssists() {
    assists++;
}

void Player::p_addPens() {
    penalties++;
}