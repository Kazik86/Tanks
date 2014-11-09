#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "graphicsViewer.hpp"
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL.h>
#include "tank.hpp"

using namespace std;


/*
 *
 *SDL config
 *
 */

extern const int screen_width;
extern const int screen_height;

const int screen_width = 800;
const int screen_height = 600;

#define TANK_SIZE_X 30
#define TANK_SIZE_Y TANK_SIZE_X

SDL_sem* gDataLock = NULL;
SDL_mutex* gMutexLock = NULL;

int main (int argc, char** argv)
{
  GraphicsViewer graphics;
  SDL_Event e;
  int vel = 0;
  int rotateSpeed = 0;
  bool rotateSpeedFlag = true;
  bool velFlag = true;
  bool quit;
  if (!graphics.init (screen_width, screen_height))
    return 1;
  const Uint8* keyState = SDL_GetKeyboardState (NULL);
  LTexture* tankTexture = graphics.loadTexture ("imgs/Tank.png", NULL);
  Tank tank((void*)tankTexture->getTextureData (),TANK_SIZE_X,TANK_SIZE_Y, 400, 300);
  graphics.clear ();
  graphics.clear ();
  graphics.putRotatedTextureNSV (400, 300, tank.getWidth (), tank.getHeight (),
      0.0, (SDL_Texture*)tank.getTexture ());
  graphics.show ();
  while (quit == false)
  {
    while (SDL_PollEvent (&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
        continue;
      }
    }
    if (keyState [SDL_SCANCODE_RIGHT])
    {
      rotateSpeed += 4;
      if (rotateSpeed > 60)
        rotateSpeed = 60;
      rotateSpeedFlag = false;
    }
    if (keyState [SDL_SCANCODE_LEFT])
    {
      rotateSpeed -= 4;
      if (rotateSpeed < -60)
        rotateSpeed = -60;
      rotateSpeedFlag = false;
      //tank.rotateCounterClockwise (3.0);
    }
    if (keyState [SDL_SCANCODE_UP])
    {
      vel += 2;
      if(vel > 60)
        vel = 60;
      velFlag = false;
    }
    if (keyState [SDL_SCANCODE_DOWN])
    {
      vel -= 2;
      if(vel < -60)
        vel = -60;
      velFlag = false;
    }
    if (rotateSpeedFlag)
    {
      if (rotateSpeed > 0)
        rotateSpeed -=4;
      else if (rotateSpeed < 0)
        rotateSpeed +=4;
    }
    if (velFlag)
    {
      if (vel > 0)
        vel -=2;
      if (vel < 0)
        vel +=2;
    }
    velFlag = true;
    rotateSpeedFlag = true;
    tank.move (vel);
    tank.rotateClockwise (rotateSpeed);
    cout << rotateSpeed << endl;
    graphics.clear ();
    graphics.putRotatedTextureNSV (tank.getPosX (), tank.getPosY (), tank.getWidth (),
        tank.getHeight (), tank.getAngle (), (SDL_Texture*)tank.getTexture ());
    graphics.show ();
  }

  return 0;
}
