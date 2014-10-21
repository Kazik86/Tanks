#include <iostream>
#include <SDL2/SDL.h>

#define TANKS_SDL_INIT (SDL_INIT_VIDEO)

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main (int argc, char** argv)
{
  SDL_Window* TanksWindow = NULL;
  
  if (SDL_Init (TANKS_SDL_INIT) < 0)
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  TanksWindow = SDL_CreateWindow ("Tanks", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (TanksWindow == NULL)
  {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return 2;
  }
  
  TanksMenu* TanksMenu_Instance = new TanksMenu (TanksWindow);
  TanksMenu_Instance->run();
}
