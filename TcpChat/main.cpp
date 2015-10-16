#include "tcpchatwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpChatWidget w;
    w.show();

    return a.exec();
}
