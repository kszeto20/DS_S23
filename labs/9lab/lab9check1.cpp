#include <iostream>
#include <map> 
#include <string>
#include <fstream>

using std::cout; using std::cerr; using std::endl; using std::ifstream; using std::string;

int main(int argc, char* argv[] ) {
    if (argc != 2) { std::cerr << "incorrect amount of args supplied"; }

    std::ifstream in_f(argv[1]); 

    std::map<std::string, int> counters;

    string in_w;
    while (in_f >> in_w) {
        ++counters[in_w];
    }

    std::map<std::string, int>::const_iterator it;
    for (it = counters.begin(); it != counters.end(); ++it) {
        std::cout << it->first << "\t" << it->second << std::endl;
    }
    return 0;
}