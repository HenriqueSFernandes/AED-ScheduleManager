#ifndef PROJAED_LESSON_H
#define PROJAED_LESSON_H


#include <string>
#include <ctime>
#include "time.h"
#include <iostream>

class lesson {
public:
    lesson(const std::string &uccode,const std::string &studentgroup,const std::string &weekday, double startTime, double duration, const std::string &type);

    const std::string &getWeekday() const;

    const Time::time &getStartTime() const;

    const Time::time &getDuration() const;
    const Time::time &getEndTime() const;

    const string &getUccode() const;

    const std::string &getType() const;

    friend std::ostream &operator<<(std::ostream &os, const lesson &lesson);
    bool operator<(const lesson& other) const {
        if (UcCode != other.getUccode()) {
            return UcCode < other.getUccode();
        } else {
            return weekday < other.weekday;
        }
    }
private:

    std::string studentGroup;
    std::string UcCode;
    std::string weekday;
    Time::time startTime;
    Time::time duration;
    Time::time endTime;
    std::string type;
};


#endif //PROJAED_LESSON_H