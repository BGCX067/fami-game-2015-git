#pragma once
#include <functional>
#include <map>
#include <string>
#include "../general_types.h"
#include "../player/interface.h"
#include <memory>

using namespace std;

namespace player {
    class PLAYER;
    class BULLET;
}

/*
Интерфейсы взаимодействия с системой игровой карты (MAP).
*/

namespace tmap {
    class TMap {
        int sizex, sizey;
        map<int, map<int, shared_ptr<Wall>>> walls;
        map<int, map<int, shared_ptr<player::PLAYER>>> players;
        map<int, map<int, shared_ptr<player::BULLET>>> bullets;

        static map<player_type, PLAYER_TYPE_STRUCT> player_types_database;
        static map<bullet_type, BULLET_TYPE_STRUCT> bullet_types_database;

    public:

        static PLAYER_TYPE_STRUCT getPlayerType(player_type pt);
        static BULLET_TYPE_STRUCT getBulletType(bullet_type bt);

        bool init(int level);
        bool clean();

        int getSizeX();
        int getSizeY();

        bool loadConfig(string config);

        bool isEmpty(PositionCoord coord);
        //Необходимо проверить ряд из n квадратиков с центром в coord по направлению a и -a
        bool isEmptyRow(int n, PositionCoord coord, Direction a);

        void forEachWall(function<void(PositionCoord, shared_ptr<Wall>) > f);
        void forEachPlayer(function<void(PositionCoord, shared_ptr<player::PLAYER>)> f);
        void forEachBullet(function<void(PositionCoord, shared_ptr<player::BULLET>)> f);

        bool createWall(PositionCoord, shared_ptr<Wall>);
        bool createPlayer(PositionCoord, shared_ptr<player::PLAYER>);
        bool createBullet(PositionCoord, shared_ptr<player::BULLET>);

        bool deleteWall(PositionCoord);
        bool deletePlayer(PositionCoord);
        bool deleteBullet(PositionCoord);
    };
};
