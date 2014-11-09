#include "tank.hpp"
#include <cmath>

Tank::Tank (SDL_Texture* texture, int w, int h, int x, int y, SDL_Rect& wallRect)
{
  this->texture = texture;
  this->tankRect.w = w;
  this->tankRect.h = h;
  this->tankRect.x = x;
  this->tankRect.y = y;
  this->xPres = (int)x;
  this->yPres = (int)y;
  this->velocity = 0;
  this->velocityFlag = true;
  this->rotateSpeed = 0;
  this->rotateSpeedFlag = true;
  this->wallRect = wallRect;
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

SDL_Texture* Tank::getTexture ()
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
  x = this->tankRect.x;
  y = this->tankRect.y;
  xPres = this->xPres;
  yPres = this->yPres;

  SDL_Rect commonRect;

  this->xPres += sin(this->angle*D2R)*velocity*0.05;
  this->tankRect.x = (int)this->xPres;

  SDL_IntersectRect (&tankRect, &this->wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->tankRect.x = x;
    this->xPres = xPres;
  }

  this->yPres -= cos(this->angle*D2R)*velocity*0.05;
  this->tankRect.y = (int)this->yPres;

  SDL_IntersectRect (&this->tankRect, &this->wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->tankRect.y = y;
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

void Tank::drawTank (SDL_Renderer* renderer)
{
  SDL_RenderCopyEx (renderer, this->texture, NULL, &this->tankRect,
      this->angle, NULL, SDL_FLIP_NONE);
}
