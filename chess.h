#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "button.h"
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Chess; }
QT_END_NAMESPACE

class Chess : public QMainWindow
{
    Q_OBJECT
    Board* board;
    bool whosTurn;  // true - white, false - black
    QGraphicsTextItem *whosTurnText;
    ChessPiece *pieceToPlace;
    Checker *originChecker;

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

    //virtual void paintEvent(QPaintEvent *event);

    Board *getBoard() const;
    void setBoard(Board *value);

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

private:
    Ui::Chess *ui;
};
#endif // CHESS_H
