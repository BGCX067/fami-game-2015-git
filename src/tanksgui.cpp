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
    ui->setupUi(this);
    ui->graphicsView->setGeometry(0, 0 , 775, 436);
	setFocus();

    // Инициализация карты(testing)
    MapModule = make_shared<tmap::TMap>();
    // Инициализация логики
    LogicModule = make_shared<logic::Logic>(MapModule);
}

TanksGUI::~TanksGUI()
{
    //Остановка таймера
    game_timer->stop();
    delete ui;
}

void TanksGUI::resizeEvent(QResizeEvent * resizeEvent)
{
    int sizeh = this->ui->graphicsView->height();
    int sizew = this->ui->graphicsView->width();
//    qDebug() << "GUI:" << sizeh << " " << sizew;
    printf("%d %d \n", sizeh, sizew);
}

void TanksGUI::keyPressEvent(QKeyEvent * keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_W :{
            //printf("BUTTON_W!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 1;    guicmd.desc = GUICommand::Up;
            //Logic::getNextCommandFromGUI(guicmd);
            //Команде gui: это тестовый пример того, как должны посылаться команды в логику
            //сделайте так же и для других клавиш
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);
            //===================================
            break;
        };

        case Qt::Key_A :{
            //printf("BUTTON_A!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 2;    guicmd.desc = GUICommand::Left;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_S :{
            //printf("BUTTON_S!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 3;    guicmd.desc = GUICommand::Down;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_D :{
            //printf("BUTTON_D!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 4;    guicmd.desc = GUICommand::Right;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_Space :{
            //printf("BUTTON_FIRE_IN_THE_HOLE!!!\n");
            guicmd.player_id = 1;   guicmd.cmd_code = 10;    guicmd.desc = GUICommand::Atack;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_Left :{
            //printf("BUTTON_LEFT!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 5;    guicmd.desc = GUICommand::Left;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_Up :{
            //printf("BUTTON_UP!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 6;    guicmd.desc = GUICommand::Up;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_Right :{
            //printf("BUTTON_RIGHT!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 7;    guicmd.desc = GUICommand::Right;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_Down :{
            //printf("BUTTON_DOWN!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 8;    guicmd.desc = GUICommand::Down;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        case Qt::Key_0 :{
            //printf("FIRE_IN_THE_HOLE!!!\n");
            guicmd.player_id = 2;   guicmd.cmd_code = 9;    guicmd.desc = GUICommand::Atack;
            //Logic::getNextCommandFromGUI(guicmd);
            CommandFromGUI testCommand;
            testCommand.setPlayerNumber(guicmd.player_id);
            testCommand.setFromGUICommand(guicmd.desc);
            LogicModule->setNextCommandFromGUI(testCommand);

            break;
        };

        update();
    }

}

// Кнопка "Start Game"
void TanksGUI::on_pushButton_clicked()
{
   // printf("BUTTON_START!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 10;    guicmd.desc = GUICommand::START;
    bool game_flag = 0;
    //Запуск таймера
    qDebug() << "BUTTON_START";
    // Создание таймера
    game_timer = new QTimer(this);
    connect(game_timer, SIGNAL(timeout()), this, SLOT(timer_event()));
    game_timer->start(10);
    if (game_flag == 1)
    {
        CommandFromGUI testCommand;
        testCommand.setPlayerNumber(guicmd.player_id);
        testCommand.setFromGUICommand(guicmd.desc);
        LogicModule->setNextCommandFromGUI(testCommand);
    }

}

// Кнопка "Exit Game"
void TanksGUI::on_pushButton_2_clicked()
{
    //printf("BUTTON_EXIT!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 11;    guicmd.desc = GUICommand::EXIT;

    CommandFromGUI testCommand;
    testCommand.setPlayerNumber(guicmd.player_id);
    testCommand.setFromGUICommand(guicmd.desc);
    LogicModule->setNextCommandFromGUI(testCommand);

}

// Кнопка "About"
void TanksGUI::on_pushButton_3_clicked()
{
    //printf("BUTTON_ABOUT!!!\n");
    guicmd.player_id = 0;   guicmd.cmd_code = 12;    guicmd.desc = GUICommand::ABOUT;
    CommandFromGUI testCommand;
    testCommand.setPlayerNumber(guicmd.player_id);
    testCommand.setFromGUICommand(guicmd.desc);
    LogicModule->setNextCommandFromGUI(testCommand);

}

void TanksGUI::on_actionDownload_Map_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*)"));
   //Отправить событие Карте!
   printf("CANT TOUCH THIS!!!\n");
}

// Обработка событий по основному игровому таймеру
void TanksGUI::timer_event() {
    qDebug() << "Timer event";
    LogicModule->run();
}
