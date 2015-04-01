#include "interface.h"

using namespace player;
using namespace map;

PLAYER::PLAYER(t_player_number id, PositionCoord startPosition, Direction startDirection, hit_points startHP, hit_points startDamage, unsigned int size_)
{
	player_id = id;
	player_pos.x = startPosition.x;
	player_pos.y = startPosition.y;
	player_direction = startDirection;
	hp = startHP;
	damage = startDamage;
	size = size_;
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

unsigned int PLAYER::getSize()
{
	return size;
}

bool PLAYER::RecieveDamage(hit_points dmg)
{
	hp -= dmg;
	if (hp <= 0) return 1;
	else return 0;
}

void PLAYER::Move(MAP* map)
{
/*	PositionCoord newPosition, np0, np1, np2;
	int s = (size - 1) / 2;

	switch (player_direction)
	{
	case Direction::Left:
		{
			np0.x = player_pos.x - s - 1;
			np0.y = player_pos.y - 1;

			np1.x = np0.x;
			np1.y = np0.y + 1;

			np2.x = np1.x;
			np2.y = np1.y + 1;

			newPosition = PositionCoord(player_pos.x - 1, player_pos.y);

			break;
		}
	case Direction::Right:
		{
			np0.x = player_pos.x + s + 1;
			np0.y = player_pos.y - 1;

			np1.x = np0.x;
			np1.y = np0.y + 1;

			np2.x = np1.x;
			np2.y = np1.y + 1;

			newPosition = PositionCoord(player_pos.x + 1, player_pos.y);

			break;
		}
	case Direction::Down:
		{
			np0.x = player_pos.x - 1;
			np0.y = player_pos.y - s - 1;

			np1.x = np0.x + 1;
			np1.y = np0.y;

			np2.x = np1.x + 1;
			np2.y = np1.y;

			newPosition = PositionCoord(player_pos.x, player_pos.y - 1);

			break;
		}
	case Direction::Up:
		{
			np0.x = player_pos.x - 1;
			np0.y = player_pos.y + s + 1;

			np1.x = np0.x + 1;
			np1.y = np0.y;

			np2.x = np1.x + 1;
			np2.y = np1.y;

			newPosition = PositionCoord(player_pos.x, player_pos.y + 1);

			break;
		}
	}

	if (map->IsEmpty(np0) && map->IsEmpty(np1) && map->IsEmpty(np2))
	{
		player_pos.x = newPosition.x;
		player_pos.y = newPosition.y;
	}*/
	//IzEmptyRow()
}

void PLAYER::Turn(Direction direction)
{
	player_direction = direction;
}

shared_ptr<BULLET> PLAYER::Attack()
{
	return make_shared<BULLET>(new BULLET(player_id, player_pos/*+- (size-1)/2 */, player_direction, damage));
}