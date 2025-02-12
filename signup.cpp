#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include "backend.h"
#include "dashboard.h"

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
    lblAcc->setText("Already have an account?<a href='login'><i> Login</i></a> now.");
    lblAcc->setTextFormat(Qt::RichText);
    lblAcc->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lblAcc->setOpenExternalLinks(false);

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

    connect(lblAcc, &QLabel::linkActivated,this ,&SignUp::onLoginClicked);
    connect(btnSignUp, &QPushButton::clicked,this , &SignUp::onbtnSignUpClicked);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::onLoginClicked(const QString &s_link){
    if(s_link == "login") {
        Login *login =new Login();
        login->show();
        this->close();
    }
}

void SignUp::onbtnSignUpClicked() {
    QString name =txtName->text();
    QString username =txtUsername->text();
    QString password =txtPassword->text();
    // QString confirmPassword =txtConfirmPassword->text();
    QString key =txtKey->text();

    user newUser;
    newUser.setData(const_cast<char*>(name.toStdString().c_str()),
                     const_cast<char*>(username.toStdString().c_str()),
                     const_cast<char*>(password.toStdString().c_str()),
                     key.toInt() );
    bool isRegistered = setNewUser(newUser);
    if(!isRegistered) {
        QMessageBox::critical(this, "Sign Up Unsuccessful","Please Try Again!");
    }
    else {
    QMessageBox::information(this, "Sign Up Successful", "Welcome, username!");
    Dashboard *dashboard = new Dashboard();
    dashboard->show();
    this->close();
    }
}
