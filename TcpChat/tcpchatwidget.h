#ifndef TCPCHATWIDGET_H
#define TCPCHATWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QTextCodec>
#include <QtDebug>
#include <QMessageBox>
namespace Ui {
class TcpChatWidget;
}

class TcpChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpChatWidget(QWidget *parent = 0);
    ~TcpChatWidget();

private:
    QString getIp();

private slots:
    void on_startServerButton_clicked();
    void readMessageSlot();
    void newConnectSlot();
    void on_sendButton_clicked();

private:
    Ui::TcpChatWidget *ui;

    QTcpServer* server;
    QList<QTcpSocket *> socketList;
//    QTcpSocket *socket;
    QString ip;//本机IP
};

#endif // TCPCHATWIDGET_H
