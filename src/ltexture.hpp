#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class LTexture
{
  public:
    LTexture();
    ~LTexture();
    bool loadFromFile (const char*, SDL_Renderer*);
    bool loadFromRenderedText (const char*, SDL_Color,
        SDL_Renderer*, const char*);
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0,
        SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
    SDL_Texture* getTextureData (void);
    TTF_Font* gFont;

  private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
