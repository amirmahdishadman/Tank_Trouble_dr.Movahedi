#include <iostream>
#include "wall.h"
#include <ctime>
#include <SDL2/SDL.h>
using namespace std;
const int SCREEN_WIDTH = 1012;
const int SCREEN_HEIGHT = 612;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Color color = {200, 100, 255};
void Init()
{
    gWindow = SDL_CreateWindow("tank trouble", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}
//generate the walls.
void map()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 12, 55, 255);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (gwallh[i][j].flag == 1)
            {
                for (int k = 1; k <= 4; k++)
                {
                    SDL_RenderDrawLine(gRenderer, gwallh[i][j].xstart,gwallh[i][j].ystart + k - 2, gwallh[i][j].xend,gwallh[i][j].yend + k - 2);
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (gwallv[i][j].flag == 1)
            {
                for (int k = 1; k <= 4; k++)
                {
                    SDL_RenderDrawLine(gRenderer, gwallv[i][j].xstart + k - 2, gwallv[i][j].ystart, gwallv[i][j].xend + k - 2, gwallv[i][j].yend);
                }
            }
        }
    }
}
//set the color of the lines and
void cover()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 100, 100, 0);
    for (int i = 0; i < 6; i++)
    {
        SDL_RenderDrawLine(gRenderer, 0, i, 912, i);
        SDL_RenderDrawLine(gRenderer, i, 0, i, 612);
        SDL_RenderDrawLine(gRenderer, 0, 607 + i, 912, 607 + i);
        SDL_RenderDrawLine(gRenderer, 912 - i, 0, 912 - i, 612);
    }
}

void InitMap()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            gwallh[i][j].random();
            gwallh[i][j].xstart = 6 + (j * 100) - 1;
            gwallh[i][j].ystart = 6 + ((i + 1) * 100);
            gwallh[i][j].yend = 6 + ((i + 1) * 100);
            gwallh[i][j].xend = 6 + ((j + 1) * 100) + 2;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gwallv[i][j].random();
            gwallv[i][j].xstart = 6 + ((j + 1) * 100);
            gwallv[i][j].xend = 6 + ((j + 1) * 100);
            gwallv[i][j].ystart = 6 + (i * 100) - 1;
            gwallv[i][j].yend = 6 + ((i + 1) * 100) + 2;
        }
    }
}
int main()
{
     srand(time(0));
     Init();
     InitMap();
     //this loop will fill with tank lose .
     while(true){
     SDL_RenderPresent(gRenderer);
     cover();
     map();
    }
    return 0;
}