#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


class ChessPiece : public QGraphicsPixmapItem
{
protected:
    int xPos;
    int yPos;
    bool color;     // white - true, black - false
    QString imagePath;
    //Checker *currentChecker;
public:
    ChessPiece();
    virtual void possibleMoves() = 0;

    // events
    //void mousePressedEvent(QGraphicsSceneMouseEvent *event);

    // getters and setters
    QString getImagePath() const;
    void setImagePath(const QString &value);
    bool getColor() const;
    void setColor(bool value);

    int getXPos() const;
    void setXPos(int value);

    int getYPos() const;
    void setYPos(int value);

    //Checker *getCurrentChecker() const;
    //void setCurrentChecker(Checker *value);

signals:
    //void pickMe();
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
