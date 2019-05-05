#include "offlinemode.h"
#include "ui_offlinemode.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void OfflineMode::process()
{


    qDebug() << "helloooooo";
    qDebug() << USERNAME;
    Root_Address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME;
    PV_Address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\PV";
    GP_Address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\GP";
    Channel_Address = "C:\\Users\\MMM\\Desktop\\QT Projects\\build-AP_Project_Messenger-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\users\\" + USERNAME + "\\Channel";

    PVList1_Address = PV_Address + "\\list1.txt";
    PVList2_Address = PV_Address + "\\list2.txt";

    GPList1_Address = GP_Address + "\\list1.txt";
    GPList2_Address = GP_Address + "\\list2.txt";

    ChList1_Address = Channel_Address + "\\list1.txt";
    ChList2_Address = Channel_Address + "\\list2.txt";




    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    QFile file1(PVList1_Address);
    file1.open(QIODevice::ReadOnly);
    QDataStream ds1(&file1);
    QVariant variant1;

    for(;!ds1.atEnd();)
    {
        ds1 >> variant1;
        QJsonObject obj = variant1.toJsonObject();
        ui->PV->insertItem(0,obj["src"].toString());
    }
    file1.close();
    //-----------------------------------------------
    QFile file2(PVList2_Address);
    file2.open(QIODevice::ReadOnly);
    QDataStream ds2(&file2);
    QVariant variant2;

    for(;!ds2.atEnd();)
    {
        ds2 >> variant2;
        QJsonObject obj = variant2.toJsonObject();
        ui->PV->insertItem(0,obj["src"].toString());
    }
    file2.close();
    //-----------------------------------------------
    //-----------------------------------------------
    QFile file3(GPList1_Address);
    file3.open(QIODevice::ReadOnly);
    QDataStream ds3(&file3);
    QVariant variant3;

    for(;!ds3.atEnd();)
    {
        ds3 >> variant3;
        QJsonObject obj = variant3.toJsonObject();
        ui->GP->insertItem(0,obj["group_name"].toString());
    }
    file3.close();
    //-----------------------------------------------
    QFile file4(GPList2_Address);
    file4.open(QIODevice::ReadOnly);
    QDataStream ds4(&file4);
    QVariant variant4;

    for(;!ds4.atEnd();)
    {
        ds4 >> variant4;
        QJsonObject obj = variant4.toJsonObject();
        ui->GP->insertItem(0,obj["group_name"].toString());
    }
    file4.close();
    //-----------------------------------------------
    //-----------------------------------------------
    QFile file5(ChList1_Address);
    file5.open(QIODevice::ReadOnly);
    QDataStream ds5(&file5);
    QVariant variant5;

    for(;!ds5.atEnd();)
    {
        ds5 >> variant5;
        QJsonObject obj = variant5.toJsonObject();
        ui->Channel->insertItem(0,obj["channel_name"].toString());
    }
    file5.close();
    //-----------------------------------------------
    QFile file6(ChList2_Address);
    file6.open(QIODevice::ReadOnly);
    QDataStream ds6(&file6);
    QVariant variant6;



    for(;!ds6.atEnd();)
    {
        ds6 >> variant6;
        QJsonObject obj = variant6.toJsonObject();
        ui->Channel->insertItem(0,obj["channel_name"].toString());
    }
    file6.close();
    //-----------------------------------------------
    //-----------------------------------------------
    connect(ui->PV,&QListWidget::itemClicked,this,&OfflineMode::process2);
    connect(ui->GP,&QListWidget::itemClicked,this,&OfflineMode::process3);
    connect(ui->Channel,&QListWidget::itemClicked,this,&OfflineMode::process4);


}

void OfflineMode::process2(QListWidgetItem* item)
{
    ui->textBrowser->clear();
    QString src;
    QString dst;
    QString pm;
    QString date;


    QString Final_Message;

    QString name = item->text();
    QString adr = PV_Address + "\\" + name + "\\chat.txt";
    QString num_adr = PV_Address + "\\" + name + "\\msg_num.txt";
    QFile file(adr);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    QVariant variant;

    QFile f(num_adr);
    f.open(QIODevice::ReadOnly);
    QTextStream ts(&f);
    int msg_num;
    QString num;
    ts >> num;
    msg_num = num.toInt();


    for(int i = 0;i < msg_num;i++)
    {
        ds >> variant;
        QJsonObject obj = variant.toJsonObject();
        src = obj["src"].toString();
        dst = obj["dst"].toString();
        pm = obj["body"].toString();
        date = obj["date"].toString();
        Final_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
        ui->textBrowser->setText(Final_Message);

    }
}

void OfflineMode::process3(QListWidgetItem *item)
{
    ui->textBrowser->clear();
    QString src;
    QString dst;
    QString pm;
    QString date;


    QString Final_Message;

    QString name = item->text();
    QString adr = GP_Address + "\\" + name + "\\chat.txt";
    QString num_adr = GP_Address + "\\" + name + "\\msg_num.txt";
    QFile file(adr);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    QVariant variant;



    QFile f(num_adr);
    f.open(QIODevice::ReadOnly);
    QTextStream ts(&f);
    int msg_num;
    QString num;
    ts >> num;
    msg_num = num.toInt();


    for(int i = 0;i < msg_num;i++)
    {
        ds >> variant;
        QJsonObject obj = variant.toJsonObject();
        src = obj["src"].toString();
        dst = obj["dst"].toString();
        pm = obj["body"].toString();
        date = obj["date"].toString();
        Final_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
        ui->textBrowser->setText(Final_Message);

    }
}

void OfflineMode::process4(QListWidgetItem *item)
{
    ui->textBrowser->clear();
    QString src;
    QString dst;
    QString pm;
    QString date;


    QString Final_Message;

    QString name = item->text();
    QString adr = Channel_Address + "\\" + name + "\\chat.txt";
    QString num_adr = Channel_Address + "\\" + name + "\\msg_num.txt";
    QFile file(adr);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    QVariant variant;

    QFile f(num_adr);
    f.open(QIODevice::ReadOnly);
    QTextStream ts(&f);
    int msg_num;
    QString num;
    ts >> num;
    msg_num = num.toInt();


    for(int i = 0;i < msg_num;i++)
    {
        ds >> variant;
        QJsonObject obj = variant.toJsonObject();
        src = obj["src"].toString();
        dst = obj["dst"].toString();
        pm = obj["body"].toString();
        date = obj["date"].toString();
        Final_Message += src + " -> " + dst + " : " + pm + "\n" + date + "\n";
        ui->textBrowser->setText(Final_Message);

    }
}


OfflineMode::OfflineMode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OfflineMode)
{
    ui->setupUi(this);
    this->setFixedSize(1004,690);


}

OfflineMode::~OfflineMode()
{
    delete ui;
}

void OfflineMode::on_run_clicked()
{
    process();
}
