#include "turma.h"

turma::turma() {
    numalunos = 0;
}

turma::turma(const std::string &dia, double inicio, double duracao, const std::string &tipo) {
    numalunos = 0;
    aulas.push_back(aula(dia, inicio, duracao, tipo));
}

void turma::addAula(const std::string &dia, double inicio, double duracao, const std::string &tipo) {
    aulas.push_back(aula(dia, inicio, duracao, tipo));
}

void turma::addStudent() {
    numalunos++;
}