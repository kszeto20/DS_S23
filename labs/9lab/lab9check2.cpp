#include <iostream>
#include <map> 
#include <string>
#include <fstream>

using std::cout; using std::cerr; using std::endl; using std::ifstream; using std::string;

int main(int argc, char* argv[] ) {
    if (argc != 2) { std::cerr << "incorrect amount of args supplied"; }

    std::ifstream in_f(argv[1]); 

    std::map<std::string, int> counters;

    std::map<std::string, int>::iterator it;

    string in_w;
    while (in_f >> in_w) {
        if (counters.find(in_w) != counters.end()) {
            it = counters.find(in_w);
            it->second++;
        }
        else {
            counters.insert(std::make_pair(in_w, 1));
        }
    }

    for (it = counters.begin(); it != counters.end(); ++it) {
        std::cout << it->first << "\t" << it->second << std::endl;
    }
    return 0;
}