#include "angerbar.h"

AngerBar::AngerBar()
{
    // 初始化精力条
    m_width = MAX_WIDTH;
    m_height = 15;
}

void AngerBar::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPen pen;
    pen.setColor("#FFFFFF");
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(0,0,MAX_WIDTH,m_height);
    painter->setBrush(QBrush(QColor("#68b4e8")));
    if(m_type == P1)
        painter->drawRect(0,0,m_width,m_height);
    else
        painter->drawRect(MAX_WIDTH-m_width, 0,MAX_WIDTH,m_height);

}

QRectF AngerBar::boundingRect() const
{
    return QRectF(0,0,MAX_WIDTH, m_height);
}

void  AngerBar::setAnger(double anger)
{
    if(anger>=0 && anger<=100)
    {
        m_width=anger/100*MAX_WIDTH;
    }
    prepareGeometryChange();
}
int AngerBar::getMaxWdith()
{
    return MAX_WIDTH;
}
int AngerBar::getHeight()const
{
    return m_height;
}

void AngerBar::setType(BAR_TYPE type)
{
    m_type = type;
}

