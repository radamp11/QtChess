#ifndef BOARD_H
#define BOARD_H
#include "checker.h"
#include <vector>

class Board
{
    // attrubutes
    QList<Checker*> checkers;
    QList<ChessPiece*> whitePieces;
    QList<ChessPiece*> blackPieces;

public:
    Board();
    QList<Checker*> getCheckers();
    void initBoard();
    void resetBoard();
    void refreshBoard();
};

#endif // BOARD_H
