#ifndef IMPORTDATAWIN_H
#define IMPORTDATAWIN_H

#include <QDialog>
#include <QVector>

class Meter;

namespace Ui {
class ImportDataWin;
}

class ImportDataWin : public QDialog
{
    Q_OBJECT
signals:
    void importData(int column,Meter *pMeter);
    void importTimeData(int column,Meter *pMeter);
public:
    explicit ImportDataWin(QWidget *parent = 0);
    ~ImportDataWin();
    void showEx(int columnCout);
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ImportDataWin *ui;
    QVector<Meter *> pmeters;
    QVector<int>  datatype;

};

#endif // IMPORTDATAWIN_H
