class Tank
{
  public:
    Tank (void*, int, int, int, int);
    ~Tank ();
    double getAngle ();
    int getWidth ();
    int getHeight ();
    void* getTexture ();
    void rotateClockwise ();
    void rotateCounterClockwise ();
    void setAngle (double);
    void move (int);
    int getPosX ();
    int getPosY ();
    void update (void);
    void moveForward (void);
    void moveBackward (void);
  private:
    double angle;
    int w, h;
    int x, y;
    double xPres, yPres;
    void* texture;
    int rotateSpeed;
    bool rotateSpeedFlag;
    int velocity;
    bool velocityFlag;
};
