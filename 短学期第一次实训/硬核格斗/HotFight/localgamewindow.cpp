#include "localgamewindow.h"
#include "localgamescene.h"
#include <QPixmap>
#include <QIcon>

LocalGameWindow::LocalGameWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    setFixedSize(800,400);
    m_localgamescene = new LocalGameScene();
    setScene(m_localgamescene);
    this->setBackgroundBrush(QBrush(
                                 QPixmap(":/images/startui_background.gif").scaled(
                                     this->size(),
                                     Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    setStyleSheet("border: 0px;"
                  "padding: 0px;");
    setCursor(QCursor(QPixmap(":/images/mouse.png")));
    setWindowIcon(QIcon(":/images/icon.png"));

    //弹出结束界面
    connect(m_localgamescene,&LocalGameScene::gameover1PSignal,this,&LocalGameWindow::showEndWindow1PSlot);
    connect(m_localgamescene,&LocalGameScene::gameover2PSignal,this,&LocalGameWindow::showEndWindow2PSlot);
    connect(m_localgamescene,&LocalGameScene::gameoverBothSignal,this,&LocalGameWindow::showEndWindowBothSlot);

    m_endWindow=NULL;
}

LocalGameWindow::~LocalGameWindow()
{
    if(m_localgamescene != nullptr)
    {
        delete m_localgamescene;
        m_localgamescene=NULL;
    }
    if(m_endWindow !=NULL)
    {
        delete m_endWindow;
        m_endWindow=NULL;
    }

}

void LocalGameWindow::showEndWindow1PSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("2P 获胜！");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal, this , &LocalGameWindow::restartSceneSlot);
        connect(m_endWindow, &EndWindow::returnToSignal,this,[=](){
            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,this,[=](){           
            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            this->close();
            emit endGameSignal();
        });
    }
}

void LocalGameWindow::showEndWindow2PSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("1P 获胜！ ");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal, this , &LocalGameWindow::restartSceneSlot);
        connect(m_endWindow, &EndWindow::returnToSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            this->close();
            emit endGameSignal();
        });
    }
}

void LocalGameWindow::showEndWindowBothSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("平局! ");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal, this , &LocalGameWindow::restartSceneSlot);
        connect(m_endWindow, &EndWindow::returnToSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            this->close();
            emit endGameSignal();
        });

    }
}

void LocalGameWindow::restartSceneSlot()
{
    if(m_localgamescene!=NULL)
    {
        delete m_localgamescene;
        m_localgamescene=NULL;
    }

    if(m_localgamescene==NULL)
    {
        m_localgamescene = new LocalGameScene();
        setScene(m_localgamescene);
        connect(m_localgamescene,&LocalGameScene::gameover1PSignal,this,&LocalGameWindow::showEndWindow1PSlot);
        connect(m_localgamescene,&LocalGameScene::gameover2PSignal,this,&LocalGameWindow::showEndWindow2PSlot);
        connect(m_localgamescene,&LocalGameScene::gameoverBothSignal,this,&LocalGameWindow::showEndWindowBothSlot);
    }
    //删除本窗口
    if(m_endWindow!=NULL)
    {
        delete m_endWindow;
        m_endWindow=NULL;
    }
}
