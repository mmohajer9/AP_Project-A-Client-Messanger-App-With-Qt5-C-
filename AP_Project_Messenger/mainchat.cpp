#include "mainchat.h"
#include "ui_mainchat.h"
#include "QFile"
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <serverthread.h>
Mainchat::Mainchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainchat)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\Users\\MMM\\Desktop\\QT Projects\\AP_Project_Messenger\\App_Data\\Images\\bg-page.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->setFixedSize(1320,741);

    SThread = new ServerThread;
    SThread->ui = ui;
    SThread->mainchat_pointer = this;
    SThread->start();
    connect(ui->PV_ListWidget,&QListWidget::itemClicked,SThread,&ServerThread::set_dst_pv);
    connect(ui->Group_ListWidget,&QListWidget::itemClicked,SThread,&ServerThread::set_dst_gp);
    connect(ui->Channel_ListWidget,&QListWidget::itemClicked,SThread,&ServerThread::set_dst_channel);
    connect(ui->sendmessage,&QPushButton::clicked,SThread,&ServerThread::send);
    connect(ui->PV_Options,&QPushButton::clicked,SThread,&ServerThread::start_message_with_user);
    connect(ui->GP_Join,&QPushButton::clicked,SThread,&ServerThread::join_gp);
    connect(ui->GP_Make,&QPushButton::clicked,SThread,&ServerThread::make_gp);
    connect(ui->Channel_Join,&QPushButton::clicked,SThread,&ServerThread::join_channel);
    connect(ui->Channel_Create,&QPushButton::clicked,SThread,&ServerThread::make_channel);

}

Mainchat::~Mainchat()
{
    delete ui;
}
void Mainchat::on_Logout_clicked()
{
    SThread->ok = false;
    QEventLoop my_loop;
    QTimer::singleShot( 2000,&my_loop,SLOT(quit()) );
    my_loop.exec();

    QFile file_username;
    QString username;
    file_username.setFileName("username.txt");
    file_username.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream_username(&file_username);
    stream_username >> username;
    file_username.close();
    //------------------------------------------------------------------------------------------------------------------------
    QFile file_password;
    QString password;
    file_password.setFileName("password.txt");
    file_password.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream_password(&file_password);
    stream_password >> password;
    file_password.close();
    //------------------------------------------------------------------------------------------------------------------------
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    QUrl url;
    url = "http://api.softserver.org:1104/logout?username=" + username + "&" + "password=" + password;
    req.setUrl(url);
    qDebug() << url;
    connect(manager, &QNetworkAccessManager::finished,this, &Mainchat::replyFinished);
    manager->get(req); //jahate estefade az get bejaye post get gharar midahim.


}
void Mainchat::replyFinished(QNetworkReply *reply)
{

    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    if(jsobj["message"].toString() == "Logged Out Successfully")
    {

        this->close();
    }
}
void Mainchat::closeEvent (QCloseEvent *event)
{
    SThread->ok = false;
    QEventLoop my_loop;
    QTimer::singleShot( 1000,&my_loop,SLOT(quit()) );
    my_loop.exec();

    QFile file_username;
    QString username;
    file_username.setFileName("username.txt");
    file_username.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream_username(&file_username);
    stream_username >> username;
    file_username.close();
    //------------------------------------------------------------------------------------------------------------------------
    QFile file_password;
    QString password;
    file_password.setFileName("password.txt");
    file_password.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream_password(&file_password);
    stream_password >> password;
    file_password.close();
    //------------------------------------------------------------------------------------------------------------------------
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    QUrl url;
    url = "http://api.softserver.org:1104/logout?username=" + username + "&" + "password=" + password;
    req.setUrl(url);
    qDebug() << url;
    connect(manager, &QNetworkAccessManager::finished,this, &Mainchat::replyFinished);
    manager->get(req); //jahate estefade az get bejaye post get gharar midahim.
}







