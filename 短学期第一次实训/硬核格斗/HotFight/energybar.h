#ifndef ENERGYBAR_H
#define ENERGYBAR_H

#include "healthybar.h"
#include <QGraphicsObject>
#include <QPen>
#include <QColor>
#include <QPainter>

class EnergyBar : public QGraphicsObject
{
public:
    EnergyBar();
    void setEnergy(double);
    static int getMaxWdith();
    int getHeight()const;
    void setType(BAR_TYPE);
protected:
    QRectF boundingRect() const;
private:
    // 宽度 高度
    static const int MAX_WIDTH = 180; // 生命值为100时
    int m_width;  // 根据blood的数值转换
    int m_height;
    BAR_TYPE m_type;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // ENERGYBAR_H
