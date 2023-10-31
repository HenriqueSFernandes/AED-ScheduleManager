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

    lessontime(int hour, int minutes);

    string displayHourFormat();

    int getHour() const;

    int getMinute() const;


    friend std::ostream &operator<<(std::ostream &os, const lessontime &t);

    bool operator<(const lessontime &other) const {
        // Compare two lessontime objects based on their hours and minutes
        if (hour < other.hour) {
            return true;
        } else if (hour == other.hour && minute < other.minute) {
            return true;
        }

        return false;
    }

    bool operator==(const lessontime &other) const {
        // Compare two lessontime objects based on their hours and minutes
        if (hour == other.getHour() && minute == other.getMinute()) {
            return true;
        }

        return false;
    }

    bool operator<=(const lessontime &other) const {
        if (hour < other.hour) {
            return true;
        } else if (hour == other.hour && minute <= other.minute) {
            return true;
        }

        return false;
    }

private:
    int hour;
    int minute;
};


#endif //PROJAED_LESSONTIME_H
