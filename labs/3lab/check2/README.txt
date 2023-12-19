Lab3Check3 Log:

Command Line Commands:
g++ *.cpp -o out -Wall -Wextra - (x3)
    - made edits 1 + 2
g++ *.cpp -o out -Wall -Wextra
    - made edits 3
Edits:
1. point.h - indented the Point class
2. line.cpp - commented out line 3 (#include "point.h") -- error (redeclaration of point class)
3. roads.cpp - added line 5 (#include "algorithm") -- error (std::sort is not in std)
