#include "netgamewindow.h"

NetGameWindow::NetGameWindow(QString ip, int port,QWidget *parent)
                             : QGraphicsView(parent),m_netGameScene(ip,port)
{
    setFixedSize(800,400);
    setScene(&m_netGameScene);
    this->setBackgroundBrush(QBrush(
                                 QPixmap(":/images/startui_background.gif").scaled(
                                     this->size(),
                                     Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    setStyleSheet("border: 0px;"
                  "padding: 0px;");

    //将子类的信号传出去
    connect(&m_netGameScene,&NetGameScene::gameover1PSignal,[=](){
        emit gameover1PSignal();
    });
    connect(&m_netGameScene,&NetGameScene::gameover2PSignal,[=](){
        emit gameover2PSignal();
    });
    connect(&m_netGameScene,&NetGameScene::gameoverBothSignal,[=](){
        emit gameoverBothSignal();
    });
        setFixedSize(800,400);
        setScene(&m_netGameScene);
        this->setBackgroundBrush(QBrush(
                                     QPixmap(":/images/startui_background.gif").scaled(
                                         this->size(),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation)));
        setStyleSheet("border: 0px;"
                      "padding: 0px;");
        setCursor(QCursor(QPixmap(":/images/mouse.png")));
}

//用来调用子类的set函数
void NetGameWindow::setSceneNetType(NetGameScene::NETTYPE Type)
{
    m_netGameScene.setNetType(Type);
}

 NetGameScene::NETTYPE NetGameWindow::getSceneNetType()const
 {
     return m_netGameScene.getNetType();
 }

 void NetGameWindow::setSceneIp(QString ip)
 {
    m_netGameScene.setObjectIp(ip);
 }

 QString NetGameWindow::getSceneIp()const
 {
     return m_netGameScene.getObjectIp();
 }
 void NetGameWindow::setScenePort(int port)
 {
     m_netGameScene.setObjectPort(port);
 }

 int NetGameWindow::getScenePort()const
 {
     return m_netGameScene.getObjectPort();
 }

 // 重载closeEvent 关闭窗口时停止udp传输
 void NetGameWindow::closeEvent(QCloseEvent *event)
 {
     m_netGameScene.closeUdpSocket();
 }
