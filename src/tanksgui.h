#ifndef TANKSGUI_H
#define TANKSGUI_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <string>

#include "gui/interface.h"
#include "general_types.h"
#include "logic/interface.h"

using namespace std;

struct gui_cmd
{
    gui_cmd()
    {
        player_id = 1;
        cmd_code = 0;
      //  desc = "default";
    };

    int player_id; // номер команды
    int cmd_code; // код команды
    GUICommand desc; // описание команды
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
    shared_ptr<logic::Logic> LogicModule; //теперь здесь живет экземплр логики
    shared_ptr<tmap::TMap> MapModule;
    Ui::TanksGUI *ui;
    gui_cmd guicmd;
    QTimer* game_timer;



    private slots:
          // Слот для обработки нажатий всех кнопок
          void keyPressEvent(QKeyEvent *keyEvent);
          void on_pushButton_clicked();
          void on_pushButton_2_clicked();
          void on_pushButton_3_clicked();
		  void on_actionDownload_Map_triggered();
          void resizeEvent(QResizeEvent *resizeEvent);
          void timer_event();

};

#endif // TANKSGUI_H
