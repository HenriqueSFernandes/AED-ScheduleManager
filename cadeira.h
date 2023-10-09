//
// Created by ricky on 08-10-2023.
//

#ifndef PROJAED_CADEIRA_H
#define PROJAED_CADEIRA_H


#include <string>
#include <vector>
#include <map>
#include "turma.h"

class cadeira {
public:
    cadeira(std::string ClassCode, std::string UcCode, std::string Weekday, double StartHour, double Duration, std::string Type);
    void addClass(std::string ClassCode, std::string Weekday, double StartHour, double Duration, std::string Type);

private:
    std::string UcCode;
    std::map<std::string, turma> turmas;
};


#endif //PROJAED_CADEIRA_H
