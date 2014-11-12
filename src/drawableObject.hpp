class DrawableMovingObject
{
  public:
    DrawableMovingObject (SDL_Texture*, int, int, int, int, SDL_Rect&);
    ~DrawableMovingObject ();
    double getAngle ();
    int getWidth ();
    int getHeight ();
    SDL_Texture* getTexture ();
    void setAngle (double);
    int getPosX ();
    int getPosY ();
    void draw (SDL_Renderer*);
    virtual void moveForward (void);
    virtual void moveBackward (void);
    virtual void rotateClockwise ();
    virtual void rotateCounterClockwise ();
    virtual void update (int, int);
    void rotate (int, int);
    void move (int, int);
  private:
    double angle;
    int w, h;
    int x, y;
    int maxRotateSpeed;
    int rotateSpeedStep;
    int maxVelocity;
    int velocityStep;
    double xPres, yPres;
    SDL_Texture* texture;
    int rotateSpeed;
    bool rotateSpeedFlag;
    int velocity;
    bool velocityFlag;
    SDL_Rect wallRect;
    SDL_Rect movingObjectRect;
};
