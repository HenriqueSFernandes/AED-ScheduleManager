#ifndef PROJAED_TIME_H
#define PROJAED_TIME_H


#include <string>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
namespace Time {
    class time {
    public:
        time(double time);

        time();

        string displayHourFormat();

        int getHour() const;

        int getMinute() const;


        friend std::ostream &operator<<(std::ostream &os, const time &t);

    private:
        int hour;
        int minute;
    };
}

#endif //PROJAED_TIME_H
