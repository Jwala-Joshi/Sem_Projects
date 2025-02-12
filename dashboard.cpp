#include "dashboard.h"
#include "ui_dashboard.h"
#include "login.h"

#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QProgressBar>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    setWindowTitle("Dashboard");
    setMinimumSize(800,600);

    QWidget *main = new QWidget;
    QVBoxLayout *lytMain = new QVBoxLayout(main);

    QSplitter *split = new QSplitter(Qt::Horizontal);

    QWidget *Menu = new QWidget;
    Menu->setFixedWidth(200);
    QVBoxLayout *lytMenu = new QVBoxLayout(Menu);
    lytMenu->setSpacing(10);

    QPushButton *btnMenu = new QPushButton;
    QIcon menuIcon(":/resources/icons/hamburger-2.png");
    btnMenu->setIcon(menuIcon);
    btnMenu->setText("Menu");
    btnMenu->setIconSize(QSize(20, 20));
    btnMenu->setStyleSheet("QPushButton {background: transparent; border: none;}");
    btnMenu->setFixedHeight(50);

    QPushButton *btnDashboard = new QPushButton("Dashboard");
    QPushButton *btnWorkoutPlans = new QPushButton("Workout Plans");
    QPushButton *btnChallenges = new QPushButton("Challenges");
    QPushButton *btnBuyProduct = new QPushButton("Buy Product");
    QPushButton *btnCalorieTracker = new QPushButton("Calorie Tracker");

    QPushButton *btnSettings = new QPushButton;
    QIcon settingsIcon(":/resources/icons/gear.png");
    btnSettings->setIcon(settingsIcon);
    btnSettings->setText("Settings");
    btnSettings->setIconSize(QSize(20, 20));
    btnSettings->setStyleSheet("QPushButton {background: transparent; border: none;}");
    btnSettings->setFixedHeight(50);

    QString buttonStyle = "QPushButton {"
                          "background: transparent;"
                          "border: none;"
                          "font-size: 16px;"
                          "padding: 8px 16px;"
                          "text-align: left;}"
                          "QPushButton:hover {"
                          "color: #4d4d4d;"
                          "background-color: #8c8c8c;}";

    btnMenu->setStyleSheet(buttonStyle);
    btnDashboard->setStyleSheet(buttonStyle);
    btnWorkoutPlans->setStyleSheet(buttonStyle);
    btnChallenges->setStyleSheet(buttonStyle);
    btnBuyProduct->setStyleSheet(buttonStyle);
    btnCalorieTracker->setStyleSheet(buttonStyle);
    btnSettings->setStyleSheet(buttonStyle);

    lytMenu->addWidget(btnMenu);
    lytMenu->addWidget(btnDashboard);
    lytMenu->addWidget(btnWorkoutPlans);
    lytMenu->addWidget(btnChallenges);
    lytMenu->addWidget(btnBuyProduct);
    lytMenu->addWidget(btnCalorieTracker);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    lytMenu->addItem(spacer);

    lytMenu->addWidget(btnSettings);
    Menu->setLayout(lytMenu);

    QStackedWidget *contentArea = new QStackedWidget;

    QWidget *header = new QWidget;
    header->setFixedHeight(40);
    QHBoxLayout *lytHeader = new QHBoxLayout(header);
    lytHeader->setContentsMargins(10, 0, 0, 0);
    lytHeader->setAlignment(Qt::AlignRight);

    QLabel *lblWelcome = new QLabel(this);
    lblWelcome->setObjectName("lblWelcome");
    lblWelcome->setStyleSheet("font-size: 18px; color: #FFFFFF;");
    lytHeader->addWidget(lblWelcome);

    QPushButton *btnUserIcon = new QPushButton;
    QIcon userIcon(":/resources/icons/user-dark.png");
    btnUserIcon->setIcon(userIcon);
    btnUserIcon->setIconSize(QSize(30, 30));
    btnUserIcon->setStyleSheet("background: white; border: none;" "border-radius: 15px; padding:2px" );

    QMenu *userMenu = new QMenu(this);
    QAction *profile = new QAction("Profile", this);
    QAction *upgrade = new QAction("Upgrade", this);
    QAction *toggle =new QAction("Change Theme",this);
    QAction *setting =new QAction("Settings",this);
    QAction *logOut = new QAction("Log Out",this);
    userMenu->addAction(profile);
    userMenu->addAction(upgrade);
    userMenu->addAction(toggle);
    userMenu->addAction(setting);
    userMenu->addAction(logOut);

    connect(btnUserIcon, &QPushButton::clicked, this, [=]() {
        userMenu->exec(QCursor::pos());
    });
    connect(profile, &QAction::triggered,this,[=]() {
        contentArea->setCurrentIndex(0);
    });
    connect(upgrade, &QAction::triggered,this,[=]() {
        contentArea->setCurrentIndex(3);
        //new window to be created later
        /*
         upgradeWindow *upgrade =new upgradeWindow();
         upgrade->show();
         */
    });
    connect(toggle, &QAction::triggered,this,[=]() {
        static bool darkMode = true;
        if (darkMode) {
            qApp->setStyleSheet("QWidget { background-color: white; color: black; }");
            QIcon menuIcon(":/resources/icons/hamburger.png");
            btnMenu->setIcon(menuIcon);
            QIcon settingsIcon(":/resources/icons/gear-2.png");
            btnSettings->setIcon(settingsIcon);
            darkMode = false;
        } else {
            qApp->setStyleSheet("QWidget { background-color: #1c1b1b; color: white; }");
            QIcon menuIcon(":/resources/icons/hamburger-2.png");
            btnMenu->setIcon(menuIcon);
            QIcon settingsIcon(":/resources/icons/gear.png");
            btnSettings->setIcon(settingsIcon);
            darkMode = true;
        }
    });
    connect(setting, &QAction::triggered,this,[=]() {
        contentArea->setCurrentIndex(5);
    });
    connect(logOut, &QAction::triggered,this,[=]() {
        Login *login =new Login();
        login->show();
        this->close();
    });

    lytHeader->addWidget(btnUserIcon);

    header->setLayout(lytHeader);

    lblCurrentWorkouts = new QLabel("Current Workouts");
    lblCurrentWorkouts->setStyleSheet("font-size: 16px;");

    currentWorkoutsWidget = new QWidget(contentArea);
    lytWorkouts = new QVBoxLayout(currentWorkoutsWidget);

    QLabel *workout_1 = new QLabel("Push-Ups",currentWorkoutsWidget);
    QLabel *workout_2 = new QLabel("Pull-Ups",currentWorkoutsWidget);
    QLabel *workout_3 = new QLabel("Squats",currentWorkoutsWidget);
    QLabel *workout_4 = new QLabel("Bicep Curls",currentWorkoutsWidget);
    QLabel *workout_5 = new QLabel("Crunches",currentWorkoutsWidget);

    QProgressBar *progress_1 = new QProgressBar(currentWorkoutsWidget);
    QProgressBar *progress_2 = new QProgressBar(currentWorkoutsWidget);
    QProgressBar *progress_3 = new QProgressBar(currentWorkoutsWidget);
    QProgressBar *progress_4 = new QProgressBar(currentWorkoutsWidget);
    QProgressBar *progress_5 = new QProgressBar(currentWorkoutsWidget);

    progress_1->setRange(0, 20);
    progress_1->setValue(10);

    progress_2->setRange(0, 20);
    progress_2->setValue(8);

    progress_3->setRange(0, 40);
    progress_3->setValue(15);

    progress_4->setRange(0, 10);
    progress_4->setValue(10);

    progress_5->setRange(0, 30);
    progress_5->setValue(13);

    lytWorkouts->addWidget(workout_1);
    lytWorkouts->addWidget(progress_1);
    lytWorkouts->addWidget(workout_2);
    lytWorkouts->addWidget(progress_2);
    lytWorkouts->addWidget(workout_3);
    lytWorkouts->addWidget(progress_3);
    lytWorkouts->addWidget(workout_4);
    lytWorkouts->addWidget(progress_4);
    lytWorkouts->addWidget(workout_5);
    lytWorkouts->addWidget(progress_5);

    lblCurrentChallenges = new QLabel("Current Challenges");
    lblCurrentChallenges->setStyleSheet("font-size: 16px");

    currentChallengesWidget =new QWidget(contentArea);
    lytChallenges = new QVBoxLayout(currentChallengesWidget);

    QLabel *challenge_1 =new QLabel("30-day Fitness Challenge",currentChallengesWidget);
    QProgressBar *cprogress_1 = new QProgressBar(currentChallengesWidget);
    cprogress_1->setRange(0,30);
    cprogress_1->setValue(10);

    QLabel *challenge_2 =new QLabel("60-day Fitness Challenge",currentChallengesWidget);
    QProgressBar *cprogress_2 = new QProgressBar(currentChallengesWidget);
    cprogress_2->setRange(0,60);
    cprogress_2->setValue(10);

    QLabel *challenge_3 =new QLabel("90-day Fitness Challenge",currentChallengesWidget);
    QProgressBar *cprogress_3 = new QProgressBar(currentChallengesWidget);
    cprogress_3->setRange(0,90);
    cprogress_3->setValue(10);

    lytChallenges->addWidget(challenge_1);
    lytChallenges->addWidget(cprogress_1);
    lytChallenges->addWidget(challenge_2);
    lytChallenges->addWidget(cprogress_2);
    lytChallenges->addWidget(challenge_3);
    lytChallenges->addWidget(cprogress_3);

    QWidget *dashboardContent = new QWidget;
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardContent);
    dashboardLayout->addWidget(header);
    dashboardLayout->addWidget(lblCurrentWorkouts);
    dashboardLayout->addWidget(currentWorkoutsWidget);
    dashboardLayout->addWidget(lblCurrentChallenges);
    dashboardLayout->addWidget(currentChallengesWidget);
    dashboardLayout->addSpacerItem(spacer);

    QWidget *workoutPlansContent = new QWidget;
    QVBoxLayout *workoutPlansLayout = new QVBoxLayout(workoutPlansContent);
    QLabel *lblWorkoutPlans = new QLabel("Workouts", workoutPlansContent);
    lblWorkoutPlans->setStyleSheet("font-size:16px");
    workoutPlansLayout->addWidget(lblWorkoutPlans);
    workoutPlansLayout->addWidget(workout_1);
    workoutPlansLayout->addWidget(workout_2);
    workoutPlansLayout->addWidget(workout_3);
    workoutPlansLayout->addWidget(workout_4);
    workoutPlansLayout->addWidget(workout_5);
    workoutPlansLayout->addSpacerItem(spacer);

    QWidget *challengesContent = new QWidget;
    QVBoxLayout *challengesLayout = new QVBoxLayout(challengesContent);
    QLabel *lblChallenges = new QLabel("Challenges", challengesContent);
    lblChallenges->setStyleSheet("font-size:16px");
    challengesLayout->addWidget(lblChallenges);
    challengesLayout->addWidget(challenge_1);
    challengesLayout->addWidget(challenge_2);
    challengesLayout->addWidget(challenge_3);
    challengesLayout->addSpacerItem(spacer);

    QWidget *buyProductContent = new QWidget;
    QVBoxLayout *buyProductLayout = new QVBoxLayout(buyProductContent);
    QLabel *lblBuyProduct = new QLabel("Buy Products", buyProductContent);
    lblBuyProduct->setStyleSheet("font-size: 16px");

    QWidget *Products = new QWidget(btnBuyProduct);
    QGridLayout *lytProducts = new QGridLayout(Products);

    for (int i = 0; i < 3; ++i) {
        QWidget *productBox = new QWidget(Products);
        QVBoxLayout *productBoxLayout = new QVBoxLayout(productBox);

        QLabel *productImage = new QLabel(productBox);
        productImage->setPixmap(QPixmap(":/resources/icons/dumbbell.jpg").scaled(100, 100, Qt::KeepAspectRatio));
        productImage->setAlignment(Qt::AlignCenter);
        productBoxLayout->addWidget(productImage);

        QLabel *productName = new QLabel("Dumbell 20Kg", productBox);
        productName->setStyleSheet("font-size: 14px;");
        productBoxLayout->addWidget(productName);

        QLabel *productPrice = new QLabel("Rs. 1999", productBox);
        productPrice->setStyleSheet("font-size: 14px;");
        productBoxLayout->addWidget(productPrice);

        QPushButton *btnBuy = new QPushButton("Buy", productBox);
        btnBuy->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
        productBoxLayout->addWidget(btnBuy);

        lytProducts->addWidget(productBox, i / 3, i % 3);
    }

    buyProductLayout->addWidget(lblBuyProduct);
    buyProductLayout->addWidget(Products);
    buyProductLayout->addSpacerItem(spacer);

    QWidget *calorieTrackerContent = new QWidget;
    QVBoxLayout *calorieTrackerLayout = new QVBoxLayout(calorieTrackerContent);
    QLabel *lblCalorieTracker = new QLabel("Track your calories here!", calorieTrackerContent);
    calorieTrackerLayout->addWidget(lblCalorieTracker);

    QWidget *settingsContent = new QWidget;
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsContent);
    QLabel *lblSettings = new QLabel("Settings page.", settingsContent);
    settingsLayout->addWidget(lblSettings);

    contentArea->addWidget(dashboardContent);
    contentArea->addWidget(workoutPlansContent);
    contentArea->addWidget(challengesContent);
    contentArea->addWidget(buyProductContent);
    contentArea->addWidget(calorieTrackerContent);
    contentArea->addWidget(settingsContent);

    split->addWidget(Menu);
    split->addWidget(contentArea);

    lytMain->addWidget(split);
    setLayout(lytMain);

    connect(btnDashboard, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(0);
    });
    connect(btnWorkoutPlans, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(1);
    });
    connect(btnChallenges, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(2);
    });
    connect(btnBuyProduct, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(3);
    });
    connect(btnCalorieTracker, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(4);
    });
    connect(btnSettings, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(5);
    });
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setUsername(const QString& username)
{
    QLabel *lblWelcome = findChild<QLabel*>("lblWelcome");
    if (lblWelcome) {
        lblWelcome->setText("Welcome " + username);
    }
}
