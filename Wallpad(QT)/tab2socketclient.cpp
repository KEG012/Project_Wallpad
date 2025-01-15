#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    ui->pPBsendButton->setEnabled(true);
    pKeyboard = new Keyboard();
    pSocketCleint = new SocketClient(this);
    connect(ui->pLErecvId, SIGNAL(selectionChanged()), this, SLOT(keyboardSlot()));
    connect(ui->pLEsendData, SIGNAL(selectionChanged()), this, SLOT(keyboardSlot()));
    connect(pSocketCleint, SIGNAL(sigSocketRecv(QString)), this, SLOT(socketRecvUpdateSlot(QString)));
    connect(ui->pLEsendData, &QLineEdit::returnPressed, this, &Tab2SocketClient::on_pPBsendButton_clicked);
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}

void Tab2SocketClient::socketRecvUpdateSlot(QString strRecvData)
{
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strRecvData.chop(1);        //'\n' 문자 제거
    strTime = strTime + " " + strRecvData;
    ui->pTErecvData->append(strTime);

    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList qList = strRecvData.split("@");
    if(qList[2].indexOf("LAMP") == 0)
    {
        emit tab4RecvDataSig(strRecvData);
    }
    else if(qList[2].indexOf("SENSOR") == 0)
    {
        emit tab3RecvDataSig(strRecvData);
    }
}

void Tab2SocketClient::on_pPBsendButton_clicked()
{
    QString strRecvId = ui->pLErecvId->text();
    QString strSendData = ui->pLEsendData->text();
    if(!strSendData.isEmpty())
    {
        if(strRecvId.isEmpty())
            strSendData = "[ALLMSG]"+strSendData;
        else
            strSendData = "["+strRecvId+"]"+strSendData;
        pSocketCleint->slotSocketSendData(strSendData);
        ui->pLEsendData->clear();
    }
}

void Tab2SocketClient::keyboardSlot()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyboard->setLineEdit(pQLineEdit);
    pKeyboard->show();
}

void Tab2SocketClient::slotSocketSendDataDial(int dialValue)
{
    QString strValue = "[SCM_PI]SETDIAL@"+QString::number(dialValue);
    pSocketCleint->slotSocketSendData(strValue);
}

SocketClient* Tab2SocketClient::getpSocketClient()
{
    return pSocketCleint;
}

void Tab2SocketClient::on_pPBrecvDataClear_clicked()
{
    ui->pTErecvData->clear();
}
