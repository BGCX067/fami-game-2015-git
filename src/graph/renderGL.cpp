#include "graphicmanager.h"
#include "spritemanager.h"

void graphicManager::paintGL()
{
    clear();
    _map->forEachWall([&](PositionCoord pc, std::shared_ptr<Wall> w){
        drawWall(pc,w);
    });
    _map->forEachPlayer([&](PositionCoord pc, std::shared_ptr<player::PLAYER> p){
        drawTank(pc,p);
    });
    _map->forEachBullet([&](PositionCoord pc, std::shared_ptr<player::BULLET> b){
        drawBullet(pc,b);
    });
}
