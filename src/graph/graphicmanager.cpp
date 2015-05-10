#include "graphicmanager.h"

graphicManager::graphicManager(QWidget *parent)
    : QGLWidget(parent)
{
}

graphicManager::~graphicManager()
{

}

void graphicManager::drawWall(PositionCoord pc, std::shared_ptr<Wall> w)
{
    if(w->getType() == 0)
        drawRect(pc.x*10, pc.y*10, 10.0, 10.0, 0.0, 1.0, 0.0, 1.0);
    else
        drawRect(pc.x*10, pc.y*10, 10.0, 10.0, 1.0, 0.5, 0.0, 1.0);
}

void graphicManager::drawTank(PositionCoord pc, std::shared_ptr<player::PLAYER> p)
{
    switch(p->getPlayerId()) {
    case 1: drawRect(pc.x*10, pc.y*10, 30.0, 30.0, 0.0, 0.0, 0.9, 1.0); break;
    case 2: drawRect(pc.x*10, pc.y*10, 30.0, 30.0, 0.9, 0.0, 0.0, 1.0); break;
    default: drawRect(pc.x*10, pc.y*10, 30.0, 30.0, 0.5, 0.5, 0.5, 1.0); break;
    }
}

void graphicManager::drawBullet(PositionCoord pc, std::shared_ptr<player::BULLET> b)
{
    (void)b;
    drawRect(pc.x*10, pc.y*10, 5.0, 5.0, 0.5, 0.5, 0.5, 1.0);
}

void graphicManager::init(shared_ptr<tmap::TMap> mapObject)
{
    _map = mapObject;
    initializeGL();
}

void graphicManager::render()
{
    paintGL();
}

void graphicManager::free()
{
    freeGL();
}

void graphicManager::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void graphicManager::initializeGL()
{
    qDebug() << this->height() << " " <<  this->width();
    initGL(this->height() , this->width());
}

void graphicManager::resizeGL(int w, int h)
{
    glViewport( 0, 0, ( GLsizei )w, ( GLsizei )h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glScalef(1,1,1); //todo: use scaling to make scene fit into the screen;
    glOrtho(0.0, w, h, 0.0, 0.0f, 1.0f);
}

void graphicManager::drawLine(GLfloat xSt, GLfloat ySt, GLfloat xEd, GLfloat yEd, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_LINES);
        glColor4f(r,g,b,a);

        glVertex2f(xSt, ySt);
        glVertex2f(xEd, yEd);
    glEnd();

    glColor4f(0., 0., 0., 1.0);

    glPopMatrix();
}

void graphicManager::drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat a, bool filled)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, 0);

    GLfloat left, bottom, top, right;

    GLfloat size = width/2;
    left = - size;
    right = + size;

    size = height/2;
    top = + size;
    bottom = - size;

    if(filled)
        glBegin(GL_QUADS);
    else
        glBegin(GL_LINE_LOOP);

        glColor4f(r,g,b,a);

        glVertex2f(left, bottom);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);

    glEnd();

    glColor4f(0., 0., 0., 1.0);

    glPopMatrix();
}

void graphicManager::drawPixel(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_POINTS);

        glColor4f(r,g,b,a);
        glVertex2f(x, y);

    glEnd();

    glColor4f(0., 0., 0., 1.0);

    glPopMatrix();
}

void graphicManager::drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a, bool filled)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, 0);

    unsigned short N = 50;

    GLfloat verX, verY;
    GLfloat phi = 2*PI/N; //not an angle, but step. Angle is found during ver(tex)X and Y computation

    if(filled)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

        glColor4f(r,g,b,a);

        for(unsigned short i=0; i<N; i++)
        {
            verX = radius*cos(phi*i);
            verY = radius*sin(phi*i);
            glVertex2f(verX, verY);
        }

    glEnd();

    glColor4f(0., 0., 0., 1.0);

    glPopMatrix();
}

void graphicManager::drawSprite(sprite *sp, GLfloat x, GLfloat y, GLfloat scale, GLfloat rotation)
{
    //Push new matrices for this sprite
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    GLfloat height = sp->getHeight(),
            width  = sp->getWidth ();

    //inits
    initDraw(sp->getTexture());
    setMatrix(x-width/2, y-height/2, width, height, rotation);

    glBegin(GL_QUADS);

        glColor4f(1.0, 1.0, 1.0, 1.0);

        glTexCoord2f (0., 1.);
        glVertex2f (0, height*scale);

        glTexCoord2f (1., 1.);
        glVertex2f (width*scale, height*scale);

        glTexCoord2f (1., 0.);
        glVertex2f (width*scale, 0);

        glTexCoord2f (0., 0.);
        glVertex2f (0, 0);

    glEnd();

    //Fallback
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glColor4f(0., 0., 0., 1.0);

}

void graphicManager::setMatrix(GLfloat x, GLfloat y, GLfloat width, GLfloat height, float rotation)
{

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(x, y, 0.0f);

    //!Scaling/rotationg aint working for now (aint needed really).
    //glMatrixMode(GL_TEXTURE);
    if( fabs(rotation)> 1e-5 )
    {
        GLfloat Xc = (width)/2,
                Yc = (height)/2;
        glTranslatef(Xc, Yc, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(-Xc, -Yc, 0.0f);
    }

    //glScalef(scaleFactor, scaleFactor, 0);
}

void graphicManager::calculateAreaScaleFactor(float xSize, float ySize)
{
    int aWidth = this->width(),
        aHeight = this->height();
    float scaleX = aWidth / xSize,
          scaleY = aHeight / ySize;

    viewportScaleFactor = (scaleX < scaleY) ? scaleX : scaleY ;
}

void graphicManager::initDraw(GLuint spr)
{
    if(currentSprite != spr)
    {
        glBindTexture(GL_TEXTURE_2D, spr);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        currentSprite = spr;
    }
}

void graphicManager::initGL(unsigned int h, unsigned int w)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.9f, 0.9f, 0.9f, 1.f );

    glViewport( 0, 0, ( GLsizei )w, ( GLsizei )h );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, w, h, 0.0, 0.0f, 1.0f);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void graphicManager::freeGL()
{
    //Well, what if?
}
