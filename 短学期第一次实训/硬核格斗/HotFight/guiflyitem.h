#ifndef GUIFLYITEM_H
#define GUIFLYITEM_H

#include<QGraphicsItem>
#include<QRectF>
#include<QString>
#include<QList>
#include<QPixmap>
#include<QPainter>

class GuiFlyItem : public QGraphicsItem
{
public:
    enum FLYDIRECTION{LEFT,RIGHT};
    GuiFlyItem();
    //加载资源的函数
    void init();

    //更新函数
    void updatePos();

    //判断是否已经存在与场景中的变量
    bool m_isExisting;

    void Flying(); //飞行物飞行的函数


    //get 和 set函数
    void setWidth(int);
    int getWidth()const;
    void setHeight(int);
    int getHeight()const;
    void setX(int);
    int getX()const;
    void setY(int);
    int getY()const;
    void setPosition(int x,int y);
    void setGuiFlyItemIndex(int);
    int getGuiFlyItemIndex()const;
    void setOriginalV(int);
    int getOriginalV()const;
    void setFlyAcceleration(int );
    int getFlyAcceleration()const;
    void setFlyTime(int);
    int getFlyTime()const;
    void setFlyDirection(FLYDIRECTION);
    FLYDIRECTION getFlyDirection()const;

protected:
    QRectF boundingRect() const;
    QList<QPixmap> p_guiFlyItem;
private:
    int m_width;
    int m_height;
    //在场景里的坐标
    int m_x;
    int m_y;
    int guiFlyItemIndex;

    //飞行的初速度
    int m_originalV;
    //飞行的加速度;
    int m_flyAcceleration;
    //飞行的时间
    int m_flyTime;
    //飞行的方向
    FLYDIRECTION m_flyDirection;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GUIFLYITEM_H
