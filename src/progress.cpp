#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);
}

Progress::~Progress()
{
    delete ui;
}

void Progress::showEx()
{
    this->setModal(true);
    this->setWindowTitle("请稍等....(采集过程不要触摸屏幕)");
    this->setFixedSize(this->width(),this->height());
    ui->progressBar->setValue(0);
    this->show();
}

void Progress::setProgress(int percent)
{
    ui->progressBar->setValue(percent);
    if(percent==100)
        hide();
}


