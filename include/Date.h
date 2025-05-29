#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>

struct Date {
    int month;
    int day;
    int year;
    
    Date() : month(0), day(0), year(0) {}   // default
    Date(int m, int d, int y) : month(m), day(d), year(y) {}
    
    std::string print_date() const {
        std::ostringstream oss;
        if(month < 10) { oss << "0"; }
        oss << month << "/";
        if(day < 10) { oss << "0"; }
        oss << day << "/";
        oss << year;
        return oss.str();
    }
};

#endif