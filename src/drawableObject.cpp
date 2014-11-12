#include "tank.hpp"
#include <cmath>

DrawableMovingObject::DrawableObject (SDL_Texture* texture, int w, int h, int x, int y, SDL_Rect& wallRect)
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

DrawableMovingObject::~DrawableObject ()
{
}

double DrawableMovingObject::getAngle ()
{
  return this->angle;
}

int DrawableMovingObject::getWidth ()
{
  return this->w;
}

int DrawableMovingObject::getHeight ()
{
  return this->h;
}

SDL_Texture* DrawableMovingObject::getTexture ()
{
  return this->texture;
}

void DrawableMovingObject::rotateClockwise (int w, int e)
{
  this->rotate (60, 4);
  //this->setAngle (this->angle + 0.05*this->rotateSpeed);
}

void DrawableMovingObject::rotateCounterClockwise (int w, int e)
{
  this->rotate (-60, 4);
  //this->setAngle (this->angle - 0.05*this->rotateSpeed);
}

void rotate (int w, int e)
{
  if (w > 0)
  {
    rotateSpeed +=e;
    if(rotateSpeed > w)
      rotateSpeed = w;
    rotateSpeedFlag = false;
  }
  else if (w < 0)
  {
    rotateSpeed -= e;
    if(rotateSpeed < -w)
      rotateSpeed = -w;
    rotateSpeedFlag = false;
  }
}

#define D2R 0.017453292519943295 
void DrawableMovingObject::update (int a, int e)
{
  if (this->rotateSpeedFlag)
  {
    if (this->rotateSpeed > 0)
      this->rotateSpeed -=e;
    else if (this->rotateSpeed < 0)
      this->rotateSpeed +=e;
  }
  this->setAngle (this->angle - 0.05*this->rotateSpeed);
  this->rotateSpeedFlag = true;

  if (this->velocityFlag)
  {
    if (this->velocity > 0)
      this->velocity -=a;
    if (this->velocity < 0)
      this->velocity +=a;
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

void DrawableMovingObject::setAngle (double angle)
{
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  this->angle = angle;
}

void DrawableMovingObject::moveForward (void)
{
  this->move (60, 2);
}

void DrawableMovingObject::moveBackward (void)
{
  this->move (-60, 2);
}

void DrawableMovingObject::move (int v, int a)
{
  if (v > 0)
  {
    velocity += a;
    if(velocity > v)
      velocity = v;
    velocityFlag = false;
  }
  else if (v < 0)
  {
    velocity -= a;
    if(velocity < -v)
      velocity = -v;
    velocityFlag = false;
  }
}

int DrawableMovingObject::getPosX ()
{
  return this->x;
}

int DrawableMovingObject::getPosY ()
{
  return this->y;
}

void DrawableMovingObject::draw (SDL_Renderer* renderer)
{
  SDL_RenderCopyEx (renderer, this->texture, NULL, &this->movingObjectRect,
      this->angle, NULL, SDL_FLIP_NONE);
}
