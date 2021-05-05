#include <QRectF>
#include <iostream>
#include <QInputDialog>
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
/*
void Chess::mouseMoveEvent(QMouseEvent *event)
{

    std::cout << "jestem w evencie chess" << std::endl;
    if (pieceToPlace){
        pieceToPlace->setOffset( event->x() - 30, event->y() - 30);
    }
    return;
}
*/

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

QGraphicsView *Chess::getBoardView()
{
    return ui->boardView;
}

void Chess::start()
{
    ui->boardView->scene()->clear();

    setWhosTurnText();
    whosTurnText->setPos(getBoardView()->rect().width()/2, 5);
    ui->boardView->scene()->addItem(whosTurnText);

    board = new Board();
    board->initBoard();
    addBoardToScene();
    //connect( ui->actionNewGame, SIGNAL(trigerred()), this, SLOT(newGame()));
}

void Chess::newGame()
{
    getBoardView()->scene()->clear();
    pieceToPlace = nullptr;
    originChecker = nullptr;
    whosTurnText = new QGraphicsTextItem();
    whosTurnText->setFont(QFont("comic sans", 15));
    gameMovesText->clear();
    setGameMovesTextField();

    whosTurn = true;
    setWhosTurnText();
    whosTurnText->setPos(getBoardView()->rect().width()/2, 5);
    getBoardView()->scene()->addItem(whosTurnText);

    board->resetBoard();
    addBoardToScene();
}

void Chess::saveGame()
{
    //QInputDialog dialogWindow = new QInputDialog();
    //QString fileName = QInputDialog::getText()
    std::cout << "jestem w funkcji saveGame" << std::endl;
    QString fileName = "../gameMoves.txt";
    QFile outFile(fileName);

    if(!outFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "could not open this file";
        return;
    }
    std::cout << "i otworzyłem plik" << std::endl;
    outFile.write(gameMovesText->toUtf8());
    outFile.close();
}

QGraphicsTextItem *Chess::getGameMovesTextField() const
{
    return gameMovesTextField;
}

void Chess::setGameMovesTextField()
{
    gameMovesTextField->setPlainText(*gameMovesText);
}

QString *Chess::getGameMovesText() const
{
    return gameMovesText;
}

void Chess::setGameMovesText(QString *value)
{
    gameMovesText = value;
}

void Chess::addBoardToScene()
{
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

ChessPiece *Chess::getPieceToPlace() const
{
    return pieceToPlace;
}

void Chess::setPieceToPlace(ChessPiece *value)
{
    pieceToPlace = value;
}

Checker *Chess::getOriginChecker() const
{
    return originChecker;
}

void Chess::setOriginChecker(Checker *value)
{
    originChecker = value;
}


Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{

    ui->setupUi(this);
    ui->boardView->setScene(new QGraphicsScene());
    whosTurn = true;
    whosTurnText = new QGraphicsTextItem();
    whosTurnText->setFont(QFont("comic sans", 15));
    pieceToPlace = nullptr;
    originChecker = nullptr;

    gameMovesText = new QString();
    gameMovesTextField = new QGraphicsTextItem();
    gameMovesTextField->setFont(QFont("helvetica", 12));
    //gameMovesText->setPos(50, 50);
    ui->textView->setScene(new QGraphicsScene());
    ui->textView->scene()->addItem(gameMovesTextField);

    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui->actionSaveMoves, SIGNAL(triggered()), this, SLOT(saveGame()));

}

Chess::~Chess()
{
    delete ui;
}
