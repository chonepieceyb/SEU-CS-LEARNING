#ifndef HEALTHBAR_H
#define HEALTHBAR_H


#include <QGraphicsObject>
#include <QPen>
#include <QColor>
#include <QPainter>

enum BAR_TYPE{ P1,P2};
class HealthyBar: public QGraphicsObject
{
public:
    HealthyBar();
    void setBlood(double);
    static int getMaxWdith();
    int getHeight()const;
    void setType(BAR_TYPE);
protected:
    QRectF boundingRect() const;
private:
    // 宽度 高度
    static const int MAX_WIDTH = 350; // 生命值为100时
    int m_width;  // 根据blood的数值转换
    int m_height;
    BAR_TYPE m_type;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // HEALTHBAR_H
