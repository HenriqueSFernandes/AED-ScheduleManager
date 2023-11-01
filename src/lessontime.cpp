#include "lessontime.h"


lessontime::lessontime() {
    hour = 0;
    minute = 0;
}

lessontime::lessontime(double time) {
    hour = (int) time;
    minute = (int) ((time - hour) * 60);
}

int lessontime::getHour() const {
    return hour;
}

int lessontime::getMinute() const {
    return minute;
}

std::ostream &operator<<(std::ostream &os, const lessontime &t) {
    os << std::setw(2) << std::setfill('0') << t.hour << ':' << std::setw(2) << std::setfill('0') << t.minute;
    return os;
}

std::string lessontime::displayHourFormat() {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute;
    return ss.str();
}

lessontime::lessontime(int hour, int minutes) {
    this->hour = hour;
    this->minute = minutes;
}


