#include "../map/interface.h"

using namespace tmap;

bool TMap::init(int level) {
    return true;
}

bool TMap::clean() {
    for(auto& m : walls) m.second.clear();
    walls.clear();
    for(auto& m : players) m.second.clear();
    players.clear();
    for(auto& m : bullets) m.second.clear();
    bullets.clear();
}

bool TMap::isEmpty(PositionCoord coord) {
    auto wallsX = walls.find(coord.x);
    if (wallsX == walls.end()) return true;
    auto wallsY = wallsX->second;
    if (wallsY.find(coord.y) == wallsY.end()) return true;
    return false;
}

//Необходимо проверить ряд из n квадратиков с центром в coord по направлению a и -a
bool TMap::isEmptyRow(int n, PositionCoord coord, Direction a) {
    return false;
}

void TMap::forEachWall(function<void(PositionCoord, shared_ptr<class Wall>) > f) {
    for (auto& xi : walls)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

void TMap::forEachPlayer(function<void(PositionCoord, shared_ptr<class Player>) > f) {
    for (auto& xi : players)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

void TMap::forEachBullet(function<void(PositionCoord, shared_ptr<class Bullet>) > f) {
    for (auto& xi : bullets)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

bool TMap::createWall(PositionCoord coord) {
    auto& wallsX = walls.find(coord.x);
    if (wallsX == walls.end())return true;
    auto& wallsY = wallsX->second;
    if (wallsY.find(coord.y) == wallsY.end()) {
        wallsY[coord.y] = shared_ptr<Wall>(new Wall());
        return true;
    }
    return false;
}

bool TMap::createPlayer(PositionCoord coord) {
    auto& playersX = players.find(coord.x);
    if (playersX == players.end())return true;
    auto& playersY = playersX->second;
    if (playersY.find(coord.y) == playersY.end()) {
        playersY[coord.y] = shared_ptr<Player>(new Player());
        return true;
    }
    return false;
}

bool TMap::createBullet(PositionCoord coord) {
    auto& bulletsX = bullets.find(coord.x);
    if (bulletsX == bullets.end())return true;
    auto& bulletsY = bulletsX->second;
    if (bulletsY.find(coord.y) == bulletsY.end()) {
        bulletsY[coord.y] = shared_ptr<Bullet>(new Bullet());
        return true;
    }
    return false;
}

bool TMap::deleteWall(PositionCoord coord) {
    auto& wallsX = walls.find(coord.x);
    if (wallsX == walls.end())return true;
    auto& wallsY = wallsX->second;
    if (wallsY.find(coord.y) != wallsY.end()) {
        wallsY.erase(coord.y);
        return true;
    }
    return false;
}

bool TMap::deletePlayer(PositionCoord coord) {
    auto& playersX = players.find(coord.x);
    if (playersX == players.end())return true;
    auto& playersY = playersX->second;
    if (playersY.find(coord.y) != playersY.end()) {
        playersY.erase(coord.y);
        return true;
    }
    return false;
}

bool TMap::deleteBullet(PositionCoord coord) {
    auto& bulletsX = bullets.find(coord.x);
    if (bulletsX == bullets.end())return true;
    auto& bulletsY = bulletsX->second;
    if (bulletsY.find(coord.y) != bulletsY.end()) {
        bulletsY.erase(coord.y);
        return true;
    }
    return false;
}
