#ifndef TAB3CHARTPLOT_H
#define TAB3CHARTPLOT_H

#include <QWidget>
#include <QLineSeries>
#include <QChartView>
#include <QDebug>
#include <QDateTimeAxis>
#include <QDate>
#include <QTime>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Tab3ChartPlot;
}

class Tab3ChartPlot : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3ChartPlot(QWidget *parent = nullptr);
    ~Tab3ChartPlot();

private:
    Ui::Tab3ChartPlot *ui;
    QLineSeries* illuLine;
    QLineSeries* tempLine;
    QLineSeries* humiLine;
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
    QDateTimeAxis * axisX;
    QDateTime firstDate;
    QDateTime lastDate;
private slots:
    void chartPlotClear();
    void tab3RecvDataSlot(QString);
    void updateLastDateTime(int);
};

#endif // TAB3CHARTPLOT_H

