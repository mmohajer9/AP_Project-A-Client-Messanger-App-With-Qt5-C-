#include "message_thread_private.h"
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
#include <message_thread_private.h>
Message_Thread_Private::Message_Thread_Private(QObject *parent)
    : QThread(parent)
{
}

void Message_Thread_Private::run()
{

}
