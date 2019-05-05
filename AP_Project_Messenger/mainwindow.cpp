#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QUrl>
#include <QtCore>
#include <login.h>
#include <signup.h>
#include <QDesktopServices>
#include <QMovie>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\Users\\MMM\\Desktop\\QT Projects\\AP_Project_Messenger\\App_Data\\Images\\12342.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //

    QMovie *movie = new QMovie("C:\\Users\\MMM\\Desktop\\QT Projects\\AP_Project_Messenger\\App_Data\\Images\\mamadgram_logo_38152.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    movie->setSpeed(120);
    processLabel->setGeometry(QRect(-25,-40,600,200));
    processLabel->setToolTip("MamadGram By:\nMohammad Mahdi Mohajer\nSoheil Fadaei");
    processLabel->setToolTipDuration(1000);
    //-----------------------------------------------------------------------------

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Signup_clicked()
{
    open_signup();
}

void MainWindow::on_Login_clicked()
{
    open_login();
}
void MainWindow::open_login()
{
    Login* login;
    login = new Login;
    login->show();
    login->setFixedSize(861,696);
}

void MainWindow::open_signup()
{
    Signup* signup;
    signup = new Signup;
    signup->show();
    signup->setFixedSize(503,493);
}


void MainWindow::on_iutlogo_clicked()
{
    QDesktopServices::openUrl(QUrl("http://iut.ac.ir", QUrl::TolerantMode));
}
