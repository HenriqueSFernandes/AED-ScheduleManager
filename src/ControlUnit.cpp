#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
#include <algorithm>
#include <climits>
#include "RemoveRequest.h"

using namespace std;

void ControlUnit::LoadCSV(string studentFilename) {
    this->filename = studentFilename;
    ControlUnit::LoadClassesPerUcCSV();
    cout << "Loaded classes and courses." << endl;
    ControlUnit::LoadClassesCSV();
    cout << "Loaded lessons." << endl;

    ControlUnit::LoadStudentsClassesCSV();
    cout << "Loaded students." << endl;
}

void ControlUnit::LoadClassesPerUcCSV() {
    string ucCode;
    string classCode;
    ifstream classes_per_uc("../data/classes_per_uc.csv");

    if (!classes_per_uc) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(classes_per_uc, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(classes_per_uc, line)) {
        istringstream iss(line);
        getline(iss, ucCode, ',');
        getline(iss, classCode, '\r');

        studentGroup *group = new studentGroup(ucCode, classCode);
        StudentGroupList.push_back(*group);

        MainKey groupKey = {ucCode, classCode};
        KeyToStudentGroup[groupKey] = group;
    }

    classes_per_uc.close();
}

void ControlUnit::LoadClassesCSV() {
    string line;
    string classCode;
    string ucCode;
    string weekday;
    string startTime;
    string duration;
    string type;
    ifstream classes("../data/classes.csv");

    if (!classes) {
        cerr << "Failed to open file\n";
        return;
    }

    getline(classes, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new lesson and add that lesson to the respective class.
    while (getline(classes, line)) {
        istringstream iss(line);
        getline(iss, classCode, ',');
        getline(iss, ucCode, ',');
        getline(iss, weekday, ',');
        getline(iss, startTime, ',');
        getline(iss, duration, ',');
        getline(iss, type, '\r');

        // Create a new lesson and add it to the vector of all lessons.
        lesson *Lesson = new lesson(ucCode, classCode, weekday, stod(startTime), stod(duration), type);
        LessonVector.push_back(*Lesson);

        MainKey groupKey = {ucCode, classCode};
        // If the lesson is the first lesson for that class add a new entry on the map.
        if (LessonMap.find(groupKey) == LessonMap.end()) {
            set<lesson *> newSet;
            newSet.insert(Lesson);
            LessonMap[groupKey] = newSet;
        }
            // Otherwise just insert the lesson on the map;
        else {
            LessonMap[groupKey].insert(Lesson);
        }
    }
    classes.close();
}

void ControlUnit::LoadStudentsClassesCSV() {
    string line;
    string studentID;
    string name;
    string ucCode;
    string classCode;
    ifstream students_classes(filename);

    if (!students_classes) {
        cerr << "Failed to open file\n";
    }

    getline(students_classes, line); // Ignore header

    // Start by getting the first student.
    getline(students_classes, line);
    istringstream iss(line);
    getline(iss, studentID, ',');
    getline(iss, name, ',');
    getline(iss, ucCode, ',');
    getline(iss, classCode, '\r');
    set<studentGroup> classesPerStudent; // set to hold all the classes for the current student.
    classesPerStudent.insert(studentGroup(ucCode, classCode));

    string previousStudentID = studentID;
    string previousName = name;

    MainKey key = {ucCode, classCode};
    // Update the map with the size of the classes.
    if (SizeMap.find(key) == SizeMap.end()) {
        SizeMap[key] = 1;
    } else {
        SizeMap[key]++;
    }

    // Iterate over the rest of the file and split the line.
    while (getline(students_classes, line)) {
        istringstream iss(line);
        getline(iss, studentID, ',');
        getline(iss, name, ',');
        getline(iss, ucCode, ',');
        getline(iss, classCode, '\r');
        key = {ucCode, classCode};
        // Update the map with the size of the classes.
        if (SizeMap.find(key) == SizeMap.end()) {
            SizeMap[key] = 1;
        } else {
            SizeMap[key]++;
        }
        // If the student is the same as before just insert a new class in the set.
        if (studentID == previousStudentID) {
            classesPerStudent.insert(studentGroup(ucCode, classCode));
        }
            // Otherwise create the student with the classes found so far and insert that student into the set.
        else {
            Student student(previousStudentID, previousName, classesPerStudent);
            StudentSet.insert(student);
            classesPerStudent.clear();
            classesPerStudent.insert(studentGroup(ucCode, classCode));
            previousStudentID = studentID;
            previousName = name;
        }
    }
    // Finally insert the last student into the set.
    Student student(previousStudentID, previousName, classesPerStudent);
    StudentSet.insert(student);
    classesPerStudent.clear();

    students_classes.close();
}

void ControlUnit::DisplayStudentSchedule() {
    cout << "Would you like the default Version or the Visual Version" << endl;
    cout << "1) Default" << endl;
    cout << "2) Visual" << endl;
    int option;
    cin >> option;
    cout << "Enter the UPCODE OF THE STUDENT" << endl;
    string studentId;
    cin >> studentId;
    Student dummyStudent(studentId, "", {});
    auto student = StudentSet.find(dummyStudent);

    // Find a valid student.
    while (student == StudentSet.end()) {
        cout << "Invalid Student Code, please provide a new one." << endl;
        cin.clear();
        cin >> studentId;
        dummyStudent.setStudentID(studentId);
        student = StudentSet.find(dummyStudent);
    }
    set<lesson> lessonSet;
    vector<lesson> myVec;
    set<studentGroup> studentGroups = student->getStudentGroups();
    // Iterate over every class of the student.
    for (const auto &studentGroup: studentGroups) {
        MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};

        // Iterate over every lesson and add it to the set.
        set<lesson *> Lectures = LessonMap[key];
        for (auto element: Lectures) {

            lessonSet.insert(*element);
            myVec.push_back(*element);
        }
    }
    cout << "Displaying schedule for student " << student->getName() << " " << student->getStudentID() << ".\n";
    if (option == 1) {
        // Display the schedule in a list format.
        for (const auto &lesson: lessonSet) {
            int width = 90;
            string horizontalLine(width, '-');

            cout << '+' << horizontalLine << '+' << endl;
            cout << "    " << lesson << endl;
            cout << '+' << horizontalLine << '+' << endl << endl;
        }
    } else if (option == 2) {
        // Display the schedule in a visual way.
        vector<vector<lesson> > overlapsVector;
        overlapsVector = formatConflicts(myVec); // Check for overlaps.
        Schedule StudentSchedule = Schedule(myVec);
        StudentSchedule.display();
        int num = 1;
        for (auto overlap: overlapsVector) {
            int width = 108;
            string horizontalLine(width, '-');

            cout << '+' << horizontalLine << '+' << endl;
            cout << "    " << "Overlap" << " # " << num << endl;
            cout << '+' << horizontalLine << '+' << endl;

            for (auto lesson: overlap) {
                cout << " " << lesson << endl;
                cout << '-' << horizontalLine << '-' << endl;
            }
            num++;
        }

    }


}

void ControlUnit::DisplayClassSchedule() {
    cout << "Would you like the default Version or the Visual Version" << endl;
    cout << "1) Default" << endl;
    cout << "2) Visual" << endl;
    int option;
    cin >> option;
    cout << "Enter the Class Code" << endl;
    string classCode;

    // Find the class.
    bool found = false;
    while (!found) {
        cin >> classCode;
        for (auto i: StudentGroupList) {
            if (i.getClassCode() == classCode) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Invalid class, please provide a new one.\n";
        }
    }
    vector<lesson> LessonsVector;
    struct LessonComparator {
        bool operator()(const lesson *lhs, const lesson *rhs) const {
            return *lhs < *rhs;
        }
    };
    // Store the lessons in a set.
    set<lesson *, LessonComparator> LessonsSet;
    for (auto studentGroup: StudentGroupList) {
        if (studentGroup.getClassCode() == classCode) {
            MainKey key = {studentGroup.getUcCode(), classCode};
            LessonsSet.insert(LessonMap[key].begin(), LessonMap[key].end());
        }
    }

    // Iterate over every lesson and display the schedule.
    for (auto lesson: LessonsSet) {

        LessonsVector.push_back(*lesson);
        if (option == 1) {
            int width = 90; // Calculate the width based on the content length
            string horizontalLine(width, '-');

            cout << '+' << horizontalLine << '+' << endl;
            cout << "    " << *lesson << endl;
            cout << '+' << horizontalLine << '+' << endl;

        }
    }
    if (option == 2) {
        Schedule ClassSchedule = Schedule(LessonsVector);
        ClassSchedule.display();
    }
}

// Removes overlaps and places inside a return vector the classes that make up each conflict.
vector<vector<lesson>> ControlUnit::formatConflicts(vector<lesson> &lessons) {
    //overLapVector stores the classes that are involved in a given conflict.
    vector<vector<lesson>> OverlapVector;

    int numofconflit = 0;
    for (int i = 0; i < lessons.size() - 1; i++) {
        for (int j = i + 1; j < lessons.size(); j++) {

            bool overLap = lessons[i].getStartTime() < lessons[j].getEndTime() and
                           lessons[j].getStartTime() < lessons[i].getEndTime();


            bool sameDay = lessons[i].getWeekday() == lessons[j].getWeekday();
            if (overLap and sameDay) { // there is an overlap if the hours overlap and they are in the same day.
                lessontime start = min(lessons[i].getStartTime(), lessons[j].getStartTime());
                lessontime end = max(lessons[i].getEndTime(), lessons[j].getEndTime());
                double startnum = start.getHour();
                if (start.getMinute() > 0) {
                    startnum += 0.5;
                }
                double endnum = end.getHour();
                if (end.getMinute() > 0) {
                    endnum += 0.5;
                }
                if (lessons[j].getUccode() == "Overlap") { // for multiple conflicts > 2 classes.
                    cout << "OVERLAP" << endl;
                    cout << "CONFLICT NUM " << numofconflit << endl;
                    //dummy is a fake class that represents a conflict.
                    lesson dummy = lesson("Overlap", "Overlap", lessons[j].getWeekday(), startnum, endnum - startnum,
                                          lessons[j].getType());
                    vector<lesson> lessonsInConflict = OverlapVector[numofconflit - 1];
                    lessonsInConflict.push_back(lessons[i]);
                    lessons.erase(lessons.begin() + j);
                    lessons.erase(lessons.begin() + i);
                    OverlapVector[numofconflit - 1] = lessonsInConflict;
                    lessons.push_back(dummy);
                } else { //normal conflicts
                    numofconflit++;
                    //dummy is a fake class that represents a conflict.
                    lesson dummy = lesson("Overlap", "Overlap", lessons[i].getWeekday(), startnum, endnum - startnum,
                                          to_string(numofconflit));

                    vector<lesson> lessonsInConflict;

                    lessonsInConflict.push_back(lessons[i]);
                    lessonsInConflict.push_back(lessons[j]);
                    lessons.erase(lessons.begin() + j);
                    lessons.erase(lessons.begin() + i);


                    OverlapVector.push_back(lessonsInConflict);

                    lessons.push_back(dummy);
                }
            }
        }
    }
    return OverlapVector;
}

// Determines number of student in at least N ucs
int ControlUnit::StudentsInAtLeastNUcs(int n) {

    int NumberOfStudents = 0;

    // Iterate over every student, if the student is enrolled in more than n courses then output it.
    for (auto student: this->StudentSet) {
        set<studentGroup> studentgroups = student.getStudentGroups();


        if (studentgroups.size() >= n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;
}

// Determines number of student in at most N ucs
int ControlUnit::StudentsInAtMostNUcs(int n) {

    int NumberOfStudents = 0;

    // Iterate over every student, if the student is enrolled in less than n courses then output it.
    for (auto student: this->StudentSet) {
        set<studentGroup> studentgroups = student.getStudentGroups();


        if (studentgroups.size() <= n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;


}

// Determines number of student in N ucs
int ControlUnit::StudentsInExactNUcs(int n) {

    int NumberOfStudents = 0;

    // Iterate over every student, if the student is enrolled in n courses then output it.
    for (auto student: this->StudentSet) {
        set<studentGroup> studentgroups = student.getStudentGroups();

        if (studentgroups.size() == n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;
}

// Outputs the students from a specific class.
void ControlUnit::classStudents(string classCode, function<bool(Student, Student)> func) {
    set<studentGroup> groups;
    set<Student, decltype(func)> students(func);
    string ucCode;
    bool notexist = true;
    while (notexist) {
        for (auto group: StudentGroupList) {
            if (classCode == group.getClassCode()) {
                notexist = false;
                break;
            }
        }
        if (notexist) {
            cout << "Given class doesn't exist, please provide a new class code:" << endl;
            cin >> classCode;
        }
    }
    cout << "Which course from class " << classCode << " you would like to see students from?:" << endl;
    cin >> ucCode;
    notexist = true;

    while (notexist) {
        for (auto group: StudentGroupList) {
            if (classCode == group.getClassCode() && ucCode == group.getUcCode()) {
                notexist = false;
                break;
            }
        }
        if (notexist) {
            cout << "This course doesn't exist in this class, please provide a new Course:" << endl;
            cin >> ucCode;
        }
    }
    for (auto student: StudentSet) {
        groups = student.getStudentGroups();
        for (auto group: groups) {
            if (group.getClassCode() == classCode && group.getUcCode() == ucCode) {
                students.insert(student);
                break;
            }
        }
    }

    cout << "Students in " << classCode << " from " << ucCode << " :" << endl << endl;
    for (auto student: students) {
        cout << student << endl;
    }
    cout << endl << "There are " << students.size() << " students in the class " << classCode << " from course "
         << ucCode << "." << endl;

}

// Outputs the students in a specific course.
void ControlUnit::courseStudents(string courseCode, function<bool(Student, Student)> func) {
    set<studentGroup> groups;
    set<Student, decltype(func)> students(func);
    bool notexist = true;
    while (notexist) {
        for (auto student: StudentSet) {
            groups = student.getStudentGroups();
            for (auto group: groups) {
                if (group.getUcCode() == courseCode) {
                    students.insert(student);
                    break;
                }
            }
        }
        if (students.size() == 0) {
            notexist = true;
            cout << "Given UC code doesn't exist, please provide a new one:" << endl;
            cin >> courseCode;
        } else {
            notexist = false;
        }
    }
    cout << "Students in " << courseCode << ":" << endl << endl;
    for (auto student: students) {
        cout << student << endl;
    }
    cout << endl << "There are " << students.size() << " students in the course " << courseCode << "." << endl;

}

// Outputs the students in a specific year.
void ControlUnit::yearStudents(char year, function<bool(Student, Student)> func) {
    set<studentGroup> groups;
    set<Student, decltype(func)> students(func);
    bool notexist = true;
    while (notexist) {
        for (auto student: StudentSet) {
            groups = student.getStudentGroups();
            for (auto group: groups) {
                if (group.getClassCode()[0] == year) {
                    students.insert(student);
                    break;
                }
            }
        }
        if (students.size() == 0) {
            notexist = true;
            cout << "Given year doesn't exist, please provide a new one:" << endl;
            cin >> year;
        } else {
            notexist = false;
        }
    }
    cout << "Students in year " << year << ":" << endl << endl;
    for (auto student: students) {
        cout << student << endl;
    }
    cout << endl << "There are " << students.size() << " students in the year " << year << "." << endl;
}


// Displays the courses starting with the one with the most students.
void ControlUnit::UCWithMostStudents() {
    set<studentGroup> groups;
    map<string, int> courseOccupation;
    // Iterate over every student and get the occupation.
    for (auto student: StudentSet) {
        groups = student.getStudentGroups();
        for (auto group: groups) {
            if (courseOccupation.find(group.getUcCode()) == courseOccupation.end()) {
                courseOccupation[group.getUcCode()] = 1;
            } else {
                courseOccupation[group.getUcCode()] += 1;
            }
        }
    }
    // Create and sort a vector with the courses.
    vector<pair<string, int>> ucsvec(courseOccupation.begin(), courseOccupation.end());
    sort(ucsvec.begin(), ucsvec.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });
    cout << "These are the Ucs in descending order of registered students." << endl;
    for (auto uc: ucsvec) {
        cout << uc.first << " with " << uc.second << " students." << endl << endl;
    }
}

// Iterates over every class from a vector and checks the balance.
int ControlUnit::NumBalanced(vector<studentGroup> groups, map<MainKey, int> myMap) {

    int cap = this->cap;
    int min = cap + 1;
    int max = -1;

    for (auto studentGroup: groups) {
        MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};

        int size = myMap[key];

        if (size > max) { max = size; }
        if (size < min) { min = size; }

    }

    return max - min;
}

bool ControlUnit::IsThereConflict(vector<lesson> lessons) {
    // Iterates over every pair of lessons in the vector.
    for (int i = 0; i < lessons.size() - 1; i++) {
        for (int j = i + 1; j < lessons.size(); j++) {
            // Checks if they overlap, are both practical and if they are on the same day.
            bool overLap = lessons[i].getStartTime() < lessons[j].getEndTime() and
                           lessons[j].getStartTime() < lessons[i].getEndTime();

            bool bothPractical = (lessons[i].getType() == "TP" or lessons[i].getType() == "PL") and
                                 (lessons[j].getType() == "TP" or lessons[j].getType() == "PL");
            bool sameDay = lessons[i].getWeekday() == lessons[j].getWeekday();
            if (overLap and bothPractical and sameDay) {
                cout << lessons[i] << "/" << lessons[j] << endl;
                return true;
            }
        }
    }
    return false;
}

void ControlUnit::createAdd() {
    string id;
    string uc;
    string studentgroup;

    cout << "What's the ID of the student that you want to add to an UC:" << endl;
    cin >> id;
    Student dummyStudent(id, "", {});
    while (StudentSet.find(dummyStudent) == StudentSet.end()) {
        cout << "Given student ID doesn't exist, please provide a new one." << endl;
        cin >> id;
        dummyStudent.setStudentID(id);
    }
    cout << "What UC do you want to add the student to:" << endl;
    cin >> uc;
    cout << "What Class of the UC you want to add the student into:" << endl;
    cin >> studentgroup;
    RequestsToProcess.push(new AddRequest(id, uc, studentgroup));
}

void ControlUnit::createRemove() {
    cout << "What's the ID of the student that you want to remove from an UC:" << endl;
    string upCode;
    string ucCode;
    string studentgroup;
    cin >> upCode;
    Student dummyStudent(upCode, "", {});
    while (StudentSet.find(dummyStudent) == StudentSet.end()) {
        cout << "Given student ID doesn't exist, please provide a new one." << endl;
        cin >> upCode;
        dummyStudent.setStudentID(upCode);
    }
    cout << "What UC you want to remove the student from:" << endl;
    cin >> ucCode;
    studentgroup = getClassInUc(upCode, ucCode);
    RequestsToProcess.push(new RemoveRequest(upCode, ucCode, studentgroup));
}

void ControlUnit::createSwitch() {
    cout << "What's the ID of the student that you want to switch from classes/UCs:" << endl;
    string id;
    string uc1;
    string uc2;
    int choice;
    string studentgroup1;
    string studentgroup2;
    cin >> id;
    Student dummyStudent(id, "", {});
    while (StudentSet.find(dummyStudent) == StudentSet.end()) {
        cout << "Given student ID doesn't exist, please provide a new one." << endl;
        cin >> id;
        dummyStudent.setStudentID(id);
    }
    while (true) {
        cout << "Do you want to switch UCs or switch Classes from an UC?" << endl;
        cout << "1) Switch UCs" << endl;
        cout << "2) Switch Classes" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "What UC do you want to leave?" << endl;
                cin >> uc1;
                studentgroup1 = getClassInUc(id, uc1);
                while (studentgroup1 == "false") {
                    cout << "Student not in given UC please give another one." << endl;
                    cin >> uc1;
                    studentgroup1 = getClassInUc(id, uc1);
                }
                cout << "What UC do you want to join?" << endl;
                cin >> uc2;
                break;
            case 2:
                cout << "What UC do you want to swap classes?" << endl;
                cin >> uc1;
                studentgroup1 = getClassInUc(id, uc1);
                while (studentgroup1 == "false") {
                    cout << "Student not in given UC please give another one." << endl;
                    cin >> uc1;
                    studentgroup1 = getClassInUc(id, uc1);
                }
                uc2 = uc1;
                break;
            default:
                cout << "Invalid option." << endl;
                continue;
        }
        break;
    }
    cout << "What class do you want to go to?";
    cin >> studentgroup2;
    RequestsToProcess.push(new SwitchRequest(id, uc1, uc2, studentgroup1, studentgroup2));
}

string ControlUnit::getClassInUc(string studentID, string ucCode) {
    auto student = StudentSet.find(Student(studentID, "", {}));
    if (student == StudentSet.end()) {
        return "invalidstudent";
    }
    // Iterate over every class of the student, if the course matches the desired course return the class.
    for (const auto &studentGroup: student->getStudentGroups()) {
        if (studentGroup.getUcCode() == ucCode) {
            return studentGroup.getClassCode();
        }
    }
    return "invalidcourse";
}

// Checks if the request is possible.
bool ControlUnit::CheckAdd(AddRequest *addrq) {
    bool result = true;
    string studentId = addrq->getStudentID();
    bool notMoreThan7 = true;
    bool studentExists = false;
    bool notInMoreThanOneClass = true;

    MainKey key = {addrq->getUCCode(), addrq->getClassCode()};
    bool classExists = KeyToStudentGroup.find(key) != KeyToStudentGroup.end();

    map<string, int> HaveISeenThisUc;
    vector<lesson> lessonVec;

    // Checks if the student exists and if already has one class regarding the chosen course.
    auto student = StudentSet.find(Student(addrq->getStudentID(), "", {}));
    if (student != StudentSet.end()) {
        studentExists = true;
        notInMoreThanOneClass = !student->isInUC(addrq->getUCCode());

        // Retrieve lessons associated with the student's current classes.
        for (auto studentGroup: student->getStudentGroups()) {
            MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};
            set<lesson *> lessonSet = LessonMap[key];
            for (auto lesson: lessonSet) {
                lessonVec.push_back(*lesson);
            }
        }
        // Checks if the student has 7 or more courses.
        if (student->getStudentGroups().size() >= 7) {
            notMoreThan7 = false;
        }
    }

    vector<studentGroup> classes;

    map<MainKey, int> dummyMap = SizeMap;
    // Iterate over all classes to find the ones related to the chosen course.
    for (auto sg: StudentGroupList) {
        if (sg.getUcCode() == addrq->getUCCode()) {
            classes.push_back(sg);

            if (sg.getClassCode() == addrq->getClassCode()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]++;
            }
        }
    }

    key = {addrq->getUCCode(), addrq->getClassCode()};
    int oldBalance = NumBalanced(classes, SizeMap);
    set<lesson *> lessonSet = LessonMap[key];
    int newbalance = NumBalanced(classes, dummyMap);

    for (auto lesson: lessonSet) {
        lessonVec.push_back(*lesson);
    }
    int classSize = SizeMap[key];

    // Checks if the class size exceeds maximum capacity.
    bool respectsCap = true;
    if (classSize >= cap) {
        respectsCap = false;
    }

    bool validBalance;
    // Checks if the balance is 4 or better or if it's better than the old balance.
    if (newbalance <= 4 or newbalance <= oldBalance) {
        validBalance = true;
    } else {
        validBalance = false;
    }
    result = notMoreThan7 and studentExists and notInMoreThanOneClass and respectsCap and classExists and
             not IsThereConflict(lessonVec) and validBalance;
    return result;
}


bool ControlUnit::CheckRemove(RemoveRequest *remrq) {
    bool result = true;

    string studentID = remrq->getStudentID();
    bool notLessThan0 = true;
    bool studentExists = false;
    bool isInClass = true;
    auto student = StudentSet.find(Student(remrq->getStudentID(), "", {}));
    // Checks if the student exists and if he has at least 2 courses.
    if (student != StudentSet.end()) {
        studentExists = true;
        if (student->getStudentGroups().size() <= 1) {
            notLessThan0 = false;
        }
        isInClass = student->isInClass(remrq->getUCCode(), remrq->getClassCode());

    }

    vector<studentGroup> classes;

    map<MainKey, int> dummyMap = SizeMap;
    // Gets all the classes related to the chosen course.
    for (auto studentGroup: StudentGroupList) {
        if (studentGroup.getUcCode() == remrq->getUCCode()) {
            classes.push_back(studentGroup);

            if (studentGroup.getClassCode() == remrq->getClassCode()) {
                MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};
                dummyMap[key]--;
            }
        }
    }
    MainKey key = {remrq->getUCCode(), remrq->getClassCode()};
    int oldBalance = NumBalanced(classes, SizeMap);
    int newbalance = NumBalanced(classes, dummyMap);
    bool validBalance;
    // Checks if the balance is 4 or better or if it's better than the old balance.
    if (newbalance <= 4 or newbalance <= oldBalance) {
        validBalance = true;
    } else {
        validBalance = false;
    }
    result = (notLessThan0 and studentExists and isInClass and validBalance);
    return result;
}

bool ControlUnit::CheckSwitch(SwitchRequest *swrq) {
    bool result;
    string studentID = swrq->getStudentID();
    bool studentExists = false;
    bool isInClass = true;
    bool respectsCap = true;
    bool notInMoreThan1Class = true;

    MainKey key = {swrq->getUCCode2(), swrq->getClassCode2()};
    bool classExists = KeyToStudentGroup.find(key) != KeyToStudentGroup.end();
    vector<lesson> mylessons;

    auto student = StudentSet.find(Student(swrq->getStudentID(), "", {}));

    // Checks if the student exists and if he is part of the given class.
    if (student != StudentSet.end()) {
        studentExists = true;
        isInClass = student->isInClass(swrq->getUCCode1(), swrq->getClassCode1());
        if (swrq->getUCCode1() != swrq->getUCCode2()) {
            notInMoreThan1Class = !student->isInUC(swrq->getUCCode2());
        }
        // Gets current lessons.
        for (auto sg: student->getStudentGroups()) {
            MainKey key = {sg.getUcCode(), sg.getClassCode()};
            if (sg.getUcCode() + sg.getClassCode() != swrq->getUCCode1() + swrq->getClassCode1()) {
                set<lesson *> lessonSet = LessonMap[key];
                for (auto les: lessonSet) {
                    mylessons.push_back(*les);
                }
            }
        }
        // Gets new lessons.
        MainKey key = {swrq->getUCCode2(), swrq->getClassCode2()};
        set<lesson *> lessonSet = LessonMap[key];
        for (auto les: lessonSet) {
            mylessons.push_back(*les);
        }

    }
    bool conflict = IsThereConflict(mylessons);
    key = {swrq->getUCCode2(), swrq->getClassCode2()};
    int classSize = SizeMap[key];
    if (classSize >= cap) {
        respectsCap = false;
    }

    bool validBalanceRem;
    bool validBalanceAdd;

    vector<studentGroup> oldClasses;
    vector<studentGroup> newClasses;
    map<MainKey, int> dummyMap = SizeMap;
    for (auto sg: StudentGroupList) {
        if (sg.getUcCode() == swrq->getUCCode1()) {
            oldClasses.push_back(sg);

            if (sg.getClassCode() == swrq->getClassCode1()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]--;
            }
        }
        if (sg.getUcCode() == swrq->getUCCode2()) {
            newClasses.push_back(sg);

            if (sg.getClassCode() == swrq->getClassCode2()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]++;
            }
        }
    }

    int oldBalance1 = NumBalanced(oldClasses, SizeMap);
    int newbalance1 = NumBalanced(oldClasses, dummyMap);

    // Checks if the balance is 4 or better or if it's better than the old balance.
    if (newbalance1 <= 4 or newbalance1 <= oldBalance1) {
        validBalanceRem = true;
    } else {
        validBalanceRem = false;
    }
    int oldBalance2 = NumBalanced(newClasses, SizeMap);
    int newbalance2 = NumBalanced(newClasses, dummyMap);
    // Checks if the balance is 4 or better or if it's better than the old balance.
    if (newbalance2 <= 4 or newbalance2 <= oldBalance2) {
        validBalanceAdd = true;
    } else {
        validBalanceAdd = false;
    }

    result = (classExists and studentExists and isInClass and respectsCap and notInMoreThan1Class and !conflict and
              validBalanceAdd and validBalanceRem);
    return result;

}


bool ControlUnit::processRequest(Request *request, bool bypassStack) {
    bool isvalid;
    // Get type of request and process it.
    if (request->getType() == "add") {
        isvalid = CheckAdd(dynamic_cast<AddRequest *>(request));
        if (isvalid) {
            processAddRequest(dynamic_cast<AddRequest *>(request));
            if (!bypassStack) {
                ProcessedRequests.push(request);
            }
            return true;
        } else {
            InvalidRequests.push(request);
            delete request;
            return false;
        }

    } else if (request->getType() == "remove") {
        isvalid = CheckRemove(dynamic_cast<RemoveRequest *>(request));
        if (isvalid) {
            processRemoveRequest(dynamic_cast<RemoveRequest *>(request));
            if (!bypassStack) {
                ProcessedRequests.push(request);
            }
            return true;
        } else {
            InvalidRequests.push(request);
            delete request;
            return false;
        }

    } else if (request->getType() == "switch") {
        isvalid = CheckSwitch(dynamic_cast<SwitchRequest *>(request));
        if (isvalid) {
            processSwitchRequest(dynamic_cast<SwitchRequest *>(request));
            if (!bypassStack) {
                ProcessedRequests.push(request);
            }
            return true;
        } else {
            InvalidRequests.push(request);
            delete request;
            cout << "Error in switch request" << endl;
            return false;
        }
    }
    delete request;
    return false;
}

void ControlUnit::processAddRequest(AddRequest *addRequest) {
    string upCode = addRequest->getStudentID();
    string classCode = addRequest->getClassCode();
    string ucCode = addRequest->getUCCode();
    Student dummyStudent(addRequest->getStudentID(), "", {});
    auto student = StudentSet.find(dummyStudent);
    if (student != StudentSet.end()) {
        dummyStudent = *student;
        StudentSet.erase(student);
        dummyStudent.addStudentGroup(studentGroup(ucCode, classCode));
        MainKey key = {ucCode, classCode};

        if (SizeMap.find(key) == SizeMap.end()) {
            SizeMap[key] = 1;
        } else {
            SizeMap[key]++;
        }
        StudentSet.insert(dummyStudent);
    }
}

void ControlUnit::processRemoveRequest(RemoveRequest *removeRequest) {
    string upCode = removeRequest->getStudentID();
    string classCode = removeRequest->getClassCode();
    string ucCode = removeRequest->getUCCode();
    Student dummyStudent(removeRequest->getStudentID(), "", {});
    auto student = StudentSet.find(dummyStudent);
    if (student != StudentSet.end()) {
        dummyStudent = *student;
        StudentSet.erase(student);
        dummyStudent.removeGroup(studentGroup(ucCode, classCode));
        MainKey key = {ucCode, classCode};
        SizeMap[key]--;

        StudentSet.insert(dummyStudent);
    }
}


void ControlUnit::processSwitchRequest(SwitchRequest *switchRequest) {
    RemoveRequest *RemReq = new RemoveRequest(switchRequest->getStudentID(), switchRequest->getUCCode1(),
                                              switchRequest->getClassCode1());
    AddRequest *AddReq = new AddRequest(switchRequest->getStudentID(), switchRequest->getUCCode2(),
                                        switchRequest->getClassCode2());
    processRemoveRequest(RemReq);
    processAddRequest(AddReq);
    delete RemReq;
    delete AddReq;
}

void ControlUnit::processAllRequests() {
    if (RequestsToProcess.empty()) {
        cout << "No requests pending\n";
    }
    // Iterate over every request in order
    while (!RequestsToProcess.empty()) {
        Request *request = RequestsToProcess.front();
        RequestsToProcess.pop();
        if (!processRequest(request)) {
            // If it isn't valid then ask to ignore only that request or ignore every request
            cout
                    << "Invalid request, do you still want to continue processing the remaining requests?\n1) Yes\n2) No\n";
            int answer;
            cin >> answer;
            if (answer == 2) {
                while (!RequestsToProcess.empty()) {

                    delete RequestsToProcess.front();
                    RequestsToProcess.pop();
                }
            }
        }
    }
}

void ControlUnit::removeLastPendingRequest() {
    // Create a new queue and move every element from the original queue to the new one except for the last one.
    queue<Request *> temporaryQueue;
    Request *request;
    while (!RequestsToProcess.empty()) {
        request = RequestsToProcess.front();
        RequestsToProcess.pop();
        if (!RequestsToProcess.empty()) {
            temporaryQueue.push(request);
        }
    }
    delete request;
    RequestsToProcess = temporaryQueue;
}

// Iterate over every applied request and undo it
void ControlUnit::undoRequest(int n) {
    for (int i = 0; i < n; i++) {
        if (ProcessedRequests.empty()) {
            cout << "No more requests to undo.\n";
            break;
        }
        Request *request = ProcessedRequests.top();
        ProcessedRequests.pop();
        if (request->getType() == "add") {
            auto *request2 = dynamic_cast<AddRequest *>(request);
            Request *request3 = new RemoveRequest(request2->getStudentID(), request2->getUCCode(),
                                                  request2->getClassCode());
            processRequest(request3, true);
            delete request3;
        } else if (request->getType() == "remove") {
            auto *request2 = dynamic_cast<RemoveRequest *>(request);
            Request *request3 = new AddRequest(request2->getStudentID(), request2->getUCCode(),
                                               request2->getClassCode());
            processRequest(request3, true);
            delete request3;
        } else if (request->getType() == "switch") {
            auto *request2 = dynamic_cast<SwitchRequest *>(request);
            Request *request3 = new SwitchRequest(request2->getStudentID(), request2->getUCCode2(),
                                                  request2->getUCCode1(), request2->getClassCode2(),
                                                  request2->getClassCode1());
            processRequest(request3, true);
            delete request3;
        } else {
            cout << "Unable to undo request\n";
        }
        delete request;
    }
}void ControlUnit::WritetoInvalidRequests() {
    try {
        fstream out("../data/InvalidRequests.csv", ios::out | ios::trunc);
        if (!out.is_open()) {
            cout << "Error opening the file." << endl;
            return;  // Exit the function if the file couldn't be opened.
        }

        out << "RequestID,Type,StudentID,UcCode1,ClassCode1,UcCode2,ClassCode2\r\n";

        while (!InvalidRequests.empty()) {
            Request *request = InvalidRequests.top();
            InvalidRequests.pop();

            if (request->getType() == "add") {
                AddRequest *request2 = dynamic_cast<AddRequest*>(request);
                if (request2) {
                    out << request2->getId() << "," << request2->getType() << "," << request2->getStudentID() << ","
                        << request2->getUCCode() << "," << request2->getClassCode() << ",,\r\n";
                    delete request2;
                }
            } else if (request->getType() == "remove") {
                RemoveRequest *request2 = dynamic_cast<RemoveRequest*>(request);
                if (request2) {
                    out << request2->getId() << "," << request2->getType() << "," << request2->getStudentID() << ","
                        << request2->getUCCode() << "," << request2->getClassCode() << ",,\r\n";
                    delete request2;
                }
            } else if (request->getType() == "switch") {
                SwitchRequest *request2 = dynamic_cast<SwitchRequest*>(request);
                if (request2) {
                    out << request2->getId() << "," << request2->getType() << "," << request2->getStudentID() << ","
                        << request2->getUCCode1() << "," << request2->getClassCode1() << ","
                        << request2->getUCCode2() << "," << request2->getClassCode2() << "\r\n";
                    delete request2;
                }
            } else {
                cout << "Unable to load to file\n";
            }
        }

        out.close(); // Close the file when you're done writing.
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void ControlUnit::saveChanges() {
    fstream out("../data/students_classes_updated.csv", ios::out | ios::trunc);
    out << "StudentCode,StudentName,UcCode,ClassCode\r\n";
    // Iterate over every student and write the respective classes to the file.
    for (Student s: StudentSet)
        for (const auto &studentGroup: s.getStudentGroups())
            out << s.getStudentID() << ',' << s.getName() << ',' << studentGroup.getUcCode() << ','
                << studentGroup.getClassCode() << "\r\n";
    out.close();
}

void ControlUnit::clearMemory() {
    for (auto i: KeyToStudentGroup) {
        delete i.second;
    }
    for (auto i: LessonMap) {
        for (auto j: i.second) {
            delete j;
        }
    }
    while (!RequestsToProcess.empty()) {
        delete RequestsToProcess.front();
        RequestsToProcess.pop();
    }
    while (!ProcessedRequests.empty()) {
        delete ProcessedRequests.top();
        ProcessedRequests.pop();
    }
}
