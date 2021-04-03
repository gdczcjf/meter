/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created: Wed Jul 18 20:35:46 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    QLabel *label_3;

    void setupUi(QDialog *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->resize(461, 245);
        comboBox = new QComboBox(Setting);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 20, 101, 25));
        label = new QLabel(Setting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 71, 21));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        buttonBox = new QDialogButtonBox(Setting);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(285, 202, 161, 31));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBox = new QSpinBox(Setting);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(130, 70, 101, 25));
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);
        spinBox->setValue(10);
        label_3 = new QLabel(Setting);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 91, 21));
        label_3->setFont(font);

        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QDialog *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "Dialog", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Setting", "1    Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Setting", "5    Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Setting", "10  Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Setting", "20  Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Setting", "50  Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Setting", "100Hz", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("Setting", "\350\256\241\346\227\266\351\242\221\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Setting", "\350\256\260\345\275\225\346\225\260\347\202\271\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
