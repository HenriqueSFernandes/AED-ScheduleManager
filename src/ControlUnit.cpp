//
// Created by nowayjose on 20/10/2023.
//
#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
#include <memory>
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
///CODIGO FANADO
void ControlUnit::LoadStudentsClassesCSV() {
    string line;
    string stCode, stName, ucCode, classCode;
    ifstream inFile;
    inFile.open("../data/students_classes.csv");
    getline(inFile,line);
    //Reading the first line with actual data
    getline(inFile,line);
    stringstream is(line);
    getline(is,stCode,',');
    getline(is,stName,',');
    getline(is,ucCode,',');
    getline(is,classCode,'\r');
    string prevStCode=stCode;
    set<studentGroup> cpu;

    Student st_class(prevStCode,stName,cpu);

    StudentVector.push_back(st_class);
    while(getline(inFile,line)){
        stringstream is(line);
        getline(is,stCode,',');
        if(prevStCode != stCode){
            st_class= Student(prevStCode,stName,cpu);
            StudentVector.push_back(st_class);
            cpu.clear();
            prevStCode = stCode;
        }
        getline(is,stName,',');
        getline(is,ucCode,',');
        getline(is,classCode,'\r');
        cpu.insert(studentGroup(ucCode,classCode));

    }
    cpu.insert(studentGroup(ucCode,classCode));
    st_class= Student(prevStCode,stName,cpu);
    StudentVector.push_back(st_class);
    inFile.close();
    StudentVector.push_back(st_class);

}



void ControlUnit::DisplayStudentSchedule(string upcode){
    vector<lesson> myVec;
    for(auto student : StudentVector){
        if(student.getStudentID()==upcode){
            set<studentGroup > studentgroups =student.getStudentGroups();
            for( auto el : studentgroups){

            }
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

void ControlUnit::DisplayClassSchedule(string classCode, string UcCode){
    vector<lesson> LessonsVector;
    MainKey key={UcCode, classCode};
    set<lesson*> LessonsSet=LessonMap[key];
    for( auto lesson : LessonsSet){
        LessonsVector.push_back(*lesson);
    }
    Schedule ClassSchedule= Schedule(LessonsVector);
    ClassSchedule.display();


}
int ControlUnit::StudentsInAtLeastNUcs(int n){
   int NumberOfStudents=0;

   for( auto student : this->StudentVector ){
       set<studentGroup > studentgroups =student.getStudentGroups();
        std::cout<<"//"<<endl;
       for( auto element : studentgroups){
           cout<<element<<endl;
       }
       if(studentgroups.size()>=n){

           NumberOfStudents++;
       }
   }
   return NumberOfStudents;


}