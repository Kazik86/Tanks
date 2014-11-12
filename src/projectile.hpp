class Projectile
{
  public:
    Projectile (SDL_Texture*, int, int, int, int, SDL_Rect&);
    ~ Projectile();
    double getAngle ();
    int getWidth ();
    int getHeight ();
    SDL_Texture* getTexture ();
    void rotateClockwise ();
    void rotateCounterClockwise ();
    void setAngle (double);
    void move (int);
    int getPosX ();
    int getPosY ();
    void update (void);
    void moveForward (void);
    void moveBackward (void);
    void draw (SDL_Renderer*);
  private:
    double angle;
    int w, h;
    int x, y;
    double xPres, yPres;
    SDL_Texture* texture;
    int rotateSpeed;
    bool rotateSpeedFlag;
    int velocity;
    bool velocityFlag;
    SDL_Rect wallRect;
    SDL_Rect projectileRect;
}
