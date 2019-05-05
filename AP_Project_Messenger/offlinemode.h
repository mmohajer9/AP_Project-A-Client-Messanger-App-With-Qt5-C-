#ifndef OFFLINEMODE_H
#define OFFLINEMODE_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <login.h>
#include <ui_login.h>
#include <QDataStream>
#include <QVariant>
#include <QListWidget>
namespace Ui {
class OfflineMode;
}

class OfflineMode : public QMainWindow
{
    Q_OBJECT

public:
    void process();
    void process2(QListWidgetItem *item);
    void process3(QListWidgetItem *item);
    void process4(QListWidgetItem *item);


    QString USERNAME;


    explicit OfflineMode(QWidget *parent = 0);
    ~OfflineMode();

private:
    QString Root_Address;
    QString PV_Address;
    QString GP_Address;
    QString Channel_Address;

    QString PVList1_Address;
    QString PVList2_Address;

    QString GPList1_Address;
    QString GPList2_Address;

    QString ChList1_Address;
    QString ChList2_Address;



    Ui::OfflineMode *ui;
    Ui::Login *login_ui;
signals:
    void done();

private slots:
    void on_run_clicked();
};

#endif // OFFLINEMODE_H
