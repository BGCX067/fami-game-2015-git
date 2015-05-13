#pragma once

#include <memory>
#include "../general_types.h"
#include "../map/interface.h"
using namespace std;

/*
Интерфейсы взаимодействия с системой управления игроком (PLAYER).
*/
namespace tmap { class TMap; }

namespace player
{
    class PLAYER
    {
        t_player_number player_id;
        PositionCoord player_pos;
        Direction player_direction;
        hit_points hp;
        player_type player_type_id;

    public:
        PLAYER(t_player_number, PositionCoord, Direction, player_type);

        t_player_number getPlayerId();

        PositionCoord getCurrentPosition();

        Direction getCurrentDirection();

        hit_points getCurrentHitPoints();

        player_type getPlayerType();

        bullet_type getBulletType();

        unsigned int getSize();

        unsigned int getVelocity();

        void setPlayerType(player_type);

        void setCurrentDirection(Direction);

        void setCurrentHitPoints (hit_points);

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
