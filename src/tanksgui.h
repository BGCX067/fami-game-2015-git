#ifndef TANKSGUI_H
#define TANKSGUI_H

#include <QMainWindow>

namespace Ui {
class TanksGUI;
}

class TanksGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit TanksGUI(QWidget *parent = 0);
    ~TanksGUI();

private:
    Ui::TanksGUI *ui;
};

#endif // TANKSGUI_H
