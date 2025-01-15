#include "mainwidget.h"
#include "ui_mainwidget.h"

mainwidget::mainwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainwidget)
{
    ui->setupUi(this);
    pTab0MainMenu = new Tab0MainMenu(ui->ptab0);
    ui->ptab0->setLayout(pTab0MainMenu->layout());

    pTab1CamSecurity = new Tab1CamSecurity(ui->ptab1);
    ui->ptab1->setLayout(pTab1CamSecurity->layout());

    pTab2SocketClient = new Tab2SocketClient(ui->ptab2);
    ui->ptab2->setLayout(pTab2SocketClient->layout());

    pTab3ChartPlot = new Tab3ChartPlot(ui->ptab3);
    ui->ptab3->setLayout(pTab3ChartPlot->layout());

    pTab4ControlPannel = new Tab4ControlPannel(ui->ptab4);
    ui->ptab4->setLayout(pTab4ControlPannel->layout());
    ui->pTabWidget->setCurrentIndex(0);

    connect(pTab4ControlPannel,SIGNAL(socketSendDataSig(QString)), pTab2SocketClient->getpSocketClient(),SLOT(slotSocketSendData(QString)));
    connect(pTab2SocketClient, SIGNAL(tab4RecvDataSig(QString)), pTab4ControlPannel,SLOT(tab4RecvDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab3RecvDataSig(QString)), pTab3ChartPlot,SLOT(tab3RecvDataSlot(QString)));
}

mainwidget::~mainwidget()
{
    delete ui;
}

