#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QSplitter>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QTextEdit>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GymEase");
    setFixedSize(800, 600);
    setWindowIcon(QIcon(":/resources/icons/main logo.png"));

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *main = new QVBoxLayout(central);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QWidget *left = new QWidget(this);
    QLabel *stimg = new QLabel(left);
    QPixmap workoutImage(":/resources/icons/model.png");
    stimg->setPixmap(workoutImage);
    stimg->setAlignment(Qt::AlignCenter);
    left->setLayout(new QVBoxLayout);
    left->layout()->addWidget(stimg);
    left->setFixedWidth(350);

    QWidget *right = new QWidget(this);
    QVBoxLayout *lytRight = new QVBoxLayout(right);

    QLabel *lblDescription = new QLabel("Project Description", this);
    lblDescription->setStyleSheet("font-size: 18px; font-weight: bold;");
    lblDescription->setAlignment(Qt::AlignLeft);

    QLabel *txtDescription = new QLabel("This project is designed to provide users with a comprehensive fitness tracking "
                                             "platform that integrates workout plans, challenges, and calorie tracking "
                                             "to help them improve their health and fitness efficiently."
                                        "\n"
                                        "This system is a fitness management platform that allows users to track their workouts, "
                                        "calories, and progress. It offers personalized workout plans and challenges, "
                                        "and integrates with the user's diet plan to help them reach their fitness goals.");
    txtDescription->setWordWrap(true);
    txtDescription->setStyleSheet("font-size: 14px;");

    QVBoxLayout *lytDescription = new QVBoxLayout();
    lytDescription->addWidget(lblDescription);
    lytDescription->addWidget(txtDescription);

    QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QLabel *lblAboutUS =new QLabel("About Us",this);
    lblAboutUS->setStyleSheet("font-size: 18px; font-weight: bold;");
    lblAboutUS->setAlignment(Qt::AlignLeft);

    QLabel *txtAboutUs =new QLabel("We are students of BIT 3rd sem. "
                                    "Our aim is to develop an intuitive and user-friendly fitness platform.");
    txtAboutUs->setWordWrap(true);
    txtAboutUs->setStyleSheet("font-size: 14px;");

    QVBoxLayout *lytAboutUs = new QVBoxLayout();
    lytAboutUs->addWidget(lblAboutUS);
    lytAboutUs->addWidget(txtAboutUs);

    lytRight->addLayout(lytDescription);
    lytRight->addSpacerItem(spacer);
    lytRight->addLayout(lytAboutUs);

    splitter->addWidget(left);
    splitter->addWidget(right);
    splitter->setStretchFactor(1, 1);

    main->addWidget(splitter);
}

// Handle closing the window to show login screen
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Create and show the login screen
    Login *loginScreen = new Login();
    loginScreen->show();

    // Close the current window
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}
