#ifndef CHECKER_H
#define CHECKER_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>
#include "chesspiece.h"

const int SCALE = 60;
const int CHECKER_SIZE = SCALE;

class Checker : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    ChessPiece *chessPiece;
    QColor color;
    int xPos, yPos;
    QString name;

public:
    Checker(QGraphicsItem *parent = nullptr);
    Checker(int xPos, int yPos, const QColor& color, QGraphicsItem *parent = nullptr);

    ChessPiece* getChessPiece(){ return chessPiece; }

    void setChessPiece(ChessPiece *piece) { chessPiece = piece; }
    void setColor(QColor newColor){ color = newColor; }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    int getXPos() const;
    void setXPos(int value);

    int getYPos() const;
    void setYPos(int value);

    bool operator==(Checker *second);

    ~Checker();

    QString getName() const;
    void setName(const QString &value);

signals:
    void clicked();


};

#endif // CHECKER_H
