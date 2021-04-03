#include "helpwin.h"
#include "ui_helpwin.h"

HelpWin::HelpWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWin)
{
    ui->setupUi(this);
}

HelpWin::~HelpWin()
{
    delete ui;
}



void HelpWin::showEx()
{
    this->setModal(true);
#ifdef DEBUG
    this->show();
#else
    this->showFullScreen();
#endif
    exec();
}

void HelpWin::on_pushButton_clicked()
{
    hide();
}
