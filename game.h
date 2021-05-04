#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "board.h"
#include "chess.h"

class Game : public QGraphicsView
{
    Q_OBJECT
    bool whosTurn;  // true - white, false - black
    QGraphicsTextItem *whosTurnText;
    ChessPiece *pieceToPlace;
    Checker *originChecker;

    //void setWhosTurn(bool val);
public:
    // public attributes
    QPointF lastPiecePreviousPos;
    QGraphicsScene *scene;
    Board *board;

    // methods
    Game(QWidget *parent = nullptr);
    void displayMainMenu();
    void pickUpPiece(ChessPiece *chessPiece);

    //events
    void mouseMoveEvent(QMouseEvent *event);

    //getters and setters
    bool getWhosTurn() const;
    void setWhosTurn(bool val);
    void setWhosTurnText();

    ChessPiece *getPieceToPlace() const;
    void setPieceToPlace(ChessPiece *value);

    Checker *getOriginChecker() const;
    void setOriginChecker(Checker *value);

public slots:
    void start();

};

#endif // GAME_H
