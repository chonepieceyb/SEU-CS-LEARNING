#include "energybar.h"

EnergyBar::EnergyBar()
{
    // 初始化精力条
    m_width = MAX_WIDTH;
    m_height = 15;
}

void EnergyBar::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPen pen;
    pen.setColor("#FFFFFF");
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(0,0,MAX_WIDTH,m_height);
    painter->setBrush(QBrush(QColor("#66ff66")));
    if(m_type == P1)
        painter->drawRect(0,0,m_width,m_height);
    else
        painter->drawRect(MAX_WIDTH-m_width, 0,MAX_WIDTH,m_height);

}

QRectF EnergyBar::boundingRect() const
{
    return QRectF(0,0,MAX_WIDTH, m_height);
}

void  EnergyBar::setEnergy(double energy)
{
    if(energy>=0 && energy<=100)
    {
        m_width=energy/100*MAX_WIDTH;
    }
    prepareGeometryChange();
}
int EnergyBar::getMaxWdith()
{
    return MAX_WIDTH;
}
int EnergyBar::getHeight()const
{
    return m_height;
}

void EnergyBar::setType(BAR_TYPE type)
{
    m_type = type;
}
