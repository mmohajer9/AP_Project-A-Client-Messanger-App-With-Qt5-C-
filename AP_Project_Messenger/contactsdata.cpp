#include "contactsdata.h"

ContactsData::ContactsData(QObject *parent) : QObject(parent)
{

}

ContactsData::ContactsData(Ui::Mainchat *mainchat_ui, Mainchat *mainchat_ptr)
{
    ContactsData_netManager = new QNetworkAccessManager(this);
    ui = mainchat_ui;
    mainchat_pointer = mainchat_ptr;
}

void ContactsData::getuserlist()
{
    QNetworkRequest req;
    QUrl url;

    QFile file;
    QString token;
    file.setFileName("token.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream >> token;
    file.close();
    //----------------------------------------------------------
    qDebug() << token << endl;
    //----------------------------------------------------------

    url = "http://api.softserver.org:1104/getuserlist?token=" + token;
    req.setUrl(url);
    qDebug() << url;
    connect(ContactsData_netManager, &QNetworkAccessManager::finished,this, &ContactsData::replyFinished_user);
    ContactsData_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ContactsData::getgrouplist()
{

}

void ContactsData::getchannellist()
{

}

void ContactsData::getuserchats()
{

}

void ContactsData::getgroupchats()
{

}

void ContactsData::getchannelchats()
{

}

void ContactsData::replyFinished_user(QNetworkReply *reply)
{
    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    int j = 0;
    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
    }
    int msg_num = message_num.toInt();
    if(msg_num == 0)
    {
    }
    else
    {
        qDebug()<< msg_num << endl;
        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["src"]).toString();
            qDebug()<<pm<<endl;
            ui->PV_ListWidget->insertItem(1,pm);
        }
    }
    emit userlist_done();
}

void ContactsData::replyFinished_group(QNetworkReply *reply)
{
    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    int j = 0;
    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
    }
    int msg_num = message_num.toInt();
    if(msg_num == 0)
    {
    }
    else
    {
        qDebug()<< msg_num << endl;
        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["group_name"]).toString();
            ui->PV_ListWidget->insertItem(0,pm);
        }
    }
    emit grouplist_done();
}

void ContactsData::replyFinished_channel(QNetworkReply *reply)
{
    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    int j = 0;
    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
    }
    int msg_num = message_num.toInt();
    if(msg_num == 0)
    {
    }
    else
    {
        qDebug()<< msg_num << endl;
        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["channel_name"]).toString();
            ui->PV_ListWidget->insertItem(0,pm);
        }
    }
    emit channellist_done();
}
