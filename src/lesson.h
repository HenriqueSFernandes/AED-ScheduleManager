#ifndef PROJAED_LESSON_H
#define PROJAED_LESSON_H


#include <string>
#include <ctime>
#include "time.h"

class lesson {
public:
    lesson(const std::string &weekday, double startTime, double duration, const std::string &type);

private:
    std::string weekday;
    Time::time startTime;
    Time::time duration;
    Time::time endTime;
    std::string type;
public:
    const std::string &getWeekday() const;

    const Time::time &getStartTime() const;

    const Time::time &getDuration() const;

    const Time::time &getEndTime() const;

    const std::string &getType() const;
};


#endif //PROJAED_LESSON_H