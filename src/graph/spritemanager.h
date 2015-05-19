#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "graphinclude.h"
#include "sprite.h"

class spriteManager
{
public:
    spriteManager();
    ~spriteManager();

    bool regSprite(sprite *spt);
    bool unregSprite(sprite *spt);

    sprite* getspriteByNumber(uint i);

private:
    std::vector <sprite *> sprite_array;

};

#endif // SPRITEMANAGER_H
