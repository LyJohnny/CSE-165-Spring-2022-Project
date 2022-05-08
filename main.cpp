#include <QApplication>
#include <QScreen>
#include "spaceinvaders.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CSpaceInvaders* pGame = new CSpaceInvaders(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->Run();

    return a.exec();
}
