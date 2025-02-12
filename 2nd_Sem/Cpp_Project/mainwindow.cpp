#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cstring>
#include<cstdlib>
#include <QMessageBox>
#include "backend.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gym Management System");
    resize(400,300);

    ui->txtPassword->setEchoMode(QLineEdit::EchoMode::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

user login(){
    char userName[100];
    char password[100];
    int key;


    user u = getUserDetails(userName,password,key);//in header file
    if(strcmp(u.getUserName(),"")==0){
        QMessageBox loginError;
        loginError.setText("User Not Found! Signup");
        loginError.exec();
        exit(0);
    }
    return u;
}

void MainWindow::on_boxEnter_clicked()
{
    QString username,password;
    int key;
    username = ui->txtUsername->text();
    password = ui->txtPassword->text();
    key = ui->txtKey->text().toInt();
    user u;
    u = login();
    char* userName = u.getUserName();
    QMessageBox loginOk;
    loginOk.setText("Welcome");
    loginOk.setText(QString(username));
    loginOk.exec();
}

