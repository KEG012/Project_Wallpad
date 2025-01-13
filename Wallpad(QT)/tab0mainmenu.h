#ifndef TAB0MAINMENU_H
#define TAB0MAINMENU_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class Tab0MainMenu;
}

class Tab0MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit Tab0MainMenu(QWidget *parent = nullptr);
    ~Tab0MainMenu();

private:
    void updateTime();

private:
    Ui::Tab0MainMenu *ui;
    QTimer* ptimer;
};

#endif // TAB0MAINMENU_H
