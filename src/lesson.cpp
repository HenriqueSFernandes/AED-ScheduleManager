#include "lesson.h"


lesson::lesson(const std::string &ucCode, const std::string &studentGroup, const std::string &weekday, double startTime,
               double duration, const std::string &type) {
    this->UcCode = ucCode;
    this->studentGroup = studentGroup;
    this->weekday = weekday;
    this->startTime = lessontime(startTime);
    this->duration = lessontime(duration);
    this->type = type;
    this->endTime = lessontime(startTime + duration);
}

const std::string &lesson::getWeekday() const {
    return weekday;
}

const std::string &lesson::getUccode() const {
    return UcCode;
}


const lessontime &lesson::getStartTime() const {
    return startTime;
}

const lessontime &lesson::getDuration() const {
    return duration;
}

const lessontime &lesson::getEndTime() const {
    return endTime;
}

const std::string &lesson::getType() const {
    return type;
}

std::ostream &operator<<(std::ostream &os, const lesson &lesson) {
    os << lesson.weekday << " from " << lesson.startTime << " to " << lesson.endTime << " of type: " << lesson.type
       << " regarding class : " << lesson.studentGroup << " of the UC " << lesson.UcCode;
    return os;
}
