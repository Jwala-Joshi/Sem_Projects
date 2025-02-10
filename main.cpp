// #include "mainwindow.h"
// #include "login.h"
// #include "signup.h"
#include "dashboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dashboard d;
    d.show();
    // SignUp s;
    // s.show();
    // Login l;
    // l.show();
    // MainWindow w;
    // w.show();
    // return a.exec();
    return a.exec();
}
