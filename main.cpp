#include <iostream>
#include "src/lessontime.h"
#include "src/lesson.h"

#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include "src/Menu.h"
#include "src/Request.h"
#include "src/AddRequest.h"
#include "src/ControlUnit.h"
#include "src/studentGroup.h"
using namespace std;


int Request::count=0;
int main() {


    //é bem simples, basicamente no default pus um continue (que faz ir pro proximo loop instantaneamente) e pus um break dps dos cases
    //pra sair do loop infinito
    studentGroup myturma=studentGroup("L.EIC023","3LEIC07");
    studentGroup myturma2=studentGroup("L.EIC024","3LEIC08");
    studentGroup myturma3=studentGroup("L.EIC024","3LEIC08");
    vector<studentGroup> mygroups;
    /*for(int i=0;i<14;i++){
        myturma.IncreaseNumOfStudents();

    }
    mygroups.push_back(myturma);
    for(int i=0;i<13;i++){
        myturma2.IncreaseNumOfStudents();

    }
    mygroups.push_back(myturma2);
    for(int i=0;i<18;i++){
        myturma3.IncreaseNumOfStudents();

    } mygroups.push_back(myturma3);

    ControlUnit control2= ControlUnit();
    cout <<"IS IT BALANCED ?"<<control2.IsBalanced(mygroups);


*/
    Menu myMenu= Menu();
    myMenu.createMenu();
}

