#include "graphicmanager.h"
#include "spritemanager.h"

void graphicManager::paintGL()
{
    clear();
    int sy = _map->getSizeY();
    _map->forEachWall([&](PositionCoord pc, std::shared_ptr<Wall> w){
        PositionCoord pc2(pc.x, sy - pc.y);
        drawWall(pc2,w);
    });
    _map->forEachPlayer([&](PositionCoord pc, std::shared_ptr<player::PLAYER> p){
        PositionCoord pc2(pc.x, sy - pc.y);
        drawTank(pc2,p);
    });
    _map->forEachBullet([&](PositionCoord pc, std::shared_ptr<player::BULLET> b){
        pc = b->getCurrentPosition();
        PositionCoord pc2(pc.x, sy - pc.y);
        drawBullet(pc2,b);
    });
}
