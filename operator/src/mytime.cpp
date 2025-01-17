#include <iostream>
#include "mytime.h"

Time::Time(){
    hours = 0;
    minutes = 0;
}

Time::Time(int h, int m){
    hours = h;
    minutes = m;
}

void Time::AddMin(int m){
    minutes += m;
    hours += minutes/60;
    minutes %= 60;
}

void Time::AddHr(int h){
    hours += h;
}

void Time::Reset(int h, int m){
    hours = h;
    minutes = m;
}

Time Time::Sum(const Time &t) const{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes/60;
    sum.minutes %= 60;
    return sum;
}

// 1
Time Time::operator+(const Time &t) const{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes/60;
    sum.minutes %= 60;
    return sum;
}

// 2
Time Time::operator*(double mult) const{
    Time result;
    long totalminutes = hours*mult*60 + minutes*mult;
    result.hours = totalminutes/60;
    result.minutes = totalminutes%60;
    return result;
}

// 3
Time operator*(double m, Time &t){
    return t*m;
}

// 3
std::ostream & operator<<(std::ostream &os, const Time &t){
    os<< t.hours << " hours, "<< t.minutes << "minutes";
    return os;
}   

void Time::Show() const{
    std::cout<< hours << " hours, "<< minutes << "minutes" <<std::endl;
}