#include <iostream>

int main(int argc, char* argv[]) {

    std::cout << "Please enter integers" << std::endl;

    int produ = 1;
    for (int i = 1; i < argc; i++) {
        produ = produ * std::stoi(argv[i]);
    }
    
    std::cout << produ;

    return 0;

}