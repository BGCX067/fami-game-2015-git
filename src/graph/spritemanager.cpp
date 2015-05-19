#include "spritemanager.h"

spriteManager::spriteManager()
{

}

spriteManager::~spriteManager()
{
    for(uint i=0; i<sprite_array.size(); i++)
        delete sprite_array[i];
}

bool spriteManager::regSprite(sprite *spt)
{
    for(uint i=0; i<sprite_array.size(); i++)
        if(sprite_array[i]->getName() == spt->getName())
            return false;

    sprite_array.push_back(spt);
    return true;
}

bool spriteManager::unregSprite(sprite *spt)
{
    for(uint i=0; i<sprite_array.size(); i++)
        if(sprite_array[i]->getName() == spt->getName())
        {
            sprite *sp = sprite_array[i];
            sprite_array.erase(sprite_array.begin()+i);
            delete sp;

            return true;
        }

    return false;
}

sprite *spriteManager::getspriteByNumber(uint i)
{
    if(i>=sprite_array.size())
        return NULL;

    return sprite_array[i];
}
