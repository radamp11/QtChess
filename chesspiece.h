#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

const char KING = 'K';
const char QUEEN = 'Q';
const char BISHOP = 'B';
const char KNIGHT = 'N';
const char ROOK = 'R';

class ChessPiece : public QGraphicsPixmapItem
{
protected:
    int xPos;
    int yPos;
    bool color;     // white - true, black - false
    QString imagePath;
    QString name;

public:
    ChessPiece();
    virtual void possibleMoves() = 0;

    // getters and setters
    QString getImagePath() const;
    void setImagePath(const QString &value);
    bool getColor() const;
    void setColor(bool value);

    int getXPos() const;
    void setXPos(int value);

    int getYPos() const;
    void setYPos(int value);

    QString getName() const;
    void setName(const QString &value);
};

//-----------------------------------------------

class King : public ChessPiece
{
public:
    King(bool color, int xPos, int yPos);
    void possibleMoves();
};


class Queen : public ChessPiece
{
public:
    Queen(bool color, int xPos, int yPos);
    void possibleMoves();
};


class Bishop : public ChessPiece
{
public:
    Bishop(bool color, int xPos, int yPos);
    void possibleMoves();
};


class Knight : public ChessPiece
{
public:
    Knight(bool color, int xPos, int yPos);
    void possibleMoves();
};


class Rook : public ChessPiece
{
public:
    Rook(bool color, int xPos, int yPos);
    void possibleMoves();
};


class Pawn : public ChessPiece
{
    bool hasMoved;
public:
    Pawn(bool color, int xPos, int yPos);
    void possibleMoves();
};


#endif // CHESSPIECE_H
