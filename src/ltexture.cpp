#include <stdio.h>
#include "ltexture.hpp"

LTexture::LTexture()
{
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
  gFont = NULL;
}

LTexture::~LTexture()
{
  free();
}

SDL_Texture* LTexture::getTextureData (void)
{
  return mTexture;
}

bool LTexture::loadFromFile( const char* path, SDL_Renderer* renderer)
{
  free();
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load( path );
  if( loadedSurface == NULL )
  {
    printf ("Unable to load image %s! SDL_image Error: %s\n", path,
        IMG_GetError());
  }
  else
  {
    SDL_SetColorKey (loadedSurface, SDL_TRUE,
        SDL_MapRGB (loadedSurface->format, 0, 0xFF, 0xFF ));
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    if( newTexture == NULL )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path,
          SDL_GetError() );
    }
    else
    {
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
    SDL_FreeSurface( loadedSurface );
  }
  mTexture = newTexture;
  return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( const char* textureText,
    SDL_Color textColor, SDL_Renderer* renderer, const char* font)
{
  free();
  if (gFont == NULL)
    gFont = TTF_OpenFont( font, 40 );
  SDL_Surface* textSurface = TTF_RenderText_Solid (gFont, textureText,
      textColor);
  if( textSurface == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n",
        TTF_GetError() );
  }
  else
  {
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( mTexture == NULL )
    {
      printf ("Unable to create texture from rendered text! SDL Error: %s\n",
          SDL_GetError());
    }
    else
    {
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }
    SDL_FreeSurface( textSurface );
  }
  return mTexture != NULL;
}

void LTexture::free()
{
  if( mTexture != NULL )
  {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
  SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
  SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
  SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle,
    SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  if( clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
  return mWidth;
}

int LTexture::getHeight()
{
  return mHeight;
}
