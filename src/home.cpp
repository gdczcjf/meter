#include "home.h"
#include "ui_home.h"
#include "calculator.h"
#include "settingwin.h"
#include "helpwin.h"
#include "hardware.h"




Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    picture.load(":/movie/27.JPG");

    closeButtonBixmap.load(":/pic/closeButton.png");
    closeButton.setPic(&closeButtonBixmap,closeButtonBixmap.width(),0.0);
    closeButton.setX(800.0);
    closeButton.setY(0.0);




    scene.setSceneRect(0,0,800,480);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    scene.addItem(new Meter);
    scene.addItem(new Meter);
    scene.addItem(new Meter);
    scene.addItem(new Meter);
    scene.addItem(&closeButton);


    view.setScene(&scene);
    view.setGeometry(0,0,800,480);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.hide();
    view.setParent(this);



    QObject::connect(&meterTimer,SIGNAL(timeout()),&scene,SLOT(advance()));
    QObject::connect(&closeButton,SIGNAL(mousePress()),this,SLOT(closeMetersView()));

    meterTimer.start(1000/8);

}

Home::~Home()
{
    delete ui;
}

void Home::showEx()
{
#ifdef DEBUG
    show();
#else
    showFullScreen();
#endif
}

void  Home::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.fillRect(0,0,800,480,Qt::black);
    painter.drawPixmap(60,160,picture,175,155,470,95);
    create();

}

 void Home::closeMetersView()
 {
     HardWare::pTimer->stop();
     view.hide();
 }

void Home::on_pushButton_calculator_clicked()
{
    Calculator calcu;
    calcu.exec();

}

void Home::on_pushButton_meter_clicked()
{
    HardWare::pTimer->start();
    view.show();
}

void Home::on_pushButton_meter_2_clicked()
{
    dataDealWin.showEx();
}

void Home::on_pushButton_calculator_2_clicked()
{
    SettingWin settingWin;
    settingWin.showEx();
}

void Home::on_pushButton_calculator_3_clicked()
{
    HelpWin helpWin;
    helpWin.showEx();

}
