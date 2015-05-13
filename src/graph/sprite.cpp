#include "sprite.h"

sprite::sprite()
{
    height = 0;
    width = 0;
    texture = 0;
    name = "";
}

sprite::sprite(const char *filename, const char *spritename)
{
    load(filename, spritename);
}

sprite::~sprite()
{
    kill();
}

bool sprite::load(const char *filename, const char *spritename)
{
    QImage *surf = new QImage(filename);

    if(surf->isNull())
    {
        qDebug() << "Failed loading texture from " << filename;
        return false;
    }

    height = surf->height();
    width = surf->width();

    name = spritename;

    glGenTextures(1, &texture); //gen tex id
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Beauty grafon

    if(surf->hasAlphaChannel())
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->convertToFormat(QImage::Format_RGBA8888).bits());
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->convertToFormat(QImage::Format_RGB888).bits());

    delete surf;

    return true;
}

GLuint sprite::getTexture()
{
    return texture;
}

GLuint sprite::getHeight()
{
    return height;
}

GLuint sprite::getWidth()
{
    return width;
}

std::string sprite::getName()
{
    return this->name;
}

void sprite::kill()
{
    glDeleteTextures(1, &texture);
}
