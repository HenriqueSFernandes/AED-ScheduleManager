
#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include "RemoveRequest.h"
#include <filesystem>

using namespace std;

void ControlUnit::Start(string filename) {
    this->filename = filename;
    ControlUnit::LoadClassesCSV();
    cout << "Loaded CLASSES" << endl;
    ControlUnit::LoadClassesPerUcCSV();
    cout << "Loaded AULAS" << endl;

    ControlUnit::LoadStudentsClassesCSV();
    cout << "Loaded ALUNOS" << endl;
}

void ControlUnit::LoadClassesPerUcCSV() {
    //ppppppppppppppp
    string line;
    string ucCode, classCode;
    ifstream inFile("../data/classes_per_uc.csv");

    if (!inFile) {
        cerr << "Failed to open file" << endl;
        return;
    }

    getline(inFile, line); // Read and discard the header line

    while (getline(inFile, line)) {
        stringstream is(line);
        getline(is, ucCode, ',');
        getline(is, classCode, '\r');

        studentGroup *group = new studentGroup(ucCode, classCode);
        //cout << *group << endl;
        StudentGroupList.push_back(*group);

        MainKey groupKey = {ucCode, classCode};
        KeyToStudentGroup[groupKey] = group;
    }

    inFile.close();
}

void ControlUnit::LoadClassesCSV() {
    //ppppppppppppppppppppppp
    string line;
    string ClassCode, UcCode, Weekday, StartHour, Duration, Type;
    ifstream inFile("../data/classes.csv");

    if (!inFile) {
        cerr << "Failed to open file" << endl;
        return;
    }

    getline(inFile, line); // Read and discard the header line

    while (getline(inFile, line)) {
        stringstream is(line);
        getline(is, ClassCode, ',');
        getline(is, UcCode, ',');
        getline(is, Weekday, ',');
        getline(is, StartHour, ',');
        getline(is, Duration, ',');
        getline(is, Type, '\r');


        lesson *Lesson = new lesson(UcCode, ClassCode, Weekday, stod(StartHour), stod(Duration), Type);
        //cout << *Lesson << endl;
        LessonVector.push_back(*Lesson);

        MainKey groupKey = {UcCode, ClassCode};
        if (LessonMap.find(groupKey) == LessonMap.end()) {
            std::set<lesson *> newSet;
            newSet.insert(Lesson);
            LessonMap[groupKey] = newSet;

        } else {
            LessonMap[groupKey].insert(Lesson);

        }
    }

    inFile.close();
}

// ppppppppp
void ControlUnit::LoadStudentsClassesCSV() {
    string line;
    string stCode, stName, ucCode, classCode;
    ifstream inFile;
        inFile.open(filename);
    getline(inFile, line);
    //Reading the first line with actual data
    getline(inFile, line);
    stringstream is(line);
    getline(is, stCode, ',');
    getline(is, stName, ',');
    getline(is, ucCode, ',');
    getline(is, classCode, '\r');
    string prevStCode = stCode;
    set<studentGroup> cpu;
    cpu.insert(studentGroup(ucCode, classCode));

    Student st_class(prevStCode, stName, cpu);
    MainKey key = {ucCode, classCode};
    if (SizeMap.find(key) == SizeMap.end()) {
        SizeMap[key] = 1;
    } else {
        SizeMap[key]++;
    }


    while (getline(inFile, line)) {
        stringstream is(line);
        getline(is, stCode, ',');
        if (prevStCode != stCode) {
            st_class = Student(prevStCode, stName, cpu);
            StudentVector.push_back(st_class);
            cpu.clear();
            prevStCode = stCode;
        }
        getline(is, stName, ',');
        getline(is, ucCode, ',');
        getline(is, classCode, '\r');
        cpu.insert(studentGroup(ucCode, classCode));
        key = {ucCode, classCode};
        if (SizeMap.find(key) == SizeMap.end()) {
            SizeMap[key] = 1;
        } else {
            SizeMap[key]++;
        }


    }
    cpu.insert(studentGroup(ucCode, classCode));
    key = {ucCode, classCode};
    if (SizeMap.find(key) == SizeMap.end()) {
        SizeMap[key] = 1;
    } else {
        SizeMap[key]++;
    }

    st_class = Student(prevStCode, stName, cpu);
    StudentVector.push_back(st_class);
    inFile.close();


}


//Deve dar confia
void ControlUnit::DisplayStudentSchedule() {
    cout << "Would you like the default Version or the Visual Version" << endl;
    cout << "1) Default" << endl;
    cout << "2) Visual" << endl;
    int option;
    cin >> option;
    std::cout << "Enter the UPCODE OF THE STUDENT" << endl;
    string upcode;

    bool valid = false;
    while (not valid) {
        //ya esta parte do bool um quites ppp especialmente  parte sinalizada
        cin >> upcode;
        valid = upcode.size() == 9;

        if (not valid) {
            cout << "Invalid number number try again a valid code is for instance 202028717" << endl;
        } else {
            break;
        }
        //PPPPPP

        cin.ignore(INT_MAX, '\n');
        cin.clear();
        //PPPPPP
    }
    bool found = false;

    vector<lesson> myVec;
    for (auto student: StudentVector) {
        if (student.getStudentID() == upcode) {
            set<studentGroup> studentgroups = student.getStudentGroups();
            for (auto el: studentgroups) {

            }
            for (auto studentgroup: studentgroups) {
                MainKey key = {studentgroup.getUcCode(), studentgroup.getClassCode()};

                set<lesson *> Lectures = LessonMap[key];
                for (auto element: Lectures) {
                    if (option == 1) {
                        int width = 85; // Calculate the width based on the content length
                        std::string horizontalLine(width, '-');

                        std::cout << '+' << horizontalLine << '+' << std::endl;

// Adjust the width for proper alignment
                        std::cout << "    " << *element << std::endl;

                        std::cout << '+' << horizontalLine << '+' << std::endl << endl;


                    }
                    found = true;

                    myVec.push_back(*element);
                }

            }

        }
    }
    if (option == 2 and found) {
        cout << " is there conflict" << IsThereConflict(myVec) << endl;
        Schedule StudentSchedule = Schedule(myVec);
        StudentSchedule.display();
    }


}
//ze
//as drenas de visual tirei a olho mais ou menos depois se der tempo faço certo
//Imaginem isto é CLASS POR UC N É LEGIT FULL CLASS
/*void ControlUnit::DisplayClassSchedule(string classCode, string UcCode){
    cout<<"Would you like the default Version or the Visual Version"<<endl;
    cout<<"1) Default"<<endl;
    cout<<"2) Visual"<<endl;
    int option;
    cin>>option;
    vector<lesson> LessonsVector;
    MainKey key={UcCode, classCode};
    set<lesson*> LessonsSet=LessonMap[key];
    for( auto lesson : LessonsSet){
        LessonsVector.push_back(*lesson);
        if(option==1){
            int width = 80; // Calculate the width based on the content length
            std::string horizontalLine(width, '-');

            std::cout << '+' << horizontalLine << '+' << std::endl;
            std::cout << "| " <<*lesson<<" |"<< std::endl;
            std::cout << '+' << horizontalLine << '+' << std::endl;

        }
    }
    if(option ==2){
        Schedule ClassSchedule= Schedule(LessonsVector);
        ClassSchedule.display();
    }



}*/
//LEGIT FULL CLASS
//TESTEI E MSM RESULTADO QUE A MAH
void ControlUnit::DisplayClassSchedule() {
    cout << "Would you like the default Version or the Visual Version" << endl;
    cout << "1) Default" << endl;
    cout << "2) Visual" << endl;
    int option;
    cin >> option;
    std::cout << "Enter the Class Code" << endl;
    string classCode;

    bool valid = false;
    while (not valid) {
        cin >> classCode;
        valid = classCode.length() == 7 && isdigit(classCode[0]) && classCode.substr(1, 4) == "LEIC" &&
                isdigit(classCode[5]) && isdigit(classCode[6]);
        //estava a dar problema de n limpar o cin resolvi com PPPPPPP da Mah atenção
        if (not valid) {
            std::cout
                    << "Invalid input. Try Again class is of the form {NUMBER]{LEIC}{NUMBER}{NUMBER} for instance 3LEIC05"
                    << std::endl;
        } else { break; }


        cin.ignore(INT_MAX, '\n');
        cin.clear();

    }
    vector<lesson> LessonsVector;
    set<lesson *> LessonsSet;
    for (auto studentGroup: StudentGroupList) {
        if (studentGroup.getClassCode() == classCode) {


            MainKey key = {studentGroup.getUcCode(), classCode};

            LessonsSet.insert(LessonMap[key].begin(), LessonMap[key].end());

        }
    }


    for (auto lesson: LessonsSet) {

        LessonsVector.push_back(*lesson);
        if (option == 1) {
            int width = 80; // Calculate the width based on the content length
            std::string horizontalLine(width, '-');

            std::cout << '+' << horizontalLine << '+' << std::endl;
            std::cout << "| " << *lesson << " |" << std::endl;
            std::cout << '+' << horizontalLine << '+' << std::endl;

        }
    }
    if (option == 2) {
        Schedule ClassSchedule = Schedule(LessonsVector);
        ClassSchedule.display();
    }


}

// Escolher se deixo ali o cout ou n
int ControlUnit::StudentsInAtLeastNUcs(int n) {

    int NumberOfStudents = 0;

    for (auto student: this->StudentVector) {
        set<studentGroup> studentgroups = student.getStudentGroups();


        if (studentgroups.size() >= n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;


}

int ControlUnit::StudentsInAtMostNUcs(int n) {

    int NumberOfStudents = 0;

    for (auto student: this->StudentVector) {
        set<studentGroup> studentgroups = student.getStudentGroups();


        if (studentgroups.size() <= n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;


}

int ControlUnit::StudentsInUcs(int n) {

    int NumberOfStudents = 0;

    for (auto student: this->StudentVector) {
        set<studentGroup> studentgroups = student.getStudentGroups();


        if (studentgroups.size() == n) {
            cout << student << endl;
            NumberOfStudents++;
        }
    }
    return NumberOfStudents;


}


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
    for (auto student: StudentVector) {
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

void ControlUnit::courseStudents(string courseCode, function<bool(Student, Student)> func) {
    set<studentGroup> groups;
    set<Student, decltype(func)> students(func);
    bool notexist = true;
    while (notexist) {
        for (auto student: StudentVector) {
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

void ControlUnit::yearStudents(char year, function<bool(Student, Student)> func) {
    set<studentGroup> groups;
    set<Student, decltype(func)> students(func);
    bool notexist = true;
    while (notexist) {
        for (auto student: StudentVector) {
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


void ControlUnit::UCWithMostStudents() {
    set<studentGroup> groups;
    map<string, int> ucs;
    for (auto student: StudentVector) {
        groups = student.getStudentGroups();
        for (auto group: groups) {
            if (ucs.find(group.getUcCode()) == ucs.end()) {
                ucs[group.getUcCode()] = 1;
            } else {
                ucs[group.getUcCode()] += 1;
            }
        }
    }
    vector<pair<string, int>> ucsvec(ucs.begin(), ucs.end());
    sort(ucsvec.begin(), ucsvec.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });
    cout << "These are the Ucs in descending order of registered students." << endl;
    for (auto uc: ucsvec) {
        cout << uc.first << " with " << uc.second << " students." << endl << endl;
    }
}

//helper functions
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

//helper functions
bool ControlUnit::IsThereConflict(vector<lesson> lessons) {

    for (int i = 0; i < lessons.size() - 1; i++) {
        for (int j = i + 1; j < lessons.size(); j++) {
            bool overLap = ((lessons[i].getStartTime() <= lessons[j].getStartTime() and
                             lessons[j].getEndTime() <= lessons[i].getEndTime()) or
                            (lessons[j].getStartTime() <= lessons[i].getStartTime() and
                             lessons[i].getEndTime() <= lessons[j].getEndTime()));

            bool bothPratical = (lessons[i].getType() == "TP" or lessons[i].getType() == "PL") and
                                (lessons[j].getType() == "TP" or lessons[j].getType() == "PL");
            bool sameDay = lessons[i].getWeekday() == lessons[j].getWeekday();
            if (overLap and bothPratical and sameDay) {
                cout << lessons[i] << "/" << lessons[j] << endl;
                return true;
            }
        }


    }
    return false;


}
//
//FUNCOES PARA REQUEST

void ControlUnit::createAdd() {
    string id;
    string uc;
    string studentgroup;
    cout << "What's the ID of the student that you want to add to an UC:" << endl;
    cin >> id;
    cout << "What UC do you want to add the student to:" << endl;
    cin >> uc;
    cout << "What Class of the UC you want to add the student into:" << endl;
    cin >> studentgroup;
    RequestsToProcess.push_back(new AddRequest(id, uc, studentgroup));
}

void ControlUnit::createRemove() {
    cout << "What's the ID of the student that you want to remove from an UC:" << endl;
    string id;
    string uc;
    string studentgroup;
    cin >> id;
    cout << "What UC you want to remove the student from:" << endl;
    cin >> uc;
    cout << "What Class is he in in the specified Uc:" << endl;
    cin >> studentgroup;
    RequestsToProcess.push_back(new RemoveRequest(id, uc, studentgroup));
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
    while (true) {
        cout << "Do you want to switch UCs or switch Classes from an UC?" << endl;
        cout << "1) Switch UCs" << endl;
        cout << "2) Switch Classes" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "What UC do you want to leave?" << endl;
                cin >> uc1;
                studentgroup1 = getClassinUc(id, uc1);
                while (studentgroup1 == "false") {
                    cout << "Student not in given UC please give another one." << endl;
                    cin >> uc1;
                    studentgroup1 = getClassinUc(id, uc1);
                }
                cout << "What UC do you want to join?" << endl;
                cin >> uc2;
                break;
            case 2:
                cout << "What UC do you want to swap classes?" << endl;
                cin >> uc1;
                studentgroup1 = getClassinUc(id, uc1);
                while (studentgroup1 == "false") {
                    cout << "Student not in given UC please give another one." << endl;
                    cin >> uc1;
                    studentgroup1 = getClassinUc(id, uc1);
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
    RequestsToProcess.push_back(new SwitchRequest(id, uc1, uc2, studentgroup1, studentgroup2));
}

string ControlUnit::getClassinUc(string upcode, string uccode) {
    for (auto student: StudentVector) {
        if (student.getStudentID() == upcode) {
            for (auto sg: student.getStudentGroups()) {
                if (sg.getUcCode() == uccode) {
                    return sg.getClassCode();

                }
            }
            return "false";
        }
    }
    return "nostudent";

}

bool ControlUnit::CheckAdd(AddRequest *addrq) {
    bool result = true;
    string upcode = addrq->getUpCodeStudent();
    bool notmorethan7 = true;
    bool studentExists = false;
    bool NotInMoreTHanONeClass = true;
    MainKey key = {addrq->getUCCode(), addrq->getClassCode()};
    bool existsclass = KeyToStudentGroup.find(key) != KeyToStudentGroup.end();
    map<string, int> HaveISeenThisUc;
    vector<lesson> lessonVec;

    for (auto student: StudentVector) {
        if (student.getStudentID() == upcode) {
            studentExists = true;
            NotInMoreTHanONeClass = !student.isinuc(addrq->getUCCode());

            for (auto studentGroup: student.getStudentGroups()) {


                MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};
                set<lesson *> lessonSet = LessonMap[key];
                for (auto lesson: lessonSet) {
                    lessonVec.push_back(*lesson);
                }
            }
            if (student.getStudentGroups().size() >= 7) {
                notmorethan7 = false;
            }
            break;
        }


    }
    vector<studentGroup> mysgs;

    map<MainKey, int> dummyMap = SizeMap;
    for (auto sg: StudentGroupList) {
        if (sg.getUcCode() == addrq->getUCCode()) {
            mysgs.push_back(sg);

            if (sg.getClassCode() == addrq->getClassCode()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]++;
            }
        }
    }
    result = notmorethan7 and studentExists and NotInMoreTHanONeClass;
    key = {addrq->getUCCode(), addrq->getClassCode()};
    int oldBalance = NumBalanced(mysgs, SizeMap);
    set<lesson *> lessonSet = LessonMap[key];
    int newbalance = NumBalanced(mysgs, dummyMap);
    for (auto lesson: lessonSet) {
        lessonVec.push_back(*lesson);
    }
    int classSize = SizeMap[key];
    bool respectsCap = true;
    if (classSize >= cap) {
        respectsCap = false;
    }

    bool validBalance;
    if (newbalance <= 4 or newbalance <= oldBalance) {
        //Se balanço menor ou igual a 4 ou não piorar
        validBalance = true;
    } else {
        validBalance = false;
    }
    result = result and respectsCap and existsclass and not IsThereConflict(lessonVec) and validBalance;
    return result;
}


bool ControlUnit::CheckRemove(RemoveRequest *remrq) {
    //Falta o isbalnced
    bool result = true;

    string upcode = remrq->getUpCodeStudent();
    bool notlessthan0 = true;
    bool studentExists = false;
    bool isinclass = true;
    for (auto student: StudentVector) {
        if (student.getStudentID() == upcode) {
            studentExists = true;
            if (student.getStudentGroups().size() <= 1) {
                notlessthan0 = false;
            }
            isinclass = student.isinclass(remrq->getUCCode(), remrq->getClassCode());
            break;
        }
    }
    vector<studentGroup> mysgs;
    map<MainKey, int> dummyMap = SizeMap;
    for (auto sg: StudentGroupList) {
        if (sg.getUcCode() == remrq->getUCCode()) {
            mysgs.push_back(sg);

            if (sg.getClassCode() == remrq->getClassCode()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]--;
            }
        }
    }
    MainKey key = {remrq->getUCCode(), remrq->getClassCode()};
    int oldBalance = NumBalanced(mysgs, SizeMap);
    int newbalance = NumBalanced(mysgs, dummyMap);
    bool validBalance;
    if (newbalance <= 4 or newbalance <= oldBalance) {
        //Se balanço menor ou igual a 4 ou não piorar
        validBalance = true;
    } else {
        validBalance = false;
    }
    result = (notlessthan0 and studentExists and isinclass and validBalance);
    return result;
}


bool ControlUnit::CheckSwitch(SwitchRequest *swrq) {
    bool result;
    string upcode = swrq->getUpCodeStudent();
    bool studentExists = false;
    bool isinclass = true;
    bool respectscap = true;
    bool NotInMoreThan1Group = true;
    MainKey key = {swrq->getUCCode2(), swrq->getClassCode2()};
    bool existsclass = KeyToStudentGroup.find(key) != KeyToStudentGroup.end();
    vector<lesson> mylessons;
    for (auto student: StudentVector) {
        if (student.getStudentID() == upcode) {
            studentExists = true;
            isinclass = student.isinclass(swrq->getUCCode1(), swrq->getClassCode1());
            if (swrq->getUCCode1() != swrq->getUCCode2()) {
                NotInMoreThan1Group = !student.isinuc(swrq->getUCCode2());
            }
            for (auto sg: student.getStudentGroups()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                if (sg.getUcCode() + sg.getClassCode() != swrq->getUCCode1() + swrq->getClassCode1()) {
                    set<lesson *> lessonSet = LessonMap[key];
                    for (auto les: lessonSet) {
                        mylessons.push_back(*les);
                    }
                }
            }
            MainKey key = {swrq->getUCCode2(), swrq->getClassCode2()};
            set<lesson *> lessonSet = LessonMap[key];
            for (auto les: lessonSet) {
                mylessons.push_back(*les);
            }

            break;
        }
    }
    bool conflict = IsThereConflict(mylessons);
    key = {swrq->getUCCode2(), swrq->getClassCode2()};
    int classSize = SizeMap[key];
    if (classSize >= cap) {
        respectscap = false;
    }

    bool validBalanceRem;
    bool validBalanceAdd;

    vector<studentGroup> mysgsUc1;
    vector<studentGroup> mysgsUc2;
    map<MainKey, int> dummyMap = SizeMap;
    for (auto sg: StudentGroupList) {
        if (sg.getUcCode() == swrq->getUCCode1()) {
            mysgsUc1.push_back(sg);

            if (sg.getClassCode() == swrq->getClassCode1()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]--;
            }
        }
        if (sg.getUcCode() == swrq->getUCCode2()) {
            mysgsUc2.push_back(sg);

            if (sg.getClassCode() == swrq->getClassCode2()) {
                MainKey key = {sg.getUcCode(), sg.getClassCode()};
                dummyMap[key]++;
            }
        }
    }

    int oldBalance1 = NumBalanced(mysgsUc1, SizeMap);
    int newbalance1 = NumBalanced(mysgsUc1, dummyMap);

    if (newbalance1 <= 4 or newbalance1 <= oldBalance1) {
        //Se balanço menor ou igual a 4 ou não piorar
        validBalanceRem = true;
    } else {
        validBalanceRem = false;
    }
    int oldBalance2 = NumBalanced(mysgsUc2, SizeMap);
    int newbalance2 = NumBalanced(mysgsUc2, dummyMap);
    if (newbalance2 <= 4 or newbalance2 <= oldBalance2) {
        //Se balanço menor ou igual a 4 ou não piorar
        validBalanceAdd = true;
    } else {
        validBalanceAdd = false;
    }

    result = (existsclass and studentExists and isinclass and respectscap and NotInMoreThan1Group and !conflict and
              validBalanceAdd and validBalanceRem);
    return result;

}


bool ControlUnit::processRequest(Request *request) {
    bool isvalid;
    if (request->getType() == "add") {
        //chamar checker de uc mais de 7
        //ver se turma nao ultrapassa cap
        // ver se nao ha conflito de horario
        // ver se nao esta em mais do que uma turma na uc
        //ver balanço
        cout << "Detetado como add request" << endl;
        isvalid = CheckAdd(dynamic_cast<AddRequest *>(request));
        if (isvalid) {
            ProcessedRequests.push(request);
            processAddRequest(dynamic_cast<AddRequest *>(request));
            return true;
        } else {
            return false;

        }

    } else if (request->getType() == "remove") {
        //ver se ele esta na cadeira e na turma
        //ver balanço
        cout << "Detetado como remove request" << endl;
        isvalid = CheckRemove(dynamic_cast<RemoveRequest *>(request));
        if (isvalid) {
            processRemoveRequest(dynamic_cast<RemoveRequest *>(request));
            return true;
        } else {
            return false;
        }

    } else if (request->getType() == "switch") {
        //ver se existe vaga na que tu vais
        //ver a cap
        // ver se nao ha confito
        // ver balanço
        cout << "Detetado como switch request" << endl;
        isvalid = CheckSwitch(dynamic_cast<SwitchRequest *>(request));
        if (isvalid) {
            processSwitchRequest(dynamic_cast<SwitchRequest *>(request));
            return true;
        } else {
            cout << "Error in switch request" << endl;
            return false;
        }
    }//then have
    return false;
}

void ControlUnit::processAddRequest(AddRequest *addRequest) {
    string upCode = addRequest->getUpCodeStudent();
    string classCode = addRequest->getClassCode();
    string ucCode = addRequest->getUCCode();
    cout << "hey i got the request" << upCode << "/" << classCode << "/" << ucCode;


    for (auto &student: StudentVector) {
        if (student.getStudentID() == upCode) {
            student.addStudentGroup(studentGroup(ucCode, classCode));
            MainKey key = {ucCode, classCode};

            if (SizeMap.find(key) == SizeMap.end()) {
                SizeMap[key] = 1;
            } else {
                SizeMap[key]++;
            }
        }
    }


}

void ControlUnit::processRemoveRequest(RemoveRequest *removeRequest) {
    string upCode = removeRequest->getUpCodeStudent();
    string classCode = removeRequest->getClassCode();
    string ucCode = removeRequest->getUCCode();
    cout << "hey i got the request" << upCode << "/" << classCode << "/" << ucCode;

    for (auto &student: StudentVector) {
        if (student.getStudentID() == upCode) {
            student.removeGroup(studentGroup(ucCode, classCode));
            MainKey key = {ucCode, classCode};
            SizeMap[key]--;


        }
    }

}

void ControlUnit::processSwitchRequest(SwitchRequest *switchRequest) {
    RemoveRequest *RemReq = new RemoveRequest(switchRequest->getUpCodeStudent(), switchRequest->getUCCode1(),
                                              switchRequest->getClassCode1());
    AddRequest *AddReq = new AddRequest(switchRequest->getUpCodeStudent(), switchRequest->getUCCode2(),
                                        switchRequest->getClassCode2());
    processRemoveRequest(RemReq);
    processAddRequest(AddReq);
}

//TESTAR
void ControlUnit::CheckIfThereAreConflicts() {


    for (auto &studentGroup: StudentGroupList) { // Use a reference to avoid unnecessary copies
        MainKey key = {studentGroup.getUcCode(), studentGroup.getClassCode()};
        cout << "student group" << studentGroup << "SIZE" << SizeMap[key] << endl;
    }
}


void ControlUnit::processAllRequests() {
    if (RequestsToProcess.empty()) {
        cout << "No requests pending\n";
    }
    // Iterate over every request in order
    while (!RequestsToProcess.empty()) {
        Request *request = RequestsToProcess.front();
        RequestsToProcess.pop_front();
        if (!processRequest(request)) {
            // If it isn't valid then ask to ignore only that request or ignore every request
            cout
                    << "Invalid request, do you still want to continue processing the remaining requests?\n1) Yes\n2) No\n";
            int answer;
            cin >> answer;
            if (answer == 2) {
                while (!RequestsToProcess.empty()) {
                    RequestsToProcess.pop_front();
                }
            }
        }
    }
}

void ControlUnit::removeLastPendingRequest() {
    RequestsToProcess.pop_back();
}

// Iterate over every applied request
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
            Request *request3 = new RemoveRequest(request2->getUpCodeStudent(), request2->getUCCode(),
                                                  request2->getClassCode());
            processRequest(request3);
        } else if (request->getType() == "remove") {
            auto *request2 = dynamic_cast<RemoveRequest *>(request);
            Request *request3 = new AddRequest(request2->getUpCodeStudent(), request2->getUCCode(),
                                               request2->getClassCode());
            processRequest(request3);
        } else if (request->getType() == "switch") {
            auto *request2 = dynamic_cast<SwitchRequest *>(request);
            Request *request3 = new SwitchRequest(request2->getUpCodeStudent(), request2->getUCCode2(),
                                                  request2->getUCCode1(), request2->getClassCode2(),
                                                  request2->getClassCode1());
        } else {
            cout << "Unable to undo request\n";
        }
    }
}

void ControlUnit::saveChanges() {
    fstream out("../data/students_classes_updated.csv", ios::out | ios::trunc);
    out << "StudentCode,StudentName,UcCode,ClassCode\r\n";
    for (Student s: StudentVector)
        for (const auto& studentGroup : s.getStudentGroups())
            out << s.getStudentID() << ',' << s.getName() << ',' << studentGroup.getUcCode() << ',' << studentGroup.getClassCode() << "\r\n";
    out.close();
}
