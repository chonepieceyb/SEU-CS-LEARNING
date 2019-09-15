#include "netplayer2p.h"

NetPlayer2P::NetPlayer2P()
{

}

void NetPlayer2P::keyPressEvent(QKeyEvent * event)
{
    // 技能释放中不处理键盘事件
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

void NetPlayer2P::keyReleaseEvent(QKeyEvent * event)
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
