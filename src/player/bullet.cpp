#include "interface.h"

using namespace player;

BULLET::BULLET(t_player_number id, PositionCoord startPosition, Direction startDirection, hit_points dmg)
{
	player_id = id;
	bullet_pos = startPosition;
	bullet_direction = startDirection;
	damage = dmg;
}

t_player_number BULLET::getPlayerId()
{
	return player_id;
}

PositionCoord BULLET::getCurrentPosition()
{
	return bullet_pos;
}

hit_points BULLET::getDamage()
{
	return damage;
}

void BULLET::Move()
{
	switch (bullet_direction)
	{
	case Direction::Left:
	{
		bullet_pos = PositionCoord(bullet_pos.x - 1, bullet_pos.y);
		break;
	}
	case Direction::Right:
	{
		bullet_pos = PositionCoord(bullet_pos.x + 1, bullet_pos.y);
		break;
	}
	case Direction::Up:
	{
		bullet_pos = PositionCoord(bullet_pos.x, bullet_pos.y + 1);
		break;
	}
	case Direction::Down:
	{
		bullet_pos = PositionCoord(bullet_pos.x, bullet_pos.y - 1);
		break;
	}
	}
}