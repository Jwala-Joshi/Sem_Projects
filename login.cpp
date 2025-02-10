#include "login.h"
#include "ui_login.h"

#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    resize(400,200);
    setMinimumSize(400,200);
    setMaximumSize(500,350);

    lblUsername = new QLabel(this);
    lblUsername->setGeometry(10,10,200,30);
    lblUsername->setText("Enter Username :");

    lblPassword = new QLabel(this);
    lblPassword->setGeometry(10,50,200,30);
    lblPassword->setText("Enter Password :");

    lblNoAcc = new QLabel(this);
    lblNoAcc->setGeometry(80,80,200,30);
    lblNoAcc->setText("Don't have an account? Sign Up now.");

    txtUsername = new QLineEdit(this);
    txtUsername->setGeometry(120,10,200,30);

    txtPassword = new QLineEdit(this);
    txtPassword->setGeometry(120,50,200,30);
    txtPassword->setEchoMode(QLineEdit::Password);

    btnLogin = new QPushButton(this);
    btnLogin->setGeometry(130,120,150,30);
    btnLogin->setText("Login");

    lblError = new QLabel(this);
    lblError->setGeometry(120,150,200,30);


}

Login::~Login()
{
    delete ui;
}
