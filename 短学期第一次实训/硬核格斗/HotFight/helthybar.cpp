#include "healthybar.h"


HealthyBar::HealthyBar()
{
    // 初始化血条
    m_width = MAX_WIDTH;
    m_height = 30;
}

void HealthyBar::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPen pen;
    pen.setColor("#FFFFFF");
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(0,0,MAX_WIDTH,m_height);
    painter->setBrush(QBrush(QColor("#e40737")));
    // 1p 2p血条削减方向不同
    if(m_type == P1)
        painter->drawRect(0,0,m_width,m_height);
    else
        painter->drawRect(MAX_WIDTH-m_width, 0,MAX_WIDTH,m_height);
}

QRectF HealthyBar::boundingRect() const
{
    return QRectF(0,0,MAX_WIDTH, m_height);
}

void  HealthyBar::setBlood(double blood)
{
    if(blood>=0 && blood<=100)
    {
        m_width=blood/100*MAX_WIDTH;
    }
    prepareGeometryChange();
}
int HealthyBar::getMaxWdith()
{
    return MAX_WIDTH;
}
int HealthyBar::getHeight()const
{
    return m_height;
}

void HealthyBar::setType(BAR_TYPE type)
{
    m_type = type;
}

