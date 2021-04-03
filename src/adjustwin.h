#ifndef ADJUSTWIN_H
#define ADJUSTWIN_H

#include <QDialog>



namespace Ui {
class AdjustWin;
}

class AdjustWin : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdjustWin(QWidget *parent = 0);
    ~AdjustWin();


    int showEx();

protected:
    void closeEvent ( QCloseEvent * );
    
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AdjustWin *ui;
    int returnValue;
    bool advance;
    void changeShowWay();


};

#endif // ADJUSTWIN_H
