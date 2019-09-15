#ifndef PLAYERITEM2_H
#define PLAYERITEM2_H

#include <playeritem.h>
#include <QKeyEvent>


class Player2P:public PlayerItem    //继承基类
{
    //用来计算精力
        friend class Rule;
public:
   Player2P();
   ~Player2P();
   virtual void JudgeingAttack();

protected:
   void keyPressEvent(QKeyEvent *);
   void keyReleaseEvent(QKeyEvent *);





};

#endif // PLAYERITEM2_H
