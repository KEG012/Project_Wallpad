#include "tab3chartplot.h"
#include "ui_tab3chartplot.h"

Tab3ChartPlot::Tab3ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab3ChartPlot)
{
    ui->setupUi(this);
    illuLine = new QLineSeries(this);
    tempLine = new QLineSeries(this);
    humiLine = new QLineSeries(this);
    illuLine->setName("조도");
    tempLine->setName("온도");
    humiLine->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);
    chart = new QChart();
//   chart->legend()->hide();
    chart->addSeries(illuLine);

    QPen pen2;
    pen2.setWidth(2);
    pen2.setBrush(Qt::green);
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setJoinStyle(Qt::MiterJoin);
    tempLine->setPen(pen2);
    chart->addSeries(tempLine);

    QPen pen3;
    pen3.setWidth(2);
    pen3.setBrush(Qt::blue);
    pen3.setCapStyle(Qt::FlatCap);
    pen3.setJoinStyle(Qt::MiterJoin);
    humiLine->setPen(pen3);
    chart->addSeries(humiLine);

//    chart->setTitle("illumination chart");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);
//    chart->axes(Qt::Horizontal).first()->setRange(0, 24);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->pChartViewLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
//    axisX->setFormat("MM-dd hh:mm");
    axisX->setFormat("hh:mm");

    updateLastDateTime(0);

    chartView->chart()->setAxisX(axisX,illuLine);
    chartView->chart()->setAxisX(axisX,tempLine);
    chartView->chart()->setAxisX(axisX,humiLine);

    connect(ui->pPBClear,SIGNAL(clicked()),this,SLOT(chartPlotClear()));
}
void Tab3ChartPlot::updateLastDateTime(int)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDate.setDate(date);
    firstDate.setTime(time);

    lastDate.setDate(date);
    QTime tempTime = time.addSecs(60*10);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate,lastDate);
}

void Tab3ChartPlot::chartPlotClear()
{

    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTime(0);
}

void Tab3ChartPlot::tab3RecvDataSlot(QString recvData)
{

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    QStringList qlist = recvData.split("@");  //@HM_CON@SENSOR@12.3@4.56@78.9  //조도,온도,습도
    QString illu = qlist[3];        //조도
    QString temp = qlist[4];        //온도
    QString humi = qlist[5];        //습도
//    qDebug() << illu;
//    qDebug() << xValue.toMSecsSinceEpoch();
    illuLine->append(xValue.toMSecsSinceEpoch(),illu.toInt());
    tempLine->append(xValue.toMSecsSinceEpoch(),temp.toDouble());
    humiLine->append(xValue.toMSecsSinceEpoch(),humi.toDouble());
}

Tab3ChartPlot::~Tab3ChartPlot()
{
    delete ui;
}
