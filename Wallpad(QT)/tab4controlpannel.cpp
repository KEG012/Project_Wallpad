#include "tab4controlpannel.h"
#include "ui_tab4controlpannel.h"

Tab4ControlPannel::Tab4ControlPannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab4ControlPannel)
{
    ui->setupUi(this);
    paletteColorOn.setColor(ui->pPBLamp->backgroundRole(),QColor(255,0,0));
    paletteColorOff.setColor(ui->pPBLamp->backgroundRole(),QColor(0,0,255));
    ui->pPBLamp->setPalette(paletteColorOff);
}

Tab4ControlPannel::~Tab4ControlPannel()
{
    delete ui;
}

void Tab4ControlPannel::on_pPBLamp_clicked(bool checked)
{
    if(checked)
    {
        emit socketSendDataSig("[KEG_STM32]LAMPON");
    }
    else
    {
        emit socketSendDataSig("[KEG_STM32]LAMPOFF");
    }
}

void Tab4ControlPannel::tab4RecvDataSlot(QString recvData)
{
    QStringList qList = recvData.split("@");
    if(qList[2] == "LAMPON")
    {
        ui->pPBLamp->setIcon(QIcon(":/Image/Image/light_on.png"));
        ui->pPBLamp->setPalette(paletteColorOn);

    }
    else if(qList[2] == "LAMPOFF")
    {
        ui->pPBLamp->setIcon(QIcon(":/Image/Image/light_off.png"));
        ui->pPBLamp->setPalette(paletteColorOff);
    }
}
