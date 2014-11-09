#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ltexture.hpp"

class GraphicsViewer
{
  public:
    GraphicsViewer ();
    ~GraphicsViewer ();
    bool init (void);
    bool init (int x, int y);
    int getWindowSizeX (void);
    int getWindowSizeY (void);
    LTexture* loadTexture (const char*, const char*);
    bool putTexture (int, int, int, int, SDL_Texture*);
    bool putRotatedTexture (int, int, int, int, double, SDL_Texture*);
    bool putRotatedTexture (SDL_Rect*, SDL_Rect*, double, SDL_Texture*);
    bool putRotatedTextureNSV (int, int, double, SDL_Texture*);
    bool putRotatedTextureNSV (int, int, int, int, double, SDL_Texture*);
    void writeText (const char* text, LTexture* texture);
    SDL_Renderer* getRenderer (void);
    void show (void);
    void clear (void);
  private:
    int sizeX, sizeY;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    TTF_Font* gFont;
};
