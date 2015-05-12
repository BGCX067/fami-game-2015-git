#include "interface.h"

using namespace player;

BULLET::BULLET(t_player_number id, bullet_type bType, PositionCoord startPosition, Direction startDirection)
{
	player_id = id;
	bullet_type_id = bType;
	bullet_pos = startPosition;
	bullet_direction = startDirection;
}

t_player_number BULLET::getPlayerId()
{
	return player_id;
}

bullet_type BULLET::getBulletType()
{
	return bullet_type_id;
}

PositionCoord BULLET::getCurrentPosition()
{
	return bullet_pos;
}

Direction BULLET::getDirection()
{
	return bullet_direction;
}

hit_points BULLET::getDamage()
{
    return tmap::TMap::getBulletType(bullet_type_id).damage;
}

unsigned int BULLET::getDmgSize()
{
    return tmap::TMap::getBulletType(bullet_type_id).damage_size;
}

unsigned int BULLET::getVelocity()
{
    return tmap::TMap::getBulletType(bullet_type_id).velocity;
}

void BULLET::Move()
{
    int v = getVelocity();
	switch (bullet_direction)
	{
	case Direction::Left:
	{
        bullet_pos = PositionCoord(bullet_pos.x - v, bullet_pos.y);
		break;
	}
	case Direction::Right:
	{
        bullet_pos = PositionCoord(bullet_pos.x + v, bullet_pos.y);
		break;
	}
	case Direction::Up:
	{
        bullet_pos = PositionCoord(bullet_pos.x, bullet_pos.y + v);
		break;
	}
	case Direction::Down:
	{
        bullet_pos = PositionCoord(bullet_pos.x, bullet_pos.y - v);
		break;
	}
	}
}
