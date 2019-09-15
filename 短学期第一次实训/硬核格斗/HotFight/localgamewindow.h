#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playeritem.h"
#include "player1p.h"
#include "player2p.h"
#include "localgamescene.h"
#include <QGraphicsView>
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QObject>
#include "endwindow.h"


class LocalGameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    LocalGameWindow(QWidget *parent = nullptr);
    ~LocalGameWindow();
signals:
    void returnToStartWindowSignal();
    void endGameSignal();
public slots:
    void showEndWindow1PSlot();
    void showEndWindow2PSlot();
    void showEndWindowBothSlot();

    //重新开始的槽函数
    void restartSceneSlot();

protected:

private:
    EndWindow *m_endWindow;    //结束窗口
    LocalGameScene *m_localgamescene;   //测试需要

};

#endif // MAINWINDOW_H
