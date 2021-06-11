/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QWidget *centralWidget;
    QFrame *rysujFrame;
    QGroupBox *groupBox;
    QPushButton *cleanButton;
    QPushButton *exitButton;
    QRadioButton *RadioButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QString::fromUtf8("MyWindow"));
        MyWindow->resize(883, 682);
        centralWidget = new QWidget(MyWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        rysujFrame = new QFrame(centralWidget);
        rysujFrame->setObjectName(QString::fromUtf8("rysujFrame"));
        rysujFrame->setGeometry(QRect(10, 10, 600, 600));
        rysujFrame->setFrameShape(QFrame::StyledPanel);
        rysujFrame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(630, 10, 241, 321));
        cleanButton = new QPushButton(groupBox);
        cleanButton->setObjectName(QString::fromUtf8("cleanButton"));
        cleanButton->setGeometry(QRect(84, 260, 81, 23));
        exitButton = new QPushButton(groupBox);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(84, 290, 81, 23));
        RadioButton = new QRadioButton(groupBox);
        RadioButton->setObjectName(QString::fromUtf8("RadioButton"));
        RadioButton->setGeometry(QRect(40, 70, 121, 23));
        RadioButton->setChecked(true);
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(40, 100, 121, 23));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(40, 130, 95, 23));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(40, 160, 95, 23));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(40, 190, 131, 21));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(70, 40, 151, 23));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 160, 45, 26));
        MyWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 883, 22));
        MyWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyWindow->setStatusBar(statusBar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QApplication::translate("MyWindow", "MyWindow", nullptr));
        groupBox->setTitle(QApplication::translate("MyWindow", "Menu", nullptr));
        cleanButton->setText(QApplication::translate("MyWindow", "Czy\305\233\304\207", nullptr));
        exitButton->setText(QApplication::translate("MyWindow", "Wyj\305\233cie", nullptr));
        RadioButton->setText(QApplication::translate("MyWindow", "Odcinek", nullptr));
        radioButton->setText(QApplication::translate("MyWindow", "Okrag", nullptr));
        radioButton_2->setText(QApplication::translate("MyWindow", "Elipsa", nullptr));
        radioButton_3->setText(QApplication::translate("MyWindow", "Wielokat", nullptr));
        radioButton_4->setText(QApplication::translate("MyWindow", "Wielokat w Elipsie", nullptr));
        checkBox->setText(QApplication::translate("MyWindow", "Dynamiczne Rysowanie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
