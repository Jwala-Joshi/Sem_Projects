#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QProgressBar>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(const QString& username,const QString& password,QWidget *parent = nullptr);
    ~Dashboard();

signals:
    void usernameSet();

private slots:

private:
    Ui::Dashboard *ui;

    QLabel *lblWelcome;
    QLabel *lblCurrentWorkouts;
    QLabel *lblCurrentChallenges;
};

#endif // DASHBOARD_H
