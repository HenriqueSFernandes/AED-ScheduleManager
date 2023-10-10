#include <iostream>
#include "time.h"
#include "lesson.h"

using namespace std;
using namespace Time;

int main() {
    lesson aula1("monday", 10.5, 1.5, "TP");
    cout << "dia: " << aula1.getWeekday() << " inicio: " << aula1.getStartTime().getHour() << ":" << aula1.getStartTime().getMinute() <<  " fim: " << aula1.getEndTime().getHour() << ":" << aula1.getEndTime().getMinute() << " tipo: " << aula1.getType() << endl;
    return 0;
}
