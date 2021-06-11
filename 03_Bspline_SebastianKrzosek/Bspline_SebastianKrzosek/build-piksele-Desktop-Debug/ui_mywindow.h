/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QStringLiteral("MyWindow"));
        MyWindow->resize(883, 682);
        centralWidget = new QWidget(MyWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        rysujFrame = new QFrame(centralWidget);
        rysujFrame->setObjectName(QStringLiteral("rysujFrame"));
        rysujFrame->setGeometry(QRect(10, 10, 600, 600));
        rysujFrame->setFrameShape(QFrame::StyledPanel);
        rysujFrame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(630, 10, 241, 191));
        cleanButton = new QPushButton(groupBox);
        cleanButton->setObjectName(QStringLiteral("cleanButton"));
        cleanButton->setGeometry(QRect(80, 50, 75, 23));
        exitButton = new QPushButton(groupBox);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(80, 80, 75, 23));
        MyWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 883, 22));
        MyWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyWindow->setStatusBar(statusBar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QApplication::translate("MyWindow", "MyWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MyWindow", "Menu", Q_NULLPTR));
        cleanButton->setText(QApplication::translate("MyWindow", "Czy\305\233\304\207", Q_NULLPTR));
        exitButton->setText(QApplication::translate("MyWindow", "Wyj\305\233cie", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
