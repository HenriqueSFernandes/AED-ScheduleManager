//
// Created by nowayjose on 20/10/2023.
//
#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
#include <memory>
#include <algorithm>

using namespace std;

void ControlUnit::Start() {
    ControlUnit::LoadClassesCSV();
    cout<<"Loaded CLASSES"<<endl;
    ControlUnit::LoadClassesPerUcCSV();
    cout<<"Loaded AULAS"<<endl;

    ControlUnit::LoadStudentsClassesCSV();
    cout<<"Loaded ALUNOS"<<endl;
}
void ControlUnit::LoadClassesCSV() {
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

        studentGroup* group = new studentGroup(ucCode, classCode);
        //cout << *group << endl;
        StudentGroupVector.push_back(*group);

        MainKey groupKey = {ucCode, classCode};
        KeyToStudentGroup[groupKey] = group;
    }

    inFile.close();
}
void ControlUnit::LoadClassesPerUcCSV() {
    //ppppppppppppppppppppppp
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
        //cout << *Lesson << endl;
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
    cout<<"Would you like the default Version or the Visual Version"<<endl;
    cout<<"1) Default"<<endl;
    cout<<"2) Visual"<<endl;
    int option;
    cin>>option;
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
                    if(option==1){
                        int width = 80; // Calculate the width based on the content length
                        std::string horizontalLine(width, '-');

                        std::cout << '+' << horizontalLine << '+' << std::endl;
                        std::cout << "| " <<*element<<" |"<< std::endl;
                        std::cout << '+' << horizontalLine << '+' << std::endl;


                    }

                    myVec.push_back(*element);
                }

            }

        }
    }
    if(option==2){
        Schedule StudentSchedule= Schedule(myVec);
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
void ControlUnit::DisplayClassSchedule(string classCode){
    cout<<"Would you like the default Version or the Visual Version"<<endl;
    cout<<"1) Default"<<endl;
    cout<<"2) Visual"<<endl;
    int option;
    cin>>option;
    vector<lesson> LessonsVector;
    set<lesson*> LessonsSet;
    for( auto studentGroup : StudentGroupVector){
        if(studentGroup.getClassCode()==classCode){


            MainKey key={studentGroup.getUcCode(), classCode};

            LessonsSet.insert(LessonMap[key].begin(),LessonMap[key].end());

        }
    }



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

//Alterações do Leandro


void ControlUnit::classStudents(string classCode){
    set<studentGroup> groups;
    set<Student> students;
    string ucCode;
    bool classnotexist = true;
    while(classnotexist){
        for(auto group:StudentGroupVector){
            if(classCode == group.getClassCode()){
                classnotexist=false;
                break;
            }
        }
        if(classnotexist){
            cout<<"Given class doesn't exist, please provide a new class code:"<<endl;
            cin>>classCode;
        }
    }
    cout<<"Which course from class " << classCode << " you would like to see students from?:" << endl;
    cin>>ucCode;
    bool ucnotexist = true;

    while(ucnotexist){
        for(auto group: StudentGroupVector){
            if(classCode == group.getClassCode() && ucCode == group.getUcCode()){
                ucnotexist = false;
                break;
            }
        }
        if(ucnotexist){
            cout<<"This course doesn't exist in this class, please provide a new Course:"<<endl;
            cin>>ucCode;
        }
    }
    for (auto student: StudentVector) {
        groups = student.getStudentGroups();
        for (auto group: groups) {
            if (group.getClassCode() == classCode && group.getUcCode() == ucCode){
                students.insert(student);
                break;
            }
        }
    }

    cout<< "Students in " << classCode <<" from " << ucCode << " :"<<endl<<endl;
    for(auto student: students){
        cout<<student<<endl;
    }
    cout<<endl<<"There are "<<students.size()<< " students in the class " << classCode << " from course " << ucCode<<"." << endl;

}

void ControlUnit::courseStudents(string courseCode){
    set<studentGroup> groups;
    set<Student> students;
    bool notexist = true;
    while(notexist) {
        for (auto student: StudentVector) {
            groups = student.getStudentGroups();
            for (auto group: groups) {
                if (group.getUcCode() == courseCode) {
                    students.insert(student);
                    break;
                }
            }
        }
        if(students.size()== 0){
            notexist=true;
            cout<<"Given UC code doesn't exist, please provide a new one:"<<endl;
            cin>>courseCode;
        }
        else{
            notexist=false;
        }
    }
    cout<< "Students in " << courseCode <<":"<<endl<<endl;
    for(auto student: students){
        cout<<student<<endl;
    }
    cout<<endl<<"There are "<<students.size()<< " students in the course " << courseCode<<"." << endl;

}

void ControlUnit::yearStudents(char year){
    set<studentGroup> groups;
    set<Student> students;
    bool notexist = true;
    while(notexist) {
        for (auto student: StudentVector) {
            groups = student.getStudentGroups();
            for (auto group: groups) {
                if (group.getClassCode()[0] == year) {
                    students.insert(student);
                    break;
                }
            }
        }
        if(students.size()== 0){
            notexist=true;
            cout<<"Given year doesn't exist, please provide a new one:"<<endl;
            cin>>year;
        }
        else{
            notexist=false;
        }
    }
    cout<< "Students in year " << year <<":"<<endl<<endl;
    for(auto student: students){
        cout<<student<<endl;
    }
    cout<<endl<<"There are "<<students.size()<< " students in the year " << year << "." <<endl;
}



void ControlUnit::UCWithMostStudents(){
    set<studentGroup> groups;
    map<string,int> ucs;
    for(auto student:StudentVector){
        groups = student.getStudentGroups();
        for(auto group:groups){
            if (ucs.find(group.getUcCode())==ucs.end()) {
                ucs[group.getUcCode()] = 1;
            } else {
                ucs[group.getUcCode()] += 1;
            }
        }
    }
    vector<pair<string,int>> ucsvec(ucs.begin(),ucs.end());
    sort(ucsvec.begin(),ucsvec.end(),[](const pair<string,int> &a, const pair<string, int> &b){
        return a.second > b.second;
    });
    cout<<"These are the Ucs in descending order of registered students.";
    for(auto uc:ucsvec){
        cout<<uc.first<<" with " << uc.second << " students."<<endl<<endl;
    }
}