#include "../logic/interface.h"
#include "../player/interface.h"
#include <array>
#include <set>
#include <QDebug>


using namespace logic;

Logic::Logic(shared_ptr<tmap::TMap> map)
{
    if(!map)
        throw QString("Error: Bad MAP descriptor");
    _currentMap = map;
    _gameStatus = LOGICCommand::GAME_CONTINUE;
}

LOGICCommand Logic::getStatusForGUI()
{
    return _gameStatus;
}

void Logic::setNextCommandFromGUI(CommandFromGUI g_commandFromGUI)
{
    _commandsFromGUI.push(g_commandFromGUI);
    qDebug() << "LOGIC: Put command, command count " <<_commandsFromGUI.size() << endl;
}

void Logic::run()
{
    if(!_logicRun.try_lock())
        return;
    // Просчет разрушений с прошлого шага
    _currentMap->forEachBullet([&](PositionCoord pc, shared_ptr<player::BULLET> bul)->void {
        PositionCoord prevPos = bul->getCurrentPosition(); // позиция на прошлом шаге
        bul->Move();
        PositionCoord curPos = bul->getCurrentPosition(); //возможная текущая позиция
        size_t traceLength = 0; //длинна пути
        Direction bulDirect = bul->getDirection();
        //ищем длину пути
        switch (bulDirect) {
        case Direction::Up:
            traceLength = curPos.y - prevPos.y;
            break;
        case Direction::Down:
            traceLength = prevPos.y - curPos.y;
            break;
        case Direction::Right:
            traceLength = curPos.x - prevPos.x;
            break;
        case Direction::Left:
            traceLength = prevPos.x - curPos.x;
            break;
        }
        // пуля - дура, ищет жертву на своем пути
        PositionCoord intermediatePos = prevPos;
        for(size_t i = 0; i < traceLength; i++) {
            switch (bulDirect) {
            case Direction::Up:
                intermediatePos.y += static_cast<int>(i);
                break;
            case Direction::Down:
                intermediatePos.y -= static_cast<int>(i);
                break;
            case Direction::Right:
                intermediatePos.x += static_cast<int>(i);
                break;
            case Direction::Left:
                intermediatePos.x -= static_cast<int>(i);
                break;
            }
            if(!_currentMap->isEmpty(intermediatePos)) {
                //может вылет за карту
                if(intermediatePos.x < 1 || intermediatePos.x > _currentMap->getSizeX()
                        || intermediatePos.y < 1 || intermediatePos.y > _currentMap->getSizeY()) {
                    _currentMap->deleteBullet(pc);
                    i = traceLength;
                    break;
                }

                //теперь смотрим кто жертва
                //может это стенка ?!
                shared_ptr<Wall> pWall = _currentMap->getWall(intermediatePos);
                if(pWall) {
                    if(pWall->getType() == 0) { //кирпичная стенка
                        //хана стенке
                        _currentMap->deleteWall(intermediatePos);
                        //и возможно окресностям
                        PositionCoord add1(intermediatePos), add2(intermediatePos); //дополнительный урон стенке
                        if(bulDirect == Direction::Left || bulDirect == Direction::Right) {
                            add1.y ++;
                            add2.y --;
                        }
                        else { //Direction::Up или Direction::Down
                            add1.x ++;
                            add2.x --;
                        }
                        auto addWall1 = _currentMap->getWall(add1);
                        auto addWall2 = _currentMap->getWall(add2);
                        if(addWall1 && addWall1->getType() == 0) _currentMap->deleteWall(add1);
                        if(addWall2 && addWall2->getType() == 0) _currentMap->deleteWall(add2);
                    }

                }
                //или кранты танку?
                _currentMap->forEachPlayer([&](PositionCoord pc, shared_ptr<player::PLAYER> pPlayer) {
                    int psize = pPlayer->getSize();
                    int k = (psize - 1) / 2;
                    for(int i = pc.x - k; i <= pc.x + k; i++) {
                        for(int j = pc.y - k; j <= pc.y + k; j++) {
                            PositionCoord curCoord(i, j);
                            if(curCoord == intermediatePos) {
                                qDebug("LOGIC: Damage to tank #%d. Current hp: %d", pPlayer->getPlayerId(), pPlayer->getCurrentHitPoints());
                                // По танку вдарила болванка, Прощай родимый экипаж.
                                if(pPlayer->RecieveDamage(bul->getDamage()) == 1)
                                    _currentMap->deletePlayer(pc);
                            }
                        }
                    }
                });
                _currentMap->deleteBullet(pc);
                // снаряд взорвался, дальше считать бессмысленно
                break;
            }
        }
    });

    // Проверка состояния игры
    auto player1Alive = _currentMap->getPlayer(1);
    auto player2Alive = _currentMap->getPlayer(2);
    if(!player1Alive || !player2Alive) {
        if(!player1Alive) {
            if(!player2Alive) {
                qDebug("LOGICCommand::GAME_OVER");
                _gameStatus = LOGICCommand::GAME_OVER;
            }
            else {
                qDebug("LOGICCommand::PLAYER_2_WIN");
                _gameStatus = LOGICCommand::PLAYER_2_WIN;
            }
        }
        else {
            qDebug("LOGICCommand::PLAYER_1_WIN");
            _gameStatus = LOGICCommand::PLAYER_1_WIN;
        }
        // игра завершилас, нет смысла продолжать
        return;
    }

    //хранит флаг наличия стрельбы и напрвления стрельбы
    array<pair<bool, set<Direction> >, 2> playerFire; //не оптимально, надо будет, исправим
    // Обработка очереди команд

    if (_commandsFromGUI.size() > 0)
        qDebug() << "LOGIC: commands count: " << _commandsFromGUI.size() << endl;

    // обрабатывем команды, доступные на текущих квант времени
    size_t currCommandCount = _commandsFromGUI.size();
    while(currCommandCount > 0) {
        currCommandCount --;

        CommandFromGUI currCommand = _commandsFromGUI.front();
        _commandsFromGUI.pop();
        size_t playerNumber = currCommand.getPlayerNumber();
        qDebug() << "LOGIC: command player id = " << playerNumber << endl;

        auto GUICommandMove = [&](Direction dir)->void {
            qDebug() << "LOGIC: Command move, procces players\n";

            auto pPlayer = _currentMap->getPlayer(playerNumber);
            if(pPlayer->getCurrentDirection() == dir) {
                // не стреляли мы в ту сторону
                qDebug() << "LOGIC: Move command\n";
                if(playerFire[playerNumber-1].second.find(dir) == playerFire[playerNumber-1].second.end()) {
                    pPlayer->Move(_currentMap.get());
                    qDebug() << "LOGIC: MOVE end\n";
                }
            }
            else {
                qDebug() << "LOGIC:\tTurn command\n";
                pPlayer->Turn(dir);
            }

        };

        switch(currCommand.getGUICommand()) {

        case GUICommand::Up:
            GUICommandMove(Direction::Up);
            break;
        case GUICommand::Down:
            GUICommandMove(Direction::Down);
            break;
        case GUICommand::Left:
            GUICommandMove(Direction::Left);
            break;
        case GUICommand::Right:
            GUICommandMove(Direction::Right);
            break;
        case GUICommand::Atack:
            qDebug() << "LOGIC: Attack command\n";
            _currentMap->forEachPlayer([&](PositionCoord, shared_ptr<player::PLAYER> pPlayer)->void {
                if(pPlayer->getPlayerId() == playerNumber) {
                    //Стреляли… Саид(c)
                    auto newBullet = pPlayer->Attack();
                    _currentMap->createBullet(newBullet->getCurrentPosition(),newBullet);

                    //теперь мы знаем куда не надо двигаться из-за отдачи
                    playerFire[playerNumber - 1].first = true;
                    playerFire[playerNumber - 1].second.insert(pPlayer->getCurrentDirection());
                }
            });
            break;
        default:
            break;
        }
    }
    _logicRun.unlock();
}
