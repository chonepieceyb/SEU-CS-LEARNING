#include "localgamewindow.h"
#include "startwindow.h"
#include "endwindow.h"
#include "netconnectdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 开始界面
    StartWindow s;
    s.show();

    // 测试结束界面
    return a.exec();
}
