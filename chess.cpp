#include <QRectF>
#include <iostream>
#include "chess.h"
#include "ui_chess.h"
#include "game.h"

extern Game *game;

Board *Chess::getBoard() const
{
    return board;
}

void Chess::setBoard(Board *value)
{
    board = value;
}

void Chess::displayMainMenu()
{
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Chess"));
    QFont titleFont("comic sans", 40);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    ui->boardView->scene()->addItem(titleText);

    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 200;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    ui->boardView->scene()->addItem(playButton);

    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    ui->boardView->scene()->addItem(quitButton);
}

void Chess::mouseMoveEvent(QMouseEvent *event)
{
    if (pieceToPlace){
        pieceToPlace->setOffset( event->x() - 30, event->y() - 30);
    }
    return;
}

bool Chess::getWhosTurn() const
{
    return whosTurn;
}

void Chess::setWhosTurn(bool value)
{
    whosTurn = value;
}

void Chess::setWhosTurnText()
{
    QString value;
    if (whosTurn)
        value = QString("whites'");
    else
        value = QString("blacks'");

    whosTurnText->setPlainText(QString("Turn: ") + value);
}

void Chess::start()
{
    ui->boardView->scene()->clear();

    setWhosTurnText();
    whosTurnText->setPos(rect().width()/2, 5);
    ui->boardView->scene()->addItem(whosTurnText);

    board = new Board();
    board->initBoard();
    if(ui->boardView->scene() == nullptr)
        std::cerr << "scene is nullptr" << std::endl;
    else{
        // need two loops to print every piece in correct order
        for(Checker *checker : board->getCheckers()){
            ui->boardView->scene()->addItem(checker);
        }
        for(Checker *checker : board->getCheckers()){
            if(checker->getChessPiece() != nullptr)
                ui->boardView->scene()->addItem(checker->getChessPiece());
        }
    }
}


Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{

    ui->setupUi(this);
    ui->boardView->setScene(new QGraphicsScene());
    whosTurn = true;
    whosTurnText = new QGraphicsTextItem();
    pieceToPlace = nullptr;
    originChecker = nullptr;

}

Chess::~Chess()
{
    delete ui;
}
