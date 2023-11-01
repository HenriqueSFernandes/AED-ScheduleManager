/// @file lessontime.h
#ifndef PROJAED_LESSONTIME_H
#define PROJAED_LESSONTIME_H


#include <string>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
/**
 * @brief Class used to represent time.
 */
class lessontime {
public:
    /**
     * @brief Copy constructor.
     * @param time
     */
    lessontime(double time);

    /**
     * @brief Default constructor (00:00)
     */
    lessontime();

    /**
     * @brief Parameterized constructor.
     * @param hour
     * @param minutes
     */
    lessontime(int hour, int minutes);

    /**
     * @brief Converts the time to a string.
     * @return A string representing the time.
     */
    string displayHourFormat();

    /**
     * @brief Hour getter.
     * @return An integer representing the hour.
     */
    int getHour() const;

    /**
     * @brief Minutes getter.
     * @return An integer representing the minutes.
     */
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
        // Compare two lessontime objects based on their hours and minutes
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
