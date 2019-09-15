#ifndef EXPLODINGITEM_H
#define EXPLODINGITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QString>
#include <QList>
#include <QPixmap>
#include <QPainter>

class ExplodingItem : public QGraphicsItem
{
public:
    ExplodingItem();
    //加载资源的函数
    void init();

    //更新函数
    void updatePos();


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

    //是否可见的标志位
    bool isItemVisable;
protected:
    QRectF boundingRect() const;
    QList<QPixmap> p_exploding;
private:
    int m_width;
    int m_height;
    //在场景里的坐标
    int m_x;
    int m_y;
    int explodingIndex;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EXPLODINGITEM_H
