#ifndef PROJAED_LESSONTIME_H
#define PROJAED_LESSONTIME_H


#include <string>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class lessontime {
public:
    lessontime(double time);

    lessontime();

    string displayHourFormat();

    int getHour() const;

    int getMinute() const;


    friend std::ostream &operator<<(std::ostream &os, const lessontime &t);

private:
    int hour;
    int minute;
};


#endif //PROJAED_LESSONTIME_H
