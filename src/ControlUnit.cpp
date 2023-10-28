
#include "studentGroup.h"
#include <fstream>
#include "ControlUnit.h"
#include "student.h"
#include "Schedule.h"
#include <memory>
#include <algorithm>
#include <cstdlib>
#include "RemoveRequest.h"
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
    ifstream inFile("../data2/classes_per_uc.csv");

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
    ifstream inFile("../data2/classes.csv");

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
    inFile.open("../data2/students_classes.csv");
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
    cpu.insert(studentGroup(ucCode,classCode));
    Student st_class(prevStCode,stName,cpu);
    MainKey key={ucCode, classCode};





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


}


//Deve dar confia
void ControlUnit::DisplayStudentSchedule(){
    cout<<"Would you like the default Version or the Visual Version"<<endl;
    cout<<"1) Default"<<endl;
    cout<<"2) Visual"<<endl;
    int option;
    cin>>option;
    std::cout<<"Enter the UPCODE OF THE STUDENT"<<endl;
    string upcode;

    bool valid=false;
    while(not valid){
        //ya esta parte do bool um quites ppp especialmente  parte sinalizada
        cin>>upcode;
        valid=upcode.size() == 9;

        if(not valid){
            cout<<"Invalid number number try again a valid code is for instance 202028717"<<endl;
        }else{break;
        }
        //PPPPPP

        cin.ignore(INT_MAX, '\n');
        cin.clear();
        //PPPPPP
    }

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
        cout<<" is there conflict"<<IsThereConflict(myVec)<<endl;
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
void ControlUnit::DisplayClassSchedule(){
    cout<<"Would you like the default Version or the Visual Version"<<endl;
    cout<<"1) Default"<<endl;
    cout<<"2) Visual"<<endl;
    int option;
    cin>>option;
    std::cout<<"Enter the Class Code"<<endl;
    string classCode;

    bool valid=false;
    while ( not valid) {
        cin>>classCode;
        valid=classCode.length() == 7 && isdigit(classCode[0]) && classCode.substr(1, 4) == "LEIC" && isdigit(classCode[5]) && isdigit(classCode[6]);
        //estava a dar problema de n limpar o cin resolvi com PPPPPPP da Mah atenção
        if(not valid){
            std::cout << "Invalid input. Try Again class is of the form {NUMBER]{LEIC}{NUMBER}{NUMBER} for instance 3LEIC05" << std::endl;
        }else{break;}


        cin.ignore(INT_MAX, '\n');
        cin.clear();

    }
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
// Escolher se deixo ali o cout ou n
int ControlUnit::StudentsInAtLeastNUcs(int n){

   int NumberOfStudents=0;

   for( auto student : this->StudentVector ){
       set<studentGroup > studentgroups =student.getStudentGroups();


       if(studentgroups.size()>=n){
            cout<<"//"<<student<<"//"<<endl;
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
    cout<<"These are the Ucs in descending order of registered students."<<endl;
    for(auto uc:ucsvec){
        cout<<uc.first<<" with " << uc.second << " students."<<endl<<endl;
    }
}
//helper functions
/*bool ControlUnit::IsBalanced(vector<studentGroup>){

    int cap=30;
    int min =cap+1;
    int max=-1;
    for(auto studentGroup : this->StudentGroupVector ){

        MainKey key={studentGroup.getUcCode(),studentGroup.getClassCode()};
        if (StudentMap.find(key) != StudentMap.end()) {
            int size = StudentMap[key].size();
            if(size >max){max=size;}
            else if(size< min){min=size;}

        }

    }
    if(max-min<=4){
        return true;

    }
    return false;

}*/
//helper functions
bool ControlUnit::IsThereConflict(vector<lesson> lessons){

   for(int i=0;i<lessons.size()-1;i++){
       for(int j=i+1; j<lessons.size();j++){
           bool overLap=((lessons[i].getStartTime()<=lessons[j].getStartTime() and lessons[j].getEndTime()<=lessons[i].getEndTime()) or (lessons[j].getStartTime()<=lessons[i].getStartTime() and lessons[i].getEndTime()<=lessons[j].getEndTime()));

           bool bothPratical=( lessons[i].getType()=="TP" or lessons[i].getType()=="PL") and ( lessons[j].getType()=="TP" or lessons[j].getType()=="PL");
           bool sameDay = lessons[i].getWeekday()==lessons[j].getWeekday();
           if(overLap and bothPratical and sameDay ){
               cout<<lessons[i]<<"/"<<lessons[j]<<endl;
               return true;
           }
       }


   }
   return false;


}
//
//FUNCOES PARA REQUEST

void ControlUnit::createAdd(){
    string id;
    string uc;
    string studentgroup;
    cin>>id;
    cout<<"What UC do you want to add the student to:"<<endl;
    cin>>uc;
    cout<<"What Class of the UC you want to add the student into:"<<endl;
    cin>>studentgroup;
    RequestsToProcess.push(new AddRequest("add",id,uc,studentgroup));
}
void ControlUnit::createRemove(){
    cout<<"What's the ID of the student that you want to remove from an UC:"<<endl;
    string id;
    string uc;
    string studentgroup;
    cin>>id;
    cout<<"What UC you want to remove the student from:"<<endl;
    cin>>uc;
    cout<<"What Class is he in in the specified Uc:"<<endl;
    cin>>studentgroup;
    RequestsToProcess.push(new RemoveRequest("remove",id,uc,studentgroup));
}
void ControlUnit::createSwitch(){
    cout<<"What's the ID of the student that you want to switch from classes/UCs:"<<endl;
    string id;
    string uc1;
    string uc2;
    int choice;
    string studentgroup1;
    string studentgroup2;
    cin>>id;
    cout<<"What UC do you want to leave:"<<endl;
    cin>>uc1;
    cout<<"What class is he in right now:"<<endl;
    cin>>studentgroup1;
    bool invalid = true;
    while(invalid) {
        cout<<"Do you want to swap classes from the same UC or swap UCs?\n1.Swap Class from UC\n2.Swap UC\nChoose one:"<<endl;
        cin>>choice;
        switch (choice) {
            case 1:
                invalid = false;
                uc2 = uc1;
                break;
            case 2:
                invalid = false;
                cout << "What UC do you want the student to go to:" << endl;
                cin >> uc2;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
    cout<<"What class do you want to go to?";
    cin>> studentgroup2;
    RequestsToProcess.push(new SwitchRequest("switch",id,uc1,uc2,studentgroup1,studentgroup2));
}
void ControlUnit::processRequest(Request * request ) {
    if (request->getType() == "add") {
        cout<<"Detetado como add request"<<endl;
        processAddRequest(dynamic_cast<AddRequest*>(request));

    }else if (request->getType() == "remove") {
        cout<<"Detetado como remove request"<<endl;
        processRemoveRequest(dynamic_cast<RemoveRequest*>(request));
    }else if (request->getType() == "switch") {
        cout<<"Detetado como switch request"<<endl;
        processSwitchRequest(dynamic_cast<SwitchRequest*>(request));
    }//then have
}
void ControlUnit::processAddRequest(AddRequest* addRequest) {
    string upCode = addRequest->getUpCodeStudent();
    string classCode = addRequest->getClassCode();
    string ucCode = addRequest->getUCCode();
    cout<<"hey i got the request"<<upCode<<"/"<<classCode<<"/"<<ucCode;


    for (auto& student : StudentVector) {
        if (student.getStudentID() == upCode) {
            student.addStudentGroup(studentGroup(ucCode,classCode));
        }
    }





}
void ControlUnit::processRemoveRequest(RemoveRequest *removeRequest) {
    string upCode = removeRequest->getUpCodeStudent();
    string classCode = removeRequest->getClassCode();
    string ucCode = removeRequest->getUCCode();
    cout<<"hey i got the request"<<upCode<<"/"<<classCode<<"/"<<ucCode;
    // Find the set in the StudentMap
    MainKey key = {ucCode, classCode};
    //ppppppp
    //PARA O MAP


    for (auto& student : StudentVector) {
        if (student.getStudentID() == upCode) {

                student.removeGroup(studentGroup(ucCode, classCode));


        }
    }


    // Replace the original vector with the updated one



}

void ControlUnit::processSwitchRequest(SwitchRequest * switchRequest) {
    RemoveRequest * RemReq= new RemoveRequest("remove",switchRequest->getUpCodeStudent(),switchRequest->getUCCode1(),switchRequest->getClassCode1());
    AddRequest  * AddReq= new AddRequest("add",switchRequest->getUpCodeStudent(),switchRequest->getUCCode2(),switchRequest->getClassCode2());
    processRemoveRequest(RemReq);
    processAddRequest(AddReq);
}