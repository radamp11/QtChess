#include "chesspiece.h"
#include "checker.h"
#include "game.h"
#include <iostream>


QString ChessPiece::getImagePath() const
{
    return imagePath;
}

void ChessPiece::setImagePath(const QString &value)
{
    imagePath = value;
}

bool ChessPiece::getColor() const
{
    return color;
}

void ChessPiece::setColor(bool value)
{
    color = value;
}

int ChessPiece::getXPos() const
{
    return xPos;
}

void ChessPiece::setXPos(int value)
{
    xPos = value;
}

int ChessPiece::getYPos() const
{
    return yPos;
}

void ChessPiece::setYPos(int value)
{
    yPos = value;
}

ChessPiece::ChessPiece()
{
    
}

//------------------------------------------

Queen::Queen(bool color, int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/queen_white.svg");
    else
        this->imagePath = QString(":/images/queen_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void Queen::possibleMoves()
{
    std::cout<< "to jest krolowa" << std::endl;
}

King::King(bool color, int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/king_white.svg");
    else
        this->imagePath = QString(":/images/king_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void King::possibleMoves()
{
    std::cout<< "to jest krol" << std::endl;
}

Bishop::Bishop(bool color, int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/bishop_white.svg");
    else
        this->imagePath = QString(":/images/bishop_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void Bishop::possibleMoves()
{
    std::cout<< "to jest goniec" << std::endl;
}

Knight::Knight(bool color, int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/knight_white.svg");
    else
        this->imagePath = QString(":/images/knight_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void Knight::possibleMoves()
{
    std::cout<< "to jest skoczek" << std::endl;
}

Rook::Rook(bool color, int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/rook_white.svg");
    else
        this->imagePath = QString(":/images/rook_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void Rook::possibleMoves()
{
    std::cout<< "to jest wieza" << std::endl;
}

Pawn::Pawn(bool color, int xPos, int yPos)
{
    this->hasMoved = false;
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    if(color)
        this->imagePath = QString(":/images/pawn_white.svg");
    else
        this->imagePath = QString(":/images/pawn_black.svg");
    this->setPixmap(QPixmap(this->imagePath));
    this->setOffset(xPos * SCALE, yPos * SCALE);
}

void Pawn::possibleMoves()
{
    std::cout<< "to jest pion" << std::endl;
}
