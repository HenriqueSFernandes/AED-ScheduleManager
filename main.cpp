#include <iostream>
#include "mytime.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Mytime hora("5");
    std::cout << "hora: " << hora.getHora() << " minuto: " << hora.getMinuto() << std::endl;
    return 0;
}
