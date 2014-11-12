#include "projectile.hpp"
#include <cmath>

Projectile::Projectile (SDL_Texture* texture, int w, int h, int x, int y, SDL_Rect& wallRect, double angle)
{
  this->texture = texture;
  this->projectileRect.w = w;
  this->projectileRect.h = h;
  this->projectileRect.x = x;
  this->projectileRect.y = y;
  this->xPres = (int)x;
  this->yPres = (int)y;
  this->velocity = 0;
  this->velocityFlag = true;
  this->rotateSpeed = 0;
  this->rotateSpeedFlag = true;
  this->wallRect = wallRect;
}

double Projectile::getAngle ()
{
  return this->angle;
}

int Projectile::getWidth ()
{
  return this->w;
}

int Projectile::getHeight ()
{
  return this->h;
}

SDL_Texture* Projectile::getTexture ()
{
  return this->texture;
}

void Projectile::rotateClockwise ()
{
  this->rotateSpeed +=4;
  if (this->rotateSpeed > 60)
    this->rotateSpeed = 60;
  this->rotateSpeedFlag = false;

  //this->setAngle (this->angle + 0.05*this->rotateSpeed);
}

void Projectile::rotateCounterClockwise ()
{
  this->rotateSpeed -=4;
  if (this->rotateSpeed < -60)
    this->rotateSpeed = -60;
  this->rotateSpeedFlag = false;

  //this->setAngle (this->angle - 0.05*this->rotateSpeed);
}

#define D2R 0.017453292519943295 
#define PROJECTILE_VELOCITY 30
void Projectile::update (void)
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

  this->xPres += sin(this->angle*D2R)*PROJECTILE_VELOCITY*0.05;
  this->tankRect.x = (int)this->xPres;

  SDL_IntersectRect (&tankRect, &this->wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->tankRect.x = x;
    this->xPres = xPres;
    delete this;
  }

  this->yPres -= cos(this->angle*D2R)*PROJECTILE_VELOCITY*0.05;
  this->tankRect.y = (int)this->yPres;

  SDL_IntersectRect (&this->tankRect, &this->wallRect, &commonRect);
  if (SDL_RectEquals (&tankRect, &commonRect) == SDL_FALSE)
  {
    this->tankRect.y = y;
    this->yPres = yPres;
    delete this;
  }
}

void Projectile::setAngle (double angle)
{
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  this->angle = angle;
}

void Projectile::moveForward (void)
{
  this->move (1);
}

void Projectile::moveBackward (void)
{
  this->move (-1);
}

void Projectile::move (int v)
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

int Projectile::getPosX ()
{
  return this->x;
}

int Projectile::getPosY ()
{
  return this->y;
}

void Projectile::drawProjectile (SDL_Renderer* renderer)
{
  SDL_RenderCopyEx (renderer, this->texture, NULL, &this->tankRect,
      this->angle, NULL, SDL_FLIP_NONE);
}
