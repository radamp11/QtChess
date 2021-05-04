#include "checker.h"
#include "game.h"
#include "chess.h"
#include <QBrush>

extern Game *game;
extern Chess *chess;

int Checker::getXPos() const
{
    return xPos;
}

void Checker::setXPos(int value)
{
    xPos = value;
}

int Checker::getYPos() const
{
    return yPos;
}

void Checker::setYPos(int value)
{
    yPos = value;
}

bool Checker::operator==(Checker *second)
{
    return xPos == second->xPos && yPos == second->yPos;
}

Checker::Checker(QGraphicsItem *parent){
    chessPiece = nullptr;
    QRectF checker(1 * SCALE, 1 * SCALE, 1 * SCALE, 1 * SCALE);
    setRect(checker);
}

Checker::Checker(int xPos, int yPos, const QColor& color, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->color = color;
    chessPiece = nullptr;
    QRectF checkerRect(xPos * SCALE, yPos * SCALE, CHECKER_SIZE, CHECKER_SIZE);
    setRect(checkerRect);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(this->color);
    setBrush(brush);

    setAcceptHoverEvents(true);

}

void Checker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //emit clicked();
    std::cout << "hey, i was clicked, my pos: " << xPos << ", " << yPos << std::endl;
    // theres no piece chosen and it is this color turn; nullptr tells that it is first click to chose piece
    if( !game->getPieceToPlace() && this->getChessPiece() && this->getChessPiece()->getColor() == game->getWhosTurn() ){
        game->setPieceToPlace(this->getChessPiece());
        game->setOriginChecker(this);
        return;     // end to require second click
    }
    // piece to place is set, the origin of piece too, so check if i can move it
    else if ( game->getPieceToPlace() && game->getOriginChecker() && game->getPieceToPlace()->getColor() == game->getWhosTurn()
              && !this->getChessPiece() /* i am moving piece to free checker */){
        this->setChessPiece(game->getPieceToPlace());
        game->getOriginChecker()->setChessPiece(nullptr);
        this->chessPiece->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);
        game->setPieceToPlace(nullptr);
        game->setOriginChecker(nullptr);
        game->setWhosTurn(!game->getWhosTurn());
        game->setWhosTurnText();
        return;
    }
    // same as previous, but i am placing piece to checker already consisting a piece
    else if ( game->getPieceToPlace() && game->getOriginChecker() && game->getPieceToPlace()->getColor() == game->getWhosTurn()
              && this->getChessPiece() && this != game->getOriginChecker()/* the checker i want to move my piece is not free and it is not the origin checker*/){
        // i am trying to attack enemy piece
        if( this->getChessPiece()->getColor() != game->getPieceToPlace()->getColor() ){
            game->scene->removeItem(this->getChessPiece());     // remove attacked piece from scene
            delete this->getChessPiece();                       // delete attacked piece object from heap
            this->setChessPiece(game->getPieceToPlace());       // change checker's pointer to piece that attacked
            this->getChessPiece()->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);     // move winning piece to new checker
            game->getOriginChecker()->setChessPiece(nullptr);   // removing reference from previous checker
            game->setOriginChecker(nullptr);                    // and preparing next move
            game->setPieceToPlace(nullptr);
            game->setWhosTurn(!game->getWhosTurn());
            game->setWhosTurnText();
            return;
        }
    }
    // leave piece on an origin checker
    else if ( game->getPieceToPlace() && game->getOriginChecker() && game->getPieceToPlace()->getColor() == game->getWhosTurn()
                  && this->getXPos() == game->getOriginChecker()->getXPos() && this->getYPos() == game->getOriginChecker()->getYPos() /* i picked origin checker again, so i leave piece in peace :D */){
        std::cout << "puts(weszlo!);" << std::endl;
        game->setPieceToPlace(nullptr);
        game->setOriginChecker(nullptr);
        this->getChessPiece()->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);
        return;
    }
}


void Checker::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor tempColor(100, 255, 100);
    brush.setColor(tempColor);
    setBrush(brush);
}

void Checker::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(this->color);
    setBrush(brush);
}


