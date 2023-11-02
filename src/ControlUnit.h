/// @file ControlUnit.h
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
#include <functional>
#include "lesson.h"
#include "Request.h"
#include "AddRequest.h"
#include "RemoveRequest.h"
#include "SwitchRequest.h"

/**
 * @brief Class used to handle the core functions of the program.
 */
class ControlUnit {

private:
    struct MainKey {
        string ucCode;
        string ClassCode;

        bool operator<(const MainKey &other) const {
            if (ucCode != other.ucCode) {
                return ucCode < other.ucCode;
            }
            return ClassCode < other.ClassCode;
        }
    };

    string filename;
    set<Student> StudentSet;
    vector<lesson> LessonVector;
    list<studentGroup> StudentGroupList;
    map<MainKey, studentGroup *> KeyToStudentGroup;
    map<MainKey, set<lesson *>> LessonMap;
    map<MainKey, int> SizeMap;
    queue<Request *> RequestsToProcess;
    stack<Request *> ProcessedRequests;
    int cap = 30;

public :

    /**
     * @brief Loads all the csv files.
     * @param studentFilename A string that represents the student csv, it can either be the original version or the updated version.
     */
    void LoadCSV(string studentFilename);

    /**
     *  @brief Loads the classes.csv file (which has all the lessons).
     */
    void LoadClassesCSV();

    /**
     * @brief Loads the classes_per_uc.csv file (which has all the courses and classes).
     */
    void LoadClassesPerUcCSV();
    /**
     * @brief deals with overlapping classes
     */
    vector<vector<lesson>> formatConflicts(vector<lesson> &lessons);

    /**
     * @brief Load students_classes.csv or student_classes_updated.csv, depending on the option chose.
     */
    void LoadStudentsClassesCSV();

    /**
     * @brief Saves the changes made, updating the file students_classes_updated.csv.
     */
    void saveChanges();

    /**
     * @brief Displays the schedule of a student.
     */
    void DisplayStudentSchedule();

    /**
     * @brief Displays the schedule of a class.
     */
    void DisplayClassSchedule();

    /**
     * @brief Displays the students enrolled in at least N courses.
     * @param n Integer representing the minimum amount of courses.
     * @return Integer representing the amount of students enrolled in at least N courses.
     */
    int StudentsInAtLeastNUcs(int n);

    /**
     * @brief Displays the students enrolled in at most N courses.
     * @param n Integer representing the maximum amount of courses.
     * @return Integer representing the amount of students enrolled in at most N courses.
     */
    int StudentsInAtMostNUcs(int n);

    /**
     * @brief Displays the students enrolled in exactly N courses.
     * @param n Integer representing the amount of courses.
     * @return Integer representing the amount of students enrolled in N courses.
     */
    int StudentsInUcs(int n);

    /**
     * @brief Displays the students enrolled in a specific course.
     * @param courseCode String representing the course code.
     * @param func Boolean function used to sort students.
     */
    void courseStudents(string courseCode, function<bool(Student, Student)> func);

    /**
     * @brief Displays the students from a specific year.
     * @param year Char representing the year,
     * @param func Boolean function used to sort students.
     */
    void yearStudents(char year, function<bool(Student, Student)> func);

    /**
     * @brief Displays the students from a specific class.
     * @param classCode String representing the class code.
     * @param func Boolean function used to sort students.
     */
    void classStudents(string classCode, function<bool(Student, Student)> func);

    /**
     * @brief Displays all the courses starting with the one with the most student.
     */
    void UCWithMostStudents();

    /**
     * @brief Checks the balance of the classes.
     * @return Returns the maximum difference between the amount of students in each class.
     */
    int NumBalanced(vector<studentGroup>, map<MainKey, int>);

    /**
     * @brief Detects conflicts in a schedule.
     * @return Boolean that represents the existence of conflicts.
     */
    bool IsThereConflict(vector<lesson>);

    /**
     * @brief Processes a request.
     * @param request Request to be processed.
     * @param bypassStack A boolean that states if the request should bypass the stack (true if the request is an undo of a previous request).
     * @return Boolean that represents if the request was processed successfully.
     */
    bool processRequest(Request *request, bool bypassStack = false);

    /**
     * @brief Processes a request of type add.
     * @param addRequest The request to be processed.
     */
    void processAddRequest(AddRequest *addRequest);

    /**
     * @brief Processes a request of type remove.
     * @param removeRequest The request to be processed.
     */
    void processRemoveRequest(RemoveRequest *removeRequest);

    /**
     * @brief Processes a request of type switch.
     * @param switchRequest The request to be processed.
     */
    void processSwitchRequest(SwitchRequest *switchRequest);

    /**
     * @brief Processes all the requests awaiting to be processed.
     */
    void processAllRequests();

    /**
     * @brief Removes the most recent request that hasn't been applied.
     */
    void removeLastPendingRequest();

    /**
     * @brief Undoes the N most recent applied request.
     * @param n Integer representing how many requests should be undone.
     */
    void undoRequest(int n); //this method removes last n applied request

    void CheckIfThereAreConflicts();

    /**
     * @brief Creates a request of type add.
     */
    void createAdd();

    /**
     * @brief Creates a request of type remove.
     */
    void createRemove();

    /**
     * @brief Creates a request of type switch.
     */
    void createSwitch();

    /**
     * @brief Checks if the request is possible.
     * @param addrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */
    bool CheckAdd(AddRequest *addrq);

    /**
     * @brief Checks if the request is possible.
     * @param remrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */
    bool CheckRemove(RemoveRequest *remrq);

    /**
     * @brief Checks if the request is possible.
     * @param swrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */
    bool CheckSwitch(SwitchRequest *swrq);

    /**
     * @brief Gets the class of a student knowing the course.
     * @param studentID String representing the student ID.
     * @param ucCode String representing the course code.
     * @return String representing the class code.
     */
    string getClassInUc(string studentID, string ucCode);

    /**
     * @brief Frees all the dynamic memory
     */
    void clearMemory();
};


#endif //PROJAED_CONTROLUNIT_H
