#include "startwindow.h"
#include "ui_startwindow.h"
#include <QPalette>
#include <QCloseEvent>

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    // 设置固定大小
    setFixedSize(QSize(600,500));
    ui->setupUi(this);
    setWindowTitle("开始游戏");
    // 设置窗口背景图
    setAutoFillBackground(true);
    QPalette back = this->palette();
    setStyleSheet("background-repeat:no-repeat;");
    back.setBrush(QPalette::Window, QBrush(
                      QPixmap(":/images/startui_background.gif").scaled(
                          this->size(),
                          Qt::IgnoreAspectRatio,
                          Qt::SmoothTransformation)));
    setPalette(back);
    setCursor(QCursor(QPixmap(":/images/mouse.png")));
    setWindowIcon(QIcon(":/images/icon.png"));
    //初始化打开窗口的类型
    m_windowType=NOWINDOW;
    // 初始化指针
    m_localGame = nullptr;
    m_netConnectDialog = nullptr;

}

StartWindow::~StartWindow()
{
    delete ui;
//    if(m_localGame != nullptr)
//        delete m_localGame;
//    if(m_netConnectDialog != nullptr)
//        delete m_netConnectDialog;
}

void StartWindow::setWindowType(WINDOWTYPE type)
{
    m_windowType=type;
}

StartWindow::WINDOWTYPE StartWindow::getWindowType()const
{
    return m_windowType;
}

void StartWindow::on_btnLocalGame_clicked()
{
    if(m_localGame!=NULL)
    {
        delete m_localGame;
        m_localGame=NULL;
    }
    // 打开单机游戏画面,如果没有窗口被打开的话
    if(m_localGame==NULL)
    {
        m_localGame = new LocalGameWindow();
        m_windowType=LOCAL;
        m_localGame->show();
        //第一个是返回主界面
        connect(m_localGame,&LocalGameWindow::returnToStartWindowSignal,this,&StartWindow::closeLocalGameSlot);
        connect(m_localGame,&LocalGameWindow::endGameSignal,this,&StartWindow::endGameSlot);
    }
    this->hide();

}

void StartWindow::on_btnNetGame_clicked()
{
   if(m_netConnectDialog!=NULL)
   {
       delete m_netConnectDialog;
       m_netConnectDialog=NULL;
   }

   //如果没有连接窗口的话
   if(m_netConnectDialog==NULL)
   {
       m_netConnectDialog= new NetConnectDialog;
       m_windowType=NET;
       m_netConnectDialog->show();
       //第一个是返回主界面，第二个是重新开始，第三个是退出游戏
       connect(m_netConnectDialog,&NetConnectDialog::returnToStartWindowSignal,this,&StartWindow::closeNetGameSlot);
       connect(m_netConnectDialog,&NetConnectDialog::restartSignal,this,&StartWindow::restartNetGameSlot);
       connect(m_netConnectDialog,&NetConnectDialog::endGameSignal,this,&StartWindow::endGameSlot);
   }
   this->hide();

}

void StartWindow::on_btnHelp_clicked()
{
    m_helpWindow = new Help();
    m_helpWindow->show();
}

void StartWindow::closeLocalGameSlot()
{
    m_localGame->close();
    if(m_localGame!=NULL)
    {
        delete m_localGame;
        m_localGame=NULL;
    }
    this->show();
}

void  StartWindow::closeNetGameSlot()
{
     m_netConnectDialog->close();
     if(m_netConnectDialog!=nullptr)
     {
         delete m_netConnectDialog;
         m_netConnectDialog=NULL;
     }
     this->show();
}

void StartWindow::restartNetGameSlot()
{
    m_netConnectDialog->close();
    if(m_netConnectDialog!=nullptr)
    {
        delete m_netConnectDialog;
        m_netConnectDialog=NULL;
    }
    if(m_netConnectDialog==NULL)
    {
        m_netConnectDialog= new NetConnectDialog;
        m_windowType=NET;
        m_netConnectDialog->show();
        connect(m_netConnectDialog,&NetConnectDialog::returnToStartWindowSignal,this,&StartWindow::closeNetGameSlot);
        connect(m_netConnectDialog,&NetConnectDialog::restartSignal,this,&StartWindow::restartNetGameSlot);
        connect(m_netConnectDialog,&NetConnectDialog::endGameSignal,this,&StartWindow::endGameSlot);
    }
    this->hide();
}

void StartWindow::endGameSlot()
{
    if(m_netConnectDialog!=nullptr)
    {
        delete m_netConnectDialog;
        m_netConnectDialog=NULL;
    }
    if(m_localGame!=NULL)
    {
        delete m_localGame;
        m_localGame=NULL;
    }
    this->close();
}
