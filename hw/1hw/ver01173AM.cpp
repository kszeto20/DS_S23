#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout; using std::cerr; using std::endl; using std::ifstream; using std::ofstream; using std::string; using std::vector;

string leftJ (int w, ifstream &in_str) {
    string total_str;
    vector<string> all_words;
    string my_str;
    while (in_str >> my_str) {
        all_words.push_back(my_str);
    }

    for (int i = 0; i < w + 4; i++) {
        total_str += "-";
    }
    total_str += '\n';

    int space_left = w;
    string to_add;
    for (int i = 0; i < all_words.size(); i++) {
        string word = all_words.at(i);
        int wLen = word.length();


        if (wLen < space_left) {
            to_add += word;
            space_left -= (wLen + 1);
            to_add += " ";
        }
        else if (wLen == space_left) {
            to_add += word;
            space_left -= (wLen);
        }
        else {
            total_str += "| ";
            total_str += to_add;
            for (int j = 0; j < space_left; j++) {
                total_str += " ";
            }
            total_str += " |\n";
            to_add = "";
            space_left = w;

            if (wLen > w) { // hyphenate
                int l_left = wLen;
                int at = 0;
                while (l_left > w) {
                    total_str += "| ";
                    total_str += word.substr(at, (w - 1));
                    total_str += "-";
                    at += (w - 1);
                    l_left -= (w - 1);
                    total_str += " |\n";
                }
                if (l_left < w) {
                    to_add += word.substr(at, wLen);
                    to_add += " ";
                    space_left -= (l_left + 1);
                }
                else {
                    to_add += word.substr(at, wLen);
                    space_left -= (l_left);
                }
                
            }
            else if (wLen < space_left) {
                to_add += word;
                space_left -= (wLen + 1);
                to_add += " ";
            }
            else {
                to_add += word;
                space_left -= (wLen);
            }
        }

        if (i == all_words.size() - 1) {
            total_str += "| ";
            total_str += to_add;
            for (int j = 0; j < space_left; j++) {
                total_str += " ";
            }
            total_str += " |\n";
            to_add = "";
            space_left = w;
        }
    }

    /*
    "hello world woah fantastic here"

    w  = 14

    space_left = w;
    for (all words) {
        if word.length < space_left -> add to other string

        if not {
            push up string
            clear string 

            check word len for hyphenation --> handle
            else : add to string
        }
    }
    */
    for (int i = 0; i < w + 4; i++) {
        total_str += "-";
    }
    return total_str;
}

string rightJ (int w, ifstream &in_str) {
    bool first = true;

    string total_str;
    vector<string> all_words;
    string my_str;
    while (in_str >> my_str) {
        all_words.push_back(my_str);
    }

    for (int i = 0; i < w + 4; i++) {
        total_str += "-";
    }
    total_str += '\n';

    int space_left = w;
    string to_add;
    for (int i = 0; i < all_words.size(); i++) {

        string word = all_words.at(i);
        int wLen = word.length();


        if (wLen <= space_left) {
            if (!first) {
                to_add += " ";
                space_left -= 1;
            }
            to_add += word;
            space_left -= (wLen);
            first = false;
        }
        else {
            first = true;
            total_str += "| ";
            for (int j = 0; j < space_left; j++) {
                total_str += " ";
            }
            total_str += to_add;
            total_str += " |\n";
            to_add = "";
            space_left = w;

            if (wLen > w) { // hyphenate
                int l_left = wLen;
                int at = 0;
                while (l_left > w) {
                    total_str += "| ";
                    total_str += word.substr(at, (w - 1));
                    total_str += "-";
                    at += (w - 1);
                    l_left -= (w - 1);
                    total_str += " |\n";
                }
                if (l_left <= w) {
                    to_add += word.substr(at, l_left);
                    first = false;
                    space_left -= (l_left);
                }
            }
            else if (wLen <= space_left) {
                to_add += word;
                first = false;
                space_left -= wLen;
            }
        }

        if (i == all_words.size() - 1) {
            total_str += "| ";
            for (int j = 0; j < space_left; j++) {
                total_str += " ";
            }
            total_str += to_add;
            total_str += " |\n";
            to_add = "";
            space_left = w;
            first = true;
        }
    }

    /*
    "hello world woah fantastic here"

    w  = 14

    space_left = w;
    for (all words) {
        if word.length < space_left -> add to other string

        if not {
            push up string
            clear string 

            check word len for hyphenation --> handle
            else : add to string
        }
    }
    */
    for (int i = 0; i < w + 4; i++) {
        total_str += "-";
    }
    return total_str;
}





int main(int argc, char* argv[]) {

    int a = 5 / 2;
    cout << a << endl;

    if (argc != 5) {
        // check for correct # of args
        cerr << "Incorrect amount of arguments supplied" << endl;
        exit(1);
    }
    
    string all_w;
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

    // check input validity
    // width
    string w = argv[3];
    for (int i = 0; i < w.length(); i++) {
        if (!isdigit(w[i])) {
            cerr << "Please input an integer for the width of the output" << endl;
            exit(1);
        }
        
    }

    // justify type
    string just = argv[4];
    int width = stoi(w);

    if (just == "flush_left") {
        string toLeft = leftJ(width, in_str);
        out_str << toLeft;
    }
    else if (just == "flush_right") {
        string toRight = rightJ(width, in_str);
        out_str << toRight;
    }
    else if (just == "full_justify") {
        cout << "full" << endl;
    }
    else {
        cerr << "Please enter a proper justification method" << endl;
        exit(1);
    }

    return 0;

}
