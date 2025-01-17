#ifndef _MYTIME_H_
#define _MYTIME_H_

#include <iostream>
class Time
{
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h=0, int m=0);
    Time Sum(const Time &t) const;
    void Show() const;
    Time operator+(const Time &t) const;    // 1
    Time operator*(double mult) const;            // 2
    friend Time operator*(double m, Time &t);     // 3
    friend std::ostream & operator<<(std::ostream &os, const Time &t);  // 3
};


#endif