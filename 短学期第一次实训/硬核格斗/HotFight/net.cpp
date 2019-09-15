#include "net.h"
#include <QJsonDocument>

Net::Net()
{

}

QString Net::m_objectIp = "127.0.0.1";
quint16 Net::m_objectPort = 8888;
void Net::setNetWorkInfo(QJsonObject json, PlayerItem &item,GameScene& scene)
{
    item.setPositonInfo(json.take("m_x").toDouble(), json.take("m_y").toDouble());
    item.setState(static_cast<PlayerItem::STATE>(json.take("m_state").toInt()));
    item.setDirection(static_cast<PlayerItem::DIRECTION>(json.take("m_direction").toInt()));
    item.setSkillType(static_cast<PlayerItem::SKILLTYPE>(json.take("m_skillType").toInt()));
    item.setBlood(json.take("m_blood").toInt());
    item.setEnergy(json.take("m_energy").toInt());
    item.setTenacity(json.take("m_tenacity").toInt());
    item.setJumpCurrentV(json.take("m_jumpCurrentV").toDouble());
    scene.setIsGameOver1PFlag(json.take("m_isGameOver1P").toBool());
    scene.setIsGameOver2PFlag(json.take("m_isGameOver2P").toBool());
}

void Net::sendJsInfo(QUdpSocket *udp, PlayerItem &item,GameScene& scene)
{
    QJsonObject js;
    js.insert("m_x", item.getX());
    js.insert("m_y", item.getY());
    js.insert("m_state", item.getState());
    js.insert("m_direction", item.getDirection());
    js.insert("m_skillType", item.getSkillType());
    // 人物属性
    js.insert("m_blood", item.getBlood());
    js.insert("m_energy", item.getEnergy());
    js.insert("m_tenacity", item.getTenacity());


    //增加跳跃的CurrentV (在跳跃属性中 m_x,m_y都可以由远程端发送的信息决定，所以把在NetGameScene中
    //不用调用jump函数（run同理）但是因为jump的动画受到JumpCurrentV的控制，而JumpCurrentV又由Jump函数
    //决定，因此为了比较容易地解决jump动画的问题，直接增加传递jumpcurrentV
    js.insert("m_jumpCurrentV",item.getJumpCurrentV());

    //增加传一个游戏结束的flag
    js.insert("m_isGameOver1P",scene.getIsGameOver1PFlag());
    js.insert("m_isGameOver2P",scene.getIsGameOver2PFlag());


    // 后面增加状态
    QByteArray array;
    QJsonDocument doc;
    doc.setObject(js);
    array = doc.toJson(QJsonDocument::Compact);
    udp->writeDatagram(array.data(),QHostAddress(m_objectIp),m_objectPort);
}

void Net::setNetInfo(QString ip, quint16 port)
{
    m_objectIp = ip;
    m_objectPort = port;
}
