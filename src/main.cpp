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
  //int vel = 0;
  //int rotateSpeed = 0;
  //bool rotateSpeedFlag = true;
  //bool velFlag = true;
  bool quit;
  if (!graphics.init (screen_width, screen_height))
    return 1;
  const Uint8* keyState = SDL_GetKeyboardState (NULL);
  LTexture* tankTexture = graphics.loadTexture ("imgs/Tank.png", NULL);
  Tank tank((void*)tankTexture->getTextureData (),TANK_SIZE_X,TANK_SIZE_Y, 100, 300);
  Tank tank2((void*)tankTexture->getTextureData (),TANK_SIZE_X,TANK_SIZE_Y, 700, 300);
  graphics.clear ();
  graphics.putRotatedTextureNSV (tank.getPosX (), tank.getPosY (), tank.getWidth (),
      tank.getHeight (), tank.getAngle (), (SDL_Texture*)tank.getTexture ());
  graphics.putRotatedTextureNSV (tank2.getPosX (), tank2.getPosY (), tank2.getWidth (),
      tank2.getHeight (), tank2.getAngle (), (SDL_Texture*)tank2.getTexture ());
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
      tank.rotateCounterClockwise ();
    }
    if (keyState [SDL_SCANCODE_LEFT])
    {
      tank.rotateClockwise ();
    }
    if (keyState [SDL_SCANCODE_UP])
    {
      tank.moveForward ();
    }
    if (keyState [SDL_SCANCODE_DOWN])
    {
      tank.moveBackward ();
    }

    if (keyState [SDL_SCANCODE_L])
    {
      tank2.rotateCounterClockwise ();
    }
    if (keyState [SDL_SCANCODE_J])
    {
      tank2.rotateClockwise ();
    }
    if (keyState [SDL_SCANCODE_I])
    {
      tank2.moveForward ();
    }
    if (keyState [SDL_SCANCODE_K])
    {
      tank2.moveBackward ();
    }
    //velFlag = true;
    //rotateSpeedFlag = true;
    /*
     *tank.rotateClockwise (rotateSpeed);
     *tank.move (vel);
     */
    tank.update ();
    tank2.update ();
    graphics.clear ();
    graphics.putRotatedTextureNSV (tank.getPosX (), tank.getPosY (), tank.getWidth (),
        tank.getHeight (), tank.getAngle (), (SDL_Texture*)tank.getTexture ());
  graphics.putRotatedTextureNSV (tank2.getPosX (), tank2.getPosY (), tank2.getWidth (),
      tank2.getHeight (), tank2.getAngle (), (SDL_Texture*)tank2.getTexture ());
    graphics.show ();
  }

  return 0;
}
