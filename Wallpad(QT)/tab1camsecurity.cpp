#include "tab1camsecurity.h"
#include "ui_tab1camsecurity.h"

Tab1CamSecurity::Tab1CamSecurity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab1CamSecurity)
{
    ui->setupUi(this);
    pCameracapture = new Cameracapture(this);
    pCameracapture->pTLcamView = ui->pTLcamView;
    //ui->pTLcamView->show();
    //QPixmap emptyImage(ui->pTLcamView->size());
    //emptyImage.fill(Qt::black); // 검은색으로 채움 (다른 색도 가능)
    //ui->pTLcamView->setPixmap(emptyImage);
    QPixmap blackScreen(320, 240);
    blackScreen.fill(Qt::black); // 검은색으로 채움

    // QLabel에 검은 화면 설정
    ui->pTLcamView->setPixmap(blackScreen);
    ui->pTLcamView->setFixedSize(320, 240); // QLabel 크기도 640x480으로 고정
    ui->pTLcamView->show(); // 항상 표시되도록 설정
    connect(ui->pPBCamView,SIGNAL(clicked(bool)),this, SLOT(slotCamView(bool)));
//    connect(ui->pPBsnapShot, SIGNAL(clicked()), this, SLOT(slotSnapShot()));
}

Tab1CamSecurity::~Tab1CamSecurity()
{
    delete ui;
}

void Tab1CamSecurity::slotCamView(bool check)
{
    if (check) // "영상 보기" 상태에서 클릭
    {
        ui->pPBCamView->setText("영상 정지");
        ui->pTLcamView->show(); // QLabel 표시
        if (!pCameracapture->getCamFlag()) {
            pCameracapture->setCamFlag(true);
            pCameracapture->start();
        }
    }
    else // "영상 정지" 상태에서 클릭
    {
        ui->pPBCamView->setText("영상 보기");
        pCameracapture->setCamFlag(false);
        pCameracapture->quit();
        pCameracapture->wait();

        QPixmap emptyImage(ui->pTLcamView->size());
        emptyImage.fill(Qt::black); // 검은색으로 채움 (다른 색도 가능)
        ui->pTLcamView->setPixmap(emptyImage);
    }
}
void Tab1CamSecurity::slotSnapShot()
{
    if(ui->pPBCamView->isChecked())
        pCameracapture->camSnapshot();
}
void Tab1CamSecurity::slotSecurityMode(bool check)
{
    pCameracapture->camTimerStartStop(check);
}

void Tab1CamSecurity::slotColorMode(bool bCheck)
{
    pCameracapture->colorMode = bCheck;
}
Cameracapture* Tab1CamSecurity::pGetCameracapture()
{
    return pCameracapture;
}

