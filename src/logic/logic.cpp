#include "../logic/interface.h"
#include "../player/interface.h"

using namespace logic;

std::string Logic::getStatusForGUI()
{
    /// @public
    /// return std::string
    ///     "GAME_OVER"
    ///     "GAME_CONTINUE"
    ///     "PLAYER_%INTEGER_WIN" %INTEGER is unsigned natural number
    ///     "GAME_PAUSE"
    return _gameStatus;
}

void Logic::setNextCommandFromGUI(CommandFromGUI g_commandFromGUI)
{
    /// @private
    /// return std::string
    ///     "PLAYER_1_UP"
    ///     "PLAYER_2_UP"
    ///     "PLAYER_1_DOWN"
    ///     "PLAYER_2_DOWN"
    ///     "PLAYER_1_LEFT"
    ///     "PLAYER_2_LEFT"
    ///     "PLAYER_1_RIGHT"
    ///     "PLAYER_2_RIGHT"
    ///     "PLAYER_1_SHOOT"
    ///     "PLAYER_2_SHOOT"
    ///     "PAUSE"
    ///     "START" only once in round
    ///     "CONTINUE" after pause

    //тут возможно нужен будет мьютекс
    g_commandFromGUI.getGUICommand();
    if(!_commandsFromGUI.empty())
        _commandsFromGUI.push(g_commandFromGUI);
}

void Logic::run()
{
    //посмотрим что нам дало gui
    shared_ptr<CommandFromGUI> guiCoomand(&(_commandsFromGUI.back()));
    _commandsFromGUI.pop();
    switch(guiCoomand->getGUICommand()){
    case GUICommand::START:
        break;
    case GUICommand::PAUSE:
        break;
    case GUICommand::CONTINUE:
        break;
    case GUICommand::Up:
        //example
        /*PositionCoord pos1 = player1.getCurrentPosition();
        pos1.y += 1;
        if(player1.getCurrentDirection() != UP)
            player1.Turn(UP);
        if(getBlockFromMap(pos1).isEmpty())
            player1.Move(pos1);*/
        break;
    case GUICommand::Atack:
        /*PositionCoord pos1 = player1.getCurrentPosition();
        Direction direct = player1.getCurrentDirection();
        map.insertBullet(player::BULLET(player1.getPlayerId(), pos1, direct, 1));
        */
        break;
    default:
        break;
    }

    //обработаем разрушения от снарядов
    /*_map::MapExample currMap;
    for(auto bullet = currMap.Bullets.begin(); bullet != currMap.Bullets.end(); ++bullet) {
        PositionCoord bulletDemandPosition = bullet.getCurrentPosition(); //позиция на которой окажется снаряд
        switch(bullet.getCurrentDirection()) {
        case UP:
            bulletDemandPosition.y += 1;
            break;
        case DOWN:
            bulletDemandPosition.y -= 1;
            break;
        case LEFT:
            bulletDemandPosition.x -= 1;
            break;
        case RIGHT:
            bulletDemandPosition.x += 1;
            break;
        }
        switch(getBlockFromMap(bulletDemandPosition)) {
        case WALL: //стеночка
            map.clear(bulletDemandPosition);
            map.Bullets.erase(bullet);
            break;
        case PLAYER: //игрок
            map.Bullets.erase(bullet);

            if(map.Players.getPlayerFromPosition(bulletDemandPosition).RecieveDamage(bullet.getDamage())) {
                map.Players.getPlayerFromPosition(bulletDemandPosition).kill();
                gameStatus = std::string("GAME_OVER");
            }
        case CLEAR: //пустая клетка
            bullet.Move(bulletDemandPosition);
            break;
        }
        case ENDOFMAP: //конец карты
            map.Bullets.erase(bullet);
            break;
    }*/

}
