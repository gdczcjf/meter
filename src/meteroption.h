#ifndef METEROPTION_H
#define METEROPTION_H

#include <QWidget>


class Meter;

namespace Ui {
class MeterOption;
}

class MeterOption : public QWidget
{
    Q_OBJECT
signals:
    void close();
    void dispValue(bool sw);
    void record();
    void saveValue();
    void changeRange();
    void dispWay(bool fullscreen);
    void deleteRecord();
    
public:
    Ui::MeterOption *ui;

    explicit MeterOption(QWidget *parent = 0);
    ~MeterOption();

    void setFullscreen(bool fullscreen);
    void recordFinish();
    
private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
};

#endif // METEROPTION_H
