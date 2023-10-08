//
// Created by ricky on 08-10-2023.
//

#include "aula.h"

aula::aula(const std::string &dia, double inicio, double duracao, const std::string &tipo) {
    this->dia = dia;
    this->inicio = tempo(inicio);
    this->duracao =  tempo(duracao);
    this->tipo = tipo;
    this->fim = tempo(inicio + duracao);
}

const std::string &aula::getDia() const {
    return dia;
}

const tempo &aula::getInicio() const {
    return inicio;
}

const tempo &aula::getDuracao() const {
    return duracao;
}

const tempo &aula::getFim() const {
    return fim;
}

const std::string &aula::getTipo() const {
    return tipo;
}
