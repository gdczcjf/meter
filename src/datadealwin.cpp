#include <QStringList>
#include <QMessageBox>


#include "datadealwin.h"
#include "ui_datadealwin.h"

#include "meter.h"
#include "importdatawin.h"
#include "calucwin.h"
#include "dataoperate.h"
#include "keyboard.h"
#include "qmath.h"

const int initRowNum=12;
const int initColumnNum=6;


DataDealWin::DataDealWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDealWin)
{   
    ui->setupUi(this);
    figure.setParent(ui->tab_2);
    ui->tabWidget->setCurrentIndex(0);
    QObject::connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(dataOperator(int,int)));
    resetTable();
    resetTable2();

}

DataDealWin::~DataDealWin()
{
    delete ui;
}

void DataDealWin::showEx()
{

    ui->tabWidget->setCurrentIndex(0);
    table2Updata(0);
    table2Updata(1);
    table2Updata(2);
    table2Updata(3);

    this->setModal(true);
#ifdef DEBUG
    this->show();
#else
    this->showFullScreen();
#endif
}
void DataDealWin::resetTable()
{
    items.clear();
    ui->tableWidget->setColumnCount(initColumnNum);
    ui->tableWidget->setRowCount(initRowNum);
    for(int c=0;c<initColumnNum;c++)
    {
        QList<TableWidgetItem> itemlist;
        items.append(itemlist);
        for(int r = 0; r < initRowNum; r++)
        {
            TableWidgetItem item;
            //item.setText(QString::number(r));//debug
            items[c].append(item);
            ui->tableWidget->setItem(r,c,&items[c].last());
        }
    }
}
void DataDealWin::resetTable2()
{
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setRowCount(SAPMPLE_COUNT);
    for(int c=0;c<4;c++)
    {
        ui->tableWidget_2->setHorizontalHeaderItem(c,&meterNames[c]);
        for(int r = 0; r <SAPMPLE_COUNT; r++)
        {
            ui->tableWidget_2->setItem(r,c,&meterDataItems[c][r]);
        }
    }
}

void DataDealWin::insertColumn(int c)
{
    ui->tableWidget->insertColumn(c);
    QList<TableWidgetItem> itemList;
    items.insert(c,itemList);
    QList<TableWidgetItem>  &newItemList=items[c];


    for(int r=0; r < ui->tableWidget->rowCount(); r++)
    {
        TableWidgetItem item;
        //item.setText("c");//debug
        newItemList.append(item);
        ui->tableWidget->setItem(r,c,&(newItemList.last()));
    }
}

void DataDealWin::insertRow(int r)
{
    ui->tableWidget->insertRow(r);
    int c=0;
    for(QList< QList<TableWidgetItem> >::iterator i = items.begin(); i!=items.end(); i++)
    {

        QList<TableWidgetItem> &itemList = *i;
        TableWidgetItem item;
        //item.setText("b");//debug
        itemList.insert(r,item);
        ui->tableWidget->setItem(r,c,&itemList[r]);
        c++;
    }
}
void DataDealWin::cleanColumn(int c)
{
    QList<TableWidgetItem> &itemList=items[c];


    for(QList<TableWidgetItem>::iterator i = itemList.begin(); i!=itemList.end(); i++)
    {
        TableWidgetItem &item = *i;
        item.reset();
    }
}

void DataDealWin::cleanRow(int r)
{
    for(QList< QList<TableWidgetItem> >::iterator i = items.begin(); i!=items.end(); i++)
    {
        QList<TableWidgetItem> &itemList = *i;
        itemList[r].setValueAndText("",0.0);
    }
}
void DataDealWin::removeColumn(int c)
{
    if(ui->tableWidget->columnCount() > 1)
    {
        items.removeAt(c);
        ui->tableWidget->removeColumn(c);
    }
}

void DataDealWin::removeRow(int r)
{
    if(ui->tableWidget->rowCount() > 1)
    {
        for(QList< QList<TableWidgetItem> >::iterator i = items.begin(); i!=items.end(); i++)
        {

            QList<TableWidgetItem> &itemList = *i;
            itemList.removeAt(r);
        }
        ui->tableWidget->removeRow(r);
    }
}

void DataDealWin::dataOperator(int row,int column)
{
    int i;
    DataOperate Win;
    i=Win.showEx(/*items[column][row].isReadOnly()*/);
    switch(i)
    {
    case 1:
        cleanRow(row);
        break;
    case 2:
        removeRow(row);
        break;
    case 3:
        cleanColumn(column);
        break;
    case 4:
        removeColumn(column);
        break;
    case 5:
        insertRow(row);
        break;
    case 6:
        insertColumn(column);
        break;
    case 7:
        insertRow(row+1);
        break;
    case 8:
        insertColumn(column+1);
        break;
    case 9:
    {
        Keyboard keyboardWin;
        QObject::connect(&keyboardWin,SIGNAL(enter(Keyboard*)),this,SLOT(editNextItem(Keyboard*)));
        keyboardWin.showEx(&items[column][row]);
        QObject::disconnect(&keyboardWin,SIGNAL(enter(Keyboard*)),this,SLOT(editNextItem(Keyboard*)));
    }
        break;
    case 10:
        resetTable();
        break;

    }

}

void DataDealWin::table2Updata(int MeterID)
{
    meterNames[MeterID].setText("电表"+QString::number(MeterID+1)+"\n"+Meter::meters[MeterID]->getChannelName());

    for(int r=0; r < SAPMPLE_COUNT; r++)
    {
        if(r < Meter::meters[MeterID]->ValueSamples.count())
            meterDataItems[MeterID][r].setText(Meter::meters[MeterID]->getValueText(Meter::meters[MeterID]->ValueSamples[r]));
        else
            meterDataItems[MeterID][r].setText("");
    }
}


void DataDealWin::importData(int column,Meter *pMeter)
{

    if(pMeter->ValueSamples.size()==0)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("提示");
        msgbox.setText(pMeter->getChannelName()+":没有数据!");
        msgbox.exec();
        return;
    }

    if(column < ui->tableWidget->columnCount())
    {
        if(column == ui->tableWidget->columnCount()-1)
            insertColumn(ui->tableWidget->columnCount());
        QList<TableWidgetItem> &ItemList = items[column];

        for(int i = ui->tableWidget->rowCount(); i < pMeter->ValueSamples.count(); i++)
        {
            insertRow(ui->tableWidget->rowCount());
        }
        int index = 0;
        for(QList<TableWidgetItem>::iterator i = ItemList.begin(); i != ItemList.end(); i++)
        {
            TableWidgetItem &item=*i;
            if(index < pMeter->ValueSamples.count())
                item.setValueAndText(pMeter->getValueText(pMeter->ValueSamples[index]),pMeter->ValueSamples[index]);
            else
                item.setText("");
            index++;
        }

    }
}

void DataDealWin::importTimeData(int column,Meter *pMeter)
{

    if(pMeter->ValueSamples.size()==0)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("提示");
        msgbox.setText(pMeter->getChannelName()+":没有数据!");
        msgbox.exec();
        return;
    }

    if(column < ui->tableWidget->columnCount())
    {
        if(column == ui->tableWidget->columnCount()-1)
            insertColumn(ui->tableWidget->columnCount());
        QList<TableWidgetItem> &ItemList = items[column];

        for(int i = ui->tableWidget->rowCount(); i < pMeter->ValueSamples.count(); i++)
        {
            insertRow(ui->tableWidget->rowCount());
        }
        int index = 0;
        for(QList<TableWidgetItem>::iterator i = ItemList.begin(); i != ItemList.end(); i++)
        {
            TableWidgetItem &item=*i;
            QString str;
            if(index < pMeter->ValueSamples.count())
            {
                str=QString::number(index*pMeter->sampleCycle/1000);
                item.setValueAndText(str,index*pMeter->sampleCycle/1000);
            }
            else
                item.setText("");
            index++;
        }

    }
}
void DataDealWin::dataCalcu(int a,int oper,int b,int c)
{
    switch(oper)
    {
    case 0://+
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "")
            {
                double res;
                res=items[a][r].getValue() + items[b][r].getValue();
                items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 1://-
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "")
            {
                double res;
                res=items[a][r].getValue() - items[b][r].getValue();
                items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 2://*
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "")
            {
                double res;
                res=items[a][r].getValue() * items[b][r].getValue();
                items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 3://除
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "" && items[b][r].getValue() != 0)
            {
                    double res;
                    res=items[a][r].getValue() / items[b][r].getValue();
                    items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 4://a^2*b
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "")
            {
                    double res;
                    res=items[a][r].getValue() * items[a][r].getValue() * items[b][r].getValue();
                    items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 5://a^2/b
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" && items[b][r].text() != "" && items[b][r].getValue() != 0)
            {
                    double res;
                    res=items[a][r].getValue() * items[a][r].getValue() / items[b][r].getValue();
                    items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 6://a^2
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "")
            {
                    double res;
                    res=items[a][r].getValue() * items[a][r].getValue();
                    items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    case 7://sqrt (a)
        for(int r=0; r < ui->tableWidget->rowCount(); r++)
        {
            if(items[a][r].text() != "" &&  items[a][r].getValue() >= 0)
            {
                    double res;

                    res= sqrt(items[a][r].getValue());
                    items[c][r].setValueAndText(QString::number(res),res);
            }
            else
            {
                items[c][r].setValueAndText("",0);
            }
        }
        break;
    }
}
void  DataDealWin::editNextItem(Keyboard *keyboard)
{
    if(ui->tableWidget->currentRow() == ui->tableWidget->rowCount()-1)
    {
        insertRow(ui->tableWidget->rowCount());
    }
    ui->tableWidget->setCurrentCell(ui->tableWidget->currentRow()+1,ui->tableWidget->currentColumn());
    keyboard->changeItem(&items[ui->tableWidget->currentColumn()][ui->tableWidget->currentRow()]);
}


void DataDealWin::on_pushButton_2_clicked()//导入数据
{
    ImportDataWin win;
    QObject::connect(&win,SIGNAL(importData(int,Meter*)),this,SLOT(importData(int,Meter*)));
    QObject::connect(&win,SIGNAL(importTimeData(int,Meter*)),this,SLOT(importTimeData(int,Meter*)));
    win.showEx(ui->tableWidget->columnCount());
    QObject::disconnect(&win,SIGNAL(importData(int,Meter*)),this,SLOT(importData(int,Meter*)));
    QObject::disconnect(&win,SIGNAL(importTimeData(int,Meter*)),this,SLOT(importTimeData(int,Meter*)));
}

void DataDealWin::on_pushButton_clicked()//退出
{
    hide();
}


void DataDealWin::on_pushButton_3_clicked()//计算
{
    CalucWin win;
    QObject::connect(&win,SIGNAL(dataCalcu(int,int,int,int)),this,SLOT(dataCalcu(int,int,int,int)));
    win.showEx(ui->tableWidget->columnCount());
    QObject::disconnect(&win,SIGNAL(dataCalcu(int,int,int,int)),this,SLOT(dataCalcu(int,int,int,int)));

}

void DataDealWin::on_tabWidget_currentChanged(int index)
{
    if(index==2)
    {
        while(ui->comboBox->count()-5 > ui->tableWidget->columnCount())
        {
            ui->comboBox->removeItem(ui->comboBox->count()-1);
        }
        while(ui->comboBox_2->count()-5 > ui->tableWidget->columnCount())
        {
            ui->comboBox_2->removeItem(ui->comboBox_2->count()-1);
        }

        while(ui->comboBox->count()-5 < ui->tableWidget->columnCount())
        {
            ui->comboBox->addItem("数据列"+QString::number(ui->comboBox->count()-5+1));
        }
        while(ui->comboBox_2->count()-5 < ui->tableWidget->columnCount())
        {
            ui->comboBox_2->addItem("数据列"+QString::number(ui->comboBox_2->count()-5+1));
        }
    }
}

void DataDealWin::on_pushButton_6_clicked()
{
    int xIndex;
    int yIndex;
    xIndex = ui->comboBox->currentIndex();
    yIndex = ui->comboBox_2->currentIndex();
    //错误组合
    if(xIndex < 4)
    {
        if(Meter::meters[xIndex]->ValueSamples.count()==0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText(ui->comboBox->currentText()+"没有数据。");
            msgBox.exec();
            return;
        }
    }
    else if(xIndex == 4)
    {
        if(yIndex >= 4 || Meter::meters[yIndex]->sampleCycle==0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText("Ｘ轴没有Ｙ轴对应的时间数据。");
            msgBox.exec();
            return;
        }
    }
    else if(xIndex >4)
    {
        if(items[xIndex-5].first().text()=="")
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText(ui->comboBox->currentText()+"没有数据或第一个数据为空。");
            msgBox.exec();
            return;
        }
    }

    if(yIndex < 4 )
    {
        if(Meter::meters[yIndex]->ValueSamples.count()==0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText(ui->comboBox_2->currentText()+"没有数据。");
            msgBox.exec();
            return;
        }
    }
    else if(yIndex == 4)
    {
        if(xIndex >= 4 || Meter::meters[xIndex]->sampleCycle==0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText("Y轴没有X轴对应的时间数据。");
            msgBox.exec();
            return;
        }
    }
    else if(yIndex >4)
    {
        if(items[yIndex-5].first().text()=="")
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误：");
            msgBox.setText(ui->comboBox_2->currentText()+"没有数据或第一个数据为空。");
            msgBox.exec();
            return;
        }
    }

    //生成数据Vector
    xData.clear();
    yData.clear();
    if(xIndex < 4)
    {
        xData = Meter::meters[xIndex]->ValueSamples;
    }
    else if(xIndex == 4)
    {
        double cycle = Meter::meters[yIndex]->sampleCycle/1000.0;
        for(int i=0; i< Meter::meters[yIndex]->ValueSamples.count(); i++)
        {
            xData.append(cycle*i);
        }
    }
    else if(xIndex > 4)
    {
        QList<TableWidgetItem> &itemList = items[xIndex-5];

        for( QList<TableWidgetItem>::iterator i = itemList.begin(); i!= itemList.end(); i++)
        {
            TableWidgetItem &item=*i;
            if(item.text() != "")
            {
                xData.append(item.getValue());
            }
            else
            {
                break;
            }
        }
    }

    if(yIndex < 4)
    {
        yData = Meter::meters[yIndex]->ValueSamples;
    }
    else if(yIndex == 4)
    {
        double cycle = Meter::meters[xIndex]->sampleCycle/1000.0;
        for(int i=0; i< Meter::meters[xIndex]->ValueSamples.count(); i++)
        {
            yData.append(cycle*i);
        }
    }
    else if(yIndex > 4)
    {
        QList<TableWidgetItem> &itemList = items[yIndex-5];

        for( QList<TableWidgetItem>::iterator i = itemList.begin(); i!= itemList.end(); i++)
        {
            TableWidgetItem &item=*i;
            if(item.text() != "")
            {
                yData.append(item.getValue());
            }
            else
            {
                break;
            }
        }
    }

    //错误检杳
    if(xData.count() != yData.count())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误：");
        msgBox.setText(ui->comboBox->currentText()+"和"+ui->comboBox_2->currentText()+"数据个数不相同。");
        msgBox.exec();
        return;
    }

    //作图
    figure.drawFigure(&xData,&yData,ui->comboBox_3->currentIndex(),ui->comboBox_4->currentIndex(),ui->comboBox_5->currentIndex());

}

void DataDealWin::on_pushButton_8_clicked()
{
    static int num=0;
    QMessageBox messageBox;
    QPixmap pixmap;
    QString fileName;
#ifdef DEBUG
    fileName = "pic/"+QString::number(num)+".png";
#else
    fileName = "/root/Documents/udisk/"+QString::number(num)+".png";
#endif
    pixmap= figure.grab();

    if(pixmap.save(fileName,"png"))
    {

        messageBox.setText(fileName + "成功保存。");
        num++;
    }
    else
    {
        messageBox.setText("保存失败。");
    }
    messageBox.exec();
}

void DataDealWin::on_pushButton_9_clicked()
{
    figure.cleanFigure();
}
