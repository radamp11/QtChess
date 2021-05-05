#include "checker.h"
#include "game.h"
#include "chess.h"
#include <QBrush>


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

Checker::~Checker()
{
    delete chessPiece;
}

QString Checker::getName() const
{
    return name;
}

void Checker::setName(const QString &value)
{
    name = value;
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
    QString moveNotation = "";

    std::cout << "hey, i was clicked, my pos: " << xPos << ", " << yPos << " and my name: " << name.toUtf8().constData() << std::endl;
    // theres no piece chosen and it is this color turn; nullptr tells that it is first click to chose piece
    if( !chess->getPieceToPlace() && this->getChessPiece() && this->getChessPiece()->getColor() == chess->getWhosTurn() ){
        chess->setPieceToPlace(this->getChessPiece());
        chess->setOriginChecker(this);
        return;     // end to require second click
    }
    // piece to place is set, the origin of piece too, so check if i can move it
    else if ( chess->getPieceToPlace() && chess->getOriginChecker() && chess->getPieceToPlace()->getColor() == chess->getWhosTurn()
              && !this->getChessPiece() /* i am moving piece to free checker */){
        moveNotation.append(chess->getPieceToPlace()->getName());
        moveNotation.append(this->getName());
        moveNotation.append('\n');
        chess->getGameMovesText()->append(moveNotation);
        chess->setGameMovesTextField();

        this->setChessPiece(chess->getPieceToPlace());
        chess->getOriginChecker()->setChessPiece(nullptr);
        this->chessPiece->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);
        chess->setPieceToPlace(nullptr);
        chess->setOriginChecker(nullptr);
        chess->setWhosTurn(!chess->getWhosTurn());
        chess->setWhosTurnText();

        return;
    }
    // same as previous, but i am placing piece to checker already consisting a piece
    else if ( chess->getPieceToPlace() && chess->getOriginChecker() && chess->getPieceToPlace()->getColor() == chess->getWhosTurn()
              && this->getChessPiece() && this != chess->getOriginChecker()/* the checker i want to move my piece is not free and it is not the origin checker*/){
        // i am trying to attack enemy piece
        if( this->getChessPiece()->getColor() != chess->getPieceToPlace()->getColor() ){
            moveNotation.append(chess->getPieceToPlace()->getName());
            moveNotation.append('x');
            moveNotation.append(this->getName());
            moveNotation.append('\n');
            chess->getGameMovesText()->append(moveNotation);
            chess->setGameMovesTextField();

            chess->getBoardView()->scene()->removeItem(this->getChessPiece());     // remove attacked piece from scene
            delete this->getChessPiece();                       // delete attacked piece object from heap
            this->setChessPiece(chess->getPieceToPlace());       // change checker's pointer to piece that attacked
            this->getChessPiece()->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);     // move winning piece to new checker
            chess->getOriginChecker()->setChessPiece(nullptr);   // removing reference from previous checker
            chess->setOriginChecker(nullptr);                    // and preparing next move
            chess->setPieceToPlace(nullptr);
            chess->setWhosTurn(!chess->getWhosTurn());
            chess->setWhosTurnText();
            return;
        }
    }
    // leave piece on an origin checker
    else if ( chess->getPieceToPlace() && chess->getOriginChecker() && chess->getPieceToPlace()->getColor() == chess->getWhosTurn()
                  && this->getXPos() == chess->getOriginChecker()->getXPos() && this->getYPos() == chess->getOriginChecker()->getYPos() /* i picked origin checker again, so i leave piece in peace :D */){
        std::cout << "puts(weszlo!);" << std::endl;
        chess->setPieceToPlace(nullptr);
        chess->setOriginChecker(nullptr);
        this->getChessPiece()->setOffset(this->getXPos() * SCALE, this->getYPos() * SCALE);
        return;
    }
}


/*
void Checker::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "jestem w evencie checker move mouse" << std::endl;
    if (chess->getPieceToPlace()){
        chess->getPieceToPlace()->setOffset( event->pos().x() - 30, event->pos().y() - 30);
    }
    return;
}
*/

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


