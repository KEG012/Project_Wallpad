#ifndef TAB1CAMSECURITY_H
#define TAB1CAMSECURITY_H

#include <QWidget>
#include "cameracapture.h"
namespace Ui {
class Tab1CamSecurity;
}

class Tab1CamSecurity : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1CamSecurity(QWidget *parent = nullptr);
    ~Tab1CamSecurity();
    Cameracapture* pGetCameracapture();
private:
    Ui::Tab1CamSecurity *ui;
    Cameracapture * pCameracapture;
private slots:
    void slotCamView(bool);
    void slotSnapShot();
    void slotSecurityMode(bool);
    void slotColorMode(bool);
};

#endif // TAB1CAMSECURITY_H
