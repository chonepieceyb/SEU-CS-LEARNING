#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "guiflyitem.h"
#include "rule.h"
#include "player1p.h"
#include "player2p.h"
#include <QSound>
#include <QEvent>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QGraphicsScene>
#include <QMediaPlayer>

#include<QDir>
#include<QUrl>

enum NETFLAG{SERVER, CLIENT};
class GameScene: public QGraphicsScene
{

public:
    GameScene();
    ~GameScene();

    bool getIsGameOver1PFlag()const;
    void setIsGameOver1PFlag(bool);
    bool getIsGameOver2PFlag()const;
    void setIsGameOver2PFlag(bool);
protected:
    //与游戏规则有关的函数
    bool isAttacked( PlayerItem& attackingitem, PlayerItem& attackeditem2); //判断攻击的函数
    //判断1P和2P是否碰上，如果item1的左边被挡住就返回-1，右边被挡住返回0,没有被挡住返回1(同时该函数也能够设定item2的状态，但是返回的是Item1的）
    int isCollided( PlayerItem& originalItem1, PlayerItem& targetItem2);
    GuiFlyItem* m_guiFlyItem;

    QGraphicsPixmapItem m_vs;
    bool m_isGameOver1P;
    bool m_isGameOver2P;

    //停止timer的标志位
    bool m_stopTimer;
private: 
    // scene大小
    QRectF size;
    // 音效
    QSound *m_riotHitSound;
    QSound *m_swordHitSound;
    QMediaPlayer *m_backgroundMusic;
    QMediaPlaylist *m_backgroundList;


};


#endif // GAMESCENE_H
