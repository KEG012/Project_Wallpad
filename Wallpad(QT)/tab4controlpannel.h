#ifndef TAB4CONTROLPANNEL_H
#define TAB4CONTROLPANNEL_H

#include <QWidget>
#include <QPalette>

namespace Ui {
class Tab4ControlPannel;
}

class Tab4ControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4ControlPannel(QWidget *parent = nullptr);
    ~Tab4ControlPannel();

signals:
    void socketSendDataSig(QString);

private slots:
    void on_pPBLamp_clicked(bool checked);
    void tab4RecvDataSlot(QString);

private:
    Ui::Tab4ControlPannel *ui;
    QPalette paletteColorOn;
    QPalette paletteColorOff;
};

#endif // TAB4CONTROLPANNEL_H
