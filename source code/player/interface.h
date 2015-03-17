#pragma once

#include "..\interface.h"
using namespace map;

/*
Интерфейсы взаимодействия с системой управления игроком (PLAYER).
*/

namespace player
{
	class PLAYER
	{
		PositionCoord player_pos;
		Direction player_direction;
		hit_points hp;
		hit_points damage;

	public:
		PLAYER(PositionCoord startPosition, unsigned int startHP)
		{
			player_pos.x = startPosition.x;
			player_pos.y = startPosition.y;
			hp = startHP;
		}

		PositionCoord getCurrentPosition()
		{
			return player_pos;
		}

		Direction getCurrentDirection()
		{
			return player_direction;
		}
	
		/*hit_points getCurrentHitPoints()
		{
			return hp;
		}  возможно лишнее*/

		//Танк получает урон. 0 - hp еще осталось, 1 - нет     (вместо проверки hp на равенство 0)
		bool RecieveDamage(hit_points dmg)
		{
			hp -= dmg;
			if (hp <= 0) return 1;
			else return 0;
		}

		/*bool Move(CommandMove command, MAP* map);*/

		void Turn(CommandWithDirection command)
		{
			player_direction = command.getCommandDirection();
		}

		//BULLET* Attack(CommandAttack command);
	};


	class BULLET
	{
		t_player_number player_id;
		PositionCoord bullet_pos;
		Direction bullet_direction;
		hit_points damage;

	public:
		BULLET(t_player_number id, PositionCoord startPosition, Direction startDirection, hit_points dmg)
		{
			player_id = id;
			bullet_pos = startPosition;
			bullet_direction = startDirection;
			damage = dmg;
		}

		t_player_number getPlayerId()
		{
			return player_id;
		}

		PositionCoord getCurrentPosition()
		{
			return bullet_pos;
		}

		hit_points getDamage()
		{
			return damage;
		}

		/*Move(CommandMove command);*/

		//~BULLET();
	};
};