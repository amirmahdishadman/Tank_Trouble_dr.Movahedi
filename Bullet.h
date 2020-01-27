#include <cmath>
#include "media.h"

using namespace std;

SDL_Renderer *gRenderer = NULL;
Uint32 lastTime = 0, currentTime;
Mix_Chunk *TE = NULL; //Tank Explosion sound
Mix_Chunk *BR = NULL; //Bullet Reflect sound
bool EBFlag = false; //Extera Bullet Flag
Uint32 lastTimebullet = 0;
class bullet
{
public:
    float x, y, xdelta, ydelta, value = 0, rball = 4;
    bool out = true;
    Uint32 lastTimeball = 0, currentTimeball;
    void move()
    {
        x += xdelta;
        y -= ydelta;
        filledCircleRGBA(gRenderer, x + 20, y + 20, rball, 255, 0, 0, 255);
        collisiontankbullet();
        collisionwallbullet();

        currentTimeball = SDL_GetTicks();
        if (currentTimeball - lastTimeball > 12000)
        {
            value = 0;
            lastTimeball = 0;
            currentTimeball = 0;
        }
    }
    void collisiontankbullet()
    {
        if ((x - gtank1.x) * (x - gtank1.x) + (y - gtank1.y) * (y - gtank1.y) <= (rball + 18) * (rball + 18))
        {
            Mix_PlayChannel(-1, TE, 0);
            value = 0;
            lastTime = SDL_GetTicks();
            gtank1.lose = true;
            gtank1.bullet = 6;
        }
        else if ((x - gtank2.x) * (x - gtank2.x) + (y - gtank2.y) * (y - gtank2.y) <= (rball + 18) * (rball + 18))
        {
            Mix_PlayChannel(-1, TE, 0);
            value = 0;
            lastTime = SDL_GetTicks();
            gtank2.lose = true;
            gtank2.bullet = 6;
        }
    }
    void collisionwallbullet()
    {
        //top
        if ((y + 20 > map.borderrectx1.y + 8 - 0.4) && (y + 20 < map.borderrectx1.y + 8 + 0.4))
        {
            Mix_PlayChannel(-1, BR, 0);
            ydelta *= -1;
        }
        //down
        if ((y + 20 > map.borderrectx2.y - 0.4) && (y + 20 < map.borderrectx2.y + 0.4))
        {
            Mix_PlayChannel(-1, BR, 0);
            ydelta *= -1;
        }
        //left
        if ((x + 20 > map.borderrecty1.x + 8 - 0.4) && (x + 20 < map.borderrecty1.x + 8 + 0.4))
        {
            Mix_PlayChannel(-1, BR, 0);
            xdelta *= -1;
        }
        //right
        if ((x + 20 > map.borderrecty2.x - 0.4) && (x + 20 < map.borderrecty2.x + 0.4))
        {
            Mix_PlayChannel(-1, BR, 0);
            xdelta *= -1;
        }

        if (map.cn == 1)
        {
            //chap
            if ((x + 20 <= map.wallrecty1.x + 0.4) && (x + 20 >= map.wallrecty1.x - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty1.x + 70 + 0.4) && (x + 20 >= map.wallrecty1.x + 70 - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y - 0.4) && (y + 20 < map.wallrecty1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y + 200 - 0.4) && (y + 20 < map.wallrecty1.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty2.x + 0.4) && (x + 20 >= map.wallrecty2.x - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty2.x + 70 + 0.4) && (x + 20 >= map.wallrecty2.x + 70 - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y - 0.4) && (y + 20 < map.wallrecty2.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y + 200 - 0.4) && (y + 20 < map.wallrecty2.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////

            //Left
            if ((x + 20 <= map.wallrecty4.x + 0.4) && (x + 20 >= map.wallrecty4.x - 0.4) && (y + 20 > map.wallrecty4.y) && (y + 20 < map.wallrecty4.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Right
            if ((x + 20 <= map.wallrecty4.x + 70 + 0.4) && (x + 20 >= map.wallrecty4.x + 70 - 0.4) && (y + 20 > map.wallrecty4.y) && (y + 20 < map.wallrecty4.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Up
            if ((x + 20 >= map.wallrecty4.x) && (x + 20 <= map.wallrecty4.x + 70) && (y + 20 > map.wallrecty4.y - 0.4) && (y + 20 < map.wallrecty4.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //Down
            if ((x + 20 >= map.wallrecty4.x) && (x + 20 <= map.wallrecty4.x + 70) && (y + 20 > map.wallrecty4.y + 200 - 0.4) && (y + 20 < map.wallrecty4.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //////////////////////////////////////////////////////////////////////////////

            //Left
            if ((x + 20 <= map.wallrecty5.x + 0.4) && (x + 20 >= map.wallrecty5.x - 0.4) && (y + 20 > map.wallrecty5.y) && (y + 20 < map.wallrecty5.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Right
            if ((x + 20 <= map.wallrecty5.x + 70 + 0.4) && (x + 20 >= map.wallrecty5.x + 70 - 0.4) && (y + 20 > map.wallrecty5.y) && (y + 20 < map.wallrecty5.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Up
            if ((x + 20 >= map.wallrecty5.x) && (x + 20 <= map.wallrecty5.x + 70) && (y + 20 > map.wallrecty5.y - 0.4) && (y + 20 < map.wallrecty5.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //Down
            if ((x + 20 >= map.wallrecty5.x) && (x + 20 <= map.wallrecty5.x + 70) && (y + 20 > map.wallrecty5.y + 200 - 0.4) && (y + 20 < map.wallrecty5.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            /////////////////////////////////////////////////////////////////////////////

            //Left
            if ((x + 20 <= map.wallrecty3.x + 0.4) && (x + 20 >= map.wallrecty3.x - 0.4) && (y + 20 > map.wallrecty3.y) && (y + 20 < map.wallrecty3.y + 210))
            {                
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Right
            if ((x + 20 <= map.wallrecty3.x + 70 + 0.4) && (x + 20 >= map.wallrecty3.x + 70 - 0.4) && (y + 20 > map.wallrecty3.y) && (y + 20 < map.wallrecty3.y + 210))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Left
            if ((x + 20 >= map.wallrecty3.x) && (x + 20 <= map.wallrecty3.x + 70) && (y + 20 > map.wallrecty3.y - 0.4) && (y + 20 < map.wallrecty3.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //Down
            if ((x + 20 >= map.wallrecty3.x) && (x + 20 <= map.wallrecty3.x + 70) && (y + 20 > map.wallrecty3.y + 210 - 0.4) && (y + 20 < map.wallrecty3.y + 210 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            //////////////////////////////////////////////////////////////////////////////////////

            //Left
            if ((x + 20 <= map.wallrectx1.x + 0.4) && (x + 20 >= map.wallrectx1.x - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Right
            if ((x + 20 <= map.wallrectx1.x + 280 + 0.4) && (x + 20 >= map.wallrectx1.x + 280 - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Up
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y - 0.4) && (y + 20 < map.wallrectx1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //Down
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y + 70 - 0.4) && (y + 20 < map.wallrectx1.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //Left
            if ((x + 20 <= map.wallrectx2.x + 0.4) && (x + 20 >= map.wallrectx2.x - 0.4) && (y + 20 > map.wallrectx2.y) && (y + 20 < map.wallrectx2.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Right
            if ((x + 20 <= map.wallrectx2.x + 280 + 0.4) && (x + 20 >= map.wallrectx2.x + 280 - 0.4) && (y + 20 > map.wallrectx2.y) && (y + 20 < map.wallrectx2.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //Up
            if ((x + 20 >= map.wallrectx2.x) && (x + 20 <= map.wallrectx2.x + 280) && (y + 20 > map.wallrectx2.y - 0.4) && (y + 20 < map.wallrectx2.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //Down
            if ((x + 20 >= map.wallrectx2.x) && (x + 20 <= map.wallrectx2.x + 280) && (y + 20 > map.wallrectx2.y + 70 - 0.4) && (y + 20 < map.wallrectx2.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
        }

        if (map.cn == 2)
        {
            //Left
            if ((x + 20 <= map.wallrecty1.x + 0.4) && (x + 20 >= map.wallrecty1.x - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty1.x + 70 + 0.4) && (x + 20 >= map.wallrecty1.x + 70 - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y - 0.4) && (y + 20 < map.wallrecty1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y + 200 - 0.4) && (y + 20 < map.wallrecty1.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty2.x + 0.4) && (x + 20 >= map.wallrecty2.x - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty2.x + 70 + 0.4) && (x + 20 >= map.wallrecty2.x + 70 - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y - 0.4) && (y + 20 < map.wallrecty2.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y + 200 - 0.4) && (y + 20 < map.wallrecty2.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty4.x + 0.4) && (x + 20 >= map.wallrecty4.x - 0.4) && (y + 20 > map.wallrecty4.y) && (y + 20 < map.wallrecty4.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty4.x + 70 + 0.4) && (x + 20 >= map.wallrecty4.x + 70 - 0.4) && (y + 20 > map.wallrecty4.y) && (y + 20 < map.wallrecty4.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty4.x) && (x + 20 <= map.wallrecty4.x + 70) && (y + 20 > map.wallrecty4.y - 0.4) && (y + 20 < map.wallrecty4.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty4.x) && (x + 20 <= map.wallrecty4.x + 70) && (y + 20 > map.wallrecty4.y + 200 - 0.4) && (y + 20 < map.wallrecty4.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty5.x + 0.4) && (x + 20 >= map.wallrecty5.x - 0.4) && (y + 20 > map.wallrecty5.y) && (y + 20 < map.wallrecty5.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty5.x + 70 + 0.4) && (x + 20 >= map.wallrecty5.x + 70 - 0.4) && (y + 20 > map.wallrecty5.y) && (y + 20 < map.wallrecty5.y + 200))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty5.x) && (x + 20 <= map.wallrecty5.x + 70) && (y + 20 > map.wallrecty5.y - 0.4) && (y + 20 < map.wallrecty5.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty5.x) && (x + 20 <= map.wallrecty5.x + 70) && (y + 20 > map.wallrecty5.y + 200 - 0.4) && (y + 20 < map.wallrecty5.y + 200 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            /////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty3.x + 0.4) && (x + 20 >= map.wallrecty3.x - 0.4) && (y + 20 > map.wallrecty3.y) && (y + 20 < map.wallrecty3.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty3.x + 70 + 0.4) && (x + 20 >= map.wallrecty3.x + 70 - 0.4) && (y + 20 > map.wallrecty3.y) && (y + 20 < map.wallrecty3.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty3.x) && (x + 20 <= map.wallrecty3.x + 70) && (y + 20 > map.wallrecty3.y - 0.4) && (y + 20 < map.wallrecty3.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty3.x) && (x + 20 <= map.wallrecty3.x + 70) && (y + 20 > map.wallrecty3.y + 280 - 0.4) && (y + 20 < map.wallrecty3.y + 280 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            //////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx1.x + 0.4) && (x + 20 >= map.wallrectx1.x - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx1.x + 280 + 0.4) && (x + 20 >= map.wallrectx1.x + 280 - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y - 0.4) && (y + 20 < map.wallrectx1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y + 70 - 0.4) && (y + 20 < map.wallrectx1.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////
        }

        if (map.cn == 3)
        {
            //chap
            if ((x + 20 <= map.wallrecty1.x + 0.4) && (x + 20 >= map.wallrecty1.x - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty1.x + 70 + 0.4) && (x + 20 >= map.wallrecty1.x + 70 - 0.4) && (y + 20 > map.wallrecty1.y) && (y + 20 < map.wallrecty1.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y - 0.4) && (y + 20 < map.wallrecty1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty1.x) && (x + 20 <= map.wallrecty1.x + 70) && (y + 20 > map.wallrecty1.y + 280 - 0.4) && (y + 20 < map.wallrecty1.y + 280 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrecty2.x + 0.4) && (x + 20 >= map.wallrecty2.x - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrecty2.x + 70 + 0.4) && (x + 20 >= map.wallrecty2.x + 70 - 0.4) && (y + 20 > map.wallrecty2.y) && (y + 20 < map.wallrecty2.y + 280))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y - 0.4) && (y + 20 < map.wallrecty2.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrecty2.x) && (x + 20 <= map.wallrecty2.x + 70) && (y + 20 > map.wallrecty2.y + 280 - 0.4) && (y + 20 < map.wallrecty2.y + 280 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            //////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx1.x + 0.4) && (x + 20 >= map.wallrectx1.x - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx1.x + 280 + 0.4) && (x + 20 >= map.wallrectx1.x + 280 - 0.4) && (y + 20 > map.wallrectx1.y) && (y + 20 < map.wallrectx1.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y - 0.4) && (y + 20 < map.wallrectx1.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx1.x) && (x + 20 <= map.wallrectx1.x + 280) && (y + 20 > map.wallrectx1.y + 70 - 0.4) && (y + 20 < map.wallrectx1.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx2.x + 0.4) && (x + 20 >= map.wallrectx2.x - 0.4) && (y + 20 > map.wallrectx2.y) && (y + 20 < map.wallrectx2.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx2.x + 280 + 0.4) && (x + 20 >= map.wallrectx2.x + 280 - 0.4) && (y + 20 > map.wallrectx2.y) && (y + 20 < map.wallrectx2.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx2.x) && (x + 20 <= map.wallrectx2.x + 280) && (y + 20 > map.wallrectx2.y - 0.4) && (y + 20 < map.wallrectx2.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx2.x) && (x + 20 <= map.wallrectx2.x + 280) && (y + 20 > map.wallrectx2.y + 70 - 0.4) && (y + 20 < map.wallrectx2.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx3.x + 0.4) && (x + 20 >= map.wallrectx3.x - 0.4) && (y + 20 > map.wallrectx3.y) && (y + 20 < map.wallrectx3.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx3.x + 280 + 0.4) && (x + 20 >= map.wallrectx3.x + 280 - 0.4) && (y + 20 > map.wallrectx3.y) && (y + 20 < map.wallrectx3.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx3.x) && (x + 20 <= map.wallrectx3.x + 280) && (y + 20 > map.wallrectx3.y - 0.4) && (y + 20 < map.wallrectx3.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx3.x) && (x + 20 <= map.wallrectx3.x + 280) && (y + 20 > map.wallrectx3.y + 70 - 0.4) && (y + 20 < map.wallrectx3.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx4.x + 0.4) && (x + 20 >= map.wallrectx4.x - 0.4) && (y + 20 > map.wallrectx4.y) && (y + 20 < map.wallrectx4.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx4.x + 280 + 0.4) && (x + 20 >= map.wallrectx4.x + 280 - 0.4) && (y + 20 > map.wallrectx4.y) && (y + 20 < map.wallrectx4.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx4.x) && (x + 20 <= map.wallrectx4.x + 280) && (y + 20 > map.wallrectx4.y - 0.4) && (y + 20 < map.wallrectx4.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx4.x) && (x + 20 <= map.wallrectx4.x + 280) && (y + 20 > map.wallrectx4.y + 70 - 0.4) && (y + 20 < map.wallrectx4.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx5.x + 0.4) && (x + 20 >= map.wallrectx5.x - 0.4) && (y + 20 > map.wallrectx5.y) && (y + 20 < map.wallrectx5.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx5.x + 280 + 0.4) && (x + 20 >= map.wallrectx5.x + 280 - 0.4) && (y + 20 > map.wallrectx5.y) && (y + 20 < map.wallrectx5.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx5.x) && (x + 20 <= map.wallrectx5.x + 280) && (y + 20 > map.wallrectx5.y - 0.4) && (y + 20 < map.wallrectx5.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx5.x) && (x + 20 <= map.wallrectx5.x + 280) && (y + 20 > map.wallrectx5.y + 70 - 0.4) && (y + 20 < map.wallrectx5.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////

            //chap
            if ((x + 20 <= map.wallrectx6.x + 0.4) && (x + 20 >= map.wallrectx6.x - 0.4) && (y + 20 > map.wallrectx6.y) && (y + 20 < map.wallrectx6.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //rast
            if ((x + 20 <= map.wallrectx6.x + 280 + 0.4) && (x + 20 >= map.wallrectx6.x + 280 - 0.4) && (y + 20 > map.wallrectx6.y) && (y + 20 < map.wallrectx6.y + 70))
            {
                Mix_PlayChannel(-1, BR, 0);
                xdelta *= -1;
            }
            //bala
            if ((x + 20 >= map.wallrectx6.x) && (x + 20 <= map.wallrectx6.x + 280) && (y + 20 > map.wallrectx6.y - 0.4) && (y + 20 < map.wallrectx6.y + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
            //pain
            if ((x + 20 >= map.wallrectx6.x) && (x + 20 <= map.wallrectx6.x + 280) && (y + 20 > map.wallrectx6.y + 70 - 0.4) && (y + 20 < map.wallrectx6.y + 70 + 0.4))
            {
                Mix_PlayChannel(-1, BR, 0);
                ydelta *= -1;
            }
        }
    }
    void Reloading()
    {
        if( gtank1.BulletFlag == true)
        {
            gtank1.bullet = 0;
        }
        else if( gtank2.BulletFlag == true)
        {
            gtank2.bullet = 0;
        }
    }


} gbullet1[6], gbullet2[6];
