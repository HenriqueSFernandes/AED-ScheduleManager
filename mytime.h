//
// Created by ricky on 08-10-2023.
//

#ifndef PROJAED_MYTIME_H
#define PROJAED_MYTIME_H


#include <string>

class Mytime {
public:
    Mytime(std::string tempo);

    int getHora() const;

    int getMinuto() const;

private:
    int hora;
    int minuto;
};


#endif //PROJAED_MYTIME_H
