#include "../map/interface.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <fstream>
#include <QDebug>

using namespace tmap;

map<player_type, PLAYER_TYPE_STRUCT> TMap::player_types_database;
map<bullet_type, BULLET_TYPE_STRUCT> TMap::bullet_types_database;

PLAYER_TYPE_STRUCT TMap::getPlayerType(player_type pt) {
    return player_types_database[pt];
}

BULLET_TYPE_STRUCT TMap::getBulletType(bullet_type pt) {
    return bullet_types_database[pt];
}

void TMap::movePlayer(PositionCoord old_p, PositionCoord new_p) {
    qDebug("MAP: move player: (%d,%d) -> (%d,%d)", old_p.x, old_p.y, new_p.x, new_p.y);
   auto player = players[old_p.x][old_p.y];
   players[new_p.x][new_p.y] = player;
   players[old_p.x].erase(old_p.y);
}

bool TMap::init(int level) {
    (void)level;
    return true;
}

bool TMap::clean() {
    walls.clear();
    players.clear();
    bullets.clear();
    return true;
}

int TMap::getSizeX() {
    return this->sizex;
}

int TMap::getSizeY() {
    return this->sizey;
}

bool TMap::loadSquare(string square) {
    fstream sq(square, std::fstream::in);
    if(sq.fail()) {
        return false;
    }
    sq >> this->sizex >> this->sizey;

    PositionCoord
            max1(-1, -1),
            min1(this->sizex, this->sizey),
            max2(-1, -1),
            min2(this->sizex, this->sizey);

    char point;
    for(int j = 0; j < this->sizey; j++) {
        for(int i = 0; i < this->sizex; i++) {
           sq >> point;
           if(point == '\t' || point == '\n')
               sq >> point;
           switch(point) {
           case 'o':
               this->createWall(
                           PositionCoord(i,j),
                           shared_ptr<Wall>(new Wall(1))
                           );
               break;
           case '*':
               this->createWall(
                           PositionCoord(i,j),
                           shared_ptr<Wall>(new Wall(0))
                           );
               break;
           case '-': break;
           case '1':
               if(i > max1.x) max1.x = i;
               if(i < min1.x) min1.x = i;
               if(j > max1.y) max1.y = j;
               if(j < min1.y) min1.y = j;
               break;
           case '2':
               if(i > max2.x) max2.x = i;
               if(i < min2.x) min2.x = i;
               if(j > max2.y) max2.y = j;
               if(j < min2.y) min2.y = j;
               break;
           }
        }
    }

    sq.close();

    PositionCoord pc1((max1.x + min1.x)/2,(max1.y + min1.y)/2);
    auto player1 = shared_ptr<player::PLAYER> (
                new player::PLAYER(1,pc1,  /*задаются в json*/ Direction(0),0)
                );
    this->createPlayer(pc1, player1);
    PositionCoord pc2((max2.x + min2.x)/2,(max2.y + min2.y)/2);
    auto player2 = shared_ptr<player::PLAYER> (
                new player::PLAYER(2,pc2,  /*задаются в json*/ Direction(0),0)
                );
    this->createPlayer(pc2, player2);

    return true;
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
        return false;
    }
    auto& dmap = doc["map"];

    auto& jpt = dmap["player_types"];
    for(unsigned int i = 0; i < jpt.Size(); i++) {
        auto& pt = jpt[i];
        PLAYER_TYPE_STRUCT pts;
        pts.default_hp = pt["default_hp"].GetInt();
        pts.tank_size = pt["tank_size"].GetInt();
        pts.velocity = pt["velocity"].GetInt();
        pts.bullet_type_id = pt["bullet_type"].GetInt();
        this->player_types_database[i] = pts;
    }

    auto& jbt = dmap["bullet_types"];
    for(unsigned int i = 0; i < jpt.Size(); i++) {
        auto& bt = jbt[i];
        BULLET_TYPE_STRUCT bts;
        bts.damage = bt["damage"].GetInt();
        bts.damage_size = bt["damage_size"].GetInt();
        bts.velocity = bt["velocity"].GetInt();
        this->bullet_types_database[i] = bts;
    }

    string square = dmap["square"].GetString();
    if(!this->loadSquare(square)) {
        qDebug("MAP: loadSquare error");
        return false;
    }

    auto& jPlayers = dmap["players"];
    for(unsigned int i = 0; i < jPlayers.Size(); i++) {
        auto& p = jPlayers[i];
        auto dir = p["dir"].GetInt();
        auto type = p["type"].GetInt();
        printf("new Player[%d]\n", i);
        this->forEachPlayer([&](PositionCoord pc, shared_ptr<player::PLAYER> p) {
            (void)pc;
            if(p->getPlayerId() == i + 1) {
                p->setCurrentDirection(Direction(dir));
                p->setPlayerType(type);
                p->setCurrentHitPoints(getPlayerType(type).default_hp);
            }
        });
    }



    return true;
}

bool TMap::isEmpty(PositionCoord coord) {
    int a = 0;
    auto wallsX = walls.find(coord.x);
    if (wallsX == walls.end()) { a ++; }
    else {
        auto wallsY = wallsX->second;
        if (wallsY.find(coord.y) == wallsY.end()) { a ++; }
    }

    if(!a) return false;

    bool b = true;

    this->forEachPlayer([&](PositionCoord pc, shared_ptr<player::PLAYER> p) {
        int psize = p->getSize();
        int k = (psize - 1) / 2;
        for(int i = pc.x - k; i <= pc.x + k; i++) {
            for(int j = pc.y - k; j <= pc.y + k; j++) {
                PositionCoord curCoord(i, j);
                if(curCoord == coord) { b = false; }
            }
        }
    });

    return b;
}

//Необходимо проверить ряд из n квадратиков с центром в coord по направлению a и -a
bool TMap::isEmptyRow(int n, PositionCoord coord, Direction a) {
    if(n%2 == 0) {
        printf("Error. TMap::isEmptyRow. n != (2*k - 1).");
        exit(0);
        return false;
    }
    bool result = true;
    switch(a) {
    case Direction::Down:
    case Direction::Up:
        result = isEmpty(coord);
        for(int i = 1; i <= (n-1)/2 && result; i++) {
            result = result && isEmpty(PositionCoord(coord.x, coord.y + i));
            result = result && isEmpty(PositionCoord(coord.x, coord.y - i));
        }
        return result;
    case Direction::Left:
    case Direction::Right:
        result = isEmpty(coord);
        for(int i = 1; i <= (n-1)/2 && result; i++) {
            result = result && isEmpty(PositionCoord(coord.x + i, coord.y));
            result = result && isEmpty(PositionCoord(coord.x - i, coord.y));
        }
        return result;
    default: return true;
    }

    return true;
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
    playersById[p->getPlayerId()] = p;
    return true;
}

bool TMap::createBullet(PositionCoord coord, shared_ptr<player::BULLET> b) {
    bullets[coord.x][coord.y] = b;
    return true;
}

shared_ptr<Wall> TMap::getWall(PositionCoord coord) {
    const auto& wallsX = walls.find(coord.x);
    if (wallsX == walls.end()) return shared_ptr<Wall>(nullptr_t());;
    auto& wallsY = wallsX->second;
    if (wallsY.find(coord.y) != wallsY.end()) {
        return walls[coord.x][coord.y];
    }
    return shared_ptr<Wall>(nullptr_t());
}

shared_ptr<player::PLAYER> TMap::getPlayer(PositionCoord coord) {
    const auto& playersX = players.find(coord.x);
    if (playersX == players.end())return shared_ptr<player::PLAYER>(nullptr_t());;
    auto& playersY = playersX->second;
    if (playersY.find(coord.y) != playersY.end()) {
        return players[coord.x][coord.y];
    }
    return shared_ptr<player::PLAYER>(nullptr_t());
}

shared_ptr<player::BULLET> TMap::getBullet(PositionCoord coord) {
    const auto& bulletsX = bullets.find(coord.x);
    if (bulletsX == bullets.end())
        return shared_ptr<player::BULLET>(nullptr_t());
    auto& bulletsY = bulletsX->second;
    if (bulletsY.find(coord.y) != bulletsY.end()) {
        return bullets[coord.x][coord.y];
    }
    return shared_ptr<player::BULLET>(nullptr_t());
}

shared_ptr<player::PLAYER> TMap::getPlayer(t_player_number player_id) {
   return this->playersById[player_id];
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
    for(map<int, shared_ptr<player::PLAYER>>::iterator p = this->playersById.begin();
        p != this->playersById.end(); p++) {
        if(p->second->getCurrentPosition() == coord) {
            this->playersById.erase(p);
            break;
        }
    }
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
