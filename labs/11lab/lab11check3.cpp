#include <iostream>
#include <vector>
#include <string>

using std::string; using std::vector; using std::cout; using std::endl;

typedef std::vector<std::string> DB;
void findBoxes(const DB& box, DB& curr_box, vector<DB>& boxes) {
    if (box.size() == 0) {
        boxes.push_back(curr_box);
        return;
    }
    else {
        for (int i = 0; i < box.size(); i++) {
            DB rest_box = box;
            curr_box.push_back(rest_box[i]);
            rest_box.erase(rest_box.begin() + i);
            findBoxes(rest_box, curr_box, boxes);
            curr_box.pop_back();
        }
    }
    return;
}

void findBoxes(const DB& box, vector<DB>& boxes) {
    DB temp;
    findBoxes(box, temp, boxes);
    return;
}

int main() {
    DB donuts;
    std::vector<DB> boxes;
    donuts.push_back("strawberry"); donuts.push_back("chocolate"); donuts.push_back("maple"); donuts.push_back("blueberry");
    findBoxes(donuts, boxes);

    cout << "there are " << boxes.size() << " different combinations." << endl;
    for (int i = 0; i < boxes.size(); i++) {
        DB curr_combo = boxes[i];
        string in_box;
        for (int j = 0; j < curr_combo.size(); j++) {
            in_box += " ";
            in_box += curr_combo[j];
        }
        cout << in_box << endl;
    }

    return 0;
}