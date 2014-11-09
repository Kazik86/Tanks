#include "graphicsViewer.hpp"
#include <stdio.h>

GraphicsViewer::GraphicsViewer ()
{
}

GraphicsViewer::~GraphicsViewer ()
{
  SDL_DestroyRenderer (gRenderer);
  SDL_DestroyWindow (gWindow);
  IMG_Quit ();
  SDL_Quit ();
}

bool GraphicsViewer::init (int x, int y)
{
  if (SDL_Init (SDL_INIT_VIDEO)<0)
  {
    printf ("SDL initialization error: %s\n\r", SDL_GetError());
    return false;
  }
  else
  {
    this->sizeX = x;
    this->sizeY = y;
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
      printf ("Warning: Linear texture filtering not enabled!\n\r");
    gWindow = SDL_CreateWindow ("Data Vizualizer", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, this->sizeX, this->sizeY, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf ("Window couldn't be created: %s\n\r", SDL_GetError());
      return false;
    }
    else
    {
      gRenderer = SDL_CreateRenderer (gWindow, -1,
          SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL)
      {
        printf ("Renderer couldn't be created: %s\n\r", SDL_GetError());
        return false;
      }
      else
      {
        SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0x00, 0x00);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init (imgFlags) & imgFlags))
        {
          printf ("SDL_image could not initialize: %s\n\r", SDL_GetError());
          return false;
        }
        if (TTF_Init() == -1)
        {
          printf ("SDL_ttf could not initialize! SDL_ttf Error: %s\n\r", SDL_GetError());
          return false;
        }
      }
    }
  }
  return true;
}

bool GraphicsViewer::init (void)
{
  return init (640, 480);
}

int GraphicsViewer::getWindowSizeX (void)
{
  return this->sizeX;
}

int GraphicsViewer::getWindowSizeY (void)
{
  return this->sizeY;
}

void GraphicsViewer::writeText (const char* text, LTexture* texture)
{
  SDL_Color textColor = {0,0xFF,0};
  texture->loadFromRenderedText (text, textColor, gRenderer, NULL);
}

LTexture* GraphicsViewer::loadTexture (const char* text, const char* fontPath)
{
  LTexture* newTexture = new LTexture;
  if (newTexture->loadFromFile (text, gRenderer) == false)
  {
    printf ("Could not load image from file. Loading as text.\n\r");
    SDL_Color textColor = {0,0xFF,0};
    if (newTexture->loadFromRenderedText (text, textColor, gRenderer, fontPath)
        == false)
    {      
      printf ("Could not load image texture.\n\r");
      delete newTexture;
      newTexture = NULL;
    }
  }
  return newTexture;
}

bool GraphicsViewer::putTexture (int xBegin, int yBegin, int xEnd, int yEnd,
    SDL_Texture* texture)
{
  SDL_Rect viewport;
  viewport.x = xBegin;
  viewport.y = yBegin;
  viewport.w = xEnd - xBegin;
  viewport.h = yEnd - yBegin;
  SDL_RenderSetViewport (gRenderer, &viewport);
  int w,h;
  SDL_QueryTexture (texture, NULL, NULL, &w, &h);
  SDL_Rect renderQuad = {(xEnd - xBegin - w)/2,(yEnd-yBegin-h)/2,w,h};
  SDL_RenderCopy (gRenderer, texture, NULL, &renderQuad);
  return true;
}

bool GraphicsViewer::putRotatedTexture (int xBegin, int yBegin, int xEnd, int yEnd,
    double angle, SDL_Texture* texture)
{
  SDL_Rect viewport;
  viewport.x = xBegin;
  viewport.y = yBegin;
  viewport.w = xEnd - xBegin;
  viewport.h = yEnd - yBegin;
  SDL_Rect renderQuad;
  int w,h;
  SDL_QueryTexture (texture, NULL, NULL, &w, &h);
  if (!(viewport.w == 0 || viewport.h == 0))
  {
    SDL_RenderSetViewport (gRenderer, &viewport);
    renderQuad = {(xEnd - xBegin - w)/2,(yEnd-yBegin-h)/2,w,h};
    SDL_RenderCopyEx (gRenderer, texture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
  }
  else
  {
    SDL_RenderSetViewport (gRenderer, NULL);
    renderQuad = {(this->sizeX-w)/2,(this->sizeY-h)/2,w,h};
    SDL_RenderCopyEx (gRenderer, texture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
  }
  return true;
}

bool GraphicsViewer::putRotatedTexture (SDL_Rect* rendRect, SDL_Rect* textRect,
    double angle, SDL_Texture* texture)
{
  //SDL_Rect* viewport = rendRect;
  //SDL_Rect* renderQuad = textRect;
  SDL_RenderSetViewport (gRenderer, rendRect);
  SDL_RenderCopyEx (gRenderer, texture, textRect, NULL, angle, NULL, SDL_FLIP_NONE);
  return true;
}

bool GraphicsViewer::putRotatedTextureNSV (int x, int y, double angle,
    SDL_Texture* texture)
{
  SDL_Rect renderQuad;
  int w,h;
  SDL_QueryTexture (texture, NULL, NULL, &w, &h);
  renderQuad.x = x;
  renderQuad.y = y;
  renderQuad.w = w;
  renderQuad.h = h;
  SDL_RenderCopyEx (gRenderer, texture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
  return true;
}

bool GraphicsViewer::putRotatedTextureNSV (int x, int y, int w, int h, double angle,
    SDL_Texture* texture)
{
  SDL_Rect renderQuad;
  renderQuad.x = x;
  renderQuad.y = y;
  renderQuad.w = w;
  renderQuad.h = h;
  SDL_RenderCopyEx (gRenderer, texture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
  return true;
}

void GraphicsViewer::clear (void)
{
  SDL_RenderClear( gRenderer );
}

void GraphicsViewer::show (void)
{
  SDL_RenderPresent( gRenderer );
}

SDL_Renderer* GraphicsViewer::getRenderer (void)
{
  return this->gRenderer;
}
