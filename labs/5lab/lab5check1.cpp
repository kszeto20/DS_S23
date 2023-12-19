#include <iostream>
#include <string>
#include <vector>

int foobar (const std::vector<std::string> &a, int b) {
    int answer = 0;
    for (int i = 0; i < a.size(); i+=b) {
        answer++;
    }
    return answer;
}

std::vector<int> bar2 (const std::vector<std::string> &a) {
    std::vector<int> answer;
    for (int i = 0 ; i < a.size(); i++) {
        answer.push_back(a[i].size());
    } 
    return answer;
}

int main() {
    
    std::vector<std::string> aTest(100, "apple");
    std::vector<std::string> bTest(1000, "apple");
    //int test = foobar(aTest, 3);
    std::vector<int> test = bar2(bTest);
}