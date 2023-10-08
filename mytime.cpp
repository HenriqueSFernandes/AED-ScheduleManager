//
// Created by ricky on 08-10-2023.
//

#include "mytime.h"

Mytime::Mytime(std::string tempo) {
    auto pos = tempo.find(".");
    if (pos != std::string::npos){
        this->hora = stoi(tempo.substr(0, pos));
        this->minuto = 30;
    }
    else{
        this->hora = stoi(tempo);
        this->minuto = 0;
    }
}

int Mytime::getHora() const {
    return hora;
}

int Mytime::getMinuto() const {
    return minuto;
}
