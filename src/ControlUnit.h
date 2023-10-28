//
// Created by nowayjose on 20/10/2023.
//

#ifndef PROJAED_CONTROLUNIT_H
#define PROJAED_CONTROLUNIT_H


#include <vector>
#include <string>
#include "studentGroup.h"
#include <map>
#include "student.h"
#include <set>
#include <list>
#include <queue>
#include <stack>
#include "lesson.h"
#include "Request.h"
#include "AddRequest.h"
#include "RemoveRequest.h"
#include "SwitchRequest.h"

class ControlUnit {
public :

    void Start();
    void LoadClassesCSV();
    void LoadClassesPerUcCSV();

    void LoadStudentsClassesCSV();
    void DisplayStudentSchedule();
    void DisplayClassSchedule();
    int StudentsInAtLeastNUcs(int n);

    //por a receber comparacao (perguntada no menu) para dar display diferente ao criar set resultado
    void courseStudents(string courseCode);
    void yearStudents(char year);
    void classStudents(string classCode);
    void UCWithMostStudents();

    //Helper Function
    bool IsBalanced(vector<studentGroup>);
    bool IsThereConflict(vector<lesson>);
    //REQUEST FUNCSTIONS
    void processRequest(Request * request );
    void processAddRequest(AddRequest * addRequest);
    void processRemoveRequest(RemoveRequest * removeRequest);
    void processSwitchRequest(SwitchRequest * switchRequest);
    void createAdd();
    void createRemove();
    void createSwitch();

private:
    struct MainKey {
        string UcCode;
        string ClassCode;

        bool operator<(const MainKey& other) const {
            if (UcCode != other.UcCode) {
                return UcCode < other.UcCode;
            }
            return ClassCode < other.ClassCode;
        }
    };
    //set<Student> StudentSet; nao ta a ser usado
    vector<Student> StudentVector;
    vector<lesson> LessonVector;
    list<studentGroup> StudentGroupVector;
    map<MainKey,studentGroup*> KeyToStudentGroup;

    map<MainKey,set<lesson*>> LessonMap;
    queue<Request*> RequestsToProcess;
    stack<Request*> ProcessedRequests;


};


#endif //PROJAED_CONTROLUNIT_H
