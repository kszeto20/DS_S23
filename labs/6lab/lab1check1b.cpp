#include <iostream>
#include <string>
#include <list>
#include <iterator>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";

  typename std::list<T>::iterator itr;  
  for (itr = data.begin(); itr != data.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
    if (data.size() > 1) {
        typename std::list<T>::reverse_iterator ri = data.rbegin();
        typename std::list<T>::iterator itr = data.begin();
        for (int i = 0; i < data.size() / 2; i++, ri++, itr++) {
            T info = *ri;
            *ri = *itr;
            *itr = info;
        }
    }
}


int main() {   
    std::list<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);

    print(data,"before:");
    reverse(data);
    print(data,"after: ");

    std::list<std::string> data2;
    data2.push_back("apple");
    data2.push_back("banana");
    data2.push_back("carrot");
    data2.push_back("date");

    print(data2,"before:");
    reverse(data2);
    print(data2,"after: ");

    std::list<int> data3;
    data3.push_back(1);
    data3.push_back(2);
    data3.push_back(3);
    data3.push_back(4);
    data3.push_back(5);
    data3.push_back(6);
    data3.push_back(7);
    data3.push_back(8);


    print(data3,"before:");
    reverse(data3);
    print(data3,  "after: ");
}