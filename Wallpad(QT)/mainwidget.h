#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab0mainmenu.h"
#include "tab1camsecurity.h"
#include "tab2socketclient.h"
#include "tab3chartplot.h"
#include "tab4controlpannel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwidget; }
QT_END_NAMESPACE

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    mainwidget(QWidget *parent = nullptr);
    ~mainwidget();

private:
    Ui::mainwidget *ui;
    Tab0MainMenu *pTab0MainMenu;
    Tab1CamSecurity *pTab1CamSecurity;
    Tab2SocketClient *pTab2SocketClient;
    Tab3ChartPlot *pTab3ChartPlot;
    Tab4ControlPannel *pTab4ControlPannel;
};
#endif // MAINWIDGET_H
