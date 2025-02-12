/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblUsername;
    QLabel *lblPassword;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLabel *lblKey;
    QLineEdit *txtKey;
    QPushButton *boxEnter;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(335, 295);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lblUsername = new QLabel(centralwidget);
        lblUsername->setObjectName("lblUsername");
        lblUsername->setGeometry(QRect(10, 10, 121, 20));
        lblUsername->setStyleSheet(QString::fromUtf8(""));
        lblPassword = new QLabel(centralwidget);
        lblPassword->setObjectName("lblPassword");
        lblPassword->setGeometry(QRect(10, 50, 111, 20));
        txtUsername = new QLineEdit(centralwidget);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(130, 10, 141, 21));
        txtPassword = new QLineEdit(centralwidget);
        txtPassword->setObjectName("txtPassword");
        txtPassword->setGeometry(QRect(130, 50, 141, 21));
        lblKey = new QLabel(centralwidget);
        lblKey->setObjectName("lblKey");
        lblKey->setGeometry(QRect(10, 90, 111, 20));
        txtKey = new QLineEdit(centralwidget);
        txtKey->setObjectName("txtKey");
        txtKey->setGeometry(QRect(130, 90, 141, 21));
        boxEnter = new QPushButton(centralwidget);
        boxEnter->setObjectName("boxEnter");
        boxEnter->setGeometry(QRect(130, 130, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 335, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblUsername->setText(QCoreApplication::translate("MainWindow", "Enter Username: ", nullptr));
        lblPassword->setText(QCoreApplication::translate("MainWindow", "Enter Password: ", nullptr));
        lblKey->setText(QCoreApplication::translate("MainWindow", "Enter Key:", nullptr));
        boxEnter->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
