#ifndef PROJAED_SCHEDULE_H
#define PROJAED_SCHEDULE_H

#include <vector>
#include "lesson.h"
#include <map>

using namespace std;

class Schedule {
private:
    vector<lesson> lessons; //the lessons that go into the schedule
    map<pair<int, int>, string> ScheduleMap; // a schedule is made up of 30 by 6 blocks
public:
    Schedule(vector<lesson>);

    void display();


};


#endif //PROJAED_SCHEDULE_H