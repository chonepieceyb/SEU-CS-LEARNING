#include "explodingitem.h"
#include<QGraphicsItem>

ExplodingItem::ExplodingItem()
{
    init();
    explodingIndex=0;
    m_x=0;
    m_y=0;
}

void  ExplodingItem::init()
{
    for(int i=1;i<=5;i++)
    {
        p_exploding.append(QString(":/images/exploding/%1.png").arg(i));
    }
    //初始化宽高
    //在这个资源下所有的资源的宽高都是一致的;
    m_width=p_exploding.at(0).width();
    m_height=p_exploding.at(0).height();
}

QRectF ExplodingItem::boundingRect() const
{
     return QRectF(0,0,m_width,m_height);
}

void ExplodingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(explodingIndex>=p_exploding.size()-1)
    {
        explodingIndex=0;
        isItemVisable=false;
    }
    else
    {
        explodingIndex++;
    }
    painter->drawPixmap(0,0,p_exploding.at(explodingIndex));
}
//更新函数
void ExplodingItem::updatePos()
{
    setPos(m_x,m_y);
    prepareGeometryChange();

}

//set和get函数
void ExplodingItem::setWidth(int width)
{
    m_width=width;
}
int ExplodingItem::getWidth()const
{
    return m_width;
}
void ExplodingItem::setHeight(int height)
{
    m_height = height;
}

int ExplodingItem::getHeight()const
{
    return m_height;
}
void ExplodingItem::setX(int x)
{
    m_x = x;
}

int ExplodingItem::getX()const
{
    return m_x;
}

void ExplodingItem::setY(int y)
{
    m_y=y;
}

int ExplodingItem::getY()const
{
    return m_y;
}

void ExplodingItem::setPosition(int x,int y)
{
    m_x=x;
    m_y=y;
}
