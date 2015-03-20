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

void PLAYER::Move(CommandMove command, MAP* map)
{

}

void PLAYER::Turn(CommandWithDirection command)
{
	player_direction = command.getCommandDirection();
}

shared_ptr<BULLET> PLAYER::Attack(CommandAttack command)
{
	
}