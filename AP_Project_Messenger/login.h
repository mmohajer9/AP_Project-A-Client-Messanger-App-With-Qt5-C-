#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_clicked();
    void replyFinished(QNetworkReply *reply);

    void on_logout_clicked();

    void on_offlinemode_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
