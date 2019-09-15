#include "netconnectdialog.h"
#include "ui_netconnectdialog.h"

NetConnectDialog::NetConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetConnectDialog)
{
    ui->setupUi(this);
    setWindowTitle("局域网连接");
    setCursor(QCursor(QPixmap(":/images/mouse.png")));
    ui->clientIP->setText("127.0.0.1");   //设置默认ip
    ui->clientPort->setText("8888");      //设置默认窗口
    ui->radioButton1P->setChecked(true);   //默认选择1P
    m_endWindow=NULL;
    m_netGameWindow=NULL;
}

NetConnectDialog::~NetConnectDialog()
{
    if(m_netGameWindow!=NULL)
    {
        delete m_netGameWindow;
        m_netGameWindow=NULL;
    }
    if(m_endWindow!=nullptr)
    {
        delete m_endWindow;
        m_endWindow=NULL;
    }
    delete ui;
}

void NetConnectDialog::on_clientConnect_clicked()
{
    if(ui->clientIP->text().isEmpty())
    {
        QMessageBox::information(this,"错误!","请输入连接对象的ip地址");
    }
    else if(ui->clientPort->text().isEmpty())
    {
        QMessageBox::information(this,"错误!","请输入连接对象的端口号");
    }
    else if(!(ui->radioButton1P->isChecked()|| ui->radioButton2P->isChecked())) //如果1P和2P都没选的话
    {
        QMessageBox::information(this,"错误!","请选择是1P还是2P");
    }
    else
    {
        //获取ip 和 端口号
        QString ip=ui->clientIP->text();
        int port=ui->clientPort->text().toInt();

        //初始化一个netGameWindow;
        m_netGameWindow = new NetGameWindow(ip,port);

        //设置1p还是2p
        if(ui->radioButton1P->isChecked())
        {
            m_netGameWindow->setSceneNetType(NetGameScene::C1);
        }
        else
        {
            m_netGameWindow->setSceneNetType(NetGameScene::C2);
        }

        //弹出结束窗口
        connect(m_netGameWindow,&NetGameWindow::gameover1PSignal,this,&NetConnectDialog::showEndWindow1PSlot);
        connect(m_netGameWindow,&NetGameWindow::gameover2PSignal,this,&NetConnectDialog::showEndWindow2PSlot);
        connect(m_netGameWindow,&NetGameWindow::gameoverBothSignal,this,&NetConnectDialog::showEndWindowBothSlot);
        m_netGameWindow->show();
        this->close();
    }
}

void NetConnectDialog::on_clientCancel_clicked()
{
    this->close();
}

//槽函数
void NetConnectDialog::showEndWindow1PSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("2P 获胜！");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal,[=](){
            emit restartSignal();
        });
        connect(m_endWindow, &EndWindow::returnToSignal,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,[=](){

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

void NetConnectDialog::showEndWindow2PSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("1P 获胜！ ");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal,[=](){
            emit restartSignal();
        });
        connect(m_endWindow, &EndWindow::returnToSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,[=](){

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

void NetConnectDialog::showEndWindowBothSlot()
{
    if(m_endWindow==NULL)
    {
        m_endWindow = new EndWindow();
        m_endWindow->setWinner("平局! ");
        m_endWindow->show();
        connect(m_endWindow,&EndWindow::restartSignal,[=](){
            emit restartSignal();
        });
        connect(m_endWindow, &EndWindow::returnToSignal,this,[=](){

            if(m_endWindow!=NULL)
            {
                delete m_endWindow;
                m_endWindow=NULL;
            }
            emit returnToStartWindowSignal();
        });
        connect(m_endWindow, &EndWindow::endGameSignal,[=](){

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


