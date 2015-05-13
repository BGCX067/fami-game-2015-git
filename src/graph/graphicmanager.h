#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "graphinclude.h"
#include "sprite.h"
#include "interface.h"
#include "spritemanager.h"
#include "../map/interface.h"
#include "../player/interface.h"
#include <QGLWidget>

class graphicManager : public QGLWidget, public graph::graphicManager
{
public:
    explicit graphicManager(QWidget *parent);
    ~graphicManager();

    void init(shared_ptr<tmap::TMap> mapObject);
    void render();
    void free();

    void drawWall(PositionCoord, std::shared_ptr<Wall>);
    void drawTank(PositionCoord, std::shared_ptr<player::PLAYER>);
    void drawBullet(PositionCoord, std::shared_ptr<player::BULLET>);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    //simple draw functions
    void drawLine(GLfloat xSt, GLfloat ySt, GLfloat xEd, GLfloat yEd,
                  GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height,
                  GLfloat r, GLfloat g, GLfloat b, GLfloat a, bool filled = 1);
    void drawPixel(GLfloat x, GLfloat y,
                   GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void drawCircle(GLfloat x, GLfloat y, GLfloat radius,
                    GLfloat r, GLfloat g, GLfloat b, GLfloat a, bool filled = 1);
    void drawSprite(sprite *sp, GLfloat x, GLfloat y,
                    GLfloat scale, GLfloat rotation);

    void clear();

    void loadSprites();

private:
    //Draw inits
    void initDraw(GLuint spr); //Inits texture;
    void setMatrix(GLfloat x, GLfloat y, GLfloat width, GLfloat height, float rotation); //For now it sets modelview matrix

    void calculateAreaScaleFactor(float xSize, float ySize);
    float getAngle(Direction dir);

    //GL micro
    void initGL(unsigned int h, unsigned int w);
    void freeGL();

    float viewportScaleFactor = 1;
    GLuint currentSprite;
    shared_ptr<tmap::TMap> _map;

    spriteManager tanks, walls, bullets;
};

#endif // GRAPHICMANAGER_H
