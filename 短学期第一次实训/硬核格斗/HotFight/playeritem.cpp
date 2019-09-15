#include "playeritem.h"
#include"rule.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <windows.h>

PlayerItem::PlayerItem()
{
    // 初始化变量
    m_state =  STAND;
    m_lastState=STAND;
    m_collidedState = NOCOLLIDED;
    m_skillType=NONESKILL;
    m_attackedState=NOATTACKED;
    m_attackingFlag=false;
    m_damageFlag=false;
    m_hasDamagedFlag=false; //还没有被攻击一次
    m_hasEnergyReduce=false; //是否消耗过一次精力，原理和多段伤害判定的原理类似
    m_characterFlag=C1; //默认是女战士


    // 动画轮播下标初始化
    standIndex = 0;
    runIndex = 0;
    punchIndex = 0;
    ishittingIndex = 0;
    kickIndex = 0;
    skillIndex = 0;
    jumpIndex = 0;
    ultimateSkillIndex=0;

    // 键盘flag初始化
    m_leftFlag = false;
    m_rightFlag = false;
    m_attackJClickFlag = true;
    m_attackKClickFlag = true;
//    m_isJumpStart = true;

    // 人物属性初始化
    m_blood = 100;
    m_energy = 100;
    m_tenacity = 100; // 硬直
    m_anger=0;// 怒气
}

PlayerItem::~PlayerItem()
{
}

void PlayerItem::init_3()
{
    // 重写成for循环
    for(int i=1; i<=13;i++)
        p_standing.append(QPixmap(QString(":/images/player3/standing/standing_%1.png").arg(i)));
    for(int i=1; i<=7;i++)
        p_running.append(QPixmap(QString(":/images/player3/running/running_%1.png").arg(i)));
    for(int i=1; i<=9;i++)
        p_punch.append(QPixmap(QString(":/images/player3/punching/punching_%1.png").arg(i)));
    for(int i=1; i<=11;i++)
        p_kicking.append(QPixmap(QString(":/images/player3/kicking/kicking_%1.png").arg(i)));
    for(int i=1; i<=4; i++)
        p_ishitting.append(QPixmap(QString(":/images/player3/ishitting/isattacked_%1.png").arg(i)));
    for(int i=1; i<=6; i++)
        p_jumping.append(QPixmap(QString(":/images/player3/jumping/jumping_%1.png").arg(i)));
    // 技能添加
    QList<QPixmap> skillList;
    // 技能1
    for(int i=1;i<=12;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_1/%1.png").arg(i)));
    p_skill.append(skillList);
    skillList.clear();
    // 技能2
    for(int i=1;i<=6;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_2/%1.png").arg(i)));
    p_skill.append(skillList);
    skillList.clear();
    // 技能3
    for(int i=1;i<=7;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_3/%1.png").arg(i)));
    p_skill.append(skillList);
    skillList.clear();
    // 技能4
    for(int i=1;i<=7;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_4/%1.png").arg(i)));
    p_skill.append(skillList);
    skillList.clear();
    // 技能5
    for(int i=1;i<=6;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_5/%1.png").arg(i)));
    p_skill.append(skillList);
    skillList.clear();
    // 技能6
    for(int i=1;i<=18;i++)
        skillList.append(QPixmap(QString(":/images/player3/skill_6/%1.png").arg(i)));
    p_skill.append(skillList);

    //终结技
    for(int i=1; i<=17; i++)
        p_ultimateSkill.append(QPixmap(QString(":/images/player3/ultimateskill/%1.png").arg(i)));





    // 加载路径
    // stand
    m_standPath.lineTo(p_standing.at(0).width(), 0);
    m_standPath.lineTo(p_standing.at(0).width()/2+20, -p_standing.at(0).height());
    m_standPath.lineTo(p_standing.at(0).width()/2-20, -p_standing.at(0).height());
    m_standPath.closeSubpath();
    // punch
    m_punchPath.addEllipse(0,0, p_punch.at(4).width(), -p_punch.at(4).height());
    // run
    m_runPath.addEllipse(0, -p_running.at(6).height()/2, p_running.at(6).width(), -p_running.at(6).height()/2);
    // kick
    m_kickPath.addEllipse(0, 0, p_kicking.at(7).width(), -p_kicking.at(7).height());
    // is hit
    m_isHitPath.addEllipse(0, 0, p_ishitting.at(3).width(), -p_ishitting.at(3).height());
    // skill 1
    m_skillPath_1.addEllipse(0, 0, p_skill.at(0).at(8).width(), -p_skill.at(0).at(8).height());
    // skill 2
    m_skillPath_2.addEllipse(0, 0, p_skill.at(1).at(2).width(), -p_skill.at(1).at(2).height());
    // skill 3
    m_skillPath_3.addEllipse(0, 0, p_skill.at(2).at(1).width(), -p_skill.at(2).at(1).height());
    // skill 4
    m_skillPath_4.addEllipse(0, 0, p_skill.at(3).at(2).width(), -p_skill.at(3).at(2).height());
    // skill 5
    m_skillPath_5.addEllipse(0, 0, p_skill.at(4).at(2).width(), -p_skill.at(4).at(2).height());
    // skill 6
    m_skillPath_6.addEllipse(0, 0, p_skill.at(5).at(5).width(), -p_skill.at(5).at(5).height());

    //预留大招的形状

    // 人物属性初始化
    // 攻击力属性
    m_basicATK = 5; // 基础攻击力 在init中初始
    m_punchATK = 10;
    m_kickATK = 15;
    for(int i=1;i<=6;i++)
        m_skillATK.append(15);
    m_ultimateATK=30;

    // 防御力属性
    m_basicDEF = 10;

    // 精力消耗值
    m_punchEnReduce = 15;
    m_jumpEnReduce = 20;
    m_kickEnReduce = 15;
    for(int i=1;i<=6;i++)
        m_skillEnReduce.append(30);

    //有的技能消耗精力要比较高
        m_skillEnReduce[0]=40;
        m_skillEnReduce[5]=40;
    m_ultimateEnReduce=50;

    // 招式的削韧
    m_punchTeReduce = 20;
    m_kickTeReduce = 20;
    for(int i=1;i<=4;i++)
        m_skillTeReduce.append(25);
    m_skillTeReduce.append(30);
    m_skillTeReduce.append(30);
    m_ultimateTeReduce=30;

    //怒气的积攒值
    m_angerIncrease=10;
}

void PlayerItem::init_4()
{
    for(int i=1; i<=8;i++)
            p_standing.append(QPixmap(QString(":/images/player4/standing/standing_%1.png").arg(i)));
        for(int i=1; i<=7;i++)
            p_running.append(QPixmap(QString(":/images/player4/running/running_%1.png").arg(i)));
        for(int i=1; i<=8;i++)
            p_punch.append(QPixmap(QString(":/images/player4/punching/punching_%1.png").arg(i)));
        for(int i=1; i<=9;i++)
            p_kicking.append(QPixmap(QString(":/images/player4/kicking/kicking_%1.png").arg(i)));
        for(int i=1;i<=2;i++)
            p_ishitting.append(QPixmap(QString(":/images/player4/ishitting/ishitting_%1.png").arg(i)));
        for(int i=1; i<=5; i++)
            p_jumping.append(QPixmap(QString(":/images/player4/jumping/jumping_%1.png").arg(i)));
        //添加技能
        QList<QPixmap> skillList;
        //技能1
        for(int i=1;i<=8 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_1/%1.png").arg(i)));
        p_skill.append(skillList);
        skillList.clear();
        //技能2
        for(int i=1;i<=6 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_2/%1.png").arg(i)));
        p_skill.append(skillList);
        skillList.clear();
        //技能3
        for(int i=1;i<=9 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_3/%1.png").arg(i)));
        p_skill.append(skillList);
        skillList.clear();

        //技能4
        for(int i=1;i<=8 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_4/%1.png").arg(i)));
        p_skill.append(skillList);
        skillList.clear();
        //技能5
        for(int i=1;i<=16 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_5/%1.png").arg(i)));
        p_skill.append(skillList);
        skillList.clear();
        //技能6
        for(int i=1;i<=7 ;i++)
            skillList.append(QPixmap(QString(":/images/player4/skill_6/%1.png").arg(i)));
        p_skill.append(skillList);

        //终结技
        for(int i=1; i<=10; i++)
            p_ultimateSkill.append(QPixmap(QString(":/images/player4/ultimateskill/%1.png").arg(i)));

        //加载路径
        //stand
        m_standPath.lineTo(p_standing.at(1).width(),0);
        m_standPath.lineTo(p_standing.at(1).width()*3/4,-p_standing.at(1).height());
        m_standPath.lineTo(p_standing.at(1).width()*1/4,-p_standing.at(1).height());
        m_standPath.lineTo(0,0);

        //punch
        m_punchPath.addEllipse(0,-p_punch.at(7).height(),p_punch.at(7).width(),p_punch.at(7).height());

        //run
        m_runPath.addEllipse(0,-p_punch.at(3).height(),p_punch.at(3).width(),p_punch.at(3).height());

        //kick
        m_kickPath.moveTo(0 , -p_kicking.at(2).height());
        m_kickPath.lineTo( p_kicking.at(2).width()*1/4 , 0 );
        m_kickPath.lineTo( p_kicking.at(2).width()*3/4 , 0 );
        m_kickPath.lineTo( p_kicking.at(2).width() , -p_kicking.at(2).height());
        m_kickPath.lineTo( 0 , -p_kicking.at(2).height());

        //Ishitting
        m_isHitPath.addRect(0,-p_ishitting.at(1).height() , p_ishitting.at(1).width() , p_ishitting.at(1).height());

        //skill_1
        m_skillPath_1.moveTo(0 , -p_skill.at(0).at(2).height());
        m_skillPath_1.lineTo( p_skill.at(0).at(2).width()*1/4 , 0 );
        m_skillPath_1.lineTo( p_skill.at(0).at(2).width()*3/4 , 0 );
        m_skillPath_1.lineTo( p_skill.at(0).at(2).width() , -p_skill.at(0).at(2).height());
        m_skillPath_1.lineTo( 0 , -p_skill.at(0).at(2).height());

        //skill_2
        m_skillPath_2.addEllipse(0,-p_skill.at(1).at(4).height() , p_skill.at(1).at(4).width() , p_skill.at(1).at(4).height());

        //skill_3
        m_skillPath_3.moveTo(0 , -p_skill.at(2).at(2).height());
        m_skillPath_3.lineTo( p_skill.at(2).at(2).width()*1/4 , 0 );
        m_skillPath_3.lineTo( p_skill.at(2).at(2).width()*3/4 , 0 );
        m_skillPath_3.lineTo( p_skill.at(2).at(2).width() , -p_skill.at(2).at(2).height());
        m_skillPath_3.lineTo( 0 , -p_skill.at(2).at(2).height());

        //skill_4
        m_skillPath_4.addEllipse(0,-p_skill.at(3).at(3).height() , p_skill.at(3).at(3).width() , p_skill.at(3).at(3).height());

        //skill_5
        m_skillPath_5.moveTo(0 , -p_skill.at(4).at(1).height());
        m_skillPath_5.lineTo( p_skill.at(4).at(1).width()*1/4 , 0 );
        m_skillPath_5.lineTo( p_skill.at(4).at(1).width()*3/4 , 0 );
        m_skillPath_5.lineTo( p_skill.at(4).at(1).width() , -p_skill.at(4).at(1).height());
        m_skillPath_5.lineTo( 0 , -p_skill.at(4).at(1).height());

        //skill_6
        m_skillPath_6.addEllipse(0,-p_skill.at(5).at(3).height() , p_skill.at(5).at(3).width() , p_skill.at(5).at(3).height());

        //预留终结技的接口

        // 人物属性初始化
        // 攻击力属性
        m_basicATK = 5; // 基础攻击力 在init中初始
        m_punchATK = 10;
        m_kickATK = 15;
        for(int i=1;i<=6;i++)
            m_skillATK.append(15);
        m_ultimateATK=50;

        // 防御力属性
        m_basicDEF = 10;

        // 精力消耗值
        m_punchEnReduce = 15;
        m_jumpEnReduce = 20;
        m_kickEnReduce = 20;
        for(int i=1;i<=6;i++)
            m_skillEnReduce.append(30);
        //有的技能消耗精力比较高
            m_skillEnReduce[1]=40;
            m_skillEnReduce[4]=45;
        m_ultimateEnReduce=50;

        // 招式的削韧
        m_punchTeReduce = 20;
        m_kickTeReduce = 20;
        for(int i=1;i<=4;i++)
            m_skillTeReduce.append(25);
        m_skillTeReduce.append(30);
        m_skillTeReduce.append(30);
        m_ultimateTeReduce=100;

        //怒气的积攒值
        m_angerIncrease=10;
}

void PlayerItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    //为了提升手感，先刷新状态
    RefreshIndex();
    //记录这一次的状态
    m_lastState=m_state;
    switch (m_state)
    {
        case RUN:
            // 奔跑视图
            // 轮播下标增加
            if(runIndex >= p_running.size()-1)
            {
                runIndex = 0;
            }
            else
                runIndex++;

            // 左右方向显示
            if(m_direction == RIGHT)
            {
                painter->drawPixmap(0, -m_height, m_width, m_height, p_running.at(runIndex));
            }
            else
            {
                painter->drawImage(0, -m_height, p_running.at(runIndex).toImage().mirrored(true,false));
            }

            break;

        case STAND:
            // 站立状态视图
            if(standIndex >= p_standing.size()-1)
            {
                standIndex = 0;
            }
            else
                standIndex++;
            if(m_direction == RIGHT)
            {
                painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage());
            }
            else
                painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage().mirrored(true,false));
            break;

        case PUNCH:
            // 出拳视图
            //为了提升操作手感加的
            m_attackJClickFlag=true;
            if(punchIndex >= p_punch.size()-1)
            {
                punchIndex = 0;
                m_state = STAND;
            }
            else
                punchIndex++;
            if(m_direction == RIGHT)
            {
                // drawPixmap 改为 drawImage 尝试修复图片拉长
                painter->drawImage(0, -m_height, p_punch.at(punchIndex).toImage());
            }
            else
            {
                painter->drawImage(0, -m_height, p_punch.at(punchIndex).toImage().mirrored(true,false));
            }

            break;
        case KICK:
            // 出脚视图
            //为了提升操作手感增加
            m_attackKClickFlag=true;
            if(kickIndex >= p_kicking.size()-1)
            {
                kickIndex = 0;
                m_state = STAND;
            }
            else
                kickIndex++;

            // 左右方向显示
            if(m_direction == RIGHT)
            {
                painter->drawImage(0, -m_height, p_kicking.at(kickIndex).toImage());
            }
            else
            {
                painter->drawImage(0, -m_height, p_kicking.at(kickIndex).toImage().mirrored(true,false));
            }

            break;
        case ISHITTING:
            //受攻击视图
            if(m_attackedState==ISATTACKED)
            {
                if(ishittingIndex >= p_ishitting.size()-1)
                {
                    punchIndex = 0;
                     //解除硬值放在rule里面
                }
                else
                    ishittingIndex++;
                if(m_direction == RIGHT)
                {
                    // drawPixmap 改为 drawImage 尝试修复图片拉长
                    painter->drawImage(0, -m_height, p_ishitting.at(ishittingIndex).toImage());
                }
                else
                {
                    painter->drawImage(0, -m_height, p_ishitting.at(ishittingIndex).toImage().mirrored(true,false));
                }
            }
            else
            {
                // 站立状态视图
                if(standIndex >= p_standing.size()-1)
                {
                    standIndex = 0;
                }
                else
                    standIndex++;
                if(m_direction == RIGHT)
                {
                    painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage());
                }
                else
                    painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage().mirrored(true,false));
            }
            break;
        case SKILL:
            // 释放技能

            if(m_skillType==NONESKILL)
            {
                m_buffer.clear();
                m_state=STAND;
                skillIndex = 0;
                // 轮播stand状态，去除点击技能键闪烁
                if(standIndex >= p_standing.size()-1)
                {
                    standIndex = 0;
                }
                else
                    standIndex++;
                if(m_direction == RIGHT)
                {
                    painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage());
                }
                else
                    painter->drawImage(0, -m_height, p_standing.at(standIndex).toImage().mirrored(true,false));
            }
            else
            {

                if(skillIndex >= p_skill.at(m_skillType).size()-1)
                {
                    skillIndex = 0;
                    m_state = STAND;
                    // 轮播完缓冲区清空
                    m_buffer.clear();
                }
                else
                    skillIndex++;

                // 左右方向显示
                if(m_direction == RIGHT)
                {
                    painter->drawImage(0, -m_height, p_skill.at(m_skillType).at(skillIndex).toImage());
                }
                else
                {
                    painter->drawImage(0, -m_height, p_skill.at(m_skillType).at(skillIndex).toImage().mirrored(true,false));
                }

            }
            break;
        case JUMP:
            // 跳跃

            if(jumpIndex <= 3 && m_jumpCurrentV > 0)
            {
                jumpIndex++;
            }
            else if(m_jumpCurrentV < 0 && jumpIndex >= 3 && jumpIndex < p_jumping.size()-1)
                jumpIndex++;
            if(m_direction == RIGHT)
            {
                painter->drawImage(0, -m_height, p_jumping.at(jumpIndex).toImage());
            }
            else
                painter->drawImage(0, -m_height, p_jumping.at(jumpIndex).toImage().mirrored(true,false));
            break;
        //终结技
        case ULTIMATESKILL:
            if(ultimateSkillIndex >= p_ultimateSkill.size()-1)
            {
                // 两个人物有区别
                if(m_characterFlag==C1)
                {
                    ultimateSkillIndex = 0;
                    m_state=STAND;
                }

            }
            else
            {
                ultimateSkillIndex++;
            }
            if(m_direction == RIGHT)
            {
                painter->drawImage(0, -m_height, p_ultimateSkill.at(ultimateSkillIndex).toImage());
            }
            else
                painter->drawImage(0, -m_height, p_ultimateSkill.at(ultimateSkillIndex).toImage().mirrored(true,false));
            break;
        default:
            break;
    }
}

//重载shape()函数
QPainterPath PlayerItem::shape()const
{
     switch(m_state)
     {
        case STAND:
            return m_standPath;
        case RUN:
            return m_runPath;
        case PUNCH:
            return m_punchPath;
        case KICK:
            return m_kickPath;
        case ISHITTING:
            return m_isHitPath;
        case SKILL:
         //根据技能具体判断
            switch(m_skillType)
            {
                case NONESKILL:
                    return m_standPath; //如果没技能返回站立的shape()
                case SKILLONE:
                    return m_skillPath_1;
                case SKILLTWO:
                    return m_skillPath_2;
                case SKILLTHREE:
                    return m_skillPath_3;
                case SKILLFOUR:
                    return m_skillPath_4;
                case SKILLFIVE:
                    return m_skillPath_5;
                case SKILLSIX:
                    return m_skillPath_6;
                default:
                    return m_standPath;
            }

          default:
                return m_standPath;
       }
}

//判断是不是攻击帧
void PlayerItem::JudgeingAttack()
{
    //空函数，在子类中实现
}

QRectF PlayerItem::boundingRect() const
{
    // 将boundingRect改为较大定值区域 去除重绘bug
    // 要重写shape函数来作为碰撞检测的根据
    return QRectF(0, -200, 200, 400);
}

void PlayerItem::setPixmapInfo()
{
    // 根据状态同步 宽高 信息
    switch (m_state)
    {
        case RUN:
            m_width = p_running.at(runIndex).width();
            m_height = p_running.at(runIndex).height();
            break;
        case STAND:
            m_width = p_standing.at(standIndex).width();
            m_height = p_standing.at(standIndex).height();
            break;
        case PUNCH:
            m_width = p_punch.at(punchIndex).width();
            m_height = p_punch.at(punchIndex).height();
            break;
        case ISHITTING:
            m_width = p_ishitting.at(ishittingIndex).width();
            m_height = p_ishitting.at(ishittingIndex).height();
            break;
        case JUMP:
            m_width = p_jumping.at(jumpIndex).width();
            m_height = p_jumping.at(jumpIndex).height();
            break;
        case SKILL:
            //可能有小bug 不知道为什么会造成指针越界
            if(m_skillType==NONESKILL)
            {
                m_width = p_standing.at(standIndex).width();
                m_height = p_standing.at(standIndex).height();

            }
            else
            {
                if(skillIndex<p_skill.at(m_skillType).size())
                {
                    m_width=p_skill.at(m_skillType).at(skillIndex).width();
                    m_height=p_skill.at(m_skillType).at(skillIndex).height();
                }
            }
            break;
        case ULTIMATESKILL:
             m_width=p_ultimateSkill.at(ultimateSkillIndex).width();
             m_height=p_ultimateSkill.at(ultimateSkillIndex).height();
            break;
        default:
            break;
    }
    // 同步速度变量
    m_speed = m_width/2;
}
    //所有的set/get函数的实现
void PlayerItem::setState(STATE t_state)
{
    m_state = t_state;
}

PlayerItem::STATE PlayerItem::getState()const
{
    return m_state;
}

void PlayerItem::setDirection(DIRECTION t_direction)
{
    m_direction = t_direction;
}

PlayerItem::DIRECTION PlayerItem::getDirection()const
{
    return m_direction;
}

void PlayerItem::setCollidedState(COLLIDEDSTATE t_collidedState)
{
    m_collidedState=t_collidedState;
}

PlayerItem::COLLIDEDSTATE PlayerItem::getCollidedState()const
{
    return m_collidedState;
}

void PlayerItem::setSkillType(SKILLTYPE skillType)
{
    m_skillType=skillType;
}

PlayerItem::SKILLTYPE PlayerItem::getSkillType()const
{
    return m_skillType;
}

void PlayerItem::setAttackedState(ATTACKEDSTATE attackedState)
{
    m_attackedState=attackedState;
}

PlayerItem::ATTACKEDSTATE PlayerItem::getAttackedState()const
{
    return m_attackedState;
}

void PlayerItem::setX(qreal x)
{
    m_x = x;
}

qreal PlayerItem::getX()const
{
    return m_x;
}

void PlayerItem::setY(qreal y)
{
    m_y = y;
}

qreal PlayerItem::getY()const
{
    return m_y;
}

void PlayerItem::setHeight(int t_height)
{
    m_height = t_height;
}

int PlayerItem::getHeight()const
{
    return m_height;
}

void PlayerItem::setWidth(int t_width)
{
    m_width = t_width;
}

int PlayerItem::getWidth()const
{
    return m_width;
}

void PlayerItem::setSpeed(int t_speed)
{
    m_speed = t_speed;
}

int PlayerItem::getSpeed()const
{
    return m_speed;
}

void PlayerItem::setBlood(int t_blood)
{
    m_blood = t_blood;
}

int  PlayerItem::getBlood()const
{
    return m_blood;
}

void PlayerItem::setEnergy(int energy)
{
    m_energy=energy;
}

int PlayerItem::getEnergy()const
{
    return m_energy;
}

void PlayerItem::setTenacity(int tenacity)
{
    m_tenacity=tenacity;
}

int PlayerItem::getTenacity()const
{
    return m_tenacity;
}

void PlayerItem::setAttackingFlag(bool flag)
{
    m_attackingFlag=flag;
}

bool PlayerItem::getAttackedFlag()const
{
    return m_attackingFlag;
}

void PlayerItem::setDamageFlag(bool flag)
{
    m_damageFlag=flag;
}

bool PlayerItem::getDamageFlag()const
{
    return m_damageFlag;
}

void PlayerItem::setHasDamagedFlag(bool flag)
{
    m_hasDamagedFlag=flag;
}

bool PlayerItem::getHasDamagedFlag()const
{
    return m_hasDamagedFlag;
}

void PlayerItem::setJumpCurrentV(qreal v)
{
    m_jumpCurrentV=v;
}

qreal PlayerItem::getJumpCurrentV()const
{
    return m_jumpCurrentV;
}

void PlayerItem::setCharacterFlag(CHARACTERFlAG flag)
{
    m_characterFlag=flag;
}

PlayerItem::CHARACTERFlAG PlayerItem::getCharacterFlag()const
{
    return m_characterFlag;
}

void PlayerItem::setUltimateSkillIndex(int index)
{
    ultimateSkillIndex=index;
}

int PlayerItem::getUltimateSkillIndex()const
{
    return ultimateSkillIndex;
}

void PlayerItem::setAnger(int anger)
{
    m_anger=anger;
}

int PlayerItem::getAnger()const
{
    return m_anger;
}

void PlayerItem::setAngerIncrease(int increase)
{
    m_angerIncrease=increase;
}
int PlayerItem::getAngerIncrease()const
{
    return m_angerIncrease;
}
void PlayerItem::run()
{
    // 人物奔跑功能 m_x控制
    if(m_state != RUN)
        return;
    if( m_direction == LEFT && m_collidedState != ISCOLLIDEDLEFT)  //左边不能被挡住
    {
        m_x -= m_speed;
    }
    else if( m_direction == RIGHT && m_collidedState !=ISCOLLIDEDRIGHT)       //修改注释进行了更改
    {
        m_x += m_speed;
    }
    else
    {
        return;
    }
}

void PlayerItem::jump()
{
    if(m_state != JUMP)
        return;
    if(m_direction == LEFT)
        m_x -= m_jumpHorizontalV;
    else
        m_x += m_jumpHorizontalV;
    m_y = m_sceneGround - (m_jumpVerticalV * m_jumpT - s_Gravity/2 * m_jumpT * m_jumpT);
    if(m_y >= m_sceneGround)
    {
        m_y = m_sceneGround;
        m_jumpHorizontalV = 0;
        m_jumpVerticalV = 0;
        m_jumpT = 0;
        jumpIndex = 0;
        m_state = STAND;
        Rule::calculateEnergy(*this, m_jumpEnReduce);
    }
    else
    {
        m_jumpCurrentV -= s_Gravity;
        m_jumpT++;
    }
}

//人物攻击时的位移补偿函数
void PlayerItem::attackingMove()
{
   switch(m_state)
   {

       //使用技能时的位移补偿
       case SKILL:
            if(m_direction==LEFT && m_collidedState!=ISCOLLIDEDLEFT)
            {
                m_x -=m_width/15;
            }
            else if(m_direction==RIGHT && m_collidedState!=ISCOLLIDEDRIGHT)
            {
                m_x +=m_width/15;
            }
            break;
        //大招的位移补偿
       case ULTIMATESKILL:
            if(m_characterFlag==C1) //如果是女战士的话
            {
                if(m_direction==LEFT && m_collidedState!=ISCOLLIDEDLEFT)
                {
                    m_x -=m_width/8;
                }
                else if(m_direction==RIGHT && m_collidedState!=ISCOLLIDEDRIGHT)
                {
                    m_x +=m_width/8;
                }
            }
            else if(m_characterFlag==C2)   //如果是孙悟空，孙悟空的龟派气功不补偿
            {
                return;
            }
            else
            {
                return;
            }
            break;
       default:
            break;
   }
}

void PlayerItem::jumpStart()
{
    if(m_state != RUN)
        m_jumpHorizontalV = 0;
    else
        m_jumpHorizontalV = 15;
    m_jumpVerticalV = 50;
    m_jumpCurrentV = m_jumpVerticalV;
    m_jumpT = 1;
}

void PlayerItem::setPositonInfo(qreal x, qreal y)
{
    m_x = x;
    m_y = y;
    m_sceneGround = y;
}

void PlayerItem::updatePos()
{
    // 存在bug 改变图像大小的时候会导致view中残留未重绘部分
    prepareGeometryChange();
    setPixmapInfo();
    // 设置item在scene上的位置
    setPos(m_x, m_y);
}

//根据缓冲区来设定出招的种类
void PlayerItem::judgeSkillType()
{
    if(m_buffer.getCurrentSize()<KeyBoardBuffer::SIZE)
    {
        m_skillType = NONESKILL;
    }
    else
    {
       if(m_buffer.getBuffer()=="JJK")
       {
           m_skillType=SKILLONE;
       }
       else if(m_buffer.getBuffer()=="JKJ")
       {
            m_skillType=SKILLTWO;
       }
       else if(m_buffer.getBuffer()=="JKK")
       {
            m_skillType=SKILLTHREE;
       }
       else if(m_buffer.getBuffer()=="KJJ")
       {
            m_skillType=SKILLFOUR;
       }
       else if(m_buffer.getBuffer()=="KJK")
       {
            m_skillType=SKILLFIVE;
       }
       else if(m_buffer.getBuffer()=="KKJ")
       {
            m_skillType=SKILLSIX;
       }
       else
       {
           m_skillType= NONESKILL;
       }
       if(m_skillType != NONESKILL)
       {
           if(m_energy < m_skillEnReduce.at(m_skillType))
           {
               m_skillType = NONESKILL;
           }
       }
    }

}
//enum STATE{JUMP, PUNCH, KICK, RUN, STAND,ISHITTING, SKILL,ULTIMATESKILL};
//刷新Index的函数 在paint中调用
void PlayerItem::RefreshIndex()
{
    if(m_lastState==m_state)
    {
        return;
    }
    else
    {
        switch(m_lastState)
        {
        case STAND:
            standIndex=0;
            break;
        case RUN:
            runIndex=0;
            break;
        case KICK:
            kickIndex=0;
            break;
        case PUNCH:
            punchIndex=0;
            break;
        case JUMP:
            jumpIndex=0;
            break;
        case ISHITTING:
            ishittingIndex=0;
            break;
        case SKILL:
            skillIndex=0;
            break;
        case ULTIMATESKILL:
            ultimateSkillIndex=0;
            break;
        default:
            break;
        }
    }
}

