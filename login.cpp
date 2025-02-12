#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include "backend.h"
#include "dashboard.h"

#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    //Design
    ui->setupUi(this);
    setWindowTitle("Login");
    resize(400,200);
    setMinimumSize(400,200);
    setMaximumSize(500,350);
    setWindowIcon(QIcon(":/resources/icons/main logo.png"));

    lblUsername = new QLabel(this);
    lblUsername->setGeometry(10,10,200,30);
    lblUsername->setText("Enter Username :");

    lblPassword = new QLabel(this);
    lblPassword->setGeometry(10,50,200,30);
    lblPassword->setText("Enter Password :");

    lblNoAcc = new QLabel(this);
    lblNoAcc->setGeometry(80,80,200,30);
    lblNoAcc->setText("Don't have an account? <a href='signup'><i>Sign Up</i></a> now.");
    lblNoAcc->setTextFormat(Qt::RichText);
    lblNoAcc->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lblNoAcc->setOpenExternalLinks(false);

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

    connect(lblNoAcc, &QLabel::linkActivated, this, &Login::onSignUpClicked);
    connect(btnLogin, &QPushButton::clicked, this, &Login::onbtnLoginClicked);

    //Logics
}

Login::~Login()
{
    delete ui;
}

void Login::onSignUpClicked(const QString &link)
{
    if (link == "signup") {
        SignUp *signUp = new SignUp();
        signUp->show();
        this->close();
    }
}

void Login::onbtnLoginClicked(){
    QString username = txtUsername->text();
    QString password = txtPassword->text();

    user u = getUserDetails( const_cast<char*>(username.toStdString().c_str()), const_cast<char*>(password.toStdString().c_str()));

    if(strcmp(u.getUserName(),"")==0 ) {
        lblError->setText("Invalid username or password!");
        lblError->setStyleSheet("color: red;");
        // lblError->setText(QString(u.getUserName()) + " WTF");
    }
    else {
        lblError->clear();

        if(u.getIsAdmin()) {
            QMessageBox::information(this, "Login Successful", "Welcome, " + QString(username) +"!");
            Dashboard *dashboard = new Dashboard();
            dashboard->setUsername(username);
            dashboard->show();
            this->close();
        }
        // else if (u.getIsMember()) {
        else {
            QMessageBox::information(this, "Login Successful", "Welcome, " + QString(username) +"!");
            Dashboard *dashboard = new Dashboard();
            dashboard->setUsername(username);
            dashboard->show();
            this->close();
        }
        // else {
        //     lblError->setText("Access denied! Please contact admin.");
        //     lblError->setStyleSheet("color: red;");
        // }
    }
}
