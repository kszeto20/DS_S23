#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout; using std::cerr; using std::endl; using std::ifstream; using std::ofstream; using std::string; using std::vector;

class Time {
public:
    Time();
    Time(int hour, int min, int sec);
    // accessors
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    int isNight() const;
    void PrintAMPM();

    // setters
    void setHour(int hr);
    void setMinute(int mn);
    void setSecond(int sc);
    
    
private:
    int nightBool;
    int h;
    int m;
    int s;
};

bool IsEarlierThan(const Time& t1, const Time& t2);