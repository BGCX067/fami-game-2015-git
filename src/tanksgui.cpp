#include "tanksgui.h"
#include "ui_tanksgui.h"
#include <QKeyEvent>

TanksGUI::TanksGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TanksGUI)
{
    ui->setupUi(this);
}

TanksGUI::~TanksGUI()
{
    delete ui;
}

void TanksGUI::keyPressEvent(QKeyEvent * keyEvent)
{
    setFocus();

    switch(keyEvent->key())
    {
        case Qt::Key_W :{
            //printf("BUTTON_W!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 1;    guicmd.desc = "but_w";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_A :{
            //printf("BUTTON_A!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 2;    guicmd.desc = "but_a";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_S :{
            //printf("BUTTON_S!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 3;    guicmd.desc = "but_s";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_D :{
            //printf("BUTTON_D!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 4;    guicmd.desc = "but_d";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_Space :{
            //printf("BUTTON_FIRE_IN_THE_HOLE!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 10;    guicmd.desc = "but_fire1";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_Left :{
            //printf("BUTTON_LEFT!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 5;    guicmd.desc = "but_lef";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_Up :{
            //printf("BUTTON_UP!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 6;    guicmd.desc = "but_up";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_Right :{
            //printf("BUTTON_RIGHT!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 7;    guicmd.desc = "but_rig";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_Down :{
            //printf("BUTTON_DOWN!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 8;    guicmd.desc = "but_dow";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        case Qt::Key_0 :{
            //printf("FIRE_IN_THE_HOLE!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 9;    guicmd.desc = "but_fire2";
            //Logic::getNextCommandFromGUI(guicmd);
            break;
        };

        update();
    }

}

// Кнопка "Start Game"
void TanksGUI::on_pushButton_clicked()
{
    //printf("BUTTON_START!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 10;    guicmd.desc = "but_start";
}

// Кнопка "Exit Game"
void TanksGUI::on_pushButton_2_clicked()
{
    //printf("BUTTON_EXIT!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 11;    guicmd.desc = "but_exit";
}

// Кнопка "About"
void TanksGUI::on_pushButton_3_clicked()
{
    //printf("BUTTON_ABOUT!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 12;    guicmd.desc = "but_about";
}
