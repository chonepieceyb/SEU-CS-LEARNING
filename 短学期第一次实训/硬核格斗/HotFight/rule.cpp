#include "rule.h"

Rule::Rule()
{

}

void Rule::calculateBlood(PlayerItem &attackItem, PlayerItem &attackedItem)
{
    int t_atk;
    switch (attackItem.m_state)
    {
        case PlayerItem::PUNCH:
            t_atk = attackItem.m_punchATK;
        break;
        case PlayerItem::KICK:
            t_atk = attackItem.m_kickATK;
        break;
        case PlayerItem::SKILL:
            if(attackItem.m_skillType == PlayerItem::NONESKILL)
                return;
            t_atk = attackItem.m_skillATK.at(attackItem.m_skillType);
        break;
        case PlayerItem::ULTIMATESKILL:
            //测试需要
            t_atk=attackItem.m_ultimateATK;
            break;
        default:
            return;
    }
    double damage=m_damageK1* t_atk + m_damageK2 * attackItem.m_energy - m_damageK4 * attackedItem.m_energy- m_damageK3 * attackedItem.m_basicDEF;
    if(damage>=0)
    {
        attackedItem.m_blood -= damage;
    }
    if(attackedItem.m_blood<=0)
        attackedItem.m_blood=0;

}

void Rule::calculateEnergy(PlayerItem &item, int energyReduce)
{
    if(item.m_energy - energyReduce <= 0)
        item.m_energy = 0;
    else
        item.m_energy -= energyReduce;
}

void Rule::calculateTenacity(PlayerItem &attackItem, PlayerItem &attackedItem)
{
    int t_tenaReduce;
    switch (attackItem.m_state)
    {
        case PlayerItem::PUNCH:
            t_tenaReduce = attackItem.m_punchTeReduce;
        break;
        case PlayerItem::KICK:
            t_tenaReduce = attackItem.m_kickTeReduce;
        break;
        case PlayerItem::SKILL:
            if(attackItem.m_skillType == PlayerItem::NONESKILL)
                return;
            t_tenaReduce = attackItem.m_skillTeReduce.at(attackItem.m_skillType);
        case PlayerItem::ULTIMATESKILL:
            t_tenaReduce = attackItem.m_ultimateTeReduce;
            break;
        default:
            return;
    }
    if(attackedItem.m_tenacity - t_tenaReduce <= 0)
        attackedItem.m_tenacity = 0;
    else
        attackedItem.m_tenacity -= t_tenaReduce;
}

//怒气积攒
void Rule::calculateAnger(PlayerItem& item,int anger)
{

    item.m_anger += anger;
    if(item.m_anger>100)
    {
        item.m_anger=100;
    }
    if(item.m_anger<0)
    {
        item.m_anger=0;
    }
}

// timerEvent中调用
void Rule::recoverEnergy(PlayerItem &item)
{   
    // 攻击时无法回复精力,终结技的时候也不能放大招
    if(item.getState() == PlayerItem::PUNCH || item.getState() == PlayerItem::KICK||item.getState() == PlayerItem::SKILL ||item.getState() == PlayerItem::JUMP
            ||item.getState()==PlayerItem::ULTIMATESKILL)
        return;
    if(item.m_energy + 2 >= 100)
        item.m_energy = 100;
    else
        item.m_energy += 2;
}

void Rule::recoverTenacity(PlayerItem &item)
{
    if(item.m_state == PlayerItem::ISHITTING && item.m_attackedState != PlayerItem::ISATTACKED)
    {
        return;
    }
    else
    {
        if(item.m_tenacity + 2 >= 100)
            item.m_tenacity = 100;
        else
            item.m_tenacity += 2;
    }
    if(item.m_tenacity>=20 && item.m_attackedState==PlayerItem::ISATTACKED )
    {
        item.m_state = PlayerItem::STAND;       //被攻击的最后一帧应该停下来
        item.m_attackedState=PlayerItem::NOATTACKED;  //解除硬直
    }
}

void Rule::restrictBorder(PlayerItem &item)
{
    if(item.m_x > 800 - item.m_width)
        item.m_x = 800 - item.m_width;
    else if(item.m_x < 0)
        item.m_x = 0;
}
