#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "team.h"
#include "player.h"


using std::cout; using std::cerr; using std::endl; using std::ifstream; using std::ofstream; using std::string; using std::vector; using std::find; using std::setw;

/*
purpose: find if (team/player) have already been created
parameters: vector<string> v (vector of (player/team) names), name (name to check for)
returns: index of the (player/team) desired; returns -1 if not found in list
*/ 
int t_getInd(const vector<string>& v, const string& name) {
    // loop through vector --> if team name if found at any point, return index. if not found return -1;
    int toRet = 0;
    for (long unsigned int i = 0; i < v.size(); i++, toRet++) {
        if (v.at(i) == name) {
            return toRet;
        }
    }
    return -1;
}

/*
purpose: find if (player) have already been created -- if so what is the index
parameters: pvnames - vector of player names, tvnames - vector of team names, pname - player name, tname - team name
returns: index of desired player; returns -1 if not found in list
*/

int p_getInd(const vector<string>& pvnames, const vector<string>& tvnames, const string& pname, const string& tname) {
    // loop through vector of pvnames (and also tvnames (have the same size as pvnames)), if name and team match pname and tname, return index. if not found return -1;
    int toRet = 0;
    for (long unsigned int i = 0; i < pvnames.size(); i++, toRet++) {
        if (pvnames.at(i) == pname && tvnames.at(i) == tname) {
            return toRet;
        }
    }
    return -1;
}

/*
purpose: isGreaterThan for sorting teams
parameters: team1 and team2
returns: boolen of true or false is team1 is bigger
*/
bool t_IsGreaterThan(const Team& te1, const Team& te2) {
    // grab data for each team
    // variables for team1
    int w1 = te1.t_getWins();
    int l1 = te1.t_getLosses();
    int t1 = te1.t_getTies();
    int totalg1 = (w1 + l1 + t1);

    float winPercent1 = (w1 + (0.5 * t1)) / totalg1; // win percent one

    // variables for team2
    int w2 = te2.t_getWins();
    int l2 = te2.t_getLosses();
    int t2 = te2.t_getTies();
    int totalg2 = (w2 + l2 + t2);

    float winPercent2 = (w2 + (0.5 * t2)) / totalg2; // win percent two

    // sort by biggest win percent
    if (winPercent1 > winPercent2) {
        return true;
    } else if (winPercent1 < winPercent2) {
        return false;
    } else { // equals case - when equals sort by who has more goals
        if (te1.t_getGoals() == te2.t_getGoals() ) {
            return te1.t_getName() < te2.t_getName();
        } else {
            return te1.t_getGoals() > te2.t_getGoals();
        }
    }
    
}

/*
purpose: isGreaterThan for sorting players
parameters: player1 and player2
returns: boolean of true or false is p1 should be ranked highed than two
*/
bool p_IsGreaterThan(const Player& pe1, const Player& pe2) {
    // variables for player1
    string n1 = pe1.p_getName();
    int g1 = pe1.p_getGoals();
    int a1 = pe1.p_getAssists();
    int p1 = pe1.p_getPens(); 

    int tot1 = g1 + a1; // total for p1

    // variables for player2
    string n2 = pe2.p_getName();
    int g2 = pe2.p_getGoals();
    int a2 = pe2.p_getAssists();
    int p2 = pe2.p_getPens();

    int tot2 = g2 + a2; // total for p2

    

    if (tot1 > tot2) { // [GOALS] if more goals return true
        return true;
    } 
    else if (tot1 == tot2) { // [GOALS] else if equal goals + assist 
        if (p1 < p2) { // [PENALTIES] check for less penalties
            return true;
        } 
        else if (p1 == p2) { // [PENALTIES] else if euqal penalties 
            if (n1.compare(n2) < 0) { // [NAME] return true if name1 comes before name2
                return true;
            }
            else { // [NAME] else return false;
                return false;
            }
        } 
        else { // [PENALTIES] if more penalties return false
            return false;
        }
    } // [GOALS] if less goals return false
    return false; 
}

/*
processing for --player_stats
purpose: process the given file and update all players with information from the input file
parameters: vector<string> of all words read from input file
returns: vector<Player> of all players with correct goal, penalty, assist, name, and team names
*/
vector<Player> p_process(const vector<string>& all_words) {
    vector<Player> all_players; // vector to hold all players
    vector<string> made_players; // vector to hold names of made players
    vector<string> player_teams; // vector to hold team names of made_players

    string player_name; // player name
    string team_name; // team name
    int player_ind; // index of player in the vector of all players
    

    for (long unsigned int i = 0; i < all_words.size(); i++) { // for each word read in
        string to_check = all_words.at(i);

        if ((to_check == "goal" || to_check == "penalty") && all_words.at(i+1) != "BENCH") { // if word = goal , penalty, and player making goal/pen is not "BENCH"

            // input text "[SCHOOL] pen/goal [NAME]"
            player_name = all_words.at(i+1);
            team_name = all_words.at(i-1);

            int pt = p_getInd(made_players, player_teams, player_name, team_name); // get index of desired player if exists
            if (pt != -1) { // if found --> update player_ind, update player team
                player_ind = pt;
                team_name = all_players.at(player_ind).p_getTeam();
            } else { // else --> create new player, add player to vector of all players, add to player_name to made_players, add team_name to player_teams, update player_ind
                Player new_player = Player(player_name, team_name);
                all_players.push_back(new_player);
                made_players.push_back(player_name);
                player_teams.push_back(team_name);
                player_ind = all_players.size() -1;
            }

            if (to_check == "goal") {
                all_players.at(player_ind).p_addGoals();
            } 
            else if (to_check == "penalty") {
                all_players.at(player_ind).p_addPens();
            }
        }
        else if (to_check == "(") {
            while (all_words.at(++i) != ")") { // did ++i to get to next word for the loop check

                player_name = all_words.at(i); // input text = "( [name] [name] )"

                int pt = p_getInd(made_players, player_teams, player_name, team_name); // get index of desired player if exists
                if (pt != -1) { //  if found --> update player_ind, update player team
                    player_ind = pt;
                } else { // else --> create new player, add player to vector of all players, add to player_name to made_players, add team_name to player_teams, update player_ind
                    Player new_player = Player(player_name, team_name);
                    all_players.push_back(new_player);
                    made_players.push_back(player_name);
                    player_teams.push_back(team_name);
                    player_ind = all_players.size() -1;
                }
                all_players.at(player_ind).p_addAssists(); // add assist to player
            }
        }
    }
    return all_players; // returns vector of all players with updated information

}

/*
processing for --team_stats
purpose: process the given file and update all players with information from the input file
parameters: vector<string> of all words read from input file
returns: vector<Player> of all players with correct goal, penalty, assist, name, and team names
*/
vector<Team> t_process(const vector<string>& all_words) {
    vector<Team> all_teams; // vector to hold all teams
    vector<string> made_teams; // vector to hold all team names for teams made
    
    string away_name;
    string home_name;
    
    int at_ind; // index of away team in vector
    int ht_ind; // index of home team in vector

    int day_play; // day being played -- for custom stat

    for (long unsigned int i = 0; i < all_words.size(); i++) { 

        // check to see if the word is a day --> to get around "at" or "vs"
        bool inIf = false; // boolean to keep track of if a new game has been started
        vector<string> days{"Monday,", "Tuesday,", "Wednesday,", "Thursday,", "Friday,", "Saturday,", "Sunday,"};
        int dayOf = 0; 
        for (long unsigned int j = 0; j < days.size(); j++, dayOf++) { // for each day
            if (all_words.at(i) == days.at(j)) { // if (word being checked) == a day name
                day_play = dayOf; // update day being played
                i+=5; // move counted to the "at" / "vs" 
                inIf = true; // new game has been started, must update home and away team info
                j = days.size(); // break out of loop
            }
        }
        if (inIf) { // if new game has been started
            // input file --> "[AWAYT] vs [HOMET]"
            away_name = all_words.at(i-1);
            home_name = all_words.at(i+1);

            // away team
            int away_ind = t_getInd(made_teams, away_name); // find ind of away team, -1 if not found
            if (away_ind != -1) { // if found --> update away index
                at_ind = away_ind;
            } else { // else create new team, update corresponding vectors and away index
                Team away_team = Team(away_name);
                all_teams.push_back(away_team);
                made_teams.push_back(away_name);
                at_ind = all_teams.size() - 1;
            }

            all_teams.at(at_ind).t_addDays(7); // for custom stat -- teams[7] is count of all days played -- increment

            // home team
            int home_ind = t_getInd(made_teams, home_name); // find ind of away team, -1 if not found 
            if (home_ind != -1) { // if found --> update home index
                ht_ind = home_ind;
            } else { // else create new team, update corresponding vectors and home index
                Team home_team = Team(home_name);
                all_teams.push_back(home_team);
                made_teams.push_back(home_name);
                ht_ind = all_teams.size() - 1;
            }

            all_teams.at(ht_ind).t_addDays(7); // for custom stat -- add to total days played
        }
        // cases where no new game has been started
        else if (all_words.at(i) == "goal") { // goals for away or home team
            if (all_words.at(i-1) == away_name) { 
                all_teams.at(at_ind).t_addGoals();
            } else {
                all_teams.at(ht_ind).t_addGoals();
            }
        }
        else if (all_words.at(i) == "penalty") { // penalties for away or home team
            if (all_words.at(i-1) == away_name) {
                all_teams.at(at_ind).t_addPens();
            } else {
                all_teams.at(ht_ind).t_addPens();
            }
        }
        else if (all_words.at(i) == "FINAL") { // signifies game end
            i+=2; // gets pointer to away score
            int away_sc = stoi(all_words.at(i));
            i+= 2; // gets pointer to home score
            int home_sc = stoi(all_words.at(i));

            if (away_sc > home_sc) { // away score is greater than = away wins
                all_teams.at(at_ind).t_addWins();
                all_teams.at(ht_ind).t_addLosses();
                all_teams.at(at_ind).t_addDays(day_play); // for custom stat - for away team, add win on day of (day_played)
            }
            else if (home_sc > away_sc) { // home score is greater = home wins
                all_teams.at(ht_ind).t_addWins();
                all_teams.at(at_ind).t_addLosses();
                all_teams.at(ht_ind).t_addDays(day_play); // for custom stat - for home team, add win on day of (day_played)
            }
            else { // tie
                all_teams.at(ht_ind).t_addTies();
                all_teams.at(at_ind).t_addTies();
                // for custom stat - for away + home team, add win on day of (day_played)
                all_teams.at(ht_ind).t_addDays(day_play);
                all_teams.at(at_ind).t_addDays(day_play);
            }
        }
    }
    return all_teams; // return vector of all updated teams
}




int main(int argc, char* argv[]) {

    if (argc != 4) {
        // check for correct # of args
        cerr << "Incorrect amount of arguments supplied" << endl;
        exit(1);
    }
    
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

    string my_str; 
    vector<string> all_words;
    while (in_str >> my_str) { // read in all words
        all_words.push_back(my_str);
    }

    // output type
    string out_type = argv[3];
    
    if (out_type == "--team_stats") {
        vector<Team> tt = t_process(all_words); // process the words - in terms of teams
        sort(tt.begin(), tt.end(), t_IsGreaterThan);
        
        int longestN = -1; // int for longest team name
        for (long unsigned int i = 0; i < tt.size(); i++) { // find longest team name
            int len = tt.at(i).t_getName().length();
            if (len > longestN) {
                longestN = len;
            }
        }

        // header
        out_str << setw(longestN + 4) << std::left << "Team Name"
                << setw(3) << std::left << "W"
                << setw(3) << std::left << "L"
                << setw(3) << std::left << "T"
                << setw(5) << std::right << "Win%"
                << setw(7) << std::right << "Goals"
                << setw(10) << std::right << "Penalties";
        out_str << "\n";

        for (long unsigned int i = 0; i < tt.size(); i++) { // for each team 
            Team t = tt.at(i);
            // variables for team
            int w1 = t.t_getWins();
            int l1 = t.t_getLosses(); 
            int t1 = t.t_getTies(); 
            int totalg1 = (w1 + l1 + t1); 

            float winper = (w1 + (0.5 * t1)) / totalg1; // win percent

            // write data in correct format
            out_str << setw(longestN + 4) << std::left << t.t_getName()
                    << setw(3) << std::left << w1
                    << setw(3) << std::left << l1
                    << setw(3) << std::left << t1
                    << setw(5) << std::right << std::setprecision(2) << std::fixed << winper
                    << setw(7) << std::right << t.t_getGoals()
                    << setw(10) << std::right << t.t_getPens();
            out_str << "\n";
        }

    }
    else if (out_type == "--player_stats") {
        vector<Player> pp = p_process(all_words); // process words --> in terms of players
        sort(pp.begin(), pp.end(), p_IsGreaterThan);

        int longestN = -1; // int for longest name
        for (long unsigned int i = 0; i < pp.size(); i++) {
            int len = pp.at(i).p_getName().length();
            if (len > longestN) {
                longestN = len;
            }
        }

        // header
        out_str << setw(longestN + 4) << std::left << "Player Name"
                << setw(longestN + 2) << std::left << "Team"
                << setw(7) << std::right << "Goals"
                << setw(9) << std::right << "Assists"
                << setw(10) << std::right << "Penalties";
        out_str << "\n";

        for (long unsigned int i = 0; i < pp.size(); i++) { // for each player
            Player p = pp.at(i);
            // variables for player1
            string name = p.p_getName();
            string team = p.p_getTeam();
            int g1 = p.p_getGoals();
            int a1 = p.p_getAssists();
            int p1 = p.p_getPens();

            // write data in correct format
            out_str << setw(longestN + 4) << std::left << name
                    << setw(longestN + 2) << std::left << team
                    << setw(7) << std::right << g1
                    << setw(9) << std::right << a1
                    << setw(10) << std::right << p1;
            out_str << "\n";
        }
    }
    else if (out_type == "--custom_stats") { // process words --> in terms of custom (runs t_process() -- because attribute been accessed is a special attribute in Team object)
        vector<Team> tt = t_process(all_words);

        sort(tt.begin(), tt.end(), t_IsGreaterThan);
        
        int longestN = -1; // int for longest team name
        for (long unsigned int i = 0; i < tt.size(); i++) { // find longest team name
            int len = tt.at(i).t_getName().length();
            if (len > longestN) {
                longestN = len;
            }
        }
        
        // header
        out_str << setw(longestN + 4) << std::left << "Team Name"
                << setw(4) << std::left << "M"
                << setw(4) << std::left << "T"
                << setw(4) << std::left << "W"
                << setw(4) << std::left << "TH"
                << setw(4) << std::left << "F"
                << setw(4) << std::left << "SAT"
                << setw(4) << std::left << "SUN"
                << setw(20) << std::left << "# of days played"
                << setw(20) << std::left << "Won most on";
        out_str << "\n";

        for (long unsigned int i = 0; i < tt.size(); i++) { // for each team
            Team now = tt.at(i); 
            out_str << setw(longestN+4) << std::left << now.t_getName(); // output name
            vector<float> days = now.t_getDays(); // get vector of days won from team
            float mostWins = 0; // counter to keep track of most wins per day
            string bDay; // string of day to output
            vector<string> d = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            for (long unsigned int k = 0; k < days.size() - 1; k++) {
                float day_num = days.at(k);
                
                // if wins on a day is bigger than mostWins counter replace the counter and update bDay acordingly
                if (day_num > mostWins) {
                    mostWins = day_num;
                    bDay = d.at(k);
                }
                else if (day_num == mostWins) {
                    bDay += " "; bDay += d.at(k);
                }
                out_str << setw(4) << std::left << day_num;

            }

            out_str << setw(20) << std::left << days.at(7);

            if (mostWins == 0.0) { // if team never won --> replace message
                bDay = "haven't won yet :(";
            }
            out_str << setw(20) << std::left << bDay;
            out_str << "\n";
        }
    }
    else {
        cerr << "Please enter a proper justification method" << endl;
        exit(1);
    }

    return 0;
}