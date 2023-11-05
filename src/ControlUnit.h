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
    list <studentGroup> StudentGroupList;
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
     * @brief Load students_classes.csv or student_classes_updated.csv, depending on the option chose.
     */
    void LoadStudentsClassesCSV();

    /**
     * @brief Deals with overlaps in a schedule.
     *
     * Complexity is O(n²) where n is the number of lessons given as input.
     * @param lessons Vector with all the lessons.
     * @return A 2d vector with the conflicts.
     */


    vector<vector<lesson>> formatConflicts(vector<lesson> &lessons);

    /**
     * @brief gives max size of all studentgroups
     *
     * Complexity is O(n) where n is the number of student groups.
     *
     * @return Max size of a studentGroup.
     */

    int maxSgSize();
    /**
     * @brief Set the cap
     *
     * Complexity is O(1)
     *
     * @return Max size of a studentGroup.
     */


    void setCap(int n);
    /**
     * @brief Saves the changes made, updating the file students_classes_updated.csv.
     *
     * Complexity is O(n * k) where n is the number of students and k is the number of classes for each student
     */
    void saveChanges();

    /**
     * @brief Displays the schedule of a student.
     *
     * Getting the schedule is O(log n + m * k ) where n is the total number of students, m is the number of student groups each student has k is the lessons in a student group.
     * Basically O(log n) as the other input is almost constant for each student and very small compared to n.
     * Additionally after getting the schedule it has to be displayed and that takes time which is not taken into consideration given its small impact on the overall performance.
     */
    void DisplayStudentSchedule();

    /**
     * @brief Displays the schedule of a class.
     *
     * Getting the schedule is O(n) where n is the total number of studentGroups.
     */
    void DisplayClassSchedule();

    /**
     * @brief Displays the students enrolled in at least N courses.
     *
     * Complexity is O(n) where n is the total number of students.
     * @param n Integer representing the minimum amount of courses.
     * @return Integer representing the amount of students enrolled in at least N courses.
     */
    int StudentsInAtLeastNUcs(int n);

    /**
     * @brief Displays the students enrolled in at most N courses.
     *
     * Complexity is O(n) where n is the total number of students.
     * @param n Integer representing the maximum amount of courses.
     * @return Integer representing the amount of students enrolled in at most N courses.
     */
    int StudentsInAtMostNUcs(int n);

    /**
     * @brief Displays the students enrolled in exactly N courses.
     *
     * Complexity is O(n) where n is the total number of students.
     * @param n Integer representing the amount of courses.
     * @return Integer representing the amount of students enrolled in N courses.
     */
    int StudentsInExactNUcs(int n);

    /**
     * @brief Displays the students enrolled in a specific course.
     *
     * Complexity is O(n * k) where n is the number of students and k is the number of classes for each student
     * @param courseCode String representing the course code.
     * @param func Boolean function used to sort students.
     */
    void courseStudents(string courseCode, function<bool(Student, Student)> func);

    /**
     * @brief Displays the students from a specific year.
     *
     * Complexity is O(n * k) where n is the number of students and k is the number of classes for each student
     * @param year Char representing the year,
     * @param func Boolean function used to sort students.
     */
    void yearStudents(char year, function<bool(Student, Student)> func);

    /**
     * @brief Displays the students from a specific class.
     *
     * Complexity is O(n * k) where n is the number of students and k is the number of classes for each student
     * @param classCode String representing the class code.
     * @param func Boolean function used to sort students.
     */
    void classStudents(string classCode, function<bool(Student, Student)> func);

    /**
     * @brief Displays all the courses starting with the one with the most student.
     *
     * Complexity is O(n * k) where n is the number of students and k is the number of classes for each student
     */
    void UCWithMostStudents();

    /**
     * @brief Checks the balance of the classes.
     *
     * Complexity is O(n) where n is the student groups given as input
     * @return Returns the maximum difference between the amount of students in each class.
     */
    int NumBalanced(vector<studentGroup>, map<MainKey, int>);

    /**
     * @brief Detects conflicts in a schedule.
     *
     * Complexity is O(n²) where n is the number of lessons given as input
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
     *
     * Complexity is O(log n) where n is the amount of students.
     * @param addRequest The request to be processed.
     */
    void processAddRequest(AddRequest *addRequest);

    /**
     * @brief Processes a request of type remove.
     *
     * Complexity is O(log n) where n is the amount of students.
     * @param removeRequest The request to be processed.
     */
    void processRemoveRequest(RemoveRequest *removeRequest);

    /**
     * @brief Processes a request of type switch.
     *
     * Complexity is O(log n) where n is the amount of students.
     * @param switchRequest The request to be processed.
     */
    void processSwitchRequest(SwitchRequest *switchRequest);

    /**
     * @brief Processes all the requests awaiting to be processed.
     *
     * Complexity is O(log n * k) where n is the amount of students and k is the amount of requests awaiting to be processed..
     */
    void processAllRequests();

    /**
     * @brief Removes the most recent request that hasn't been applied.
     *
     * Complexity is O(n) where n is the amount of requests awaiting to be processed..
     */
    void removeLastPendingRequest();

    /**
     * @brief Undoes the N most recent applied request.
     *
     * Complexity is O(log n * k) where n is the amount of students and k is the amount of requests that need to be undone..
     * @param n Integer representing how many requests should be undone.
     */
    void undoRequest(int n); //this method removes last n applied request

    /**
     * @brief Creates a request of type add.
     *
     * Complexity is O(log n) where n is the amount of students.
     */
    void createAdd();

    /**
     * @brief Creates a request of type remove.
     *
     * Complexity is O(log n) where n is the amount of students.
     */
    void createRemove();

    /**
     * @brief Creates a request of type switch.
     *
     * Complexity is O(log²(n) * k) where n is the amount of students and k is the amount of classes of that student.
     */
    void createSwitch();

    /**
     * @brief Checks if the request is possible.
     *
     * Complexity is O(log n * k + m) where n is the amount of students, k is the amount of classes of that student and m is the amount of classes related to the course.
     * @param addrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */
    bool CheckAdd(AddRequest *addrq);

    /**
     * @brief Checks if the request is possible.
     *
     * Complexity is O(log n * k) where n is the amount of students and k is the amount of classes of that student.
     * @param remrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */

    bool CheckRemove(RemoveRequest *remrq);

    /**
     * @brief Checks if the request is possible.
     *
     * Complexity is O(log n ) where n is the amount of students.
     * @param swrq Request to be analysed.
     * @return Boolean representing if the request is possible or not.
     */
    bool CheckSwitch(SwitchRequest *swrq);

    /**
     * @brief Gets the class of a student knowing the course.
     *
     * Complexity is O(log n * k) where n is the amount of students and k is the amount of classes of that student.
     * @param studentID String representing the student ID.
     * @param ucCode String representing the course code.
     * @return String representing the class code.
     */
    string getClassInUc(string studentID, string ucCode);



    /**
     * @brief Frees all the dynamic memory.
     *
     * Complexity is O(n) where n is the amount of classes plus the amount of lessons.
     */
    void clearMemory();
};


#endif //PROJAED_CONTROLUNIT_H
