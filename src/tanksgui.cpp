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
    MapModule->loadConfig(DEFAULT_CONFIG_MAP);
    ui->graphicsView->init(MapModule);
    ui->progressBarP1->setStyleSheet("QProgressBar {background-color: #ccc; color: #fff; border-radius: 5px; text-align: middle; } QProgressBar::chunk {color: #fff; background-color: blue; border-radius: 5px;}");
    ui->progressBarP2->setStyleSheet("QProgressBar {background-color: #ccc; color: #fff; border-radius: 5px; text-align: middle; } QProgressBar::chunk {color: #fff; background-color: red; border-radius: 5px;}");

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

void TanksGUI::sendCommand(int player_id, GUICommand desc)
{
    CommandFromGUI testCommand;
    testCommand.setPlayerNumber(player_id);
    testCommand.setFromGUICommand(desc);
    LogicModule->setNextCommandFromGUI(testCommand);
}

void TanksGUI::newStatus()
{
    LOGICCommand new_status = LogicModule->getStatusForGUI();
    switch(new_status)
    {//enum class LOGICCommand {GAME_CONTINUE, GAME_OVER, PLAYER_1_WIN, PLAYER_2_WIN};
        case LOGICCommand::GAME_CONTINUE:{break;};
        case LOGICCommand::GAME_OVER:
        {
            logic_flag = 0;
            game_timer->stop();
            printf("TIMER IS DEAD\n");
            QMessageBox::about(this, " ", "GAME OVER!");
            break;
        };
        case LOGICCommand::PLAYER_1_WIN:
        {
            logic_flag = 0;
            ui->progressBarP2->setValue(0);
            game_timer->stop();
            printf("TIMER IS DEAD\n");
            QMessageBox::about(this, "CONGRATULATIONS!", "PLAYER 1 WINS!");
            break;
        };
        case LOGICCommand::PLAYER_2_WIN:
        {
            logic_flag = 0;
            ui->progressBarP2->setValue(0);
            game_timer->stop();
            printf("TIMER IS DEAD\n");
            QMessageBox::about(this, "CONGRATULATIONS!", "PLAYER 2 WINS!");
            break;
        };
    }
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
                sendCommand(1, GUICommand::Up);
                break;
            };

            case Qt::Key_A :{
                //printf("BUTTON_A!!!\n");
                sendCommand(1, GUICommand::Left);
                break;
            };

            case Qt::Key_S :{
                //printf("BUTTON_S!!!\n");
                sendCommand(1, GUICommand::Down);
                break;
            };

            case Qt::Key_D :{
                //printf("BUTTON_D!!!\n");
                sendCommand(1, GUICommand::Right);

                break;
            };

            case Qt::Key_Space :{
                //printf("BUTTON_FIRE_IN_THE_HOLE!!!\n");
                sendCommand(1, GUICommand::Attack);
                break;
            };

            case Qt::Key_Left :{
                //printf("BUTTON_LEFT!!!\n");
                sendCommand(2, GUICommand::Left);
                break;
            };

            case Qt::Key_Up :{
                //printf("BUTTON_UP!!!\n");
                sendCommand(2, GUICommand::Up);
                break;
            };

            case Qt::Key_Right :{
                //printf("BUTTON_RIGHT!!!\n");
                sendCommand(2, GUICommand::Right);
                break;
            };

            case Qt::Key_Down :{
                //printf("BUTTON_DOWN!!!\n");
                sendCommand(2, GUICommand::Down);
                break;
            };

            case Qt::Key_I :{
                //printf("FIRE_IN_THE_HOLE!!!\n");
                sendCommand(2, GUICommand::Attack);
                break;
            };

            case Qt::Key_Escape :
            {
                //printf("NEED A BRAKE, CAP!!!\n");
                sendCommand(0, GUICommand::PAUSE);
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
        sendCommand(0, GUICommand::START);
    }
    setFocus();
}

// Кнопка "Stop Game"
void TanksGUI::on_pushButton_2_clicked()
{
    if(logic_flag == 1)
    {
        printf("BUTTON_STOP!!!\n");
        sendCommand(0, GUICommand::STOP);
        logic_flag = 0;
        game_timer->stop();
        printf("TIMER IS DEAD\n");
    }
}

// Кнопка "About"
void TanksGUI::on_pushButton_3_clicked()
{
    //printf("BUTTON_ABOUT!!!\n");
    QMessageBox::about(this, "About", "Game was created by PMM-41/42 under M. Royak guidance! Thank you!");
}

void TanksGUI::setHPBarValue(int player_id, QProgressBar *bar)
{
    auto player = MapModule->getPlayer(player_id);
    int hp = player->getCurrentHitPoints();
    auto player_type = player->getPlayerType();
    auto max_hp = MapModule->getPlayerType(player_type).default_hp;

    double percent;
    if (hp < max_hp)
        percent = hp * 100 / max_hp;
    else
        percent = 100;
    bar->setValue(percent);
}


// Обработка событий по основному игровому таймеру
void TanksGUI::timer_event()
{
   // qDebug() << "Timer event";
    LogicModule->run();
    ui->graphicsView->render();
    newStatus();
    if(logic_flag != 0)
    {
        setHPBarValue(1, ui->progressBarP1);
        setHPBarValue(2, ui->progressBarP2);
    }

}

void TanksGUI::on_actionDownload_Map_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*)"));
    //Отправить событие Карте!
    //printf("CANT TOUCH THIS!!!\n");

    this->MapModule->loadConfig(fileName.toStdString());
}
