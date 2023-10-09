#ifndef PROJAED_ESTUDANTE_H
#define PROJAED_ESTUDANTE_H


#include <tuple>
#include <string>
#include "cadeira.h"

class estudante {
public:
private:
    std::string IdEstudante;
    std::string Nome;
    std::map<cadeira, std::string> cadeira_turma;

};


#endif //PROJAED_ESTUDANTE_H
