#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QNetworkReply>
namespace Ui {
class Signup;
}

class Signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = 0);
    ~Signup();
public slots:

private slots:
    void on_complete_signup_clicked();
    void replyFinished(QNetworkReply *);
    void on_close_signup_clicked();

private:
    Ui::Signup *ui;

};

#endif // SIGNUP_H
