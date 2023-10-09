//
// Created by ricky on 08-10-2023.
//

#ifndef PROJAED_TURMA_H
#define PROJAED_TURMA_H


#include <vector>
#include <string>
#include "aula.h"

class turma {
public:
    turma();
    turma(const std::string &dia, double inicio, double duracao, const std::string &tipo);
    void addAula(const std::string &dia, double inicio, double duracao, const std::string &tipo);
    void addStudent();
private:
    int numalunos;
    std::vector<aula> aulas;
};


#endif //PROJAED_TURMA_H
