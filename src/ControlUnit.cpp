//
// Created by nowayjose on 20/10/2023.
//
#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
using namespace std;

void ControlUnit::Start() {
    ControlUnit::LoadClassesCSV();
    cout<<"Loaded CLASSES"<<endl;
    ControlUnit::LoadClassesPerUcCSV();
    cout<<"Loaded AULAS"<<endl;

    ControlUnit::LoadStudentsClassesCSV();
    cout<<"Loaded AULUNOS"<<endl;
}
void ControlUnit::LoadClassesCSV() {
    //MUDAR CODIGO FANADO
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

        studentGroup* group = new studentGroup(ucCode, classCode);
        cout << *group << endl;
        StudentGroupVector.push_back(*group);

        MainKey groupKey = {ucCode, classCode};
        KeyToStudentGroup[groupKey] = group;
    }

    inFile.close();
}
void ControlUnit::LoadClassesPerUcCSV() {
    //MUDAR CODIGO FANADO
    string line;
    string ClassCode,UcCode,Weekday,StartHour,Duration,Type;
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


        lesson * Lesson = new lesson(UcCode,ClassCode,Weekday,stod(StartHour) ,stod(Duration),Type);
        cout << *Lesson << endl;
        LessonVector.push_back(*Lesson);

        MainKey groupKey = {UcCode, ClassCode};
        if( LessonMap.find(groupKey)==LessonMap.end()){
            std::set<lesson*> newSet;
            newSet.insert(Lesson);
            LessonMap[groupKey] = newSet;

        }else{
            LessonMap[groupKey].insert(Lesson);

        }
    }

    inFile.close();
}
void ControlUnit::LoadStudentsClassesCSV()  {
    //MUDAR CODIGO FANADO
    string line;
    string StudentCode,StudentName,UcCode,ClassCode;
    ifstream inFile("../data/students_classes.csv");

    if (!inFile) {
        cerr << "Failed to open file" << endl;
        return;
    }

    getline(inFile, line); // Read and discard the header line

    while (getline(inFile, line)) {
        stringstream is(line);
        getline(is, StudentCode, ',');
        getline(is, StudentName, ',');
        getline(is, UcCode, ',');
        getline(is, ClassCode, '\r');



        Student * Student_ = new Student(StudentCode,StudentName);
        MainKey key={UcCode,ClassCode};
        studentGroup * CorrespondingClass=KeyToStudentGroup[key];
        Student_->addStudentGroup(*CorrespondingClass);
        cout<<*Student_<<endl;
        StudentVector.push_back(*Student_);

        MainKey groupKey = {UcCode, ClassCode};
        if( StudentMap.find(groupKey)!=StudentMap.end()){
            std::set<Student*> newSet;
            newSet.insert(Student_);
            StudentMap[groupKey] = newSet;

        }else{
            StudentMap[groupKey].insert(Student_);

        }
    }

    inFile.close();
}
void ControlUnit::DisplayStudentSchedule(string upcode){
    vector<lesson> myVec;
    for(auto student : StudentVector){
        if(student.getStudentID()==upcode){
            set<studentGroup> studentgroups =student.getStudentGroups();
            for(auto studentgroup : studentgroups){
                MainKey key={studentgroup.getUcCode(),studentgroup.getClassCode()};
                set<lesson*> Lectures= LessonMap[key];
                for(auto element : Lectures){
                    cout<<"aula"<<*element<<endl;
                    myVec.push_back(*element);
                }

            }

        }
    }
    Schedule StudentSchedule= Schedule(myVec);
    StudentSchedule.display();

}