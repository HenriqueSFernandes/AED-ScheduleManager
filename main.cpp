#include <iostream>
#include "tempo.h"
#include "aula.h"

using namespace std;

int main() {
    aula aula1("monday", 10.5, 1.5, "TP");
    cout << "dia: " << aula1.getDia() << " inicio: " << aula1.getInicio().getHora() << ":" << aula1.getInicio().getMinuto() <<  " fim: " << aula1.getFim().getHora() << ":" << aula1.getFim().getMinuto() << "tipo: " << aula1.getTipo() << endl;
    return 0;
}
