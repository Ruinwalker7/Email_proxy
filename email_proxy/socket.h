#ifndef SOCKET_H
#define SOCKET_H
#include "QTcpSocket"
#include "qbytearray.h"

class socket
{
public:
    socket(QByteArray user,QByteArray password);
    bool sendEmail( QByteArray s_title, QByteArray s_Content, QByteArray sendIp);
    bool checkAccount();
    QString WaitAndReadData();
    ~socket();
private:
    QByteArray userName,password;
    QString stmp_addr;
    QTcpSocket *m_socket;

};

#endif // SOCKET_H
