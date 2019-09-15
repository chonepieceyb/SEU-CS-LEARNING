#ifndef LOCALGAMESCENE_H
#define LOCALGAMESCENE_H

#include "gamescene.h"
#include "healthybar.h"
#include "energybar.h"
#include "angerbar.h"
#include "explodingitem.h"
#include "guiflyitem.h"
#include <QEvent>
#include <QObject>
#include <QCloseEvent>

class LocalGameScene : public GameScene
{
Q_OBJECT
public:
    LocalGameScene();
    ~LocalGameScene();


    // 关闭窗口时killTimer,
//自定义信号
signals:
    void gameover1PSignal();
    void gameover2PSignal();
    void gameoverBothSignal();


protected:
    // 游戏线程
    void timerEvent(QTimerEvent *);

    bool event(QEvent *);



private:
    Player1P m_item1;
    Player2P m_item2;
    HealthyBar m_healthBar_1;
    HealthyBar m_healthBar_2;
    EnergyBar m_energyBar_1;
    EnergyBar m_energyBar_2;
    AngerBar m_angerBar_1;
    AngerBar m_angerBar_2;
    ExplodingItem m_explodingitem;
};

#endif // LOCALGAMESCENE_H
