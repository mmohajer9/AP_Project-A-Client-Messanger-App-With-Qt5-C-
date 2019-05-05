#ifndef MAINCHAT_H
#define MAINCHAT_H

#include <QMainWindow>
#include <QNetworkReply>
#include <serverthread.h>
namespace Ui {
class Mainchat;

}
class ServerThread;
class MainThread;
class Mainchat : public QMainWindow
{
    Q_OBJECT

public:
    ServerThread* SThread;



    void closeEvent (QCloseEvent *event);
    explicit Mainchat(QWidget *parent = 0);
    ~Mainchat();

private slots:
    void replyFinished(QNetworkReply *reply);
    void on_Logout_clicked();


private:
    Ui::Mainchat *ui;
};

#endif // MAINCHAT_H
