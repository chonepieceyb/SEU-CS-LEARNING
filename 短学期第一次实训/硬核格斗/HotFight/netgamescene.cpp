#include "netgamescene.h"
#include "net.h"
#include <QJsonDocument>


NetGameScene::NetGameScene(QString ip, int port)
{
    //设置初始的ip 和 端口
    setObjectIp(ip);
    setObjectPort(port);
    Net::setNetInfo(ip,port);
    m_netType = C1;
//    isSceneUdpConnected=false;
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(static_cast<quint16>(m_objectPort));
    startTimer(100);
    connect(m_udpSocket,&QUdpSocket::readyRead,this,&NetGameScene::onReceiveUdp);
    // 设置Scene大小
    setSceneRect(0,0,800,400);
    // 初始化人物位置
    m_item1.setPositonInfo(200, 350);
    m_item2.setPositonInfo(500, 350);
    m_item1.updatePos();
    m_item2.updatePos();
    //设置血条精力条的位置
    m_healthBar_1.setType(P1);
    m_healthBar_2.setType(P2);
    m_healthBar_1.setPos(0,0);
    m_healthBar_2.setPos(800-m_healthBar_2.getMaxWdith(),0);

    m_energyBar_1.setType(P1);
    m_energyBar_2.setType(P2);
    m_energyBar_1.setPos(0,m_healthBar_1.getHeight());
    m_energyBar_2.setPos(800-m_energyBar_2.getMaxWdith(),m_healthBar_1.getHeight());

    m_angerBar_1.setType(P1);
    m_angerBar_2.setType(P2);
    m_angerBar_1.setPos(0,m_healthBar_1.getHeight()+m_energyBar_1.getHeight());
    m_angerBar_2.setPos(800-m_angerBar_2.getMaxWdith(),m_healthBar_1.getHeight()+m_energyBar_1.getHeight());
    //增加血条精力条
    addItem(&m_healthBar_1);
    addItem(&m_healthBar_2);
    addItem(&m_energyBar_1);
    addItem(&m_energyBar_2);
    addItem(&m_item1);
    addItem(&m_item2);
    addItem(&m_explodingitem);
    addItem(&m_angerBar_1);
    addItem(&m_angerBar_2);
    addItem(&m_vs);
    m_explodingitem.setVisible(false);
    //测试用
    qDebug()<<"2P的y坐标:"<<m_item2.getY();
}

NetGameScene::~NetGameScene()
{
   if(m_udpSocket!=NULL)
   {
       m_udpSocket->disconnectFromHost();
       delete m_udpSocket;
       m_udpSocket=NULL;
   }
}

void NetGameScene::timerEvent(QTimerEvent *event)
{
    if(m_stopTimer)
    {
        return ;
    }
   // 增加游戏线程，只需要判断操作的一方
    if(m_netType==C1)
    {
        Rule::recoverEnergy(m_item1);
        Rule::recoverTenacity(m_item1);
        //判断硬直
        if(m_item1.getTenacity()==0)
        {
            m_item1.setAttackedState(PlayerItem::ISATTACKED);
        }
        if(m_item2.getTenacity()==0)
        {
            m_item2.setAttackedState(PlayerItem::ISATTACKED);
        }
    }
    else if(m_netType==C2)
    {
         Rule::recoverEnergy(m_item2);
         Rule::recoverTenacity(m_item2);
         if(m_item1.getTenacity()==0)
         {
             m_item1.setAttackedState(PlayerItem::ISATTACKED);
         }
         if(m_item2.getTenacity()==0)
         {
             m_item2.setAttackedState(PlayerItem::ISATTACKED);
         }
    }
    qDebug()<<"1:"<<m_item1.getBlood()<<"||"<<m_item1.getEnergy()<<"||"<<m_item1.getTenacity();
    qDebug()<<"2:"<<m_item2.getBlood()<<"||"<<m_item2.getEnergy()<<"||"<<m_item2.getTenacity();
    isCollided(m_item1,m_item2);   //1P 和2P的 碰撞检测，必须放在攻击检测的前面，否则ISATTACKED会被替换成 ISCOLLIDEDLEFT，以后可以考虑整合成一个大函数
    //人物的攻击判定  测试,

    m_item1.JudgeingAttack();
    if(m_item1.getAttackedFlag())
    {
        if(isAttacked(m_item1,m_item2))
        {
           if(m_item2.getCollidedState()==PlayerItem::ISCOLLIDEDLEFT)
           {
               m_explodingitem.setX(m_item2.x());
               m_explodingitem.setY(m_item2.y()-m_item2.getHeight()*4/5);
               //把爆炸物状态视为可见
               m_explodingitem.updatePos();
               m_explodingitem.isItemVisable=true;
               qDebug()<<m_explodingitem.getX()<<m_explodingitem.getY()<<m_explodingitem.scenePos();
           }
           else if(m_item2.getCollidedState()==PlayerItem::ISCOLLIDEDRIGHT)
           {
               m_explodingitem.setX(m_item2.x()+m_item2.getWidth());
               m_explodingitem.setY(m_item2.y()-m_item2.getHeight()*4/5);
               //把爆炸物状态视为可见
               m_explodingitem.updatePos();
               m_explodingitem.isItemVisable=true;
               qDebug()<<m_explodingitem.getX()<<m_explodingitem.getY()<<m_explodingitem.scenePos();
           }
        }
    }
    m_item2.JudgeingAttack();
    if(m_item2.getAttackedFlag())
    {
        if(isAttacked(m_item2,m_item1))
        {
           if(m_item1.getCollidedState()==PlayerItem::ISCOLLIDEDLEFT)
           {
                m_explodingitem.setX(m_item1.x()+m_item1.getWidth()*2/5);
                m_explodingitem.setY(m_item1.y()-m_item1.getHeight()*4/5);
                //把爆炸物状态视为可见
                m_explodingitem.updatePos();
                m_explodingitem.isItemVisable=true;
           }
           else if(m_item1.getCollidedState()==PlayerItem::ISCOLLIDEDRIGHT)
           {
               m_explodingitem.setX(m_item1.x()+m_item1.getWidth()*3/5);
               m_explodingitem.setY(m_item1.y()-m_item1.getHeight()*4/5);
               //把爆炸物状态视为可见
               m_explodingitem.updatePos();
               m_explodingitem.isItemVisable=true;
           }
        }
    }
//        龟派气功的伤害判定
//        如果还存在的话
    if(m_guiFlyItem!=NULL && m_item1.getState()!=PlayerItem::JUMP)
    {
        //飞行物还没有被销毁就一直保持大招状态
        m_item2.setState(PlayerItem::ULTIMATESKILL);
        //如果飞出场景之外了，那么就销毁，600暂时指的是场景的宽
        if( m_guiFlyItem->getX()<=0 || m_guiFlyItem->getX()>=800)
        {
            m_guiFlyItem->m_isExisting=false;
            delete m_guiFlyItem;
            m_guiFlyItem=NULL;
            m_item2.setState(PlayerItem::STAND);
            //将index重置
            m_item2.setUltimateSkillIndex(0);
        }
        else
        {
            if(m_guiFlyItem->collidesWithItem(&m_item1))
            {
                //测试用
                //伤害计算函数和碰撞效果的接口
                //碰撞特效
                m_explodingitem.setX(m_item1.x()+m_item1.getWidth()/2);
                m_explodingitem.setY(m_item1.y()-m_item1.getHeight()/2);
                //把爆炸物状态视为可见
                m_explodingitem.updatePos();
                m_explodingitem.isItemVisable=true;
                //伤害和削韧计算
                Rule::calculateBlood(m_item2,m_item1);
                Rule::calculateTenacity(m_item2,m_item1);
                //怒气
                Rule::calculateAnger(m_item1,m_item1.getAngerIncrease());
                m_item1.setState(PlayerItem::ISHITTING); //被打中了
                //打中了之后要销毁
                m_guiFlyItem->m_isExisting=false;
                delete m_guiFlyItem;
                m_guiFlyItem=NULL;
                m_item2.setState(PlayerItem::STAND);
                //将index重置
                m_item2.setUltimateSkillIndex(0);
            }
        }
    }
    //刷新龟派气功
    if(m_guiFlyItem!=NULL)
    {
        m_guiFlyItem->Flying();
        m_guiFlyItem->updatePos();
    }

    //刷新爆炸物
    if(m_explodingitem.isItemVisable)
    {

        m_explodingitem.setVisible(true);
    }
    else
    {

         m_explodingitem.setVisible(false);
    }


    //刷新血条和精力条和怒气条
    m_healthBar_1.setBlood(m_item1.getBlood());
    m_healthBar_2.setBlood(m_item2.getBlood());
    m_energyBar_1.setEnergy(m_item1.getEnergy());
    m_energyBar_2.setEnergy(m_item2.getEnergy());
    m_angerBar_1.setAnger(m_item1.getAnger());
    m_angerBar_2.setAnger(m_item2.getAnger());

    // 游戏线程 刷新视图和人物跑动 碰撞 跳跃
    //只需要可操控的角色进行奔跑即可
    if(m_netType==C1)
    {
        m_item1.jump();
        m_item1.run();
        m_item1.attackingMove();
    }
    else if(m_netType==C2)
    {
        m_item2.jump();
        m_item2.run();
        m_item2.attackingMove();
    }
    //设置游戏结束的flag
    if(m_item1.getBlood()<=0 && m_item2.getBlood()>0)
    {
        setIsGameOver1PFlag(true);
        setIsGameOver2PFlag(false);
    }
    else if(m_item2.getBlood()<=0 && m_item1.getBlood()>0)
    {
        setIsGameOver1PFlag(false);
        setIsGameOver2PFlag(true);
    }
    else if((m_item1.getBlood()<=0 && m_item2.getBlood()<=0))
    {
        setIsGameOver1PFlag(true);
        setIsGameOver2PFlag(true);
    }

    // 传输数据
    if(m_netType == C1)
        Net::sendJsInfo(m_udpSocket, m_item1,*this);
    else
        Net::sendJsInfo(m_udpSocket, m_item2,*this);

    Rule::restrictBorder(m_item1);
    Rule::restrictBorder(m_item2);
    m_item1.updatePos();
    m_item2.updatePos();

    //游戏结束的判定
    if(getIsGameOver1PFlag() && !getIsGameOver2PFlag())
    {
        m_stopTimer=true;
        emit gameover1PSignal();
    }
    else if(! getIsGameOver1PFlag() && getIsGameOver2PFlag())
    {
        m_stopTimer=true;
        emit gameover2PSignal();
    }
    else if(getIsGameOver1PFlag() && getIsGameOver2PFlag())
    {
        m_stopTimer=true;
        emit gameoverBothSignal();
    }

}

//set和get函数
void NetGameScene::setNetType( NETTYPE t_netType)
{
    m_netType=t_netType;
}
NetGameScene::NETTYPE  NetGameScene::getNetType(void)const
{
    return m_netType;
}

void NetGameScene::setObjectIp(const QString ip)
{
    m_objectIp=ip;
}

QString NetGameScene::getObjectIp(void)const
{
    return m_objectIp;
}
void NetGameScene::setObjectPort(const int port)
{
    m_objectPort=port;
}

int NetGameScene::getObjectPort(void)const
{
    return m_objectPort;
}

//接受键盘输入的槽函数
void NetGameScene::onReceiveUdp()
{
    qint64 size=m_udpSocket->pendingDatagramSize();
    QByteArray array;
    array.resize(size);
    m_udpSocket->readDatagram(array.data(),size);
    QJsonDocument doc = QJsonDocument::fromJson(array);
    if(m_netType == C1)
        Net::setNetWorkInfo(doc.object(), m_item2,*this);
    else
        Net::setNetWorkInfo(doc.object(), m_item1,*this);
}
//关闭套接字的函数
void NetGameScene::closeUdpSocket()
{
    if(m_udpSocket!=NULL)
    {
         m_udpSocket->abort();
    }
}

// 事件分发
bool NetGameScene::event(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::KeyPress:
            if(m_netType == C1)
                sendEvent(&m_item1, event);
            else
                sendEvent(&m_item2, event);
            return true;
        case QEvent::KeyRelease:
            if(m_netType == C1)
                sendEvent(&m_item1, event);
            else
                sendEvent(&m_item2, event);
            return true;
        default:
            return GameScene::event(event);
    }
}

