#include "board.h"
#include <QPainter>

Board::Board()
{

}

QList<Checker *> Board::getCheckers()
{
    return checkers;
}

void Board::initBoard()
{
    QColor dark(143, 87, 54);
    QColor light(226, 184, 126);
    char letterField = 'a';
    for(int i = 1; i <= 8; ++i){
        for(int j = 1; j <= 8; ++j){
            Checker *checker;
            if((j % 2 == 0 && i % 2 != 0) || (j % 2 != 0 && i % 2 == 0))
                checker = new Checker(i, j, dark);
            else
                checker = new Checker(i, j, light);

            if ( (i == 1 || i == 8) && j == 1 )
                checker->setChessPiece(new Rook(false, checker->getXPos(), checker->getYPos()));
            else if ( (i == 2 || i == 7) && j == 1 )
                checker->setChessPiece(new Knight(false, checker->getXPos(), checker->getYPos()));
            else if ( (i == 3 || i == 6) && j == 1 )
                checker->setChessPiece(new Bishop(false, checker->getXPos(), checker->getYPos()));
            else if ( (i == 4) && j == 1 )
                checker->setChessPiece(new Queen(false, checker->getXPos(), checker->getYPos()));
            else if ( (i == 5) && j == 1 )
                checker->setChessPiece(new King(false, checker->getXPos(), checker->getYPos()));
            else if ( j == 2 ){
                checker->setChessPiece(new Pawn(false, checker->getXPos(), checker->getYPos()));
            }
            else if ( j == 7 ){
                checker->setChessPiece(new Pawn(true, checker->getXPos(), checker->getYPos()));
            }
            else if ( (i == 1 || i == 8) && j == 8 )
                checker->setChessPiece(new Rook(true, checker->getXPos(), checker->getYPos()));
            else if ( (i == 2 || i == 7) && j == 8 )
                checker->setChessPiece(new Knight(true, checker->getXPos(), checker->getYPos()));
            else if ( (i == 3 || i == 6) && j == 8 )
                checker->setChessPiece(new Bishop(true, checker->getXPos(), checker->getYPos()));
            else if ( (i == 4) && j == 8 )
                checker->setChessPiece(new Queen(true, checker->getXPos(), checker->getYPos()));
            else if ( (i == 5) && j == 8 )
                checker->setChessPiece(new King(true, checker->getXPos(), checker->getYPos()));

            checker->setName(QString(letterField + QString::number(9 - j)));
            //std::string checkName = checker->getName().toUtf8().constData();

            //std::cout << "ustawione nazwa pola: " << checkName << std::endl;
            checkers.append(checker);

        }
        letterField++;
    }
}

void Board::resetBoard()
{
    checkers.clear();
    initBoard();
}

