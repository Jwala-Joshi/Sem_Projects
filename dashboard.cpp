#include "dashboard.h"
#include "ui_dashboard.h"

#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWidget>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    setWindowTitle("Dashboard");
    setMinimumSize(800,600);

    QWidget *main =new QWidget;
    QVBoxLayout *lytMain = new QVBoxLayout(main);

    QSplitter *split = new QSplitter(Qt::Horizontal);

    QWidget *Menu = new QWidget;
    QVBoxLayout *lytMenu =new QVBoxLayout(Menu);

    QPushButton *btnDashboard = new QPushButton("Dashboard");
    QPushButton *btnWorkoutPlans = new QPushButton("Workout Plans");
    QPushButton *btnChallenges = new QPushButton("Challenges");
    QPushButton *btnBuyProduct = new QPushButton("Buy Product");
    QPushButton *btnCalorieTracker = new QPushButton("Calorie Tracker");
    QPushButton *btnSettings = new QPushButton("Settings");

    lytMenu->addWidget(btnDashboard);
    lytMenu->addWidget(btnWorkoutPlans);
    lytMenu->addWidget(btnChallenges);
    lytMenu->addWidget(btnBuyProduct);
    lytMenu->addWidget(btnCalorieTracker);
    lytMenu->addWidget(btnSettings);
    Menu->setLayout(lytMenu);

    QStackedWidget *contentArea = new QStackedWidget;

    // Create widgets for each content area
    QWidget *dashboardContent = new QWidget;
    QLabel *lblDashboard = new QLabel("Welcome to the Dashboard!", dashboardContent);
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardContent);
    dashboardLayout->addWidget(lblDashboard);

    QWidget *workoutPlansContent = new QWidget;
    QLabel *lblWorkoutPlans = new QLabel("Here are your workout plans!", workoutPlansContent);
    QVBoxLayout *workoutPlansLayout = new QVBoxLayout(workoutPlansContent);
    workoutPlansLayout->addWidget(lblWorkoutPlans);

    QWidget *challengesContent = new QWidget;
    QLabel *lblChallenges = new QLabel("Here are your challenges!", challengesContent);
    QVBoxLayout *challengesLayout = new QVBoxLayout(challengesContent);
    challengesLayout->addWidget(lblChallenges);

    QWidget *buyProductContent = new QWidget;
    QLabel *lblBuyProduct = new QLabel("Buy products here!", buyProductContent);
    QVBoxLayout *buyProductLayout = new QVBoxLayout(buyProductContent);
    buyProductLayout->addWidget(lblBuyProduct);

    QWidget *calorieTrackerContent = new QWidget;
    QLabel *lblCalorieTracker = new QLabel("Track your calories here!", calorieTrackerContent);
    QVBoxLayout *calorieTrackerLayout = new QVBoxLayout(calorieTrackerContent);
    calorieTrackerLayout->addWidget(lblCalorieTracker);

    QWidget *settingsContent = new QWidget;
    QLabel *lblSettings = new QLabel("Settings page.", settingsContent);
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsContent);
    settingsLayout->addWidget(lblSettings);

    // Add all content widgets to QStackedWidget
    contentArea->addWidget(dashboardContent);
    contentArea->addWidget(workoutPlansContent);
    contentArea->addWidget(challengesContent);
    contentArea->addWidget(buyProductContent);
    contentArea->addWidget(calorieTrackerContent);
    contentArea->addWidget(settingsContent);

    // Add widgets to the splitter (menu and content area)
    split->addWidget(Menu);
    split->addWidget(contentArea);

    // Add the splitter to the main layout
    lytMain->addWidget(split);
    setLayout(lytMain);

    // Connect buttons to switch between content
    connect(btnDashboard, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(0);  // Switch to the Dashboard content
    });
    connect(btnWorkoutPlans, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(1);  // Switch to the Workout Plans content
    });
    connect(btnChallenges, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(2);  // Switch to the Challenges content
    });
    connect(btnBuyProduct, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(3);  // Switch to the Buy Product content
    });
    connect(btnCalorieTracker, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(4);  // Switch to the Calorie Tracker content
    });
    connect(btnSettings, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(5);  // Switch to the Settings content
    });
}

Dashboard::~Dashboard()
{
    delete ui;
}
