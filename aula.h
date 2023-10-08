#ifndef PROJAED_AULA_H
#define PROJAED_AULA_H


#include <string>
#include <ctime>
#include "tempo.h"

class aula {
public:
    aula(const std::string &dia, double inicio, double duracao, const std::string &tipo);

private:
    std::string dia;
    tempo inicio;
    tempo duracao;
    tempo fim;
    std::string tipo;
public:
    const std::string &getDia() const;

    const tempo &getInicio() const;

    const tempo &getDuracao() const;

    const tempo &getFim() const;

    const std::string &getTipo() const;
};


#endif //PROJAED_AULA_H