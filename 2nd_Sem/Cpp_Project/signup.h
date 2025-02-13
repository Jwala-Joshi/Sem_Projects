#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void onLoginClicked(const QString &s_link);
    void onbtnSignUpClicked();

private:
    Ui::SignUp *ui;
    QLabel *lblName;
    QLabel *lblUsername;
    QLabel *lblPassword;
    QLabel *lblConfirmPassword;
    QLabel *lblKey;
    QLabel *lblAcc;

    QLineEdit *txtName;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLineEdit *txtConfirmPassword;
    QLineEdit *txtKey;

    QPushButton *btnSignUp;
};

#endif // SIGNUP_H
