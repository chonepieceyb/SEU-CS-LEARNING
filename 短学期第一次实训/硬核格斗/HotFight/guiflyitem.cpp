#include "guiflyitem.h"

GuiFlyItem::GuiFlyItem()
{
    init();
    guiFlyItemIndex=0;
    m_isExisting=false;

    //与飞行相关的属性
    m_originalV=1;
    m_flyAcceleration=5;  //以毫秒为时间单位

    //time放在游戏的线程函数中所以时间以毫秒计
    m_flyTime=0;


    m_x=0;
    m_y=0;
}

void  GuiFlyItem::init()
{
    for(int i=1;i<=8;i++)
    {
        p_guiFlyItem.append(QString(":/images/player4/guiflyitem/%1.png").arg(i));
    }
    //初始化宽高
    //在这个资源下所有的资源的宽高相差不多，去第一个资源的宽高作为整个item的宽高;
    m_width=p_guiFlyItem.at(0).width();
    m_height=p_guiFlyItem.at(0).height();
}

QRectF GuiFlyItem::boundingRect() const
{
     return QRectF(0,0,m_width,m_height);
}

void GuiFlyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(guiFlyItemIndex>=p_guiFlyItem.size()-1)
    {
       guiFlyItemIndex=0;
    }
    else
    {
         guiFlyItemIndex++;
    }
    if(m_flyDirection == RIGHT)
    {
        painter->drawImage(0, 0, p_guiFlyItem.at(guiFlyItemIndex).toImage());
    }
    else
        painter->drawImage(0, 0,p_guiFlyItem.at(guiFlyItemIndex).toImage().mirrored(true,false));
}
//更新函数
void GuiFlyItem::updatePos()
{
    setPos(m_x,m_y);
    prepareGeometryChange();

}

void GuiFlyItem::Flying()
{
    //如果飞行物不存在的话
    if(!m_isExisting)
    {
        return;
    }
    else
    {
        if(m_flyDirection==RIGHT)
        {
            m_x += m_originalV*m_flyTime +  0.5*m_flyAcceleration*(m_flyTime*m_flyTime);
        }
        else if(m_flyDirection==LEFT)
        {
            m_x -= m_originalV*m_flyTime +  0.5*m_flyAcceleration*(m_flyTime*m_flyTime);
        }
    }
    //飞行时间++
    m_flyTime++;
}

//set和get函数
void GuiFlyItem::setWidth(int width)
{
    m_width=width;
}
int GuiFlyItem::getWidth()const
{
    return m_width;
}
void GuiFlyItem::setHeight(int height)
{
    m_height = height;
}

int GuiFlyItem::getHeight()const
{
    return m_height;
}
void GuiFlyItem::setX(int x)
{
    m_x = x;
}

int GuiFlyItem::getX()const
{
    return m_x;
}

void GuiFlyItem::setY(int y)
{
    m_y=y;
}

int GuiFlyItem::getY()const
{
    return m_y;
}

void GuiFlyItem::setPosition(int x,int y)
{
    m_x=x;
    m_y=y;
}
void GuiFlyItem::setGuiFlyItemIndex(int index)
{
    guiFlyItemIndex=index;
}

int GuiFlyItem::getGuiFlyItemIndex()const
{
    return guiFlyItemIndex;
}
void GuiFlyItem::setOriginalV(int v )
{
    m_originalV=v;
}
int GuiFlyItem::getOriginalV()const
{
    return m_originalV;
}
void GuiFlyItem::setFlyAcceleration(int a )
{
    m_flyAcceleration=a;
}

int GuiFlyItem::getFlyAcceleration()const
{
    return m_flyAcceleration;
}

void GuiFlyItem::setFlyTime(int time)
{
    m_flyTime=time;
}

int GuiFlyItem::getFlyTime()const
{
    return m_flyTime;
}
void GuiFlyItem::setFlyDirection(FLYDIRECTION direction)
{
    m_flyDirection=direction;

}

GuiFlyItem::FLYDIRECTION GuiFlyItem::getFlyDirection()const
{
    return m_flyDirection;
}
