/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClear;
    QAction *action2px;
    QAction *action5px;
    QAction *action10px;
    QAction *actionBlack;
    QAction *actionWhite;
    QAction *actionRed;
    QAction *actionGreen;
    QAction *actionBlue;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *recognitionDisplay;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuBrush;
    QMenu *menuSize;
    QMenu *menuColour;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(570, 440);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        action2px = new QAction(MainWindow);
        action2px->setObjectName(QStringLiteral("action2px"));
        action5px = new QAction(MainWindow);
        action5px->setObjectName(QStringLiteral("action5px"));
        action10px = new QAction(MainWindow);
        action10px->setObjectName(QStringLiteral("action10px"));
        actionBlack = new QAction(MainWindow);
        actionBlack->setObjectName(QStringLiteral("actionBlack"));
        actionWhite = new QAction(MainWindow);
        actionWhite->setObjectName(QStringLiteral("actionWhite"));
        actionRed = new QAction(MainWindow);
        actionRed->setObjectName(QStringLiteral("actionRed"));
        actionGreen = new QAction(MainWindow);
        actionGreen->setObjectName(QStringLiteral("actionGreen"));
        actionBlue = new QAction(MainWindow);
        actionBlue->setObjectName(QStringLiteral("actionBlue"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        pushButton_3->setFont(font);

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(80, 30));
        pushButton_4->setFont(font);

        verticalLayout->addWidget(pushButton_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(80, 30));
        pushButton->setFont(font);
        pushButton->setAutoFillBackground(false);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(80, 30));
        pushButton_2->setFont(font);

        verticalLayout->addWidget(pushButton_2);

        recognitionDisplay = new QLabel(centralWidget);
        recognitionDisplay->setObjectName(QStringLiteral("recognitionDisplay"));
        recognitionDisplay->setMaximumSize(QSize(300, 80));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(14);
        recognitionDisplay->setFont(font1);

        verticalLayout->addWidget(recognitionDisplay);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuBrush = new QMenu(menuBar);
        menuBrush->setObjectName(QStringLiteral("menuBrush"));
        menuSize = new QMenu(menuBrush);
        menuSize->setObjectName(QStringLiteral("menuSize"));
        menuColour = new QMenu(menuBrush);
        menuColour->setObjectName(QStringLiteral("menuColour"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuHelp->menuAction());
        menuBar->addAction(menuBrush->menuAction());
        menuHelp->addAction(actionAbout);
        menuBrush->addAction(menuSize->menuAction());
        menuBrush->addAction(menuColour->menuAction());
        menuSize->addAction(action2px);
        menuSize->addAction(action5px);
        menuSize->addAction(action10px);
        menuColour->addAction(actionBlack);
        menuColour->addAction(actionRed);
        menuColour->addAction(actionGreen);
        menuColour->addAction(actionBlue);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(clear_click()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(recognize_click()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), MainWindow, SLOT(load_click()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), MainWindow, SLOT(train_click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        action2px->setText(QApplication::translate("MainWindow", "2px", 0));
        action5px->setText(QApplication::translate("MainWindow", "5px", 0));
        action10px->setText(QApplication::translate("MainWindow", "10px", 0));
        actionBlack->setText(QApplication::translate("MainWindow", "Black", 0));
        actionWhite->setText(QApplication::translate("MainWindow", "White", 0));
        actionRed->setText(QApplication::translate("MainWindow", "Red", 0));
        actionGreen->setText(QApplication::translate("MainWindow", "Green", 0));
        actionBlue->setText(QApplication::translate("MainWindow", "Blue", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "about", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "load", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "train", 0));
        pushButton->setText(QApplication::translate("MainWindow", "clear", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "recognize", 0));
        recognitionDisplay->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuBrush->setTitle(QApplication::translate("MainWindow", "Br&ush", 0));
        menuSize->setTitle(QApplication::translate("MainWindow", "Size", 0));
        menuColour->setTitle(QApplication::translate("MainWindow", "Colour", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
