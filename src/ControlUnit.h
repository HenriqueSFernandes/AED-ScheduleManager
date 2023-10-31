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
#include <deque>
#include <stack>
#include <functional>
#include "lesson.h"
#include "Request.h"
#include "AddRequest.h"
#include "RemoveRequest.h"
#include "SwitchRequest.h"

class ControlUnit {


private:
    struct MainKey {
        string UcCode;
        string ClassCode;

        bool operator<(const MainKey &other) const {
            if (UcCode != other.UcCode) {
                return UcCode < other.UcCode;
            }
            return ClassCode < other.ClassCode;
        }
    };
    
    string filename;
    vector<Student> StudentVector;
    vector<lesson> LessonVector;
    list <studentGroup> StudentGroupList;
    map<MainKey, studentGroup *> KeyToStudentGroup;
    map<MainKey, set<lesson *>> LessonMap;
    map<MainKey, int> SizeMap;
    deque<Request *> RequestsToProcess;
    stack<Request *> ProcessedRequests;
    int cap = 30;

public :

    void Start(string filename);

    void LoadClassesCSV();

    void LoadClassesPerUcCSV();

    void LoadStudentsClassesCSV();

    void saveChanges();

    void DisplayStudentSchedule();

    void DisplayClassSchedule();

    int StudentsInAtLeastNUcs(int n);

    int StudentsInAtMostNUcs(int n);

    int StudentsInUcs(int n);

    //por a receber comparacao (perguntada no menu) para dar display diferente ao criar set resultado
    void courseStudents(string courseCode, function<bool(Student, Student)> func);

    void yearStudents(char year, function<bool(Student, Student)> func);

    void classStudents(string classCode, function<bool(Student, Student)> func);

    void UCWithMostStudents();

    //Helper Function
    int NumBalanced(vector<studentGroup>, map<MainKey, int>);

    bool IsThereConflict(vector<lesson>);

    //REQUEST FUNCSTIONS
    bool processRequest(Request *request);

    void processAddRequest(AddRequest *addRequest);

    void processRemoveRequest(RemoveRequest *removeRequest);

    void processSwitchRequest(SwitchRequest *switchRequest);

    void processAllRequests();  //this method process all requests in the queue;

    void removeLastPendingRequest(); //this method removes the most recent request that hasn't been applied

    void undoRequest(int n); //this method removes last n applied request

    void CheckIfThereAreConflicts();

    void createAdd();

    void createRemove();

    void createSwitch();

    bool CheckAdd(AddRequest *addrq);

    bool CheckRemove(RemoveRequest *remrq);

    bool CheckSwitch(SwitchRequest *swrq);

    string getClassinUc(string upcode, string uccode);
};


#endif //PROJAED_CONTROLUNIT_H
