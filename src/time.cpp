#include "time.h"

using namespace Time;

time::time(){
    hour = 0;
    minute = 0;
}

time::time(double time) {
    hour = (int) time;
    minute = (int) ((time - hour) * 60);
}

int time::getHour() const {
    return hour;
}

int time::getMinute() const {
    return minute;
}

std::ostream& Time::operator<<(std::ostream& os, const time& t){
    os << t.hour << ':' << t.minute;
    return os;
}
