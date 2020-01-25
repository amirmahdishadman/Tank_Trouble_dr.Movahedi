#include <cmath>

using namespace std;
SDL_Renderer *gRenderer = NULL;
Uint32 lastTime = 0, currentTime;
class bullet
{
  public:
    float x, y, xdelta, ydelta, value = 0, rball = 3;
    bool out = true;
    Uint32 lastTimeball = 0, currentTimeball;
    void move()
    {
        x += xdelta;
        y -= ydelta;
        filledCircleRGBA(gRenderer, x, y, rball, 0, 0, 0, 255);
        currentTimeball = SDL_GetTicks();
        if (currentTimeball - lastTimeball > 12000)
        {
            value = 0;
            lastTimeball = 0;
            currentTimeball = 0;
        }
    }
    

} gbullet1[6], gbullet2[6];
