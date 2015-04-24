#include "interface.h"

using namespace player;

PLAYER::PLAYER(t_player_number id, PositionCoord startPosition, Direction startDirection, hit_points startHP, bullet_type bType)
{
    player_id = id;
    player_pos.x = startPosition.x;
    player_pos.y = startPosition.y;
    player_direction = startDirection;
    hp = startHP;
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

bullet_type PLAYER::getBulletType()
{
	return bullet_type_id;
}

unsigned int PLAYER::getSize()
{
	auto itMap = player_types_database.find(player_type_id);
	return itMap->second.tank_size;
}

bool PLAYER::RecieveDamage(bullet_type bType)
{
	auto itMap = bullet_types_database.find(bType);
	auto dmg = itMap->second.damage;
    hp -= dmg;
    if (hp <= 0) return 1;
    else return 0;
}

void PLAYER::Move(tmap::TMap* map_)
{
    PositionCoord newPosition, checkPosition;
    Direction d;
	auto itMap = player_types_database.find(player_type_id);
	auto size = itMap->second.tank_size;
    int s = (size - 1) / 2;

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
    case Direction::Down:
        {
            checkPosition = PositionCoord(player_pos.x, player_pos.y - s - 1);
            newPosition = PositionCoord(player_pos.x, player_pos.y - 1);
            d = Direction::Right;
            break;
        }
    case Direction::Up:
        {
            checkPosition = PositionCoord(player_pos.x, player_pos.y +  s + 1);
            newPosition = PositionCoord(player_pos.x, player_pos.y + 1);
            d = Direction::Right;
            break;
        }
    }

    if (map_->isEmptyRow(size, checkPosition, d))
    {
        player_pos.x = newPosition.x;
        player_pos.y = newPosition.y;
    }
}

void PLAYER::Turn(Direction direction)
{
    player_direction = direction;
}

shared_ptr<BULLET> PLAYER::Attack()
{
	auto itMap = player_types_database.find(player_type_id);
	auto size = itMap->second.tank_size;
    PositionCoord start_pos;
    int s = (size - 1) / 2;

    switch (player_direction)
    {
    case Direction::Left:
    {
        start_pos = PositionCoord(start_pos.x - s - 1, start_pos.y);
        break;
    }
    case Direction::Right:
    {
        start_pos = PositionCoord(start_pos.x + s + 1, start_pos.y);
        break;
    }
    case Direction::Up:
    {
        start_pos = PositionCoord(start_pos.x, start_pos.y + s + 1);
        break;
    }
    case Direction::Down:
    {
        start_pos = PositionCoord(start_pos.x, start_pos.y - s - 1);
        break;
    }
    }
    return make_shared<BULLET>(player_id, bullet_type_id, start_pos, player_direction);
}
