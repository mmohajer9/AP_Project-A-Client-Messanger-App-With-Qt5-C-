#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QCloseEvent>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include "mainchat.h"
#include "QFile"
#include <QDesktopServices>
#include <QDir>
#include <offlinemode.h>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\Users\\MMM\\Desktop\\QT Projects\\AP_Project_Messenger\\App_Data\\Images\\bg-page.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    QUrl url;
    url = "http://api.softserver.org:1104/login?username=" + ui->username->text() + "&" + "password=" + ui->password->text();
    req.setUrl(url);
    qDebug() << url;
    connect(manager, &QNetworkAccessManager::finished,this, &Login::replyFinished);
    manager->get(req); //jahate estefade az get bejaye post get gharar midahim.

}

void Login::replyFinished(QNetworkReply *reply)
{
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    qDebug() << jsobj["token"].toString();
    //QString res=reply->readAll();
    //qDebug()<<res;
    ui->login_message->setText(jsobj["message"].toString());
    if(jsobj["message"].toString() == "")
    {
        ui->login_message->setText("Connection Problem");
    }
    //----------------------------------------------------------
    QFile file;
    file.setFileName("token.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text); //token
    QTextStream stream(&file);
    stream << jsobj["token"].toString() << endl;
    file.close();
    //----------------------------------------------------------
    QFile file_username;
    file_username.setFileName("username.txt");
    file_username.open(QIODevice::WriteOnly | QIODevice::Text); //username
    QTextStream stream_username(&file_username);
    stream_username << ui->username->text();
    file_username.close();
    //----------------------------------------------------------
    QFile file_password;
    file_password.setFileName("password.txt");
    file_password.open(QIODevice::WriteOnly | QIODevice::Text); //password
    QTextStream stream_password(&file_password);
    stream_password << ui->password->text();
    file_password.close();
    //----------------------------------------------------------




    if(jsobj["message"].toString() == "Logged in Successfully")
    {
        //----------------------------------------------------------
        QDir dir1;

        QString full_address1 = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + ui->username->text();
        dir1.mkpath(full_address1);
        full_address1 += "\\PV";
        dir1.mkpath(full_address1);
        QFile offline1;
        offline1.setFileName(full_address1);
        if(!offline1.open(QIODevice::WriteOnly))
        {
            qDebug() << "file is not opened" << endl;
        }
        else
        {
            offline1.close();
        }
        //----------------------------------------------------------
        QString full_address2 = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + ui->username->text();
        dir1.mkpath(full_address2);
        full_address2 += "\\GP";
        dir1.mkpath(full_address2);
        QFile offline2;
        offline2.setFileName(full_address2);
        if(!offline2.open(QIODevice::WriteOnly))
        {
            qDebug() << "file is not opened" << endl;
        }
        else
        {
            offline2.close();
        }
        //----------------------------------------------------------
        QString full_address3 = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + ui->username->text();
        dir1.mkpath(full_address3);
        full_address3 += "\\Channel";
        dir1.mkpath(full_address3);
        QFile offline3;
        offline3.setFileName(full_address1);
        if(!offline1.open(QIODevice::WriteOnly))
        {
            qDebug() << "file is not opened" << endl;
        }
        else
        {
            offline3.close();
        }
        //----------------------------------------------------------

        //----------------------------------------------------------
        QFile f1;
        f1.setFileName("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + ui->username->text() + "\\username.txt");
        f1.open(QIODevice::WriteOnly | QIODevice::Text); //username
        QTextStream s1(&f1);
        s1 << ui->username->text();
        f1.close();
        //----------------------------------------------------------
        QFile f2;
        f2.setFileName("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + ui->username->text() + "\\password.txt");
        f2.open(QIODevice::WriteOnly | QIODevice::Text); //password
        QTextStream s2(&f2);
        s2 << ui->username->text();
        f2.close();
        //----------------------------------------------------------











        QEventLoop my_loop;
        QTimer::singleShot( 300,&my_loop,SLOT(quit()) );
        my_loop.exec();
        this->close();
        Mainchat* mainchat;
        mainchat = new Mainchat;
        mainchat->show();
    }

}

void Login::on_logout_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    QUrl url;
    url = "http://api.softserver.org:1104/logout?username=" + username + "&" + "password=" + password;
    req.setUrl(url);
    qDebug() << url;
    connect(manager, &QNetworkAccessManager::finished,this, &Login::replyFinished);
    manager->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void Login::on_offlinemode_clicked()
{
    QFile file1;
    QFile file2;
    QString temp_username = ui->username->text();
    QString temp_password = ui->password->text();
    QString Adr1 = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + temp_username + "\\username.txt";
    QString Adr2 = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + temp_username + "\\password.txt";
    file1.setFileName(Adr1);
    file2.setFileName(Adr2);

    file1.open(QIODevice::ReadOnly);
    file2.open(QIODevice::ReadOnly);

    QTextStream ts1(&file1);
    QTextStream ts2(&file2);

    QString username , password;
    ts1 >> username;
    ts2 >> password;

    if(username == temp_username && password == temp_password && temp_username != "")
    {
        ui->login_message->setText("OK! Going To Offline Mode");
        OfflineMode* offline = new OfflineMode;
        offline->USERNAME = ui->username->text();
        offline->show();
    }
    else if(username == temp_username && password != temp_password)
    {
        ui->login_message->setText("Password Is Wrong");
    }
    else if(temp_password == "" || temp_username == "")
    {
        ui->login_message->setText("No Entery");
    }
    else
    {
         ui->login_message->setText("User Not Found");
    }
}
