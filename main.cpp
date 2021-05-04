#include "chess.h"

#include <QApplication>
#include "game.h"

Game *game;
Chess *chess;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();

    game->show();
    game->displayMainMenu();


    //chess = new Chess();
    //chess->show();
    //chess->displayMainMenu();
    //w.initBoard();

    return a.exec();
}
