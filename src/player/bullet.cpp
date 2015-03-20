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

void BULLET::Move(CommandMove command)
{

}