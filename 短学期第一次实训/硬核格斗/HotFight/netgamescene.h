#ifndef NETGAMESCENE_H
#define NETGAMESCENE_H

#include "gamescene.h"
#include "netplayer1p.h"
#include "netplayer2p.h"
#include "healthybar.h"
#include "energybar.h"
#include "angerbar.h"
#include "explodingitem.h"
#include <QEvent>
#include <QUdpSocket>
#include <QGraphicsScene>
#include <QObject>

class NetGameScene : public GameScene
{
 Q_OBJECT
public:
//    bool isSceneUdpConnected;
    //构造函数需要ip 和 port作为参数， 并且默认的Ip是127.0.0.1 默认端口是8888
    NetGameScene(QString ip="127.0.0.1", int port=8888);
    ~NetGameScene();
    enum NETTYPE{C1,C2};
    //关闭套接字的函数
    void closeUdpSocket();

    //set 和 get的函数

    void setNetType( NETTYPE);
    NETTYPE getNetType(void)const;
    void setObjectIp(const QString);
    QString getObjectIp(void)const;
    void setObjectPort(const int);
    int getObjectPort(void)const;

signals:
    void gameover1PSignal();
    void gameover2PSignal();
    void gameoverBothSignal();

protected:
    //游戏线程
    void timerEvent(QTimerEvent *);
    // 重载事件分发
    bool event(QEvent *);
private slots:
    void onReceiveUdp();
private:
    QString m_objectIp;
    int m_objectPort;
    // 传输数据套接字
    QUdpSocket *m_udpSocket;
    // 游戏元素
    NetPlayer1P m_item1;
    NetPlayer2P m_item2;
    HealthyBar m_healthBar_1;
    HealthyBar m_healthBar_2;
    EnergyBar m_energyBar_1;
    EnergyBar m_energyBar_2;
    AngerBar m_angerBar_1;
    AngerBar m_angerBar_2;
    ExplodingItem m_explodingitem;
    //窗口的类型，是客户端或者是服务器
    // 调试时在构造函数里面设置，实际用对话框设置
    NETTYPE m_netType;
};

#endif // NETGAMESCENE_H
