#include "mainwindow.h"
#include <QApplication>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QMovie>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Welcome To Messenger Program (MamadGram)");
    w.setFixedSize(552,626);
    w.setToolTipDuration(2000);
    return a.exec();
}
