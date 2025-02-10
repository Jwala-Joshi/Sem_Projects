#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    QLabel *lblUsername;
    QLabel *lblPassword;
    QLabel *lblNoAcc;
    QLabel *lblError;

    QLineEdit *txtUsername;
    QLineEdit *txtPassword;

    QPushButton *btnLogin;
};

#endif // LOGIN_H
