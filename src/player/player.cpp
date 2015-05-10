#include "interface.h"
#include <QDebug>

using namespace player;

PLAYER::PLAYER(t_player_number id, PositionCoord startPosition, Direction startDirection, player_type pType, bullet_type bType)
{
    player_id = id;
    player_pos.x = startPosition.x;
    player_pos.y = startPosition.y;
    player_direction = startDirection;
    hp = tmap::TMap::getPlayerType(pType).default_hp;
    player_type_id = pType;
    bullet_type_id = bType;
}

t_player_number PLAYER::getPlayerId()
{
    return player_id;
}

PositionCoord PLAYER::getCurrentPosition()
{
    return player_pos;
}

Direction PLAYER::getCurrentDirection()
{
    return player_direction;
}

hit_points PLAYER::getCurrentHitPoints()
{
    return hp;
}

player_type PLAYER::getPlayerType()
{
    return player_type_id;
}

bullet_type PLAYER::getBulletType()
{
    return bullet_type_id;
}

unsigned int PLAYER::getSize()
{
    return tmap::TMap::getPlayerType(player_type_id).tank_size;
}

unsigned int PLAYER::getVelocity()
{
    return tmap::TMap::getPlayerType(player_type_id).velocity;
}

bool PLAYER::RecieveDamage(hit_points damage)
{
    hp -= damage;
    if (hp <= 0) return 1;
    else return 0;
}

void PLAYER::setPlayerType(player_type pt){
    this->player_type_id = pt;
}

void PLAYER::setCurrentDirection(Direction dir) {
    this->player_direction = dir;
}

void PLAYER::Move(tmap::TMap* map_)
{
    qDebug() << "PLAYER: move, id = " << player_id << endl;
    PositionCoord newPosition, checkPosition;
    Direction d;
    auto size = tmap::TMap::getPlayerType(player_type_id).tank_size;
    int s = (size - 1) / 2;

    qDebug() << "PLAYER: tank size = " << size << endl;

    switch (player_direction)
    {
    case Direction::Left:
        {
            checkPosition = PositionCoord(player_pos.x - s - 1, player_pos.y);
            newPosition = PositionCoord(player_pos.x - 1, player_pos.y);
            d = Direction::Up;
            break;
        }
    case Direction::Right:
        {

            checkPosition = PositionCoord(player_pos.x + s + 1, player_pos.y);
            newPosition = PositionCoord(player_pos.x + 1, player_pos.y);
            d = Direction::Up;
            break;
        }
    case Direction::Up:
        {
            checkPosition = PositionCoord(player_pos.x, player_pos.y + s + 1);
            newPosition = PositionCoord(player_pos.x, player_pos.y + 1);
            d = Direction::Right;
            break;
        }
    case Direction::Down:
        {
            checkPosition = PositionCoord(player_pos.x, player_pos.y - s - 1);
            newPosition = PositionCoord(player_pos.x, player_pos.y - 1);
            d = Direction::Right;
            break;
        }
    }

    qDebug() << "PLAYER: cur position " << player_pos.x << " " << player_pos.y << endl;
    qDebug() << "PLAYER: new position " << newPosition.x << " " << newPosition.y << endl;

    if (map_->isEmptyRow(size, checkPosition, d))
    {
        map_->movePlayer(player_pos, newPosition);
        qDebug() << "PLAYER: new position valide "<< endl;
        player_pos.x = newPosition.x;
        player_pos.y = newPosition.y;


    }
    else
         qDebug() << "PLAYER: new position invalide "<< endl;

    qDebug() << "PLAYER: MOVE end\n";

}

void PLAYER::Turn(Direction direction)
{
    player_direction = direction;
}

shared_ptr<BULLET> PLAYER::Attack()
{
    qDebug() << "PLAYER: Attack started player coords: " << player_pos.x << " " << player_pos.y << endl;
    auto size = tmap::TMap::getPlayerType(player_type_id).tank_size;
    PositionCoord start_pos;
    int s = ((int)size - 1) / 2;

    switch (player_direction)
    {
    case Direction::Left:
    {
        start_pos = PositionCoord(player_pos.x - s - 1, player_pos.y);
        break;
    }
    case Direction::Right:
    {
        start_pos = PositionCoord(player_pos.x + s + 1, player_pos.y);
        break;
    }
    case Direction::Up:
    {
        start_pos = PositionCoord(player_pos.x, player_pos.y + s + 1);
        break;
    }
    case Direction::Down:
    {
        start_pos = PositionCoord(player_pos.x, player_pos.y - s - 1);
        break;
    }
    }
    qDebug() << "PLAYER: bullet position " << start_pos.x << " " << start_pos.y << endl;
    return make_shared<BULLET>(player_id, bullet_type_id, start_pos, player_direction);
}
