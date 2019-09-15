#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "localgamewindow.h"
#include "netgamewindow.h"
#include "netconnectdialog.h"
#include "help.h"
#include <QWidget>

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    enum WINDOWTYPE{NOWINDOW,LOCAL,NET};
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

    void setWindowType(WINDOWTYPE);
    WINDOWTYPE getWindowType()const;
public slots:
    void closeLocalGameSlot();
    void closeNetGameSlot();
    void restartNetGameSlot();
    void endGameSlot();
private slots:
    void on_btnLocalGame_clicked();

    void on_btnNetGame_clicked();

    void on_btnHelp_clicked();

private:
    WINDOWTYPE m_windowType;
    Ui::StartWindow *ui;

    // 单机游戏界面
    LocalGameWindow *m_localGame;

    //必须先进入联网的客户段的窗口
    NetConnectDialog *m_netConnectDialog;
    //帮助界面
    Help *m_helpWindow;

};

#endif // STARTWINDOW_H
