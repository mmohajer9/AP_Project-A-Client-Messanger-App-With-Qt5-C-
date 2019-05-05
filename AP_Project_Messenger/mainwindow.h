#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void open_signup();

    void open_login();
private slots:
    void on_Signup_clicked();

    void on_Login_clicked();

    void on_iutlogo_clicked();

private:
    Ui::MainWindow *ui;


};


#endif // MAINWINDOW_H
