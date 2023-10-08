//
// Created by ricky on 08-10-2023.
//

#ifndef PROJAED_TEMPO_H
#define PROJAED_TEMPO_H


#include <string>

class tempo {
public:
    tempo(double tempo);

    tempo();


    int getHora() const;

    int getMinuto() const;

private:
    int hora;
    int minuto;
};


#endif //PROJAED_TEMPO_H
