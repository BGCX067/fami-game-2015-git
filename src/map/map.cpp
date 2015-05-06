#include "../map/interface.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace tmap;

map<player_type, PLAYER_TYPE_STRUCT> TMap::player_types_database;
map<bullet_type, BULLET_TYPE_STRUCT> TMap::bullet_types_database;

PLAYER_TYPE_STRUCT TMap::getPlayerType(player_type pt) {
    return player_types_database[pt];
}

BULLET_TYPE_STRUCT TMap::getBulletType(bullet_type pt) {
    return bullet_types_database[pt];
}


bool TMap::init(int level) {
    (void)level;
    return true;
}

bool TMap::clean() {
    for(auto& m : walls) m.second.clear();
    walls.clear();
    for(auto& m : players) m.second.clear();
    players.clear();
    for(auto& m : bullets) m.second.clear();
    bullets.clear();
    return true;
}

int TMap::getSizeX() {
    return this->sizex;
}

int TMap::getSizeY() {
    return this->sizey;
}

bool TMap::loadConfig(string config) {
    using namespace rapidjson;

    printf("Start load Map from file %s\n", config.c_str());

    FILE* fp;

#ifdef WIN32
    fopen_s(&fp, config.c_str(), "r");
#else
    fp = fopen(config.c_str(), "r");
#endif

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if(doc.HasParseError()) {
        return 0;
    }
    auto& dmap = doc["map"];

    this->sizex = dmap["sizex"].GetInt();
    this->sizey = dmap["sizey"].GetInt();

    auto& jWalls = dmap["walls"];
    int block_size = dmap["block_size"].GetInt();
    for(unsigned int i = 0; i < jWalls.Size(); i++) {
        auto& w = jWalls[i];
        int type = w["type"].GetInt();
        auto& xy1 = w["xy"][0];
        auto& xy2 = w["xy"][1];
        int x1 = xy1[0].GetInt();
        int x2 = xy2[0].GetInt();
        int y1 = xy1[1].GetInt();
        int y2 = xy2[1].GetInt();
        for(int k = x1; k <= x2; k++) {
            for(int l = y1; l <= y2; l++) {
                for(int o = 0; o < block_size; o++) {
                    for(int p = 0; p < block_size; p++) {
                        printf("new Wall [%d, %d]\n", block_size*k + o, block_size*l+p);
                        this->createWall(
                            PositionCoord(block_size*k + o, block_size*l+p),
                            shared_ptr<Wall>(new Wall(type))
                        );
                    }
                }
            }
        }
    }
    auto& jPlayers = dmap["players"];
    for(unsigned int i = 0; i < jPlayers.Size(); i++) {
        auto& p = jPlayers[i];
        auto xy = PositionCoord(p["xy"][0].GetInt(), p["xy"][1].GetInt());
        auto dir = (Direction) p["dir"].GetInt();
        auto type = p["type"].GetInt();
        auto btype = dmap["player_types"][type]["bullet_type"].GetInt();
        auto speed = dmap["player_types"][type]["speed"].GetInt();
        (void) speed;
        auto hp = p["health"].GetInt();
        printf("new Player [%d, %d]\n", xy.x, xy.y);
        this->createPlayer(
            xy,
            shared_ptr<player::PLAYER>(
                new player::PLAYER(i, xy, dir, type, btype)
            )
        );
    }
    return true;
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
    (void)n; (void)coord; (void)a;
    return false;
}

void TMap::forEachWall(function<void(PositionCoord, shared_ptr<Wall>) > f) {
    for (auto& xi : walls)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

void TMap::forEachPlayer(function<void(PositionCoord, shared_ptr<player::PLAYER>) > f) {
    for (auto& xi : players)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

void TMap::forEachBullet(function<void(PositionCoord, shared_ptr<player::BULLET>) > f) {
    for (auto& xi : bullets)
    for (auto&yi : xi.second) {
        f(PositionCoord(xi.first, yi.first), yi.second);
    }
}

bool TMap::createWall(PositionCoord coord, shared_ptr<Wall> w) {
    walls[coord.x][coord.y] = w;
    return true;
}

bool TMap::createPlayer(PositionCoord coord, shared_ptr<player::PLAYER> p) {
    players[coord.x][coord.y] = p;
    return true;
}

bool TMap::createBullet(PositionCoord coord, shared_ptr<player::BULLET> b) {
    bullets[coord.x][coord.y] = b;
    return true;
}

shared_ptr<Wall> TMap::getWall(PositionCoord pc) {
    return walls[pc.x][pc.y];
}

shared_ptr<player::PLAYER> TMap::getPlayer(PositionCoord pc) {
    return players[pc.x][pc.y];
}

shared_ptr<player::BULLET> TMap::getBullet(PositionCoord pc) {
    return bullets[pc.x][pc.y];
}

bool TMap::deleteWall(PositionCoord coord) {
    const auto& wallsX = walls.find(coord.x);
    if (wallsX == walls.end())return true;
    auto& wallsY = wallsX->second;
    if (wallsY.find(coord.y) != wallsY.end()) {
        wallsY.erase(coord.y);
        return true;
    }
    return false;
}

bool TMap::deletePlayer(PositionCoord coord) {
    const auto& playersX = players.find(coord.x);
    if (playersX == players.end())return true;
    auto& playersY = playersX->second;
    if (playersY.find(coord.y) != playersY.end()) {
        playersY.erase(coord.y);
        return true;
    }
    return false;
}

bool TMap::deleteBullet(PositionCoord coord) {
    const auto& bulletsX = bullets.find(coord.x);
    if (bulletsX == bullets.end())return true;
    auto& bulletsY = bulletsX->second;
    if (bulletsY.find(coord.y) != bulletsY.end()) {
        bulletsY.erase(coord.y);
        return true;
    }
    return false;
}
