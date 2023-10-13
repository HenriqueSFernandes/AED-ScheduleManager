#ifndef PROJAED_LESSON_H
#define PROJAED_LESSON_H


#include <string>
#include <ctime>
#include "time.h"
#include <iostream>

class lesson {
public:
    lesson(const std::string &weekday, double startTime, double duration, const std::string &type);

    const std::string &getWeekday() const;

    const Time::time &getStartTime() const;

    const Time::time &getDuration() const;

    const Time::time &getEndTime() const;

    const std::string &getType() const;

    friend std::ostream& operator<<(std::ostream& os, const lesson& lesson);

private:
    std::string weekday;
    Time::time startTime;
    Time::time duration;
    Time::time endTime;
    std::string type;
};


#endif //PROJAED_LESSON_H