#ifndef SPRITE_H
#define SPRITE_H

#include "graphinclude.h"

class sprite
{
friend class graphicsManager;
public:
    sprite();
    sprite(const char *filename);
    ~sprite();

    bool load(const char *filename);

    GLuint getTexture();
    GLuint getHeight();
    GLuint getWidth();

    std::string getName();

private:
    void kill(); //deletes sprite

    GLuint texture;
    GLuint height, width;
    std::string name;

};

#endif // SPRITE_H
