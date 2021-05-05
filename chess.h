#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
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
    QString *gameMovesText;
    QGraphicsTextItem *gameMovesTextField;
    ChessPiece *pieceToPlace;
    Checker *originChecker;

    void addBoardToScene();

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

    void displayMainMenu();

    //getters and setters
    bool getWhosTurn() const;
    void setWhosTurn(bool val);
    void setWhosTurnText();

    Board *getBoard() const;
    void setBoard(Board *value);

    QGraphicsView *getBoardView();

    ChessPiece *getPieceToPlace() const;
    void setPieceToPlace(ChessPiece *value);

    Checker *getOriginChecker() const;
    void setOriginChecker(Checker *value);

    QGraphicsTextItem *getGameMovesTextField() const;
    void setGameMovesTextField();

    QString *getGameMovesText() const;
    void setGameMovesText(QString *value);

public slots:
    void start();
    void newGame();
    void saveGame();

private:
    Ui::Chess *ui;
};
#endif // CHESS_H
