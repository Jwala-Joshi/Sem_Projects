#include "dashboard.h"
#include "ui_dashboard.h"

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
                          "color: #e6e6e6;"
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

    QLabel *lblWelcome = new QLabel("Welcome <Username>");
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
    QAction *toggle =new QAction("Dark Mode",this);
    QAction *setting =new QAction("Settings",this);
    userMenu->addAction(profile);
    userMenu->addAction(upgrade);
    userMenu->addAction(toggle);
    userMenu->addAction(setting);

    connect(btnUserIcon, &QPushButton::clicked, this, [=]() {
        userMenu->exec(QCursor::pos());
    });

    lytHeader->addWidget(btnUserIcon);

    header->setLayout(lytHeader);

    QWidget *dashboardContent = new QWidget;
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardContent);
    dashboardLayout->addWidget(header);
    QLabel *lblDashboard = new QLabel("Welcome to the Dashboard!", dashboardContent);
    dashboardLayout->addWidget(lblDashboard);

    QWidget *workoutPlansContent = new QWidget;
    QVBoxLayout *workoutPlansLayout = new QVBoxLayout(workoutPlansContent);
    QLabel *lblWorkoutPlans = new QLabel("Here are your workout plans!", workoutPlansContent);
    workoutPlansLayout->addWidget(lblWorkoutPlans);

    QWidget *challengesContent = new QWidget;
    QVBoxLayout *challengesLayout = new QVBoxLayout(challengesContent);
    QLabel *lblChallenges = new QLabel("Here are your challenges!", challengesContent);
    challengesLayout->addWidget(lblChallenges);

    QWidget *buyProductContent = new QWidget;
    QVBoxLayout *buyProductLayout = new QVBoxLayout(buyProductContent);
    QLabel *lblBuyProduct = new QLabel("Buy products here!", buyProductContent);
    buyProductLayout->addWidget(lblBuyProduct);

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
