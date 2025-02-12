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
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
    void setUsername(const QString &username);

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

    QWidget *currentWorkoutsWidget;
    QWidget *currentChallengesWidget;

    QVBoxLayout *lytWorkouts;
    QVBoxLayout *lytChallenges;
};

#endif // DASHBOARD_H
