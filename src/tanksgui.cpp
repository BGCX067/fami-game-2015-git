#include "tanksgui.h"
#include "ui_tanksgui.h"
#include <QKeyEvent>
#include <QShowEvent>
#include <QFileDialog>
#include <QResizeEvent>
#include <QDebug>

TanksGUI::TanksGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TanksGUI)
{
    logic_flag = 0;
    ui->setupUi(this);
    ui->graphicsView->setGeometry(0, 0 , 775, 436);
    setFocus();
    // Инициализация карты(testing)
    MapModule = make_shared<tmap::TMap>();
    ui->graphicsView->init(MapModule);


}

TanksGUI::~TanksGUI()
{
    delete ui;
}

void TanksGUI::resizeEvent(QResizeEvent * resizeEvent)
{
    (void) resizeEvent;
    int sizeh = this->ui->graphicsView->height();
    int sizew = this->ui->graphicsView->width();
//    qDebug() << "GUI:" << sizeh << " " << sizew;
    printf("%d %d \n", sizeh, sizew);
}

void TanksGUI::keyPressEvent(QKeyEvent * keyEvent)
{
    qDebug() << "GUI: keyPressEvent. Logic : "<< logic_flag << endl;
    if (logic_flag == 1)
    {
        switch(keyEvent->key())
        {
            case Qt::Key_W :{
                //printf("BUTTON_W!!!\n");
                guicmd.player_id = 1;   guicmd.cmd_code = 1;    guicmd.desc = GUICommand::Up;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);
                break;
            };

            case Qt::Key_A :{
                //printf("BUTTON_A!!!\n");
                guicmd.player_id = 1;   guicmd.cmd_code = 2;    guicmd.desc = GUICommand::Left;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_S :{
                //printf("BUTTON_S!!!\n");
                guicmd.player_id = 1;   guicmd.cmd_code = 3;    guicmd.desc = GUICommand::Down;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_D :{
                //printf("BUTTON_D!!!\n");
                guicmd.player_id = 1;   guicmd.cmd_code = 4;    guicmd.desc = GUICommand::Right;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Space :{
                //printf("BUTTON_FIRE_IN_THE_HOLE!!!\n");
                guicmd.player_id = 1;   guicmd.cmd_code = 10;    guicmd.desc = GUICommand::Atack;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Left :{
                //printf("BUTTON_LEFT!!!\n");
                guicmd.player_id = 2;   guicmd.cmd_code = 5;    guicmd.desc = GUICommand::Left;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Up :{
                //printf("BUTTON_UP!!!\n");
                guicmd.player_id = 2;   guicmd.cmd_code = 6;    guicmd.desc = GUICommand::Up;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Right :{
                //printf("BUTTON_RIGHT!!!\n");
                guicmd.player_id = 2;   guicmd.cmd_code = 7;    guicmd.desc = GUICommand::Right;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Down :{
                //printf("BUTTON_DOWN!!!\n");
                guicmd.player_id = 2;   guicmd.cmd_code = 8;    guicmd.desc = GUICommand::Down;
                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_I :{
                //printf("FIRE_IN_THE_HOLE!!!\n");
                guicmd.player_id = 2;   guicmd.cmd_code = 9;    guicmd.desc = GUICommand::Atack;

                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            };

            case Qt::Key_Escape :
            {
                //printf("NEED A BRAKE, CAP!!!\n");
                guicmd.player_id = 0;   guicmd.cmd_code = 13;    guicmd.desc = GUICommand::PAUSE;

                CommandFromGUI testCommand;
                testCommand.setPlayerNumber(guicmd.player_id);
                testCommand.setFromGUICommand(guicmd.desc);
                LogicModule->setNextCommandFromGUI(testCommand);

                break;
            }
            update();
        }
    }
    else printf("The game has not started yet, dumbass!\n");
}

// Кнопка "Start Game"
void TanksGUI::on_pushButton_clicked()
{
   // printf("BUTTON_START!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 10;    guicmd.desc = GUICommand::START;

    if(logic_flag == 0)
    {
        //Запуск таймера
        qDebug() << "BUTTON_START";

        // Создание таймера
        game_timer = new QTimer(this);
        connect(game_timer, SIGNAL(timeout()), this, SLOT(timer_event()));
        connect(game_timer, SIGNAL(timeout()), ui->graphicsView ,SLOT(updateGL()));
        game_timer->start(10);
        printf("TIMER IS ALIVE\n");

        // Инициализация логики
        LogicModule = make_shared<logic::Logic>(MapModule);
        logic_flag = 1;
    }
    else
    {
        CommandFromGUI testCommand;
        testCommand.setPlayerNumber(guicmd.player_id);
        testCommand.setFromGUICommand(guicmd.desc);
        LogicModule->setNextCommandFromGUI(testCommand);
    }
    setFocus();
}

// Кнопка "Stop Game"
void TanksGUI::on_pushButton_2_clicked()
{
    if(logic_flag == 1)
    {
        printf("BUTTON_STOP!!!\n");
        guicmd.player_id = 0;   guicmd.cmd_code = 11;    guicmd.desc = GUICommand::STOP;

        CommandFromGUI testCommand;
        testCommand.setPlayerNumber(guicmd.player_id);
        testCommand.setFromGUICommand(guicmd.desc);
        LogicModule->setNextCommandFromGUI(testCommand);
        logic_flag = 0;
        game_timer->stop();
        printf("TIMER IS DEAD\n");
    }
}

// Кнопка "About"
void TanksGUI::on_pushButton_3_clicked()
{
    //printf("BUTTON_ABOUT!!!\n");
    //guicmd.player_id = 0;   guicmd.cmd_code = 12;    guicmd.desc = GUICommand::ABOUT;
    //CommandFromGUI testCommand;
    //testCommand.setPlayerNumber(guicmd.player_id);
    //testCommand.setFromGUICommand(guicmd.desc);
    //LogicModule->setNextCommandFromGUI(testCommand);

    QMessageBox::about(this, "About", "Game was created by PMM-41/42 under M. Royak guidance! Thank you!");
}

void TanksGUI::on_actionDownload_Map_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*)"));
   //Отправить событие Карте!
   //printf("CANT TOUCH THIS!!!\n");

   this->MapModule->loadConfig(fileName.toStdString());
}

// Обработка событий по основному игровому таймеру
void TanksGUI::timer_event() {
   // qDebug() << "Timer event";
    LogicModule->run();
    ui->graphicsView->render();
}
