#pragma once
#include <functional>
#include <map>
#include "../general_types.h"
#include <memory>

using namespace std;

/*
Интерфейсы взаимодействия с системой игровой карты (MAP).
*/

namespace tmap {
    class TMap {
        int sizex, sizey;
        map<int, map<int, shared_ptr<class Wall> > > walls;
        map<int, map<int, shared_ptr<class Player> > > players;
        map<int, map<int, shared_ptr<class Bullet> > > bullets;
    public:
        bool init(int level);
        bool clean();

        bool isEmpty(PositionCoord coord);
        //Необходимо проверить ряд из n квадратиков с центром в coord по направлению a и -a
        bool isEmptyRow(int n, PositionCoord coord, Direction a);

        void forEachWall(function<void(PositionCoord, shared_ptr<class Wall>) > f);
        void forEachPlayer(function<void(PositionCoord, shared_ptr<class Player>) > f);
        void forEachBullet(function<void(PositionCoord, shared_ptr<class Bullet>) > f);

        bool createWall(PositionCoord);
        bool createPlayer(PositionCoord);
        bool createBullet(PositionCoord);

        bool deleteWall(PositionCoord);
        bool deletePlayer(PositionCoord);
        bool deleteBullet(PositionCoord);
    };
};
