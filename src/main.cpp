#include <QApplication>
#include <QTextCodec>

#include "welcome.h"
#include "home.h"
#include "hardware.h"

//#include "QWindowsStyle"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle(new QWindowsStyle);

#if WELCOME_EN
        Welcome *welWin = new Welcome;
        welWin->preShow();
#endif

#ifdef Q_OS_UNIX
    QFont font("wenquanyi");
    a.setFont(font);
#endif
    HardWare::init();


    Home pHome;

#if WELCOME_EN
        welWin->dia=&pHome;
        welWin->showEx();
 #endif
    pHome.showEx();
#if WELCOME_EN
    delete welWin;
 #endif

    return a.exec();
}
