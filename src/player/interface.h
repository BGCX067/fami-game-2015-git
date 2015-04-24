#pragma once

#include <memory>
#include "../general_types.h"
#include "../map/interface.h"
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
		player_type player_type_id;
		bullet_type bullet_type_id;
       /* hit_points damage; //к удалению
        unsigned int size; //к удалению*/

    public:
        PLAYER(t_player_number, PositionCoord, Direction, hit_points, player_type, bullet_type);

        t_player_number getPlayerId();

        PositionCoord getCurrentPosition();

        Direction getCurrentDirection();

        hit_points getCurrentHitPoints();

		bullet_type getBulletType();

        unsigned int getSize();

        //Танк получает урон. 0 - hp еще осталось, 1 - нет     (вместо проверки hp на равенство 0)
        bool RecieveDamage(hit_points);

        void Move(tmap::TMap*);

        void Turn(Direction);

        shared_ptr<class BULLET> Attack();
    };


    class BULLET
    {
        t_player_number player_id;
		bullet_type bullet_type_id;
        PositionCoord bullet_pos;
        Direction bullet_direction;
       /* hit_points damage;  //к удалению
        unsigned int dmgsize; //к удалению	//Пуля будет уничтожать ряд квадратиков, перпендикулярно направлению движения
        double velocity; //к удалению*/
        

    public:
        BULLET(t_player_number, bullet_type, PositionCoord, Direction);

		bullet_type getBulletType();

        t_player_number getPlayerId();

        PositionCoord getCurrentPosition();

		Direction getDirection();

        hit_points getDamage();

        unsigned int getDmgSize();

        unsigned int getVelocity();

        void Move();

        ~BULLET(){};
    };
};
