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
}

void Logic::run()
{
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
                    if(pWall->getType() == 1) //кирпичная стенка
                        //хана стенке
                        _currentMap->deleteWall(intermediatePos);
                }
                //или кранты танку?
                shared_ptr<player::PLAYER> pPlayer = _currentMap->getPlayer(intermediatePos);
                if(pPlayer) {
                    // По танку вдарила болванка, Прощай родимый экипаж.
                    if(pPlayer->RecieveDamage(bul->getDamage()) == 1)
                        _currentMap->deletePlayer(intermediatePos);
                }
                _currentMap->deleteBullet(pc);
                // снаряд взорвался, дальше считать бессмысленно
                break;
            }
        }
    });

    // Проверка состояния игры
    bool player1Dead = true, player2Dead = true;
    _currentMap->forEachPlayer([&](PositionCoord, shared_ptr<player::PLAYER> pPlayer)->void {
        if(pPlayer->getPlayerId() == 1) player1Dead = false;
        if(pPlayer->getPlayerId() == 2) player2Dead = false;
    });
    if(player1Dead)
        if(player2Dead)
            _gameStatus = LOGICCommand::GAME_OVER;
        else
            _gameStatus = LOGICCommand::PLAYER_2_WIN;
    else
        if(player2Dead)
            _gameStatus = LOGICCommand::PLAYER_1_WIN;

    //хранит флаг наличия стрельбы и напрвления стрельбы
    array<pair<bool, set<Direction> >, 2> playerFire; //не оптимально, надо будет, исправим
    // Обработка очереди команд
    while(!_commandsFromGUI.empty()) {

        CommandFromGUI currCommand = _commandsFromGUI.back();
        _commandsFromGUI.pop();
        size_t playerNumber = currCommand.getPlayerNumber();

        auto GUICommandMove = [&](Direction dir)->void {
            _currentMap->forEachPlayer([&](PositionCoord, shared_ptr<player::PLAYER> pPlayer)->void {
                if(pPlayer->getPlayerId() == playerNumber) {
                    if(pPlayer->getCurrentDirection() == dir) {
                        // не стреляли мы в ту сторону
                        if(playerFire[playerNumber].second.find(dir) == playerFire[playerNumber].second.end())
                            pPlayer->Move(_currentMap.get());
                    }
                    else
                        pPlayer->Turn(dir);
                }
            });
        };

        switch(currCommand.getGUICommand()){

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
            _currentMap->forEachPlayer([&](PositionCoord, shared_ptr<player::PLAYER> pPlayer)->void {
                if(pPlayer->getPlayerId() == playerNumber) {
                    //Стреляли… Саид(c)
                    auto newBullet = pPlayer->Attack();
                    _currentMap->createBullet(newBullet->getCurrentPosition(),newBullet);

                    //теперь мы знаем куда не надо двигаться из-за отдачи
                    playerFire[playerNumber].first = true;
                    playerFire[playerNumber].second.insert(pPlayer->getCurrentDirection());
                }
            });
            break;
        default:
            break;
        }
    }
}
