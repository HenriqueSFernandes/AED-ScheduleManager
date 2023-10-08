#include "tempo.h"

tempo::tempo(){
    hora = 0;
    minuto = 0;
}

tempo::tempo(double tempo) {
    hora = (int)tempo;
    if (tempo > hora){
        minuto = 30;
    }
    else{
        minuto = 0;
    }
}

int tempo::getHora() const {
    return hora;
}

int tempo::getMinuto() const {
    return minuto;
}
