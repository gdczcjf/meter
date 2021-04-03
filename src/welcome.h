#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QTimer>
#include <QVector>

#define PIC_NUM 27

class Welcome : public QDialog
{
    Q_OBJECT
    
public:
    Welcome(QWidget *parent = 0);
    ~Welcome();

    void loadPic();
    void preShow();
    void showEx();
    QDialog *dia;
protected:
    void paintEvent(QPaintEvent *);

private:
    QVector<QPixmap> pictures;
    int picture_num;
    QTimer timer;

private slots:
    void changePic();
};

#endif // WELCOME_H
