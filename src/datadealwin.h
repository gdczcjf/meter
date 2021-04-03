#ifndef DATADEALWIN_H
#define DATADEALWIN_H

#include <QDialog>

#include "tablewidgetitem.h"
#include "figure.h"

const int SAPMPLE_COUNT = 50;

class Keyboard;
class Meter;

namespace Ui {
class DataDealWin;
}

class DataDealWin : public QDialog
{
    Q_OBJECT
    
public:
    explicit DataDealWin(QWidget *parent = 0);
    ~DataDealWin();
    void showEx();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void importData(int column,Meter *pMeter);
    void importTimeData(int column,Meter *pMeter);
    void dataCalcu(int a,int oper,int b,int c);

    void editNextItem(Keyboard *keyboard);



    void resetTable();
    void resetTable2();



    void insertColumn(int c);
    void insertRow(int r);
    void cleanColumn(int c);
    void cleanRow(int r);
    void removeColumn(int c);
    void removeRow(int r);


    void dataOperator(int row,int column);


    void table2Updata(int MeterID);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::DataDealWin *ui;
    Figure figure;
    QList< QList<TableWidgetItem> > items;

    QTableWidgetItem meterDataItems[4][SAPMPLE_COUNT];
    QTableWidgetItem meterNames[4];

    QVector<double> xData,yData;

};

#endif // DATADEALWIN_H
