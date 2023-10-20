#include "lesson.h"

using namespace Time;

lesson::lesson(const std::string &uccode,const std::string &studentgroup,  const std::string &weekday, double startTime, double duration, const std::string &type) {
    this->UcCode=uccode;
    this->studentGroup=studentgroup;
    this->weekday = weekday;
    this->startTime = Time::time(startTime);
    this->duration = Time::time(duration);
    this->type = type;
    this->endTime = Time::time(startTime + duration);
}

const std::string &lesson::getWeekday() const {
    return weekday;
}
const std::string &lesson::getUccode() const {
    return UcCode;
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

std::ostream &operator<<(std::ostream &os, const lesson &lesson) {
    os << lesson.weekday << " from " << lesson.startTime << " to " << lesson.endTime << " type: " << lesson.type<< " regarding class :"<<lesson.studentGroup<< "of the UC"<<lesson.UcCode;
    return os;
}
