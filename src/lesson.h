#ifndef PROJAED_LESSON_H
#define PROJAED_LESSON_H


#include <string>
#include <ctime>
#include "lessontime.h"
#include <iostream>
#include <map>

class lesson {
public:
    lesson(const std::string &uccode, const std::string &studentgroup, const std::string &weekday, double startTime,
           double duration, const std::string &type);

    const std::string &getWeekday() const;

    const lessontime &getStartTime() const;

    const lessontime &getDuration() const;

    const lessontime &getEndTime() const;

    const string &getUccode() const;

    const std::string &getType() const;

    friend std::ostream &operator<<(std::ostream &os, const lesson &lesson);
    mutable std::map<std::string, int> dayMap = {{"Monday",    0},
                                                 {"Tuesday",   1},
                                                 {"Wednesday", 2},
                                                 {"Thursday",  3},
                                                 {"Friday",    4},
                                                 {"Saturday",  5},
                                                 {"Sunday",    6}};
    bool operator<(const lesson &other) const {
        if(dayMap[this->getWeekday()]<dayMap[other.getWeekday()]){
            return true;
        }else if(dayMap[this->getWeekday()]==dayMap[other.getWeekday()]){
            if(this->getStartTime()<other.getStartTime()){
                return true;
            }
            return false;

        }
        return false;

    }

private:

    std::string studentGroup;
    std::string UcCode;
    std::string weekday;
    lessontime startTime;
    lessontime duration;
    lessontime endTime;
    std::string type;
};


#endif //PROJAED_LESSON_H