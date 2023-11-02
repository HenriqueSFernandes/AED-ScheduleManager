/// @file Schedule.h
#ifndef PROJAED_SCHEDULE_H
#define PROJAED_SCHEDULE_H

#include <vector>
#include "lesson.h"
#include <map>

using namespace std;

/**
 * @brief Class used to display a schedule
 */
class Schedule {
private:
    vector<lesson> lessons; //the lessons that go into the schedule
    map<pair<int, int>, string> ScheduleMap; // a schedule is made up of 30 by 6 blocks
public:
    /**
     * @brief Parameterized constructor.
     * @param lessons Vector with all the lessons to be displayed.
     */
    Schedule(vector<lesson> lessons);

    /**
     * @brief Displays the schedule.
     */
    void display();

};


#endif //PROJAED_SCHEDULE_H