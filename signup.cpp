#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    setWindowTitle("Sign Up");
    resize(400,250);
    setMinimumSize(400,250);
    setMaximumSize(600,450);

    lblName = new QLabel(this);
    lblName->setGeometry(10,10,200,30);
    lblName->setText("Enter Name :");

    lblUsername = new QLabel(this);
    lblUsername->setGeometry(10,50,200,30);
    lblUsername->setText("Enter Username :");

    lblPassword = new QLabel(this);
    lblPassword->setGeometry(10,90,200,30);
    lblPassword->setText("Enter Password :");

    lblKey = new QLabel(this);
    lblKey->setGeometry(10,130,200,30);
    lblKey->setText("Enter Key :");

    lblAcc = new QLabel(this);
    lblAcc->setGeometry(100,160,200,30);
    lblAcc->setText("Already have an account? Login now.");

    txtName = new QLineEdit(this);
    txtName->setGeometry(120,10,200,30);

    txtUsername = new QLineEdit(this);
    txtUsername->setGeometry(120,50,200,30);

    txtPassword = new QLineEdit(this);
    txtPassword->setGeometry(120,90,200,30);
    txtPassword->setEchoMode(QLineEdit::Password);

    txtKey = new QLineEdit(this);
    txtKey->setGeometry(120,130,200,30);

    btnSignUp = new QPushButton(this);
    btnSignUp->setGeometry(130,190,150,30);
    btnSignUp->setText("Sign Up");

}

SignUp::~SignUp()
{
    delete ui;
}
