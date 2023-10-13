#ifndef PROJAED_TIME_H
#define PROJAED_TIME_H


#include <string>

namespace Time {
    class time {
    public:
        time(double time);
        time();
        int getHour() const;
        int getMinute() const;

    private:
        int hour;
        int minute;
    };
}

#endif //PROJAED_TIME_H
