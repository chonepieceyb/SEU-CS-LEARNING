#ifndef NETGAMEWINDOW_H
#define NETGAMEWINDOW_H

#include "netgamescene.h"
#include <QGraphicsView>
#include<QCloseEvent>
#include<QMessageBox>
#include<QObject>

class NetGameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    //ip 和端口参数是成员初始化需要的,并且有默认值
    NetGameWindow(QString ip="127.0.0.1",int port=8888,QWidget *parent = nullptr);

    //用来调用子类的set和get函数
    void setSceneNetType(NetGameScene::NETTYPE);
    NetGameScene::NETTYPE getSceneNetType()const;
    void setSceneIp(QString);
    QString getSceneIp()const;
    void setScenePort(int);
    int getScenePort()const;

signals:
    void gameover1PSignal();
    void gameover2PSignal();
    void gameoverBothSignal();

protected:
    void closeEvent(QCloseEvent *);
private:
    NetGameScene m_netGameScene;

};

#endif // NETGAMEWINDOW_H
