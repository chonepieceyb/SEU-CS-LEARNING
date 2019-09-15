#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    setFixedSize(QSize(600,500));
    ui->setupUi(this);
    setWindowTitle("帮助");
    setAutoFillBackground(true);
    QPalette back = this->palette();
    setStyleSheet("background-repeat:no-repeat;");
    back.setBrush(QPalette::Window, QBrush(
                      QPixmap(":/images/startui_background.gif").scaled(
                          this->size(),
                          Qt::IgnoreAspectRatio,
                          Qt::SmoothTransformation)));
    setPalette(back);
    setWindowModality(Qt::ApplicationModal);
    setWindowIcon(QIcon(":/images/icon.png"));
    setCursor(QCursor(QPixmap(":/images/mouse.png")));
}

Help::~Help()
{
    delete ui;
}

void Help::on_btnClose_clicked()
{
    this->close();
}
