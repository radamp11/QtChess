#include "game.h"
#include "board.h"
#include "button.h"
#include <QGraphicsTextItem>
#include <iostream>


bool Game::getWhosTurn() const
{
    return whosTurn;
}

void Game::setWhosTurn(bool val){
    whosTurn = val;
}

void Game::setWhosTurnText()
{
    QString value;
    if (whosTurn)
        value = QString("whites'");
    else
        value = QString("blacks'");

    whosTurnText->setPlainText(QString("Turn: ") + value);
}

ChessPiece *Game::getPieceToPlace() const
{
    return pieceToPlace;
}

void Game::setPieceToPlace(ChessPiece *value)
{
    pieceToPlace = value;
}

Checker *Game::getOriginChecker() const
{
    return originChecker;
}

void Game::setOriginChecker(Checker *value)
{
    originChecker = value;
}

Game::Game(QWidget *parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

    whosTurn = true;
    whosTurnText = new QGraphicsTextItem();
    pieceToPlace = nullptr;
    originChecker = nullptr;

    //setAcceptHoverEvents(true);

/*
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("Chess"));
    QFont titleFont("comic sans", 50);
    title->setFont(titleFont);
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    int tyPos = 150;
    title->setPos(txPos, tyPos);
    scene->addItem(title);
    */
}

void Game::displayMainMenu()
{
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Chess"));
    QFont titleFont("comic sans", 40);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button *playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 200;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

}
/*
void Game::pickUpPiece(ChessPiece *chessPiece)
{
    if( chessPiece->getColor() == whosTurn && !pieceToPlace ){
        pieceToPlace = chessPiece;
        lastPiecePreviousPos = chessPiece->pos();
        return;
    }

}
*/

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (pieceToPlace){
        pieceToPlace->setOffset(event->x() - 30, event->y() - 30);
    }
    return;
    //QGraphicsView::mouseMoveEvent(event);
}

void Game::start(){
    scene->clear();

    setWhosTurnText();
    whosTurnText->setPos(rect().width()/2, 5);
    scene->addItem(whosTurnText);

    board = new Board();
    board->initBoard();
    if(scene == nullptr)
        std::cerr << "scene is nullptr" << std::endl;
    else{
        // need two loops to print every piece in correct order
        for(Checker *checker : board->getCheckers()){
            scene->addItem(checker);
        }
        for(Checker *checker : board->getCheckers()){
            if(checker->getChessPiece() != nullptr)
                scene->addItem(checker->getChessPiece());
        }
    }
}
