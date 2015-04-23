#include "../logic/interface.h"
#include "../player/interface.h"
#include <QDebug>


using namespace logic;

Logic::Logic(shared_ptr<tmap::TMap> map)
{
    _currentMap = map;
    _gameStatus = LOGICCommand::GAME_CONTINUE;
}

Logic::~Logic()
{

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
    _currentMap->forEachBullet([&](PositionCoord pc, shared_ptr<Bullet> bul1)->void {
        player::BULLET bul(1, pc, Direction::Down, 100, 100, 1.0);// временно. bul = bul1
        PositionCoord prevPos = bul.getCurrentPosition(); // позиция на прошлом шаге
        bul.Move();
        PositionCoord curPos = bul.getCurrentPosition(); //возможная текущая позиция
        size_t traceLength = 0; //длинна пути
        Direction bulDirect = bul.getDirection();
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
                intermediatePos.y += i;
                break;
            case Direction::Down:
                intermediatePos.y -= i;
                break;
            case Direction::Right:
                intermediatePos.x += i;
                break;
            case Direction::Left:
                intermediatePos.x -= i;
                break;
            }
            if(!_currentMap->isEmpty(intermediatePos)) {
                //теперь смотрим кто жертва
                _currentMap->forEachWall([&](PositionCoord pcWall, shared_ptr<Wall> pWall)->void {
                    //может это стенка ?!
                    if(pcWall == intermediatePos) {
                        //хана стенке
                        _currentMap->deleteWall(pcWall);
                    }
                });
                _currentMap->forEachPlayer([&](PositionCoord pcPlayer, shared_ptr<Player> pPlayer1)->void {
                    //или кранты танку?
                    if(pcPlayer == intermediatePos) {
                        // По танку вдарила болванка, Прощай родимый экипаж.
                        player::PLAYER pPlayer(1, pcPlayer, Direction::Up, 100, 100, 100); //delete
                        if(pPlayer.RecieveDamage(bul.getDamage()) == 1)
                            _currentMap->deletePlayer(pcPlayer);
                    }
                });
                _currentMap->deleteBullet(pc);
                // снаряд взорвался, дальше считать бессмысленно
                break;
            }
        }
    });

    // Проверка состояния игры
    bool player1Dead = true, player2Dead = true;
    _currentMap->forEachPlayer([&](PositionCoord pcPlayer, shared_ptr<Player> pPlayer1)->void {
        player::PLAYER pPlayer(1, pcPlayer, Direction::Up, 100, 100, 100); //delete
        if(pPlayer.getPlayerId() == 1) player1Dead = false;
        if(pPlayer.getPlayerId() == 2) player2Dead = false;
    });
    if(player1Dead)
        if(player2Dead)
            _gameStatus = LOGICCommand::GAME_OVER;
        else
            _gameStatus = LOGICCommand::PLAYER_2_WIN;
    else
        if(player2Dead)
            _gameStatus = LOGICCommand::PLAYER_1_WIN;

    // Обработка очереди команд
    while(_commandsFromGUI.size() > 0) {
        shared_ptr<CommandFromGUI> guiCoomand(&(_commandsFromGUI.back()));
        _commandsFromGUI.pop();
        int playerNumber = guiCoomand->getPlayerNumber();
        switch(guiCoomand->getGUICommand()){
        case GUICommand::Up:
            _currentMap->forEachPlayer([&](PositionCoord pcPlayer, shared_ptr<Player> pPlayer1)->void {
                player::PLAYER pPlayer(1, pcPlayer, Direction::Up, 100, 100, 100); //delete
                if(pPlayer.getPlayerId() == playerNumber) {
                    // Нашли игрока
                    PositionCoord prevPos = pPlayer.getCurrentPosition(); // позиция на прошлом шаге
                    pPlayer.Move(_currentMap.get()); // узнать о методе
                    PositionCoord curPos = pPlayer.getCurrentPosition(); //возможная текущая позиция
                }
            });
            break;
        case GUICommand::Down:
            break;
        case GUICommand::Left:
            break;
        case GUICommand::Right:
            break;
        case GUICommand::Atack:
            _currentMap->forEachPlayer([&](PositionCoord pcPlayer, shared_ptr<Player> pPlayer1)->void {
                player::PLAYER pPlayer(1, pcPlayer, Direction::Up, 100, 100, 100); //delete
                if(pPlayer.getPlayerId() == playerNumber) {
                    //Стреляли… Саид(c)
                    auto newBullet = pPlayer.Attack();
                    //_currentMap->создать пулю
                }
            });
            break;
        default:
            break;
        }
    }

}
