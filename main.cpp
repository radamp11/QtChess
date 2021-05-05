#include "chess.h"

#include <QApplication>

Chess *chess;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    chess = new Chess();  
    chess->show();
    chess->displayMainMenu();

    return a.exec();
}
