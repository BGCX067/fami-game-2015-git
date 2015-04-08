#ifndef TANKSGUI_H
#define TANKSGUI_H

#include <QMainWindow>
#include <QGraphicsView>
#include <string>

using namespace std;

struct gui_cmd
{
    gui_cmd()
    {
        player_id = 1;
        cmd_code = 0;
        desc = 'default';
    };

    int player_id; // номер команды
    int cmd_code; // код команды
    string desc; // описание команды
};

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
    gui_cmd guicmd;
    private slots:
          // Слот для обработки нажатий всех кнопок
          void keyPressEvent(QKeyEvent *keyEvent);
          void on_pushButton_clicked();
          void on_pushButton_2_clicked();
          void on_pushButton_3_clicked();
};

#endif // TANKSGUI_H
