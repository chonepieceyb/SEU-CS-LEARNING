#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include "keyboardbuffer.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QList>
#include <QWidget>
#include <QObject>
#include <QGraphicsObject>
#include <QTimerEvent>
#include <QPainterPath>


/*
 *  角色基类
 *  1P 2P需重载键盘操作事件
 *  子类需重载加载资源函数
*/
class PlayerItem : public QGraphicsObject
{
public:
    // 被规则所支配
    friend class Rule;

    //与运动(角色动画）有关的状态,新增终结技状态
    enum STATE{JUMP, PUNCH, KICK, RUN, STAND,ISHITTING, SKILL,ULTIMATESKILL};
    //判断招式种类的枚举常量
    enum SKILLTYPE{SKILLONE,SKILLTWO,SKILLTHREE,SKILLFOUR,SKILLFIVE,SKILLSIX,NONESKILL};
    enum DIRECTION{LEFT, RIGHT};
    //与战斗时碰撞有关的状态 目前ISATTACKED表示格斗游戏中的硬直状态
    // ISHITTING 和ISATTACKED所表示的意义相同，但是用在不同的函数上
    enum COLLIDEDSTATE{NOCOLLIDED,ISCOLLIDEDLEFT,ISCOLLIDEDRIGHT};
    enum ATTACKEDSTATE{NOATTACKED,ISATTACKED};

    //因为某些功能因为角色、加载的资源不同存在分歧，用这个枚举量来进行区分
    enum CHARACTERFlAG{C1,C2};


    PlayerItem();
    ~PlayerItem();


    //重载shape函数
    virtual QPainterPath shape()const;

    // 功能函数
    // 需在scene中调用
    void run();
    void jump();
    void attackingMove(); //攻击的位移补偿，需要在scene中调用

    // 跳跃开始设置速度
    void jumpStart();

    // GameScene中调用设置人物位置
    void setPositonInfo(qreal, qreal);

    // 刷新设置人物位置
    void updatePos();

    //攻击的时候根据特定攻击动作的判定帧来决定attackingflag的值
    virtual void JudgeingAttack();



    //所有的get和set函数
    void setState(STATE);
    STATE getState()const;
    void setDirection(DIRECTION);
    DIRECTION getDirection()const;
    void setCollidedState(COLLIDEDSTATE);
    COLLIDEDSTATE getCollidedState()const;
    void setSkillType(SKILLTYPE);
    SKILLTYPE getSkillType()const;
    void setAttackedState(ATTACKEDSTATE);
    ATTACKEDSTATE getAttackedState()const;
    void setCharacterFlag(CHARACTERFlAG);
    CHARACTERFlAG getCharacterFlag()const;


    void setX(qreal);
    qreal getX()const;
    void setY(qreal);
    qreal getY()const;
    void setHeight(int);
    int getHeight()const;
    void setWidth(int);
    int getWidth()const;
    void setSpeed(int);
    int getSpeed()const;
    void setBlood(int);
    int  getBlood()const;

    void setEnergy(int);
    int getEnergy()const;
    void setTenacity(int);
    int getTenacity()const;

    void setAttackingFlag(bool);
    bool getAttackedFlag()const;

    void setDamageFlag(bool);
    bool getDamageFlag()const;

    void setHasDamagedFlag(bool);
    bool getHasDamagedFlag()const;

    void setJumpCurrentV(qreal);
    qreal getJumpCurrentV()const;

    //龟派气功动作的需要
    void setUltimateSkillIndex(int);
    int getUltimateSkillIndex()const;

    void setAnger(int);
    int getAnger()const;

    void setAngerIncrease(int);
    int getAngerIncrease()const;
protected:

    //人物状态变量 子类重载暂时需直接修改 变为保护型 在该类的构造函数中初始化
    STATE m_state;
    //为了改善操作手感而设计的变量,上一次的状态。
    STATE m_lastState;
    DIRECTION m_direction;
    COLLIDEDSTATE m_collidedState;
    SKILLTYPE m_skillType;
    ATTACKEDSTATE m_attackedState;
     //因为某些功能因为角色、加载的资源不同存在分歧，用这个成员变量来进行区分
    CHARACTERFlAG m_characterFlag;
    //攻击的模式，近战或者远程


    // 加载图片资源
    // 子类需直接加载资源 将私有变成保护型  在子类的资源加载函数中进行初始化
    // 调试： standing设为动态 改为QList
    QList<QPixmap> p_standing;
    QList<QPixmap> p_running;
    QList<QPixmap> p_punch;
    QList<QPixmap> p_ishitting;
    QList<QPixmap> p_kicking;
    QList<QPixmap> p_jumping;
    QList<QList<QPixmap>> p_skill;
    QList<QPixmap> p_ultimateSkill;

    // 图片的path 在shape()中返回
    QPainterPath m_standPath;
    QPainterPath m_runPath;
    QPainterPath m_punchPath;
    QPainterPath m_kickPath;
    QPainterPath m_isHitPath;
    QPainterPath m_skillPath_1;
    QPainterPath m_skillPath_2;
    QPainterPath m_skillPath_3;
    QPainterPath m_skillPath_4;
    QPainterPath m_skillPath_5;
    QPainterPath m_skillPath_6;

    //设置item碰撞边缘
    QRectF boundingRect()const;

    // 资源加载函数，子类选择
    void init_3();
    void init_4();

    /*
     *  键盘操作需要的flag 子类直接调用
     */
    bool m_leftFlag;
    bool m_rightFlag;
    bool m_attackJClickFlag;
    bool m_attackKClickFlag;

    // 键盘缓冲区，技能释放使用
    KeyBoardBuffer m_buffer;

    //刷新index的函数,在paint中调用
    void RefreshIndex();
    //根据键盘缓冲区判断出招种类的函数
    void judgeSkillType();


    // 攻击力属性
    int m_basicATK; // 基础攻击力 在init中初始
    int m_punchATK;
    int m_kickATK;
    QList<int> m_skillATK;
    int m_ultimateATK;

    // 防御力属性
    int m_basicDEF;

    // 精力消耗值
    int m_punchEnReduce;
    int m_jumpEnReduce;
    int m_kickEnReduce;
    QList<int> m_skillEnReduce;
    int m_ultimateEnReduce;

    // 招式的削韧
    int m_punchTeReduce;
    int m_kickTeReduce;
    QList<int> m_skillTeReduce;
    int m_ultimateTeReduce;

    //怒气的积攒值
    int m_angerIncrease;

    //判定帧的flag
    bool m_attackingFlag;
    //伤害判定的flag
    bool m_damageFlag;
    //已经计算完一次伤害的Flag；
    bool m_hasDamagedFlag;
    //已经计算完一次精力
    bool m_hasEnergyReduce;


    //动画控制变量 如果要添加新变量到该类的构造函数去初始化
    int standIndex;
    int runIndex;
    int punchIndex;
    int ishittingIndex;
    int kickIndex;
    int skillIndex;
    int jumpIndex;
    int ultimateSkillIndex; //终结技的

private:
    // 绘制函数
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    // 在Scene坐标下的 x,y(item坐标系下的原点)  该属性在scene中调用setPosiition函数进行赋值
    qreal m_x;
    qreal m_y;

    // 图片资源的宽高  加载资源的时候自动初始化
    int m_height;
    int m_width;
    void setPixmapInfo();


    // 跳跃属性
    static constexpr qreal s_Gravity = 9.8;
    int m_jumpT;
    DIRECTION m_jumpDirection;
    qreal m_jumpHorizontalV;
    qreal m_jumpVerticalV;
    qreal m_jumpCurrentV;
    qreal m_sceneGround;  // setPositionInfo()中初始化

    // 人物属性
    int m_speed; //奔跑速度 在 setinfo中初始化
    double m_blood; //生命值
    int m_energy;  // 精力值
    int m_tenacity;  // 韧性值
    int m_anger;
};

#endif // PLAYERITEM_H
