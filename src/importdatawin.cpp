#include "QMessageBox"

#include "importdatawin.h"
#include "ui_importdatawin.h"

#include "meter.h"


ImportDataWin::ImportDataWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDataWin)
{
    ui->setupUi(this);
}

ImportDataWin::~ImportDataWin()
{
    delete ui;
}


void ImportDataWin::showEx(int columnCount)
{
    setWindowTitle("导入数据");
    bool isHasData = false;
    for(int i=0; i<4; i++)
    {
        if(Meter::meters[i]->ValueSamples.size()>0)
        {
            ui->comboBox->addItem(Meter::meters[i]->getChannelName());
            pmeters.append(Meter::meters[i]);
            datatype.append(0);
            if(Meter::meters[i]->sampleCycle != 0)
            {
                ui->comboBox->addItem(Meter::meters[i]->getChannelName()+"时间");
                pmeters.append(Meter::meters[i]);
                datatype.append(1);
            }
            isHasData = true;
        }
    }
    if(isHasData)
    {
        for(int i=1; i<=columnCount; i++)
        {
            QString str = QString::number(i);
            ui->comboBox_2->addItem(str);
        }
        exec();
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("提示");
        msgbox.setText("你还没有记录数据!");
        msgbox.exec();
    }
}

void ImportDataWin::on_pushButton_2_clicked()//取消
{
    hide();
}

void ImportDataWin::on_pushButton_clicked()//确定
{
    switch(datatype[ui->comboBox->currentIndex()])
    {
    case 0:
        emit importData(ui->comboBox_2->currentIndex(),pmeters[ui->comboBox->currentIndex()]);
        break;
    case 1:
        emit importTimeData(ui->comboBox_2->currentIndex(),pmeters[ui->comboBox->currentIndex()]);
        break;
    }
    hide();
}
