class Tank
{
  public:
    Tank (void*, int, int, int, int);
    ~Tank ();
    double getAngle ();
    int getWidth ();
    int getHeight ();
    void* getTexture ();
    void rotateClockwise (int);
    void rotateCounterClockwise (int);
    void setAngle (double);
    void move (int);
    int getPosX ();
    int getPosY ();
  private:
    double angle;
    int w, h;
    int x, y;
    double xPres, yPres;
    void* texture;
};
