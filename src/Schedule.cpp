//
// Created by kali on 10/10/23.
//

#include "Schedule.h"
#include <iostream>
#include <iomanip>

std::map<std::string, int> dayMap = {
        {"Monday",    0},
        {"Tuesday",   1},
        {"Wednesday", 2},
        {"Thursday",  3},
        {"Friday",    4},
        {"Saturday",  5},
        {"Sunday",    6}
};
std::vector<std::string> dayVector = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
};

Schedule::Schedule(vector<lesson> lessons) {
    this->lessons = lessons;
    for (auto lesson: lessons) {
        int StartingHour = lesson.getStartTime().getHour();
        int hasMin = 0;
        if (lesson.getStartTime().getMinute() == 30) {
            hasMin = 1;
        }
        int row = 3 * ((StartingHour - 8) * 2 + hasMin);
        int col = dayMap[lesson.getWeekday()];
        int size = lesson.getDuration().getHour() * 2;

        if (lesson.getDuration().getMinute()) {
            size++;
        }
        int cellWidth = 15;
        int numRows = size * 3;
        std::string contentCadeira = lesson.getUccode();
        std::string contentType = lesson.getType();


        std::string cellContent = "| " + contentCadeira + "-" + contentType;
        while (cellContent.size() < cellWidth - 2) {
            cellContent += " ";
        }
        cellContent += " |";

        std::string FILLERclass = "| ";
        while (FILLERclass.size() < cellWidth - 2) {
            FILLERclass += " ";
        }
        FILLERclass += " |";
        std::string BORDER = "";
        while (BORDER.size() < cellWidth) {
            BORDER += "-";
        }



// Calculate the position for the middle row
        int middleRow = row + numRows / 2;

// Place the content in the middle row and fill the other rows with borders
        for (int i = 0; i < numRows; i++) {
            if (i == 0 || i == numRows - 1) {
                ScheduleMap[{row + i, col}] = BORDER;
            } else if (i == numRows / 2) {
                ScheduleMap[{middleRow, col}] = cellContent;
            } else {
                ScheduleMap[{row + i, col}] = FILLERclass;
            }
        }


    }
}

void Schedule::display() {
    int cellWidth = 15;
    std::string FILLER = "";
    while (FILLER.size() < cellWidth) {
        FILLER += "*";
    }

    for (int i = 0; i < 3; i++) {
        string diasSemana = "";
        for (int j = 0; j < 6; j++) {
            if (i % 3 == 0) {
                std::string BORDER = "";
                while (BORDER.size() < cellWidth) {
                    BORDER += "-";
                }
                diasSemana += BORDER;
                diasSemana += "    ";


            } else if (i % 3 == 1) {
                string content = "";
                if (j != 0) {
                    int index = j - 1;
                    content = dayVector[index];

                }
                std::string cellContent = "| " + content;
                while (cellContent.size() < cellWidth - 2) {
                    cellContent += " ";
                }
                cellContent += " |";
                diasSemana += cellContent;
                diasSemana += "    ";


            } else {
                std::string BORDER = "";
                while (BORDER.size() < cellWidth) {
                    BORDER += "-";
                }
                diasSemana += BORDER;
                diasSemana += "    ";

            }

        }
        std::cout << diasSemana << std::endl;

    }

    for (int i = 0; i < 29 * 3; i++) {
        string line = "";
        if (i % 3 == 0) {
            std::string BORDER = "";
            while (BORDER.size() < cellWidth) {
                BORDER += "-";
            }
            line += BORDER;
            line += "    ";

        } else if (i % 3 == 1) {
            int meiasHoras = i / 3;
            int horas = meiasHoras / 2 + 8;
            int meiaHora = (meiasHoras % 2) * 30;
            int nextHoras = 0;
            int nextMin = 0;
            if (meiaHora) {
                nextHoras = horas + 1;
                nextMin = 0;
            } else {
                nextHoras = horas;
                nextMin = 30;
            }

            std::string cellContent = "| " + lessontime(horas, meiaHora).displayHourFormat() + "-" +
                                      lessontime(nextHoras, nextMin).displayHourFormat();
            while (cellContent.size() < cellWidth - 2) {
                cellContent += " ";
            }
            cellContent += " |";
            line += cellContent;
            line += "    ";

        } else {
            std::string BORDER = "";
            while (BORDER.size() < cellWidth) {
                BORDER += "-";
            }
            line += BORDER;
            line += "    ";
        }


        for (int j = 0; j < 5; j++) {
            if (ScheduleMap.find({i, j}) != ScheduleMap.end()) {
                line += ScheduleMap[{i, j}];
                line += "    ";
            } else {
                line += FILLER;
                line += "    ";
            }
        }
        std::cout << line << std::endl;
    }
}