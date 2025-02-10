#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    Ui::Dashboard *ui;
    QLabel *lblDashboard;
    QLabel *lblWorkoutPlans;
    QLabel *lblChallenges;
    QLabel *lblBuyProduct;
    QLabel *lblCalorieTracker;
    QLabel *lblSettings;

    QLabel *lblWelcome;
    QLabel *lblCurrentWorkouts;
    QLabel *lblCurrentChallenges;
};

#endif // DASHBOARD_H
