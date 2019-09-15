#include "player2p.h"
#include <windows.h>
#include"rule.h"
Player2P::Player2P()
{
    init_4();
    setCharacterFlag(PlayerItem::C2);
    setHeight(p_standing.at(0).height());
    m_direction=PlayerItem::LEFT;
    setPositonInfo(500,350);

}

 Player2P::~Player2P()
 {

 }

/*
 * 1p控制方法 ← →左右行走
 * 1 2分别为出拳和出腿
*/
void Player2P::keyPressEvent(QKeyEvent *event)
{
    if(m_state != SKILL &&m_attackedState!=ISATTACKED && m_state != JUMP&& m_state!=ULTIMATESKILL)
    {
        switch (event->key())
        {
            case Qt::Key_Left:
                m_state = RUN;
                m_direction = LEFT;
                m_leftFlag = true;
                break;
            case Qt::Key_Right:
                m_state = RUN;
                m_direction = RIGHT;
                m_rightFlag = true;
                break;
            case Qt::Key_Up:
                if(getEnergy() < m_jumpEnReduce)
                    return;
                jumpStart();
                m_state = JUMP;
                break;
            case Qt::Key_1:
                if(m_attackJClickFlag)
                {
                    m_attackJClickFlag = false;
                    if(getEnergy() < m_punchEnReduce)
                        return;
                    m_state = PUNCH;
                    m_buffer.addKey('J');
                }
                break;
            case Qt::Key_2:
                if(m_attackKClickFlag)
                {

                    m_attackKClickFlag = false;
                    if(getEnergy() < m_kickEnReduce)
                        return;
                    m_state = KICK;
                    m_buffer.addKey('K');
                }
                break;
            case Qt::Key_5:
                m_state = SKILL;
                judgeSkillType();
                break;
            case Qt::Key_4:
                if(getAnger()<50 || getEnergy()<m_ultimateEnReduce)
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

void Player2P::keyReleaseEvent(QKeyEvent *event)
{
    //这样改应该能提升操作手感
    if(m_state != SKILL &&m_attackedState!=ISATTACKED && m_state != JUMP &&m_state!=ULTIMATESKILL)
    {
        switch (event->key())
        {
            case Qt::Key_Left:
                m_leftFlag = false;
                if(!m_leftFlag && !m_rightFlag)
                    m_state = STAND;
                break;
            case Qt::Key_Right:
                m_rightFlag = false;
                if(!m_leftFlag && !m_rightFlag)
                    m_state = STAND;
                break;
            case Qt::Key_1:
                m_attackJClickFlag=true;
                break;
            case Qt::Key_2:
                m_attackKClickFlag = true;
                break;
            default:
                break;
        }
    }
}

//决定攻击判定帧的函数
void Player2P::JudgeingAttack()
{
    switch(m_state)
    {
       case PUNCH:
        // 2到3帧 或者 7到8帧数
            if((punchIndex>=1 && punchIndex<=2)||(punchIndex>=6&&punchIndex<=7))
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
        // 3-5帧数
            if(kickIndex>=2 && kickIndex<=4)
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
                //技能1 3-5
                    if(skillIndex>=2 && skillIndex<=4)
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
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(0));
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
                //1-3 5-6
                    if((skillIndex>=0 && skillIndex<=2)||(skillIndex>=4 && skillIndex<=5))
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
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(1)/2);
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
                // 3-5帧
                    if(skillIndex>=2 && skillIndex<=4)
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
                        m_hasEnergyReduce=false;
                    }
                    break;
                case SKILLFIVE:
                 //2-5 8-11 15-16
                    if((skillIndex>=1 && skillIndex<=4)||(skillIndex>=7 && skillIndex<=10)
                            ||(skillIndex>=14 && skillIndex<=15))
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
                             //有三段，精力要减两次所以改了一下
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(4)/3);
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
                //技能6 4-7
                    if((skillIndex>=3 && skillIndex<=6))
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
                           Rule::calculateEnergy(*this,m_skillEnReduce.at(5));
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
        //2P的终结技
       case ULTIMATESKILL:
        // 6 7 8帧
            if(ultimateSkillIndex>=5 && ultimateSkillIndex<=7)
            {
               m_attackingFlag=true;
               if(!m_hasEnergyReduce)
               {
                  Rule::calculateEnergy(*this,m_skillEnReduce.at(4));
                  //怒气消耗
                  Rule::calculateAnger(*this,-50);
                  m_hasEnergyReduce=true;
               }

            }
            else
            {
                m_attackingFlag=false;
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

