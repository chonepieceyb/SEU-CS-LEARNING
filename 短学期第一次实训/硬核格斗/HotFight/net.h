#ifndef NET_H
#define NET_H

#include "playeritem.h"
#include"guiflyitem.h"
#include"gamescene.h"
#include <QUdpSocket>
#include <QJsonObject>

class Net
{
public:
    Net();
    static void setNetWorkInfo(QJsonObject, PlayerItem &,GameScene&);
    static void sendJsInfo(QUdpSocket *, PlayerItem &,GameScene&);
    static void setNetInfo(QString, quint16);
private:
    static QString m_objectIp;
    static quint16 m_objectPort;
};

#endif // NET_H
