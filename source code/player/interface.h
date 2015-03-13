#pragma once

#include "..\interface.h"

/*
Интерфейсы взаимодействия с системой управления игроком (PLAYER).
*/

namespace player
{
	class PLAYER
	{
		PositionCoord player_pos;
		Direction player_direction;
		//unsigned int player_color;
		hit_points hp;
		hit_points damage;

	public:
		PLAYER(PositionCoord startPosition, /*unsigned int color*/ unsigned int startHP)
		{
			player_pos.x = startPosition.x;
			player_pos.y = startPosition.y;
			//player_color = color;
			hp = startHP;
		}

		PositionCoord getCurrentPosition();

		Direction getCurrentDirection();

		unsigned int getCurrentHitPoints();

		//unsigned int getColor();

		bool GetDamage(hit_points dmg)
		{
			hp -= dmg;
			if (hp <= 0) return 1;
			else return 0;
		}

		void Move(CommandMove command);

		void Turn(CommandWithDirection command);

		BULLET* Attack(CommandAttack command);
	};


	class BULLET
	{
		PositionCoord bullet_pos;
		hit_points damage;

	public:
		BULLET(PositionCoord startPosition, hit_points dmg)
		{
			bullet_pos = startPosition;
			damage = dmg;
		}

		PositionCoord getCurrentPosition()
		{
			return bullet_pos;
		}

		hit_points getDamage()
		{
			return damage;
		}

		//~BULLET();
	};
};