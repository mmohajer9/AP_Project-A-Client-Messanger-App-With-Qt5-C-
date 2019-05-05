#include "serverthread.h"

ServerThread::ServerThread(QObject *parent) : QThread(parent)
{
    QFile file_username;
    QString username;
    file_username.setFileName("username.txt");
    file_username.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream_username(&file_username);
    stream_username >> username;
    file_username.close();

    USERNAME = username;
//    QDir directory("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME);
//    directory.removeRecursively();

    qDebug() << "\nThread Created and username is : " << USERNAME;
    ok = true;
    stepU = 1;
    stepG = 1;
    stepC = 1;
    scene = NULL;

}

void ServerThread::set_dst_pv(QListWidgetItem *item)
{
    dst_pv = item->text();
    dst_gp = "";
    dst_channel = "";
    dst = item->text();
}

void ServerThread::set_dst_gp(QListWidgetItem *item)
{
    dst_gp = item->text();
    dst_channel = "";
    dst_pv = "";
    dst = item->text();
}

void ServerThread::set_dst_channel(QListWidgetItem *item)
{
    dst_channel = item->text();
    dst_gp = "";
    dst_pv = "";
    dst = item->text();
}
//int ServerThread::stepU = 1;
//int ServerThread::stepG = 1;
//int ServerThread::stepC = 1;
void ServerThread::getuserlist()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::userlist_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::getgrouplist()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/getgrouplist?token=" + token;
    req.setUrl(url);
    qDebug() << url;

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::grouplist_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::getchannellist()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/getchannellist?token=" + token;
    req.setUrl(url);
    qDebug() << url;

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::channellist_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::getuserchats()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/getuserchats?token=" + token + "&dst=" + dst_pv;
    req.setUrl(url);
    qDebug() << url;

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::userchats_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::getgroupchats()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/getgroupchats?token=" + token + "&dst=" + dst_gp;
    req.setUrl(url);
    qDebug() << url;

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::groupchats_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::getchannelchats()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/getchannelchats?token=" + token + "&dst=" + dst_channel;
    req.setUrl(url);
    qDebug() << url;

    Thread_netManager->get(req); //jahate estefade az get bejaye post get gharar midahim.
    connect(this,&ServerThread::channelchats_done,&loop,&QEventLoop::quit);
    loop.exec();
}

void ServerThread::send_message_user()
{

    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/sendmessageuser?token=" + token + "&dst=" + dst + "&body=" + ui->chatbar->text();
    req.setUrl(url);
    qDebug() << url;

    Send_User->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::send_message_gp()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/sendmessagegroup?token=" + token + "&dst=" + dst + "&body=" + ui->chatbar->text();
    req.setUrl(url);
    qDebug() << url;

    Send_Group->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::send_message_channel()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/sendmessagechannel?token=" + token + "&dst=" + dst + "&body=" + ui->chatbar->text();
    req.setUrl(url);
    qDebug() << url;

    Send_Channel->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::send()
{
    if(dst_pv != "")
     send_message_user();
    if(dst_gp != "")
     send_message_gp();
    if(dst_channel != "")
        send_message_channel();
}

void ServerThread::make_gp()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/creategroup?token=" + token + "&group_name=" + ui->make_id->text() + "&group_title=" + ui->Group_Channel_Title->text();
    req.setUrl(url);
    qDebug() << url;

    MakeGroup->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::make_channel()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/createchannel?token=" + token + "&channel_name=" + ui->make_id->text() + "&channel_title=" + ui->Group_Channel_Title->text();
    req.setUrl(url);
    qDebug() << url;

    MakeChannel->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::join_gp()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/joingroup?token=" + token + "&group_name=" + ui->make_id->text();
    req.setUrl(url);
    qDebug() << url;

    JoinGroup->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::join_channel()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/joinchannel?token=" + token + "&channel_name=" + ui->make_id->text();
    req.setUrl(url);
    qDebug() << url;

    JoinChannel->get(req); //jahate estefade az get bejaye post get gharar midahim.
}

void ServerThread::start_message_with_user()
{
    QNetworkRequest req;
    QUrl url;
    QEventLoop loop;
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

    url = "http://api.softserver.org:1104/sendmessageuser?token=" + token + "&dst=" + ui->PV_usernamelabel_startchat->text() + "&body=" + ui->chatbar->text();
    req.setUrl(url);
    qDebug() << url;

    startchat->get(req); //jahate estefade az get bejaye post get gharar midahim.
}
void ServerThread::replyFinished_user(QNetworkReply *reply)
{

    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;
    for(int i = 20;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();

        qDebug()<< msg_num << endl;


        for(int i = 0;i < msg_num;i++)
        {
            if(msg_num != user_num && stepU == 1)
            {
                pm = (jsobj[QString("block %1").arg(i)].toObject()["src"]).toString();


                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QDir dir;
                QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\";
                full_address += pm;
                dir.mkpath(full_address);
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\list1.txt");
                file.open(QIODevice::Append);
                QDataStream ds(&file);
                ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
                file.close();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


                qDebug()<<pm<<endl;
                QListWidgetItem* c = new QListWidgetItem;
                c->setText(pm);
                UserList.push_back(*c);
                ui->PV_ListWidget->insertItem(0,c);
            }
            else if(msg_num != user_num && stepU != 1)
            {
                pm = (jsobj[QString("block %1").arg(msg_num - 1)].toObject()["src"]).toString();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QDir dir;
                QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\";
                full_address += pm;
                dir.mkpath(full_address);
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\list2.txt");
                file.open(QIODevice::Append);
                QDataStream ds(&file);
                ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
                file.close();
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                qDebug()<<pm<<endl;
                QListWidgetItem* c = new QListWidgetItem;
                c->setText(pm);
                UserList.push_back(*c);
                ui->PV_ListWidget->insertItem(0,c);
                break;
            }
        }
        user_num = msg_num;
        stepU++;
        emit userlist_done();
}

void ServerThread::replyFinished_group(QNetworkReply *reply)
{
    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;
    for(int i = 12;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();
        qDebug()<< msg_num << endl;


        for(int i = 0;i < msg_num;i++)
        {
           if(msg_num != group_num && stepG == 1)
           {
                pm = (jsobj[QString("block %1").arg(i)].toObject()["group_name"]).toString();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QDir dir;
                QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\";
                full_address += pm;
                dir.mkpath(full_address);
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\list1.txt");
                file.open(QIODevice::Append);
                QDataStream ds(&file);
                ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
                file.close();


                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                    qDebug()<<pm<<endl;
                    QListWidgetItem* c = new QListWidgetItem;
                    c->setText(pm);
                    GroupList.push_back(*c);
                    ui->Group_ListWidget->insertItem(0,c);
           }
           else if(msg_num != group_num && stepG != 1)
           {
               pm = (jsobj[QString("block %1").arg(msg_num - 1)].toObject()["group_name"]).toString();

               //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
               QDir dir;
               QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\";
               full_address += pm;
               dir.mkpath(full_address);
               //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
               QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\list2.txt");
               file.open(QIODevice::Append);
               QDataStream ds(&file);
               ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
               file.close();

               //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------



               qDebug()<<pm<<endl;
               QListWidgetItem* c = new QListWidgetItem;
               c->setText(pm);
               GroupList.push_back(*c);
               ui->Group_ListWidget->insertItem(0,c);
               break;
           }

        }
    group_num = msg_num;
    stepG++;
    emit grouplist_done();
}

void ServerThread::replyFinished_channel(QNetworkReply *reply)
{
    QString pm;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;
    for(int i = 12;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();
        qDebug()<< msg_num << endl;
        for(int i = 0;i < msg_num;i++)
        {
            if(msg_num != channel_num && stepC == 1)
            {
                pm = (jsobj[QString("block %1").arg(i)].toObject()["channel_name"]).toString();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QDir dir;
                QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\";
                full_address += pm;
                dir.mkpath(full_address);
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\list1.txt");
                file.open(QIODevice::Append);
                QDataStream ds(&file);
                ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
                file.close();
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                qDebug()<<pm<<endl;
                QListWidgetItem* c = new QListWidgetItem;
                c->setText(pm);
                ChannelList.push_back(*c);
                ui->Channel_ListWidget->insertItem(0,c);
            }
            else if(msg_num != channel_num && stepC != 1)
            {
                pm = (jsobj[QString("block %1").arg(msg_num - 1)].toObject()["channel_name"]).toString();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QDir dir;
                QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\";
                full_address += pm;
                dir.mkpath(full_address);
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                QFile file("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\list2.txt");
                file.open(QIODevice::Append);
                QDataStream ds(&file);
                ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
                file.close();

                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                qDebug()<<pm<<endl;
                QListWidgetItem* c = new QListWidgetItem;
                c->setText(pm);
                ChannelList.push_back(*c);
                ui->Channel_ListWidget->insertItem(0,c);
                break;
            }


        }
    channel_num = msg_num;
    stepC++;
    emit channellist_done();
}

void ServerThread::replyFinished_user_chats(QNetworkReply *reply)
{
    QString pm;
    QString src;
    QString dst;
    QString date;
    QString Final_Display_Message;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;
    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();
    User_Message_Number[dst_pv] = msg_num;
        qDebug()<< msg_num << endl;
    if(msg_num == 0)
    {
        ui->textBrowser->clear();
    }

    {
        int i = 0;
        QString x = (jsobj[QString("block %1").arg(i)].toObject()["dst"]).toString();

        QFile f("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\" + x + "\\msg_num.txt");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&f);
        ts << msg_num;
        f.close();
    }


        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["body"]).toString();
            qDebug()<< pm<< endl;
            src = (jsobj[QString("block %1").arg(i)].toObject()["src"]).toString();
            qDebug()<< src<< endl;
            dst = (jsobj[QString("block %1").arg(i)].toObject()["dst"]).toString();
            qDebug()<< dst<< endl;
            date = (jsobj[QString("block %1").arg(i)].toObject()["date"]).toString();
            qDebug()<< date << endl;
            Final_Display_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
            qDebug()<< Final_Display_Message << endl;
            ui->textBrowser->setText(Final_Display_Message);

            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV\\" + dst + "\\chat.txt";
            QFile file(full_address);
            file.open(QIODevice::Append);
            QDataStream ds(&file);
            ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
            file.close();
            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            qDebug() << pm << endl << endl;



        }

        emit userchats_done();
}

void ServerThread::replyFinished_group_chats(QNetworkReply *reply)
{
    QString pm;
    QString src;
    QString dst;
    QString date;
    QString Final_Display_Message;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;
    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();
    Group_Message_Number[dst_gp] = msg_num;
        qDebug()<< msg_num << endl;
        if(msg_num == 0)
        {
            ui->textBrowser->clear();
        }





        QFile f("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\" + dst_gp + "\\msg_num.txt");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&f);
        ts << msg_num;
        f.close();



        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["body"]).toString();
            qDebug()<< pm<< endl;
            src = (jsobj[QString("block %1").arg(i)].toObject()["src"]).toString();
            qDebug()<< src<< endl;
            dst = (jsobj[QString("block %1").arg(i)].toObject()["dst"]).toString();
            qDebug()<< dst<< endl;
            date = (jsobj[QString("block %1").arg(i)].toObject()["date"]).toString();
            qDebug()<< date << endl;
            Final_Display_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
            qDebug()<< Final_Display_Message << endl;
            ui->textBrowser->setText(Final_Display_Message);
            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP\\" + dst + "\\chat.txt";
            QFile file(full_address);
            file.open(QIODevice::Append);
            QDataStream ds(&file);
            ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
            file.close();
            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            qDebug() << pm << endl << endl;



        }
        emit groupchats_done();
}

void ServerThread::replyFinished_channel_chats(QNetworkReply *reply)
{
    QString pm;
    QString src;
    QString dst;
    QString date;
    QString Final_Display_Message;
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj;
    jsobj = jsdoc.object();
    ui->MessageBox->setText(jsobj["message"].toString());
    QString msg = jsobj["message"].toString();
    QString message_num;
    qDebug() << msg << endl;
    int j = 0;

    for(int i = 11;msg[i] != '-';i++ , j++)
    {
        message_num[j] = msg[i];
        //qDebug()<<msg[i] << endl;
    }
    int msg_num = message_num.toInt();
    Channel_Message_Number[dst_channel] = msg_num;
        qDebug()<< msg_num << endl;
        if(msg_num == 0)
        {
            ui->textBrowser->clear();
        }


        QFile f("C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\" + dst_channel + "\\msg_num.txt");
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ts(&f);
        ts << msg_num;
        f.close();



        for(int i = 0;i < msg_num;i++)
        {
            pm = (jsobj[QString("block %1").arg(i)].toObject()["body"]).toString();
            qDebug()<< pm<< endl;
            src = (jsobj[QString("block %1").arg(i)].toObject()["src"]).toString();
            qDebug()<< src<< endl;
            dst = (jsobj[QString("block %1").arg(i)].toObject()["dst"]).toString();
            qDebug()<< dst<< endl;
            date = (jsobj[QString("block %1").arg(i)].toObject()["date"]).toString();
            qDebug()<< date << endl;
            Final_Display_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
            qDebug()<< Final_Display_Message << endl;
            ui->textBrowser->setText(Final_Display_Message);
            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            QString full_address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel\\" + dst + "\\chat.txt";
            QFile file(full_address);
            file.open(QIODevice::Append);
            QDataStream ds(&file);
            ds << QJsonDocument(jsobj[QString("block %1").arg(i)].toObject()).toVariant();
            file.close();
            //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            qDebug() << pm << endl << endl;



        }
        emit channelchats_done();
}

void ServerThread::run()
{

    QEventLoop my_loop;
    Thread_netManager = new QNetworkAccessManager(this);
    Send_User = new QNetworkAccessManager(this);
    Send_Group = new QNetworkAccessManager(this);
    Send_Channel = new QNetworkAccessManager(this);

    JoinChannel = new QNetworkAccessManager(this);
    JoinGroup = new QNetworkAccessManager(this);
    MakeChannel = new QNetworkAccessManager(this);
    MakeGroup = new QNetworkAccessManager(this);

    startchat = new QNetworkAccessManager(this);

    while(ok)
    {
    connect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_user);
        getuserlist();
        QTimer::singleShot( 200,&my_loop,SLOT(quit()) );
        my_loop.exec();
    disconnect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_user);
    //------------------------------------------------------------------------------------------------------
    qDebug() << "Disconnected\n";
    connect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_group);
    qDebug() << "Connected\n";
        getgrouplist();
        QTimer::singleShot( 200,&my_loop,SLOT(quit()) );
        my_loop.exec();
    disconnect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_group);
    //------------------------------------------------------------------------------------------------------
    qDebug() << "Disconnected\n";
    connect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_channel);
    qDebug() << "Connected\n";
        getchannellist();
        QTimer::singleShot( 200,&my_loop,SLOT(quit()) );
        my_loop.exec();
    disconnect(Thread_netManager, &QNetworkAccessManager::finished,this, &ServerThread::replyFinished_channel);
    //------------------------------------------------------------------------------------------------------
    connect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_user_chats);
    if(dst_pv.isEmpty())
    {

    }
    else
    {
        getuserchats();
        QTimer::singleShot( 200,&my_loop,SLOT(quit()) );
        my_loop.exec();
    }
    disconnect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_user_chats);
    //---------------------------------------------------------------------------------------------------------
    connect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_group_chats);
    if(dst_gp.isEmpty())
    {

    }
    else
    {
        getgroupchats();
    }
    disconnect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_group_chats);
    //---------------------------------------------------------------------------------------------------------
    connect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_channel_chats);
    if(dst_channel.isEmpty())
    {

    }
    else
    {
        getchannelchats();
    }
    disconnect(Thread_netManager,&QNetworkAccessManager::finished,this,&ServerThread::replyFinished_channel_chats);
    //---------------------------------------------------------------------------------------------------------




    }

}

