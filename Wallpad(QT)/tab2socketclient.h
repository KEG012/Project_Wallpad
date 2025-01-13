#ifndef TAB2SOCKETCLIENT_H
#define TAB2SOCKETCLIENT_H

#include <QWidget>
#include <QTime>
#include <QLineEdit>
#include "socketclient.h"
#include "keyboard.h"

namespace Ui {
class Tab2SocketClient;
}

class Tab2SocketClient : public QWidget
{
    Q_OBJECT

private:
    Ui::Tab2SocketClient *ui;
    SocketClient *pSocketCleint;
    Keyboard* pKeyboard;

public:
    explicit Tab2SocketClient(QWidget *parent = nullptr);
    ~Tab2SocketClient();
    SocketClient* getpSocketClient();

signals:
    void ledWriteSig(int);
    void setDialValueSig(int);
    void tab3RecvDataSig(QString);
    void tab4RecvDataSig(QString);

private slots:
    void socketRecvUpdateSlot(QString);
    void on_pPBsendButton_clicked();
    void slotSocketSendDataDial(int);
    void keyboardSlot();
    void on_pPBrecvDataClear_clicked();
};

#endif // TAB2SOCKETCLIENT_H
