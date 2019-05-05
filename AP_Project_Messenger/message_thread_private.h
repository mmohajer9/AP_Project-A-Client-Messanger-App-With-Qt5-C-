#ifndef MESSAGE_THREAD_PRIVATE_H
#define MESSAGE_THREAD_PRIVATE_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class Message_Thread_Private : public QObject
{
    Q_OBJECT
public:
    explicit Message_Thread_Private(QObject *parent = nullptr);
    QJsonObject jsobj;
    int msg_num;
    QString Final;
protected:
    void run();
};

#endif // MESSAGE_THREAD_PRIVATE_H
