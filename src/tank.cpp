#include "tank.hpp"
#include <cmath>
#include <SDL2/SDL_rect.h>

Tank::Tank (void* texture, int w, int h, int x, int y)
{
  this->texture = texture;
  this->w = w;
  this->h = h;
  this->x = x;
  this->y = y;
  this->xPres = (int)x;
  this->yPres = (int)y;
  this->velocity = 0;
  this->velocityFlag = true;
  this->rotateSpeed = 0;
  this->rotateSpeedFlag = true;
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

void Tank::rotateClockwise ()
{
  this->rotateSpeed +=4;
  if (this->rotateSpeed > 60)
    this->rotateSpeed = 60;
  this->rotateSpeedFlag = false;

  //this->setAngle (this->angle + 0.05*this->rotateSpeed);
}

void Tank::rotateCounterClockwise ()
{
  this->rotateSpeed -=4;
  if (this->rotateSpeed < -60)
    this->rotateSpeed = -60;
  this->rotateSpeedFlag = false;

  //this->setAngle (this->angle - 0.05*this->rotateSpeed);
}

#define D2R 0.017453292519943295 
void Tank::update (void)
{
  if (this->rotateSpeedFlag)
  {
    if (this->rotateSpeed > 0)
      this->rotateSpeed -=4;
    else if (this->rotateSpeed < 0)
      this->rotateSpeed +=4;
  }
  this->setAngle (this->angle - 0.05*this->rotateSpeed);
  this->rotateSpeedFlag = true;

  if (this->velocityFlag)
  {
    if (this->velocity > 0)
      this->velocity -=2;
    if (this->velocity < 0)
      this->velocity +=2;
  }
  this->velocityFlag = true;
  int x ,y;
  double xPres, yPres;
  x = this->x;
  y = this->y;
  xPres = this->xPres;
  yPres = this->yPres;

  SDL_Rect tankRect;
  SDL_Rect wallRect = {0,0,800,600};
  SDL_Rect commonRect;

  this->xPres += sin(this->angle*D2R)*velocity*0.05;
  this->x = (int)this->xPres;
  tankRect = {this->x, this->y, this->w, this->h};

  SDL_IntersectRect (&tankRect, &wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->x = x;
    this->xPres = xPres;
  }

  this->yPres -= cos(this->angle*D2R)*velocity*0.05;
  this->y = (int)this->yPres;
  tankRect = {this->x, this->y, this->w, this->h};

  SDL_IntersectRect (&tankRect, &wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->y = y;
    this->yPres = yPres;
  }
}

void Tank::setAngle (double angle)
{
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  this->angle = angle;
}

void Tank::moveForward (void)
{
  this->move (1);
}

void Tank::moveBackward (void)
{
  this->move (-1);
}

void Tank::move (int v)
{
  if (v == 1)
  {
    velocity += 2;
    if(velocity > 60)
      velocity = 60;
    velocityFlag = false;
  }
  else if (v == -1)
  {
    velocity -= 2;
    if(velocity < -60)
      velocity = -60;
    velocityFlag = false;
  }
}

int Tank::getPosX ()
{
  return this->x;
}

int Tank::getPosY ()
{
  return this->y;
}
