#include "tab0mainmenu.h"
#include "ui_tab0mainmenu.h"

Tab0MainMenu::Tab0MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab0MainMenu)
{
    ui->setupUi(this);
    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &Tab0MainMenu::updateTime);
    ptimer->start(1000);

    ui->pLNHour->resize(200,100);
    ui->pLNMin->resize(200,100);
    ui->pLNSec->resize(200,100);

}

Tab0MainMenu::~Tab0MainMenu()
{
    delete ui;
}

void Tab0MainMenu::updateTime(){
    QDateTime utcTime = QDateTime::currentDateTimeUtc();

    QDateTime koreatime = utcTime.addSecs(9*60*60);

    QString timeYear = koreatime.toString("yyyy");
    QString timeMonth = koreatime.toString("MM");
    QString timeHour = koreatime.toString("HH");
    QString timeMin = koreatime.toString("mm");
    QString timeSec = koreatime.toString("ss");

    ui->pLNYear->display(timeYear);
    ui->pLNMonth->display(timeMonth);
    ui->pLNHour->display(timeHour);
    ui->pLNMin->display(timeMin);
    ui->pLNSec->display(timeSec);

    ui->pLNYear->setDigitCount(QString("%2").arg(timeYear).length());
    ui->pLNMonth->setDigitCount(QString("%2").arg(timeMonth).length());
    ui->pLNHour->setDigitCount(QString("%2").arg(timeHour).length());
    ui->pLNMin->setDigitCount(QString("%2").arg(timeMin).length());
    ui->pLNSec->setDigitCount(QString("%2").arg(timeSec).length());
}
