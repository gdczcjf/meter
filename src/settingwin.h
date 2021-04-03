#ifndef SETTINGWIN_H
#define SETTINGWIN_H

#include <QDialog>


struct MeterSetting
{
    float inertance;
    int inertanceIndex;
    int randomType;
    int ValueDispWay;

};



namespace Ui {
class SettingWin;
}

class SettingWin : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingWin(QWidget *parent = 0);
    ~SettingWin();

    static MeterSetting setting;

    static void loadSetting();
    static void saveSetting();
    void showEx();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SettingWin *ui;


    static void setInertance(int i=2);
};

#endif // SETTINGWIN_H
