#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <QGraphicsView>
#include <QTimer>


#include "graphicsitem.h"
#include "meter.h"
#include "datadealwin.h"



namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT
    
public:
    explicit Home(QWidget *parent = 0);
    ~Home();

    void showEx();

protected:
    void paintEvent(QPaintEvent *);


    
private slots:
    void on_pushButton_calculator_clicked();

    void on_pushButton_meter_clicked();

private:
    Ui::Home *ui;

    QTimer meterTimer;
    QGraphicsView view; 
    QGraphicsScene scene;
    GraphicsItem closeButton;
    QPixmap closeButtonBixmap;
    DataDealWin dataDealWin;
    QPixmap picture;

private slots:

    void closeMetersView();


    void on_pushButton_meter_2_clicked();
    void on_pushButton_calculator_2_clicked();
    void on_pushButton_calculator_3_clicked();
};

#endif // HOME_H
