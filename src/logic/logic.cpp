#include "logic/interface.h"
#include "player/interface.h"

using namespace logic;

std::string Logic::getStatusForGUI()
{
    /// @public
    /// return std::string
    ///     "GAME_OVER"
    ///     "GAME_CONTINUE"
    ///     "PLAYER_%INTEGER_WIN" %INTEGER is unsigned natural number
    ///     "GAME_PAUSE"
    return gameStatus;
}

std::string Logic::getNextCommandFromGUI()
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
    if(!commandsFromGUI.empty())
        return commandsFromGUI.pop();
    return std::string("NONE"); //комманд нет
}

void Logic::run()
{
    //посмотрим что нам дало gui
    std::string guiCoomand = getNextCommandFromGUI();
    switch(guiCoomand){
    case "NONE":
        break;
    case "START":
        break;
    case "PAUSE":
        break;
    case "CONTINUE":
        break;
    case "PLAYER_1_UP":
        //example
        PositionCoord pos1 = player1.getCurrentPosition();
        pos1.y += 1;
        if(player1.getCurrentDirection() != UP)
            player1.Turn(UP);
        if(getBlockFromMap(pos1).isEmpty())
            player1.Move(pos1);
        break;
    case "PLAYER_1_SHOOT":
        PositionCoord pos1 = player1.getCurrentPosition();
        Direction direct = player1.getCurrentDirection();
        map.insertBullet(player::BULLET(player1.getPlayerId(), pos1, direct, 1));
        break;
    default:
        continue;
    }

    //обработаем разрушения от снарядов
    for(auto bullet = map.Bullets.begin(); bullet != map.Bullets.end(); ++bullet) {
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
    }

}
