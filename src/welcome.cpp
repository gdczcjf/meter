#include "welcome.h"

#include <QPainter>
#include <QApplication>

const int frameTime=150;

Welcome::Welcome(QWidget *parent)
    : QDialog(parent)
{
    pictures.resize(PIC_NUM);
    picture_num=1;
    pictures[0].load(":/movie/"+QString::number(PIC_NUM)+".JPG");
    dia=0;
}

void Welcome::loadPic()
{
    for(int i=2; i<=PIC_NUM; i++)
    {
        QString str;
        str=":/movie/"+QString::number(i)+".JPG";
        pictures[i-1].load(str);
    }
    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(changePic()));
    timer.start(frameTime);
}

Welcome::~Welcome()
{
    
}

void Welcome::changePic()
{
    if(picture_num < PIC_NUM)
    {
       picture_num++;
    }
    else
    {
        if(dia!=0)
#ifdef DEBUG
            dia->show();
#else
            dia->showFullScreen();
#endif
        QApplication::processEvents();
        this->hide();
    }
    this->repaint();
}

void Welcome::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,800,480,pictures[picture_num-1]);
}
void Welcome::preShow()
{
    this->resize(800,480);
#ifdef DEBUG
    //this->setWindowFlags(Qt::FramelessWindowHint);
    show();
#else
    this->setWindowFlags(Qt::FramelessWindowHint);
    showFullScreen();
    QApplication::processEvents();
#endif

}
void Welcome::showEx()
{
    this->loadPic();
    exec();
}
