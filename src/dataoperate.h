#ifndef DATAOPERATE_H
#define DATAOPERATE_H

#include <QDialog>

namespace Ui {
class DataOperate;
}

class DataOperate : public QDialog
{
    Q_OBJECT
    
public:
    explicit DataOperate(QWidget *parent = 0);
    ~DataOperate();
    int showEx(/*bool readOnly*/);
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::DataOperate *ui;
    int returnValue;
};

#endif // DATAOPERATE_H
