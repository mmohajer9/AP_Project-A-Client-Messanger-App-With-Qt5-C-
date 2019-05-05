#ifndef CONTACTSDATA_H
#define CONTACTSDATA_H

#include <QHash>
#include <QMap>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QCloseEvent>
#include <QFile>
#include <QThread>
#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QIODevice>
#include <QCloseEvent>
#include <QMessageBox>
#include <mainchat.h>
#include <QTimer>
#include <QEventLoop>
#include "ui_mainchat.h"
#define APP_NAME "MamadGram"

class Mainchat;
class ContactsData;
class ContactsData : public QObject
{
    Q_OBJECT
public:
    explicit ContactsData(QObject *parent = nullptr);
    ContactsData(Ui::Mainchat *mainchat_ui , Mainchat* mainchat_ptr);
    void getuserlist();
    void getgrouplist();
    void getchannellist();
    void getuserchats();
    void getgroupchats();
    void getchannelchats();
signals:
    void userlist_done();
    void grouplist_done();
    void channellist_done();
    void userchats_done();
    void groupchats_done();
    void channelchats_done();

public slots:
    void replyFinished_user(QNetworkReply *reply);
    void replyFinished_group(QNetworkReply *reply);
    void replyFinished_channel(QNetworkReply *reply);


private:
    Mainchat* mainchat_pointer;
    Ui_Mainchat *ui;
    QNetworkAccessManager* ContactsData_netManager;

    QVector <QString> UserList;
    QMap <QString , int> User_Message_Number;

    QVector <QString> GroupList;
    QMap <QString , int> Group_Message_Number;

    QVector <QString> ChannelList;
    QMap <QString , int> Channel_Message_Number;
};

#endif // CONTACTSDATA_H
