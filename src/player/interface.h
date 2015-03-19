#pragma once

#include "..\interface.h"
#include <memory>
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
		int size;

	public:
		PLAYER(PositionCoord, Direction, hit_points, hit_points,int size);

		PositionCoord getCurrentPosition();

		Direction getCurrentDirection();
	
		hit_points getCurrentHitPoints();

		//Танк получает урон. 0 - hp еще осталось, 1 - нет     (вместо проверки hp на равенство 0)
		bool RecieveDamage(hit_points);

		bool Move(CommandMove command, class MAP* map);

		void Turn(CommandWithDirection);

		std::shared_ptr<class BULLET> Attack(CommandAttack command);
	};


	class BULLET
	{
		t_player_number player_id;
		PositionCoord bullet_pos;
		Direction bullet_direction;
		hit_points damage;

		double velocity;

	public:
		BULLET(t_player_number, PositionCoord, Direction, hit_points);

		t_player_number getPlayerId();

		PositionCoord getCurrentPosition();

		hit_points getDamage();

		//Move(CommandMove command);

		//~BULLET();
	};
};