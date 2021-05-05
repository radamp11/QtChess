#ifndef BOARD_H
#define BOARD_H
#include "checker.h"
#include <vector>

class Board
{
    // attrubutes
    QList<Checker*> checkers;

public:
    Board();
    QList<Checker*> getCheckers();
    void initBoard();
    void resetBoard();
};

#endif // BOARD_H
