#include "time.h"

Time::Time() {
    h = 0;
    m = 0;
    s = 0;
    nightBool = false;
}

Time::Time(int hour, int min, int sec) {
    h = hour;
    m = min;
    s = sec;

    if (hour >= 12) {
        nightBool = true;
    } else {
        nightBool = false;
    }
}

int Time::getHour() const {
    return h;
}

int Time::getMinute() const {
    return m;
}

int Time::getSecond() const {
    return s;
}

int Time::isNight() const {
    return nightBool;
}

void Time::PrintAMPM() {
    string total_str;
    int nHour;
    if (nightBool) {
        if (h == 12) {
            nHour = 12;
        } else {
            nHour = h - 12;
        }
        
    }
    else {
        if (h == 0) {
            nHour = 12;
        } else {
            nHour = h;
        }
        
    }

    if (nHour < 10) {
        total_str += '0';
        total_str += std::to_string(nHour);
    } else {
        total_str += std::to_string(nHour);
    }

    total_str += ":";

    if (m < 10) {
        total_str += '0';
        total_str += std::to_string(m);
    } else {
        total_str += std::to_string(m);
    }

    total_str += ":";

    if (s < 10) {
        total_str += '0';
        total_str += std::to_string(s);
    } else {
        total_str += std::to_string(s);
    }

    
    if (nightBool) {
        total_str += " pm";
    } else {
        total_str += " am";
    }
    
    cout << total_str << endl;

}

void Time::setHour(int hr) {
    h = hr;
}

void Time::setMinute(int mn) {
    m = mn;
}

void Time::setSecond(int sc) {
    s = sc;
}

