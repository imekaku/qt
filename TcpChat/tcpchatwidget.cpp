#include "tcpchatwidget.h"
#include "ui_tcpchatwidget.h"

TcpChatWidget::TcpChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpChatWidget)
{
    ui->setupUi(this);
    ui->severIpLineEdit->setText(getIp());
    ui->severIpLineEdit->setReadOnly(true);//设置ip地址只读
    ui->chatTextEdit->setReadOnly(true);//设置聊天文本只读


    server = new QTcpServer;
    connect(ui->messageLineEdit,SIGNAL(returnPressed()),this,SLOT(on_sendButton_clicked()));
}

TcpChatWidget::~TcpChatWidget()
{
    delete ui;
}

void TcpChatWidget::on_startServerButton_clicked()//启动服务器
{
    if(ui->userNameLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","请输入您的用户名");
        return;
    }
    ui->userNameLineEdit->setReadOnly(true);//用户名置灰
    this->setWindowTitle(ui->userNameLineEdit->text()+"服务端");
    ui->startServerButton->setEnabled(false);//服务器按钮置灰
    ui->sendButton->setEnabled(true);//发送按钮置显

    quint16 i = 58080;

    bool ok = server->listen(QHostAddress::Any,i);//监听任何主机，这个端口号
    if(ok)
    {
        ui->ipTextEdit->append("服务器已经启动");
    }
    else
    {
        ui->ipTextEdit->append("服务器启动失败");
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
    //有新连接时,启动newConnectSlot()槽

    ui->portLineEdit->setText("58080");
    ui->portLineEdit->setReadOnly(true);
}

void TcpChatWidget::newConnectSlot()
{
    QTcpSocket *tcp = server->nextPendingConnection();
    socketList << tcp;//存储这个tcp
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessageSlot()));
}

void TcpChatWidget::readMessageSlot()//读取消息
{
    QTcpSocket *tcp = static_cast<QTcpSocket*>(sender());
    QByteArray qba = tcp->readAll();
    QString s = QVariant(qba).toString();
    ui->chatTextEdit->append(s);

    for(int i = 0; i < socketList.size(); ++i)
    {
        if(socketList.at(i) == tcp)
            ;
        else
            socketList.at(i)->write(s.toStdString().c_str(),strlen(s.toStdString().c_str()));
            //将读取到的消息发送给其他客户端
    }
}

void TcpChatWidget::on_sendButton_clicked()
{
    QString name, message;//发送者和消息
    name = "["+ui->userNameLineEdit->text()+":]";
    message = ui->messageLineEdit->text();
    QString sendMessage = name + message;
    for(int i=0; i<socketList.size();i++)
    {
        socketList.at(i)->write(sendMessage.toStdString().c_str(),strlen(sendMessage.toStdString().c_str()));
    }
    //发送给所有的客户端消息

    ui->messageLineEdit->clear();
    ui->chatTextEdit->append(sendMessage);
    ui->messageLineEdit->setFocus();
}

QString TcpChatWidget::getIp()//获取Ip地址
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol)
       {
           if (address.toString().contains("127.0."))
           {
               continue;
           }
           return address.toString();
       }
    }
    return 0;
}
