#ifndef NETCONNECTDIALOG_H
#define NETCONNECTDIALOG_H

#include <QDialog>
#include <QObject>
#include "netgamescene.h"
#include "netgamewindow.h"
#include <QMessageBox>
#include "endwindow.h"

namespace Ui {
class NetConnectDialog;
}

class NetConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetConnectDialog(QWidget *parent = nullptr);
    ~NetConnectDialog();

signals:
    void returnToStartWindowSignal();
    void restartSignal();
    void endGameSignal();
    void gameover1PSignal();
    void gameover2PSignal();
    void gameoverBothSignal();
public slots:
    void showEndWindow1PSlot();
    void showEndWindow2PSlot();
    void showEndWindowBothSlot();

private slots:
    void on_clientConnect_clicked();

    void on_clientCancel_clicked();

private:
    Ui::NetConnectDialog *ui;
    NetGameWindow *m_netGameWindow;
    EndWindow* m_endWindow;
};

#endif // NETCONNECTDIALOG_H
