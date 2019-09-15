#ifndef NETPLAYER2P_H
#define NETPLAYER2P_H

#include "player2p.h"
#include "playeritem.h"
#include <QEvent>

class NetPlayer2P : public Player2P
{
public:
    NetPlayer2P();
protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
};

#endif // NETPLAYER2P_H
