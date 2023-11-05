/// @file lesson.h
#ifndef PROJAED_LESSON_H
#define PROJAED_LESSON_H


#include <string>
#include <ctime>
#include "lessontime.h"
#include <iostream>
#include <map>

/**
 * @brief Class used to represent a lesson from a course.
 */
class lesson {
public:
    /**
     * @brief Parameterized Constructor.
     * @param ucCode String representing the course.
     * @param studentGroup String representing the class.
     * @param weekday String representing the weekday.
     * @param startTime The time the lesson starts.
     * @param duration The duration of the lesson.
     * @param type The type of the lesson.
     */
    lesson(const std::string &ucCode, const std::string &studentGroup, const std::string &weekday, double startTime,
           double duration, const std::string &type);

    /**
     * @brief Gets the lesson's weekday.
     * @return A string representing the weekday.
     */
    const std::string &getWeekday() const;

    /**
     * @brief Gets the time the lesson starts.
     * @return The time the lesson starts.
     */
    const lessontime &getStartTime() const;

    /**
     * @brief Gets the duration of the lesson.
     * @return The duration of the lesson.
     */
    const lessontime &getDuration() const;

    /**
     * @brief Gets the time the lesson ends.
     * @return The time the lesson ends.
     */
    const lessontime &getEndTime() const;

    /**
     * @brief Gets the course code of the lesson.
     * @return A string representing the course code.
     */
    const string &getUccode() const;

    /**
     * @brief Gets the type of the lesson.
     * @return A string representing the type of the lesson.
     */
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
            }else if(other.getStartTime()<this->getStartTime()){
                return false;
            }else if(this->getUccode()<other.getUccode()){
                return true;
            }else{
                return false;
            }


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