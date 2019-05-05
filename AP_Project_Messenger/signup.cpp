#include "signup.h"
#include "ui_signup.h"
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
Signup::Signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\Users\\MMM\\Desktop\\QT Projects\\AP_Project_Messenger\\App_Data\\Images\\images.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_complete_signup_clicked()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    QUrl url;
    url = "http://api.softserver.org:1104/signup?username=" + ui->username->text() + "&" + "password=" + ui->password->text() + "&" + "firstname=" + ui->name->text() + "&" + "lastname=" + ui->lastname->text();
    req.setUrl(url);
    qDebug() << url;
    connect(manager, &QNetworkAccessManager::finished,this, &Signup::replyFinished);
    manager->get(req); //jahate estefade az get bejaye post get gharar midahim.
}
void Signup::replyFinished(QNetworkReply *reply)
{
    //QString res=reply->readAll();
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->signup_message->setText(jsobj["message"].toString());

//qDebug()<<res;
}

void Signup::on_close_signup_clicked()
{

   this->close();
}

