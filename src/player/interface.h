#pragma once

#include "../interface.h"
#include <memory>
using namespace map;
using namespace std;

/*
Интерфейсы взаимодействия с системой управления игроком (PLAYER).
*/

namespace player
{
	class PLAYER
	{
		t_player_number player_id;
		PositionCoord player_pos;
		Direction player_direction;
		hit_points hp;
		hit_points damage;
		unsigned int size;

	public:
		PLAYER(t_player_number, PositionCoord, Direction, hit_points, hit_points, unsigned int);

		t_player_number getPlayerId();

		PositionCoord getCurrentPosition();

		Direction getCurrentDirection();
	
		hit_points getCurrentHitPoints();

		unsigned int getSize();

		//Танк получает урон. 0 - hp еще осталось, 1 - нет     (вместо проверки hp на равенство 0)
		bool RecieveDamage(hit_points);

		void Move(CommandMove command, MAP* map);

		void Turn(CommandWithDirection);

		shared_ptr<class BULLET> Attack(CommandAttack command);
	};


	class BULLET
	{
		t_player_number player_id;
		PositionCoord bullet_pos;
		Direction bullet_direction;
		hit_points damage;

		//double velocity;

	public:
		BULLET(t_player_number, PositionCoord, Direction, hit_points);

		t_player_number getPlayerId();

		PositionCoord getCurrentPosition();

		hit_points getDamage();

		void Move(CommandMove command);

		//~BULLET();
	};
};
