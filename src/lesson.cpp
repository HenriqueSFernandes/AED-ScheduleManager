#include "lesson.h"

using namespace Time;

lesson::lesson(const std::string &weekday, double startTime, double duration, const std::string &type) {
    this->weekday = weekday;
    this->startTime = Time::time(startTime);
    this->duration =  Time::time(duration);
    this->type = type;
    this->endTime = Time::time(startTime + duration);
}

const std::string &lesson::getWeekday() const {
    return weekday;
}

const Time::time &lesson::getStartTime() const {
    return startTime;
}

const Time::time &lesson::getDuration() const {
    return duration;
}

const Time::time &lesson::getEndTime() const {
    return endTime;
}

const std::string &lesson::getType() const {
    return type;
}
