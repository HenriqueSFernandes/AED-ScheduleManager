//
// Created by ricky on 08-10-2023.
//

#include "cadeira.h"

cadeira::cadeira(std::string ClassCode, std::string UcCode, std::string Weekday, double StartHour, double Duration,
                 std::string Type) {
    this->UcCode = UcCode;
    this->turmas.insert({ClassCode, turma(Weekday, StartHour, Duration, Type)});
}

void cadeira::addClass(std::string ClassCode, std::string Weekday, double StartHour, double Duration,
                       std::string Type) {
    if (turmas.find(ClassCode) != turmas.end()){
        turmas[ClassCode].addAula(Weekday, StartHour, Duration, Type);
    }
    else{
        turmas.insert({ClassCode, turma(Weekday, StartHour, Duration, Type)});
    }
}