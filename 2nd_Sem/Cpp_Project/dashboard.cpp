#include "dashboard.h"
#include "ui_dashboard.h"
#include "login.h"
#include "backend.h"

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
#include <QFile>

QString path = "E:/Programming/Qt/Sem_Projects/2nd_Sem/Cpp_Project/datas/";

Dashboard::Dashboard(const QString& username,const QString& password,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    setWindowTitle("Dashboard");
    setMinimumSize(800,600);
    setWindowIcon(QIcon(":/resources/icons/main logo.png"));

    user currentUser;
    currentUser = getUserDetails(const_cast <char*>(username.toStdString().c_str()),const_cast <char*>(password.toStdString().c_str()));

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
    QPushButton *btnCalorieDetails = new QPushButton("Calorie Details");

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

    btnMenu->setStyleSheet(buttonStyle + "hover: none");
    btnDashboard->setStyleSheet(buttonStyle);
    btnWorkoutPlans->setStyleSheet(buttonStyle);
    btnChallenges->setStyleSheet(buttonStyle);
    btnBuyProduct->setStyleSheet(buttonStyle);
    btnCalorieDetails->setStyleSheet(buttonStyle);
    btnSettings->setStyleSheet(buttonStyle);

    lytMenu->addWidget(btnMenu);
    lytMenu->addWidget(btnDashboard);
    lytMenu->addWidget(btnWorkoutPlans);
    lytMenu->addWidget(btnChallenges);
    lytMenu->addWidget(btnBuyProduct);
    lytMenu->addWidget(btnCalorieDetails);

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
    lblWelcome->setText("Welcome " + username);
    lblWelcome->setStyleSheet("font-size: 18px;");
    lytHeader->addWidget(lblWelcome);

    QPushButton *btnUserIcon = new QPushButton;
    QIcon userIcon(":/resources/icons/user-dark.png");
    btnUserIcon->setIcon(userIcon);
    btnUserIcon->setIconSize(QSize(30, 30));
    btnUserIcon->setStyleSheet("background: white; border: none;" "border-radius: 15px; padding:2px" );

    QMenu *userMenu = new QMenu(this);
    QAction *profile = new QAction("Profile", this);
    QAction *toggle =new QAction("Change Theme",this);
    QAction *setting =new QAction("Settings",this);
    QAction *logOut = new QAction("Log Out",this);
    userMenu->addAction(profile);
    userMenu->addAction(toggle);
    userMenu->addAction(setting);
    userMenu->addAction(logOut);

    connect(btnUserIcon, &QPushButton::clicked, this, [=]() {
        userMenu->exec(QCursor::pos());
    });
    connect(profile, &QAction::triggered,this,[=]() {
        contentArea->setCurrentIndex(6);
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
    lblCurrentWorkouts->setStyleSheet("font-size: 22px;");

    lblCurrentChallenges = new QLabel("Current Challenges");
    lblCurrentChallenges->setStyleSheet("font-size: 22px");

    QWidget *dashboardContent = new QWidget;
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardContent);
    dashboardLayout->addWidget(header);
    dashboardLayout->addWidget(lblCurrentWorkouts);

    //File userWorkout
    QLabel *noWorkout =new QLabel;
    QFile dashboard1(path + "userworkout.txt");
    if(!dashboard1.open(QIODevice::ReadOnly |QIODevice::Text)) {
        qDebug() << "Can't open file." << "userworkout.txt";
        noWorkout->setText("Your Workout is empty.");
        dashboardLayout->addWidget(noWorkout);
    }
    else {
        QTextStream dFile1(&dashboard1);
        // QWidget *holdUserWorkout = new QWidget(dashboardContent);
        // QGridLayout *lytUserWorkout = new QGridLayout(holdUserWorkout);
        int flag=0;
        while(!dFile1.atEnd() && flag==0){
            noWorkout->clear();
            if( QString::compare(username,dFile1.readLine().trimmed()) == 0) {
                QLabel *Title =new QLabel("Title : " + dFile1.readLine());
                Title->setStyleSheet("font-size:18px");
                dashboardLayout->addWidget(Title);

                for(int j=1;j<6;j++){
                    QLabel *exercise =new QLabel (dFile1.readLine());
                    exercise->setStyleSheet("font-size:14px");
                    dashboardLayout->addWidget(exercise);
                }
                flag=1;
            }
        }
        if(flag==0) {
            noWorkout->setText("Your Workout is empty.");
            dashboardLayout->addWidget(noWorkout);
        }
        dashboard1.close();
    }
    if(noWorkout->text() == "Your Workout is empty.") {
        dashboardLayout->addSpacerItem(spacer);
    }
    dashboardLayout->addWidget(lblCurrentChallenges);

    //File userChallenges
    QLabel *noChallenge =new QLabel;
    QFile dashboard2(path + "userchallenge.txt");
    if(!dashboard2.open(QIODevice::ReadOnly |QIODevice::Text)) {
        qDebug() << "Can't open file." << "userchallenge";
        noChallenge->setText("Your Challenge is empty.");
        dashboardLayout->addWidget(noChallenge);
    }
    else {
        QTextStream dFile2(&dashboard2);
        int flag=0;
        while(!dFile2.atEnd() && flag==0) {
            noChallenge->clear();
                if( QString::compare(username,dFile2.readLine().trimmed()) == 0 ) {
                    QLabel *cTitle =new QLabel(dFile2.readLine());
                    cTitle->setStyleSheet("font-size:18px");
                    dashboardLayout->addWidget(cTitle);

                    for(int j=1;j<6;j++){
                        QLabel *cexercise =new QLabel (dFile2.readLine());
                        dFile2.readLine();
                        cexercise->setStyleSheet("font-size:14px");
                        dashboardLayout->addWidget(cexercise);
                        qDebug()<< j << '\n';
                    }
                    flag=1;
                }
        }
        if(flag==0) {
            noChallenge->setText("Your Challenge is empty.");
            dashboardLayout->addWidget(noChallenge);
        }
        dashboard2.close();
    }
    dashboardLayout->addSpacerItem(spacer);

    QWidget *workoutPlansContent = new QWidget;
    QVBoxLayout *workoutPlansLayout = new QVBoxLayout(workoutPlansContent);
    QLabel *lblWorkoutPlans = new QLabel("Workouts", workoutPlansContent);
    lblWorkoutPlans->setStyleSheet("font-size:22px");
    workoutPlansLayout->addWidget(lblWorkoutPlans);

    //File all Workouts
    QString currentWorkout;
    QLabel *emWorkout =new QLabel;
    QFile workoutFile(path + "workout.txt");

    if(!workoutFile.exists()) {
        qDebug() << "No File.";
    }
    if(!workoutFile.open(QIODevice::ReadOnly )) {
        qDebug() << "Can't open file." << path + "workout.txt";
        emWorkout->setText("No Workouts.");
        workoutPlansLayout->addWidget(emWorkout);
    }
    else {
        QTextStream wFile(&workoutFile);
        emWorkout->clear();
        int flag=0;
        while(!wFile.atEnd() && flag<3) {
            QLabel *wTitle =new QLabel(wFile.readLine());
            wTitle->setStyleSheet("font-size:18px");
            workoutPlansLayout->addWidget(wTitle);

            currentWorkout =wTitle->text() + "\n";

            for(int j=1;j<6;j++){
                QLabel *wexercise =new QLabel (wFile.readLine());
                wexercise->setStyleSheet("font-size:14px");
                workoutPlansLayout->addWidget(wexercise);
                currentWorkout += wexercise->text() + "\n";
            }
            QPushButton *btnAdd= new QPushButton("Add",workoutPlansContent);
            btnAdd->setFixedWidth(80);
            btnAdd->setStyleSheet("background-color: green");
            workoutPlansLayout->addWidget(btnAdd,Qt::AlignLeft);

            connect(btnAdd,&QPushButton::clicked,[=](){
                QFile uwFile(path + "userworkout.txt");
                if(uwFile.open(QIODevice::Append | QIODevice::Text)) {
                    QTextStream out(&uwFile);
                    out<< username << '\n';
                    out << currentWorkout;
                    qDebug() << "Workout added to user workout file!";
                } else {
                    qDebug() << "Failed to open user workout file for appending!";
                }
            });
            flag++;
        }
        workoutFile.close();
    }
    workoutPlansLayout->addSpacerItem(spacer);

    QWidget *challengesContent = new QWidget;
    QVBoxLayout *challengesLayout = new QVBoxLayout(challengesContent);
    QLabel *lblChallenges = new QLabel("Challenges", challengesContent);
    lblChallenges->setStyleSheet("font-size:22px");
    challengesLayout->addWidget(lblChallenges);

    //File all Challenges
    QString currentChallenge,tmp;
    QLabel *emChallenge =new QLabel;
    QFile challengeFile(path + "challenge.txt");

    if(!challengeFile.open(QIODevice::ReadOnly |QIODevice::Text)) {
        qDebug() << "Can't open file." << "challenge";
        emChallenge->setText("No Challenges.");
        challengesLayout->addWidget(emChallenge);
    }
    else {
        QTextStream cFile(&challengeFile);
        emChallenge->clear();

        int flag=0;
        while(!cFile.atEnd() && flag<3) {
            QLabel *cTitle =new QLabel(cFile.readLine());
            qDebug()<<cTitle->text();
            cTitle->setStyleSheet("font-size:18px");
            challengesLayout->addWidget(cTitle);

            currentChallenge =cTitle->text() + "\n";
            qDebug()<<currentChallenge;

            for(int i=1;i<11;i++) {
                tmp=cFile.readLine();
                currentChallenge +=tmp + "\n";
                qDebug() << "first" << i;
                if(i%2 != 0){
                    qDebug() << "sencond" << i;
                    QLabel *cexercise =new QLabel (QString(tmp));
                    qDebug() << cexercise->text();
                    cexercise->setStyleSheet("font-size:14px");
                    challengesLayout->addWidget(cexercise);
                    // currentChallenge +=cexercise->text() + "\n";
                }
            }
            QPushButton *btnAdd= new QPushButton("Add",challengesContent);
            btnAdd->setFixedWidth(80);
            btnAdd->setStyleSheet("background-color: green");
            challengesLayout->addWidget(btnAdd,Qt::AlignLeft);

            connect(btnAdd,&QPushButton::clicked,[=](){
                QFile ucFile(path + "userchallenge.txt");
                if(ucFile.open(QIODevice::Append | QIODevice::Text)) {
                    QTextStream out(&ucFile);
                    out<< username << '\n';
                    out << currentChallenge;
                    qDebug() << "Challenge added to user challenge file!";
                } else {
                    qDebug() << "Failed to open user challenge file for appending!";
                }
            });
            flag++;
        }
        challengeFile.close();
    }
    challengesLayout->addSpacerItem(spacer);

    QWidget *buyProductContent = new QWidget;
    QVBoxLayout *buyProductLayout = new QVBoxLayout(buyProductContent);
    QLabel *lblBuyProduct = new QLabel("Buy Products", buyProductContent);
    lblBuyProduct->setStyleSheet("font-size: 22px");

    QWidget *Products = new QWidget(btnBuyProduct);
    QGridLayout *lytProducts = new QGridLayout(Products);

    QWidget *product_1 = new QWidget(Products);
    QVBoxLayout *lytProduct_1 = new QVBoxLayout(product_1);

    QLabel *productImage_1 = new QLabel(product_1);
    productImage_1->setPixmap(QPixmap(":/resources/icons/dumbbell.jpg").scaled(100, 100, Qt::KeepAspectRatio));
    productImage_1->setAlignment(Qt::AlignCenter);
    lytProduct_1->addWidget(productImage_1);

    QLabel *productName_1 = new QLabel("Dumbell 20Kg", product_1);
    productName_1->setStyleSheet("font-size: 14px;");
    lytProduct_1->addWidget(productName_1);

    QLabel *productPrice1 = new QLabel("Rs. 1999", product_1);
    productPrice1->setStyleSheet("font-size: 14px;");
    lytProduct_1->addWidget(productPrice1);

    QPushButton *btnBuy1 = new QPushButton("Buy", product_1);
    btnBuy1->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
    lytProduct_1->addWidget(btnBuy1);

    QWidget *product_2 = new QWidget(Products);
    QVBoxLayout *lytProduct_2 = new QVBoxLayout(product_2);

    QLabel *productImage_2 = new QLabel(product_2);
    productImage_2->setPixmap(QPixmap(":/resources/icons/Weight Plates.jpg").scaled(100, 100, Qt::KeepAspectRatio));
    productImage_2->setAlignment(Qt::AlignCenter);
    lytProduct_2->addWidget(productImage_2);

    QLabel *productName_2 = new QLabel("Weight Plates 20Kg", product_2);
    productName_2->setStyleSheet("font-size: 14px;");
    lytProduct_2->addWidget(productName_2);

    QLabel *productPrice2 = new QLabel("Rs. 2999", product_2);
    productPrice2->setStyleSheet("font-size: 14px;");
    lytProduct_2->addWidget(productPrice2);

    QPushButton *btnBuy2 = new QPushButton("Buy", product_2);
    btnBuy2->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
    lytProduct_2->addWidget(btnBuy2);

    QWidget *product_3 = new QWidget(Products);
    QVBoxLayout *lytProduct_3 = new QVBoxLayout(product_3);

    QLabel *productImage_3 = new QLabel(product_3);
    productImage_3->setPixmap(QPixmap(":/resources/icons/protein powder.jpg").scaled(100, 100, Qt::KeepAspectRatio));
    productImage_3->setAlignment(Qt::AlignCenter);
    lytProduct_3->addWidget(productImage_3);

    QLabel *productName_3 = new QLabel("Whey Protein", product_3);
    productName_3->setStyleSheet("font-size: 14px;");
    lytProduct_3->addWidget(productName_3);

    QLabel *productPrice3 = new QLabel("Rs. 16999", product_3);
    productPrice3->setStyleSheet("font-size: 14px;");
    lytProduct_3->addWidget(productPrice3);

    QPushButton *btnBuy3 = new QPushButton("Buy", product_3);
    btnBuy3->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
    lytProduct_3->addWidget(btnBuy3);

    lytProducts->addWidget(product_1,0,0);
    lytProducts->addWidget(product_2,0,1);
    lytProducts->addWidget(product_3,0,2);


    buyProductLayout->addWidget(lblBuyProduct);
    buyProductLayout->addWidget(Products);
    buyProductLayout->addSpacerItem(spacer);

    QWidget *calorieDetailsContent = new QWidget;
    QVBoxLayout *calorieDetailsLayout = new QVBoxLayout(calorieDetailsContent);
    QLabel *lblcalorieDetails = new QLabel("Foods with their calorie", calorieDetailsContent);
    lblcalorieDetails->setStyleSheet("font-size: 22px");
    calorieDetailsLayout->addWidget(lblcalorieDetails);

    //File all Challenges
    QLabel *emCalorie =new QLabel;
    QFile calorieFile(path + "calorie.txt");
    if(!calorieFile.open(QIODevice::ReadOnly |QIODevice::Text)) {
        qDebug() << "Can't open file." << "calorie";
        emCalorie->setText("No data yet.");
        calorieDetailsLayout->addWidget(emCalorie);
    }
    else {
        QTextStream calFile(&calorieFile);
        emCalorie->clear();
        while(!calFile.atEnd()) {
            QLabel *calTitle =new QLabel(calFile.readLine());
            calTitle->setStyleSheet("font-size:18px");
            calorieDetailsLayout->addWidget(calTitle);

            for(int j=1;j<2;j++){
                QLabel *calorie =new QLabel (calFile.readLine());
                calorie->setStyleSheet("font-size:14px");
                calorieDetailsLayout->addWidget(calorie);
            }
        }
        calorieFile.close();
    }
    calorieDetailsLayout->addSpacerItem(spacer);

    QWidget *settingsContent = new QWidget;
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsContent);
    QLabel *lblSettings = new QLabel("Settings", settingsContent);
    lblSettings->setStyleSheet("font-size: 22px");
    settingsLayout->addWidget(lblSettings);

    QWidget *mainSettings = new QWidget;
    QGridLayout *lytSettings = new QGridLayout(mainSettings);

    QLabel *sName = new QLabel(mainSettings);
    sName->setText("Name : " + QString(currentUser.getName()));
    sName->setStyleSheet("font-size: 18px");

    QLabel *sUsername = new QLabel(mainSettings);
    sUsername->setText("Username : " + username);
    sUsername->setStyleSheet("font-size: 18px");

    QLabel *clblName = new QLabel("Change Name: ", mainSettings);
    clblName->setStyleSheet("font-size:16px");
    QLabel *clblUsername = new QLabel("Change Username: ", mainSettings);
    clblUsername->setStyleSheet("font-size:16px");
    QLabel *clblPassword = new QLabel("Change Password: ", mainSettings);
    clblPassword->setStyleSheet("font-size:16px");

    QLineEdit *ctxtName = new QLineEdit(mainSettings);
    ctxtName->setFixedWidth(200);

    QLineEdit *ctxtUsername = new QLineEdit(mainSettings);
    ctxtUsername->setFixedWidth(200);

    QLineEdit *ctxtPassword = new QLineEdit(mainSettings);
    ctxtPassword->setFixedWidth(200);
    ctxtPassword->setEchoMode(QLineEdit::Password);

    QPushButton *cbtnName = new QPushButton("Change", mainSettings);
    cbtnName->setFixedWidth(80);

    QPushButton *cbtnUsername = new QPushButton("Change", mainSettings);
    cbtnUsername->setFixedWidth(80);

    QPushButton *cbtnPassword = new QPushButton("Change", mainSettings);
    cbtnPassword->setFixedWidth(80);

    lytSettings->addWidget(sName, 0, 0, Qt::AlignLeft);
    lytSettings->addWidget(sUsername, 1, 0, Qt::AlignLeft);
    lytSettings->addWidget(clblName, 3, 0, Qt::AlignLeft);
    lytSettings->addWidget(ctxtName, 3, 1, Qt::AlignLeft);
    lytSettings->addWidget(cbtnName, 3, 2, Qt::AlignLeft);
    lytSettings->addWidget(clblUsername, 4, 0, Qt::AlignLeft);
    lytSettings->addWidget(ctxtUsername, 4, 1, Qt::AlignLeft);
    lytSettings->addWidget(cbtnUsername, 4, 2, Qt::AlignLeft);
    lytSettings->addWidget(clblPassword, 5, 0, Qt::AlignLeft);
    lytSettings->addWidget(ctxtPassword, 5, 1, Qt::AlignLeft);
    lytSettings->addWidget(cbtnPassword, 5, 2, Qt::AlignLeft);
    lytSettings->setAlignment(Qt::AlignLeft);

    settingsLayout->addWidget(mainSettings);
    settingsLayout->addSpacerItem(spacer);

    static int flag=0;
    connect(cbtnName,&QPushButton::clicked ,[=]() {
        QString name =ctxtName->text();
        changeName(const_cast <user&>(currentUser) , const_cast <char*>(name.toStdString().c_str()));
        if(flag==0){
            QLabel *change = new QLabel("Please Re-login to see the changes",settingsContent);
            settingsLayout->addWidget(change);
            settingsLayout->addSpacerItem(spacer);
            flag++;
        }
    });

    connect(cbtnUsername,&QPushButton::clicked ,[=]() {
        QString usern =ctxtUsername->text();
        changeUsername(const_cast <user&>(currentUser) ,const_cast <char*>(usern.toStdString().c_str()) );
        if(flag==0){
            QLabel *change = new QLabel("Please Re-login to see the changes",settingsContent);
            settingsLayout->addWidget(change);
            settingsLayout->addSpacerItem(spacer);
            flag++;
        }
    });

    connect(cbtnPassword,&QPushButton::clicked ,[=]() {
        QString pass =ctxtPassword->text();
        changePassword(const_cast <user&>(currentUser), const_cast <char*>(pass.toStdString().c_str()) );
        if(flag==0){
            QLabel *change = new QLabel("Please Re-login to see the changes",settingsContent);
            settingsLayout->addWidget(change);
            settingsLayout->addSpacerItem(spacer);
            flag++;
        }
    });

    QWidget *Profile =new QWidget(contentArea);
    QLabel *pName = new QLabel(Profile);
    pName->setText("Name : " + QString(currentUser.getName()));
    pName->setStyleSheet("font-size: 20px");
    QLabel *pUsername = new QLabel(Profile);
    pUsername->setText("Username : "+ username);
    pUsername->setStyleSheet("font-size: 20px");
    QLabel *pCompletedWorkouts = new QLabel(Profile);
    pCompletedWorkouts->setText("Workouts Completed: (10/10)");
    pCompletedWorkouts->setStyleSheet("font-size: 20px");
    QLabel *pCompletedChallenges = new QLabel(Profile);
    pCompletedChallenges->setText("Challenges Completed: (3/3)");
    pCompletedChallenges->setStyleSheet("font-size: 20px");
    QLabel *pChange = new QLabel(Profile);
    pChange->setText("Want to change something. Go to settings ");
    QPushButton *pSetting = new QPushButton(Profile);
    pSetting->setText("Settings");
    pSetting->setFixedSize(200,40);
    pSetting->setStyleSheet("background-color: gray");

    QVBoxLayout *lytProfile = new QVBoxLayout(Profile);
    lytProfile->addWidget(pName);
    lytProfile->addWidget(pUsername);
    lytProfile->addWidget(pCompletedWorkouts);
    lytProfile->addWidget(pCompletedChallenges);
    lytProfile->addSpacerItem(spacer);
    lytProfile->addWidget(pChange);
    lytProfile->addWidget(pSetting);

    contentArea->addWidget(dashboardContent);
    contentArea->addWidget(workoutPlansContent);
    contentArea->addWidget(challengesContent);
    contentArea->addWidget(buyProductContent);
    contentArea->addWidget(calorieDetailsContent);
    contentArea->addWidget(settingsContent);
    contentArea->addWidget(Profile);

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
    connect(btnCalorieDetails, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(4);
    });
    connect(btnSettings, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(5);
    });
    connect(pSetting, &QPushButton::clicked, [=]() {
        contentArea->setCurrentIndex(5);
    });
};

Dashboard::~Dashboard()
{
    delete ui;
}
