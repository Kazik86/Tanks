#include "tank.hpp"
#include <cmath>

Tank::Tank (void* texture, int w, int h, int x, int y)
{
  this->texture = texture;
  this->w = w;
  this->h = h;
  this->x = x;
  this->y = y;
  this->xPres = (int)x;
  this->yPres = (int)y;
}

Tank::~Tank ()
{
}

double Tank::getAngle ()
{
  return this->angle;
}

int Tank::getWidth ()
{
  return this->w;
}

int Tank::getHeight ()
{
  return this->h;
}

void* Tank::getTexture ()
{
  return this->texture;
}

void Tank::rotateClockwise (int angle)
{
  this->setAngle (this->angle + 0.05*angle);
}

void Tank::rotateCounterClockwise (int angle)
{
  this->setAngle (this->angle - 0.05*angle);
}

void Tank::setAngle (double angle)
{
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  this->angle = angle;
}
#define D2R 0.017453292519943295 
void Tank::move (int v)
{
  this->xPres += sin(this->angle*D2R)*v*0.05;
  this->yPres -= cos(this->angle*D2R)*v*0.05;
  this->x = (int)this->xPres;
  this->y = (int)this->yPres;
}

int Tank::getPosX ()
{
  return this->x;
}

int Tank::getPosY ()
{
  return this->y;
}
