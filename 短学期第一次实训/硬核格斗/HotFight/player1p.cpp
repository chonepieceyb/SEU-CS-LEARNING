#include "player1p.h"
#include <QPixmap>
#include <QKeyEvent>
#include <windows.h>
#include<QDebug>
#include"rule.h"

Player1P::Player1P()
{
    init_3();
    setCharacterFlag(PlayerItem::C1);
    setHeight(p_standing.at(0).height());
    m_direction=PlayerItem::RIGHT;
    setPositonInfo(200,350);

}

/*
 * 1p控制方法 W D左右行走
 * J K分别为出拳和出腿
*/
void Player1P::keyPressEvent(QKeyEvent *event)
{
    // 技能释放中不处理键盘事件
    // 更改了键盘的KJ，将它们的标志位分开
    if(m_state != SKILL &&m_attackedState!=ISATTACKED && m_state != JUMP && m_state!=ULTIMATESKILL)
    {
        switch (event->key())
        {
            case Qt::Key_A:
                m_state = RUN;
                m_direction = LEFT;
                m_leftFlag = true;
                break;
            case Qt::Key_D:
                m_state = RUN;
                m_direction = RIGHT;
                m_rightFlag = true;
                break;
            case Qt::Key_W:
              if(getEnergy() < m_jumpEnReduce)
                    return;
                jumpStart();
                m_state = JUMP;
                break;
            case Qt::Key_J:
                if(m_attackJClickFlag)
                {
                    m_attackJClickFlag = false;
                    // 精力过低时无法出招
                    if(getEnergy() < m_punchEnReduce)
                        return;
                    m_state = PUNCH;
                    // 添加进缓冲区
                    m_buffer.addKey('J');
                }
                break;
            case Qt::Key_K:
                if(m_attackKClickFlag)
                {
                    m_attackKClickFlag = false;
                    if(getEnergy() < m_kickEnReduce)
                        return;
                    m_state = KICK;
                    // 添加进缓冲区
                    m_buffer.addKey('K');
                }
                break;
            case Qt::Key_I:
                m_state = SKILL;
                judgeSkillType();
                break;
            case Qt::Key_U:
                if(getAnger()<100 || getEnergy()<m_ultimateEnReduce)
                {
                    return;
                }
                m_state=ULTIMATESKILL;   //大招
                break;
            default:
                break;
        }
    }
}

void Player1P::keyReleaseEvent(QKeyEvent *event)
{
    // 技能释放中或者硬直状态下或者跳跃状态不处理键盘事件
    if(m_state != SKILL &&m_attackedState!=ISATTACKED && m_state != JUMP && m_state!=ULTIMATESKILL)
    {
        switch (event->key())
        {
            case Qt::Key_A:
                m_leftFlag = false;
                if(!m_leftFlag && !m_rightFlag)
                    m_state = STAND;
                break;
            case Qt::Key_D:
                m_rightFlag = false;
                if(!m_leftFlag && !m_rightFlag)
                    m_state = STAND;
                break;
            case Qt::Key_J:
                m_attackJClickFlag=true;
                break;
            case Qt::Key_K:
                m_attackKClickFlag = true;
                break;
            default:
                break;
        }
    }
}

//决定攻击判定帧的函数
void Player1P::JudgeingAttack()
{
    switch(m_state)
    {
       case PUNCH:
        // 3到5帧 或者 7到8帧数
            if((punchIndex>=2 && punchIndex<=4)||(punchIndex>=6&&punchIndex<=7))
            {
                m_attackingFlag=true;
                //这段代码是为了在一个区间只计算一次伤害
                //如果伤害还没有被计算
                if(!m_hasDamagedFlag)
                {
                    m_damageFlag=true;
                }
                else
                {
                    //如果已经计算过一次伤害了，那就不能再次造成伤害
                    m_damageFlag=false;
                }
                //如果本阶段精力还没有消耗
                if(!m_hasEnergyReduce)
                {
                     //有两段，精力要减两次所以改了一下
                   Rule::calculateEnergy(*this,m_punchEnReduce/2);
                   m_hasEnergyReduce=true;
                }
            }
            else
            {
               m_attackingFlag=false;
               //不在判定帧内伤害肯定就还没被计算，至少对于下一批的判定帧来说
               m_hasDamagedFlag=false;
               m_damageFlag=false;
               m_hasEnergyReduce=false;
            }
            break;
       case KICK:
        // 7 8 9帧数
            if(kickIndex>=6 && kickIndex<=8)
            {
                m_attackingFlag=true;
                //如果伤害还没有被计算
                if(!m_hasDamagedFlag)
                {
                    m_damageFlag=true;
                }
                else
                {
                    //如果已经计算过一次伤害了，那就不能再次造成伤害
                    m_damageFlag=false;
                }
                if(!m_hasEnergyReduce)
                {
                   Rule::calculateEnergy(*this,m_kickEnReduce);
                   m_hasEnergyReduce=true;
                }
            }
            else
            {
                 m_attackingFlag=false;
                 m_damageFlag=false;
                 m_hasDamagedFlag=false;
                 m_hasEnergyReduce=false;
            }
            break;
       case SKILL:
            switch(m_skillType)
            {
                case SKILLONE:
                //技能1 3-5 一段 8-9二段
                    if((skillIndex>=2 && skillIndex<=4) || (skillIndex>=7&&skillIndex<=8))
                    {
                        m_attackingFlag=true;
                        //如果伤害还没有被计算
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                             //有两段，精力要减两次所以改了一下
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(0)/2);
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;

                case SKILLTWO:
                //第3帧
                    if(skillIndex==2)
                    {
                        m_attackingFlag=true;
                        //如果伤害还没有被计算
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(1));
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;

                case SKILLTHREE:
                // 2-4帧
                    if(skillIndex>=1 && skillIndex<=3)
                    {
                        m_attackingFlag=true;
                        //如果伤害还没有被计算
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(2));
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;

                case SKILLFOUR:
                 //3-6帧
                    if(skillIndex>=2 && skillIndex<=5)
                    {
                        m_attackingFlag=true;
                        //如果伤害还没有被计算
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(3));
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasDamagedFlag=false;
                    }
                    break;
                case SKILLFIVE:
                 //3-5帧
                    if(skillIndex>=2 && skillIndex<=4)
                    {
                        m_attackingFlag=true;
                        //这段代码是为了在一个区间只计算一次伤害
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(4));
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;
                case SKILLSIX:
                //技能6 5-6 一段 11-13二段
                    if((skillIndex>=4 && skillIndex<=5) || (skillIndex>=10&&skillIndex<=12))
                    {
                        m_attackingFlag=true;
                        //这段代码是为了在一个区间只计算一次伤害
                        if(!m_hasDamagedFlag)
                        {
                            m_damageFlag=true;
                        }
                        else
                        {
                            //如果已经计算过一次伤害了，那就不能再次造成伤害
                            m_damageFlag=false;
                        }
                        if(!m_hasEnergyReduce)
                        {
                             //有两段，精力要减两次所以改了一下
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(5)/2);
                           m_hasEnergyReduce=true;
                        }
                    }
                    else
                    {
                        m_damageFlag=false;
                        m_attackingFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;
                default:
                    {
                        m_attackingFlag=false;
                        m_damageFlag=false;
                        m_hasDamagedFlag=false;
                        m_hasEnergyReduce=false;
                    }
                    break;
            }
            break;
       case ULTIMATESKILL:
        //2-4帧 ,6-8,14-17
           if((ultimateSkillIndex>=1&&ultimateSkillIndex<=3)||
                   (ultimateSkillIndex>=5&&ultimateSkillIndex<=7)||
                   (ultimateSkillIndex>=13&&ultimateSkillIndex<=16))
           {
               m_attackingFlag=true;
               //如果伤害还没有被计算
               if(!m_hasDamagedFlag)
               {
                   m_damageFlag=true;
               }
               else
               {
                   //如果已经计算过一次伤害了，那就不能再次造成伤害
                   m_damageFlag=false;
               }
               if(!m_hasEnergyReduce)
               {
                    //有三段，精力要减两次所以改了一下
                  Rule::calculateEnergy(*this,m_ultimateEnReduce/3);
                  //怒气消耗
                  Rule::calculateAnger(*this,-35);
                  m_hasEnergyReduce=true;
               }
           }
           else
           {
               m_damageFlag=false;
               m_attackingFlag=false;
               m_hasDamagedFlag=false;
               m_hasEnergyReduce=false;
           }
           break;
       default:
            {
                m_attackingFlag=false;
                m_damageFlag=false;
                m_hasDamagedFlag=false;
                m_hasEnergyReduce=false;
            }
            break;
    }
}
