#include "interface.h"

using namespace player;
using namespace map;

PLAYER::PLAYER(PositionCoord startPosition, Direction startDirection, hit_points startHP, hit_points startDamage)
{
	player_pos.x = startPosition.x;
	player_pos.y = startPosition.y;
	player_direction = startDirection;
	hp = startHP;
	damage = startDamage;
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

bool PLAYER::RecieveDamage(hit_points dmg)
{
	hp -= dmg;
	if (hp <= 0) return 1;
	else return 0;
}

void PLAYER::Turn(CommandWithDirection command)
{
	player_direction = command.getCommandDirection();
}