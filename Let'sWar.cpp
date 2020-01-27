#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include "tank.h"
#include "Bullet.h"
#include "Laser.h"


using namespace std;


//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 790;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Surface for loading png images (except map)
SDL_Surface* gSurface1 = NULL; //tank1
SDL_Surface* gSurface2 = NULL; //tank2
SDL_Surface* gSurface3 = NULL; //laser
SDL_Surface* gSurface = NULL; //Numbers
SDL_Surface* gSurface5 = NULL; // extra ammo
SDL_Surface* gSurface6 = NULL; //For winning


//The image we will load and show on the screen
SDL_Surface* Wallsurface= NULL;
SDL_Surface* background=NULL;

//Textures
SDL_Texture* gTexture1 = NULL, * gTexture2 = NULL;
SDL_Texture* glaser = NULL;
SDL_Texture* gTF1 = NULL; //Texture for the font of tank1 score
SDL_Texture* gTF2 = NULL; //Texture for the font of tank2 score
SDL_Texture* gborderx1 = NULL;
SDL_Texture* gborderx2= NULL;
SDL_Texture* gbordery1 = NULL;
SDL_Texture* gbordery2 = NULL;
SDL_Texture* gbackgroundT = NULL;
SDL_Texture* walltexture_x1= NULL;
SDL_Texture* walltexture_x2= NULL;
SDL_Texture* walltexture_x3= NULL;
SDL_Texture* walltexture_x4= NULL;
SDL_Texture* walltexture_x5= NULL;
SDL_Texture* walltexture_x6= NULL;
SDL_Texture* walltexture_y1= NULL;
SDL_Texture* walltexture_y2= NULL;
SDL_Texture* walltexture_y3= NULL;
SDL_Texture* walltexture_y4= NULL;
SDL_Texture* walltexture_y5= NULL;
SDL_Texture* walltexture_y6= NULL;
SDL_Texture* ammotexture = NULL;//For Extera Ammo
SDL_Texture* WinTexture1 = NULL;
SDL_Texture* WinTexture2 = NULL;

//Score Textures
SDL_Texture* T0 = NULL;
SDL_Texture* T1 = NULL;
SDL_Texture* T2 = NULL;
SDL_Texture* T3 = NULL;
SDL_Texture* T4 = NULL;
SDL_Texture* T5 = NULL;
SDL_Texture* T6 = NULL;
SDL_Texture* T7 = NULL;


//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//rects
SDL_Rect grect1;
SDL_Rect grect2; 
SDL_Rect LaserRect;
SDL_Rect BulletRect;
SDL_Rect backrect={0,0,1280,790};
SDL_Rect scoreRect1 = {150, 740, 30, 30}; //grect for the font of tank1 score 
SDL_Rect scoreRect2 = {1090, 740, 30, 30};//grect for the font of tank2 score 
SDL_Rect WinRect = {0, 0, 1280, 720};

//Musics and Audios
Mix_Music *gMusic = NULL;
Mix_Chunk *TB = NULL;//Tank Bullet sound
Mix_Chunk *Reloading = NULL;// Tank bullets reloading

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Let's war", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		//Initialise SDL_mixer and Music
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		gMusic = Mix_LoadMUS("Lose-Yourself.wav");
		TB = Mix_LoadWAV("Tank Bullet.wav");
		TE = Mix_LoadWAV("Tank explosion.wav");
		BR = Mix_LoadWAV("Bullet reflect.wav");
		Reloading = Mix_LoadWAV("Reload.wav");

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
		    //gScreenSurface = SDL_GetWindowSurface( gWindow );
			gSurface1 = gSurface1 = SDL_LoadBMP("tank1.bmp");
   			gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
    		gSurface2 = gSurface2 = SDL_LoadBMP("tank2.bmp");
  			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface2);
			gSurface3 = SDL_LoadBMP("pointer.bmp");
    		glaser = SDL_CreateTextureFromSurface(gRenderer, gSurface3);
			gSurface5 = SDL_LoadBMP("Extra Bullet.bmp");
			ammotexture = SDL_CreateTextureFromSurface(gRenderer, gSurface5);
			gSurface = SDL_LoadBMP("Numbers/0.bmp");
			T0 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/1.bmp");
			T1 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/2.bmp");
			T2 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/3.bmp");
			T3 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/4.bmp");
			T4 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/5.bmp");
			T5 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/6.bmp");
			T6 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
			gSurface = SDL_LoadBMP("Numbers/7.bmp");
			T7 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
            gSurface6 = SDL_LoadBMP("T1.bmp");
            WinTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface6);
            gSurface6 = SDL_LoadBMP("T2.bmp");
            WinTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface6);

	  		gtank1.x = 125;
    		gtank1.y = 55;
			grect1.x = gtank1.x;
			grect1.y = gtank1.y;
    
        	gtank2.x = 1090;
        	gtank2.y = 618;
			grect2.x = gtank2.x;
			grect2.y = gtank2.y;
		}
	}

	return success;
}

void loadMedia(int cn)
{
	//Load random image
  			background = SDL_LoadBMP("background.bmp");
   			gbackgroundT = SDL_CreateTextureFromSurface(gRenderer, background);
			background=SDL_LoadBMP("xborder.bmp");
			gborderx1 = SDL_CreateTextureFromSurface(gRenderer, background);
			gborderx2 = SDL_CreateTextureFromSurface(gRenderer, background);
			background=SDL_LoadBMP("yborder.bmp");
			gbordery1 = SDL_CreateTextureFromSurface(gRenderer, background);
			gbordery2 = SDL_CreateTextureFromSurface(gRenderer, background);
 	if (cn == 1)
    {

        map.wallrecty1.h = 200;
        map.wallrecty2.h = 200;

        map.wallrecty4.h = 200;
        map.wallrecty5.h = 200;
        map.wallrecty3.h = 210;

        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y3 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y4 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y5 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

        map.wallrectx1.x = 500;
        map.wallrectx1.y = 75;

        map.wallrectx2.x = 500;
        map.wallrectx2.y = 575;

        map.wallrecty1.x = 215;
        map.wallrecty1.y = 106.7;

        map.wallrecty2.x = 215;
        map.wallrecty2.y = 413.4;

        map.wallrecty3.x = 605;
        map.wallrecty3.y = 255;

        map.wallrecty4.x = 995;
        map.wallrecty4.y = 106.7;
        ;

        map.wallrecty5.x = 995;
        map.wallrecty5.y = 413.4;
    }

    if (cn == 2)
    {
        map.wallrecty1.h = 200;
        map.wallrecty2.h = 200;

        map.wallrecty4.h = 200;
        map.wallrecty5.h = 200;

        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y3 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y4 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y5 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

        map.wallrecty1.x = 267.5;
        map.wallrecty1.y = 106.7;

        map.wallrecty2.x = 380;
        map.wallrecty2.y = 413.4;

        map.wallrecty3.x = 605;
        map.wallrecty3.y = 106.6;

        map.wallrecty4.x = 942.5;
        map.wallrecty4.y = 106.7;
        ;

        map.wallrecty5.x = 830;
        map.wallrecty5.y = 413.4;
    }

    if (cn == 3)
    {
        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x3 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wallx.bmp");
        walltexture_x4 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
        Wallsurface = SDL_LoadBMP("wally.bmp");
        walltexture_y2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

        map.wallrectx1.x = 116;
        map.wallrectx1.y = 150;

        map.wallrectx2.x = 884;
        map.wallrectx2.y = 150;

        map.wallrectx3.x = 884;
        map.wallrectx3.y = 500;

        map.wallrectx4.x = 116;
        map.wallrectx4.y = 500;

        map.wallrecty1.x = 512;
        map.wallrecty1.y = 220;

        map.wallrecty2.x = 698;
        map.wallrecty2.y = 220;
    }
}



//movements of tanks

void tankmoveup1()
{

    //map1 collision of walls
    if (map.cn == 1)
    {
        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < -90 && degree1 > -180)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 0 && degree1 > -90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 180 && degree1 > 90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > 0)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {
                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 < 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x += gtank1.dx;
                            gtank1.y -= gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 > 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x += gtank1.dx;
                                gtank1.y -= gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty1) == true && (degree1 > 90 || degree1 < -90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x += gtank1.dx;
                                    gtank1.y -= gtank1.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > -90)
                                    {
                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                        gtank1.dx = 0;
                                        gtank1.x += gtank1.dx;
                                        gtank1.y -= gtank1.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x += gtank1.dx;
                                            gtank1.y -= gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank1.dy = 0;
                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                gtank1.x += gtank1.dx;
                                                gtank1.y -= gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x += gtank1.dx;
                                                    gtank1.y -= gtank1.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                        gtank1.dx = 0;
                                                        gtank1.x += gtank1.dx;
                                                        gtank1.y -= gtank1.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x += gtank1.dx;
                                                            gtank1.y -= gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank1.dy = 0;
                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                gtank1.x += gtank1.dx;
                                                                gtank1.y -= gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x += gtank1.dx;
                                                                    gtank1.y -= gtank1.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                        gtank1.dx = 0;
                                                                        gtank1.x += gtank1.dx;
                                                                        gtank1.y -= gtank1.dy;
                                                                    } //wally1
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x += gtank1.dx;
                                                                            gtank1.y -= gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                            {
                                                                                gtank1.dy = 0;
                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                gtank1.x += gtank1.dx;
                                                                                gtank1.y -= gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                    gtank1.dx = 0;
                                                                                    gtank1.x += gtank1.dx;
                                                                                    gtank1.y -= gtank1.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                                                    {
                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                        gtank1.dx = 0;
                                                                                        gtank1.x += gtank1.dx;
                                                                                        gtank1.y -= gtank1.dy;
                                                                                    } //wally2
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x += gtank1.dx;
                                                                                            gtank1.y -= gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                            {
                                                                                                gtank1.dy = 0;
                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                gtank1.x += gtank1.dx;
                                                                                                gtank1.y -= gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x += gtank1.dx;
                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                                                    {
                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                        gtank1.dx = 0;
                                                                                                        gtank1.x += gtank1.dx;
                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                    } //wally3
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                                                        {
                                                                                                            gtank1.dy = 0;
                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                            gtank1.x += gtank1.dx;
                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                                                            {
                                                                                                                gtank1.dy = 0;
                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty3.x + 35)
                                                                                                                {
                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                    gtank1.dx = 0;
                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty3.x + 35)
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0;
                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                    } //wally4
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                                                        {
                                                                                                                            gtank1.dy = 0;
                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                            gtank1.x += gtank1.dx;
                                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                                                            {
                                                                                                                                gtank1.dy = 0;
                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                                            }
                                                                                                                            else
                                                                                                                            {
                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty4.x + 35)
                                                                                                                                {
                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                    gtank1.dx = 0;
                                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                                }
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty4.x + 35)
                                                                                                                                    {
                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                        gtank1.dx = 0;
                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                    } //wally5
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank1.dy = 0;
                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                            gtank1.x += gtank1.dx;
                                                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank1.dy = 0;
                                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty5.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty5.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.dx = 0;
                                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                                    } //default
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 2)
    {

        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < -90 && degree1 > -180)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 0 && degree1 > -90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 180 && degree1 > 90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > 0)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 < 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x += gtank1.dx;
                            gtank1.y -= gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 > 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x += gtank1.dx;
                                gtank1.y -= gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty1) == true && (degree1 > 90 || degree1 < -90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x += gtank1.dx;
                                    gtank1.y -= gtank1.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > -90)
                                    {
                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                        gtank1.dx = 0;
                                        gtank1.x += gtank1.dx;
                                        gtank1.y -= gtank1.dy;
                                    } //wallx1

                                    else
                                    {
                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x += gtank1.dx;
                                            gtank1.y -= gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                            {
                                                gtank1.dy = 0;
                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                gtank1.x += gtank1.dx;
                                                gtank1.y -= gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x += gtank1.dx;
                                                    gtank1.y -= gtank1.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                    {
                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                        gtank1.dx = 0;
                                                        gtank1.x += gtank1.dx;
                                                        gtank1.y -= gtank1.dy;
                                                    } //wally2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x += gtank1.dx;
                                                            gtank1.y -= gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                            {
                                                                gtank1.dy = 0;
                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                gtank1.x += gtank1.dx;
                                                                gtank1.y -= gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x += gtank1.dx;
                                                                    gtank1.y -= gtank1.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                    {
                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                        gtank1.dx = 0;
                                                                        gtank1.x += gtank1.dx;
                                                                        gtank1.y -= gtank1.dy;
                                                                    } //wally3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x += gtank1.dx;
                                                                            gtank1.y -= gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                            {
                                                                                gtank1.dy = 0;
                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                gtank1.x += gtank1.dx;
                                                                                gtank1.y -= gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty3.x + 35)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                    gtank1.dx = 0;
                                                                                    gtank1.x += gtank1.dx;
                                                                                    gtank1.y -= gtank1.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty3.x + 35)
                                                                                    {
                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                        gtank1.dx = 0;
                                                                                        gtank1.x += gtank1.dx;
                                                                                        gtank1.y -= gtank1.dy;
                                                                                    } //wally4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x += gtank1.dx;
                                                                                            gtank1.y -= gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                            {
                                                                                                gtank1.dy = 0;
                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                gtank1.x += gtank1.dx;
                                                                                                gtank1.y -= gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty4.x + 35)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x += gtank1.dx;
                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty4.x + 35)
                                                                                                    {
                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                        gtank1.dx = 0;
                                                                                                        gtank1.x += gtank1.dx;
                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                    } //wally5
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                        {
                                                                                                            gtank1.dy = 0;
                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                            gtank1.x += gtank1.dx;
                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                            {
                                                                                                                gtank1.dy = 0;
                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty5.x + 35)
                                                                                                                {
                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                    gtank1.dx = 0;
                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty5.x + 35)
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0;
                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                    } //default
                                                                                                                    else
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 3)
    {

        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < -90 && degree1 > -180)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 0 && degree1 > -90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 180 && degree1 > 90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > 0)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 < 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x += gtank1.dx;
                            gtank1.y -= gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 > 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x += gtank1.dx;
                                gtank1.y -= gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty1) == true && (degree1 > 90 || degree1 < -90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x += gtank1.dx;
                                    gtank1.y -= gtank1.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 90 && degree1 > -90)
                                    {
                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                        gtank1.dx = 0;
                                        gtank1.x += gtank1.dx;
                                        gtank1.y -= gtank1.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x += gtank1.dx;
                                            gtank1.y -= gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank1.dy = 0;
                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                gtank1.x += gtank1.dx;
                                                gtank1.y -= gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x += gtank1.dx;
                                                    gtank1.y -= gtank1.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                        gtank1.dx = 0;
                                                        gtank1.x += gtank1.dx;
                                                        gtank1.y -= gtank1.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x += gtank1.dx;
                                                            gtank1.y -= gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank1.dy = 0;
                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                gtank1.x += gtank1.dx;
                                                                gtank1.y -= gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x += gtank1.dx;
                                                                    gtank1.y -= gtank1.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                        gtank1.dx = 0;
                                                                        gtank1.x += gtank1.dx;
                                                                        gtank1.y -= gtank1.dy;
                                                                    } //wallx3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx3.y && gtank1.x + 36 > map.wallrectx3.x && gtank1.x + 5 < map.wallrectx3.x + 280)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x += gtank1.dx;
                                                                            gtank1.y -= gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx3.y && gtank1.x + 36 > map.wallrectx3.x && gtank1.x + 5 < map.wallrectx3.x + 280)
                                                                            {
                                                                                gtank1.dy = 0;
                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                gtank1.x += gtank1.dx;
                                                                                gtank1.y -= gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx3.x + 150)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                    gtank1.dx = 0;
                                                                                    gtank1.x += gtank1.dx;
                                                                                    gtank1.y -= gtank1.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx3.x + 150)
                                                                                    {
                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                        gtank1.dx = 0;
                                                                                        gtank1.x += gtank1.dx;
                                                                                        gtank1.y -= gtank1.dy;
                                                                                    } //wallx4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 > 0 && gtank1.y - 5 < map.wallrectx4.y && gtank1.x + 36 > map.wallrectx4.x && gtank1.x + 5 < map.wallrectx4.x + 280)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x += gtank1.dx;
                                                                                            gtank1.y -= gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 < 0 && gtank1.y + 5 > map.wallrectx4.y && gtank1.x + 36 > map.wallrectx4.x && gtank1.x + 5 < map.wallrectx4.x + 280)
                                                                                            {
                                                                                                gtank1.dy = 0;
                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                gtank1.x += gtank1.dx;
                                                                                                gtank1.y -= gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrectx4.x + 150)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x += gtank1.dx;
                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrectx4.x + 150)
                                                                                                    {
                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                        gtank1.dx = 0;
                                                                                                        gtank1.x += gtank1.dx;
                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                    } //wa
																									 else
                                                                                                        {
                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank1.dy = 0;
                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                            gtank1.x += gtank1.dx;
                                                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank1.dy = 0;
                                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.dx = 0;
                                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                                    } //wally2
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                        {
                                                                                                                                                            gtank1.dy = 0;
                                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                            gtank1.x += gtank1.dx;
                                                                                                                                                            gtank1.y -= gtank1.dy;
                                                                                                                                                        }
                                                                                                                                                        else
                                                                                                                                                        {
                                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                            {
                                                                                                                                                                gtank1.dy = 0;
                                                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                                gtank1.x += gtank1.dx;
                                                                                                                                                                gtank1.y -= gtank1.dy;
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 > 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                                                                                                                {
                                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                                    gtank1.x += gtank1.dx;
                                                                                                                                                                    gtank1.y -= gtank1.dy;
                                                                                                                                                                }
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                                                                                                                    {
                                                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                        gtank1.dx = 0;
                                                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                                                    } //default
                                                                                                                                                                    else
                                                                                                                                                                    {
                                                                                                                                                                        gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                                        gtank1.x += gtank1.dx;
                                                                                                                                                                        gtank1.y -= gtank1.dy;
                                                                                                                                                            
                                                                                                                                                                
                                                                                                                                                            
                                                                                                                                                        
                                                                                                                                                    
                                                                                                                                                
                                                                                                                                            
                                                                                                                                        
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tankmoveup2()
{
    //map1 collision of walls
    if (map.cn == 1)
    {

        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < -90 && degree2 > -180)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 0 && degree2 > -90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 180 && degree2 > 90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > 0)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 < 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x += gtank2.dx;
                            gtank2.y -= gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 > 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x += gtank2.dx;
                                gtank2.y -= gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > 90 || degree2 < -90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x += gtank2.dx;
                                    gtank2.y -= gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > -90)
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x += gtank2.dx;
                                        gtank2.y -= gtank2.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x += gtank2.dx;
                                            gtank2.y -= gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x += gtank2.dx;
                                                gtank2.y -= gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x += gtank2.dx;
                                                    gtank2.y -= gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x += gtank2.dx;
                                                        gtank2.y -= gtank2.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x += gtank2.dx;
                                                            gtank2.y -= gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x += gtank2.dx;
                                                                gtank2.y -= gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x += gtank2.dx;
                                                                    gtank2.y -= gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x += gtank2.dx;
                                                                        gtank2.y -= gtank2.dy;
                                                                    } //wally1
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x += gtank2.dx;
                                                                            gtank2.y -= gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x += gtank2.dx;
                                                                                gtank2.y -= gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x += gtank2.dx;
                                                                                    gtank2.y -= gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x += gtank2.dx;
                                                                                        gtank2.y -= gtank2.dy;
                                                                                    } //wally2
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x += gtank2.dx;
                                                                                            gtank2.y -= gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x += gtank2.dx;
                                                                                                gtank2.y -= gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x += gtank2.dx;
                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x += gtank2.dx;
                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                    } //wally3
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                                                        {
                                                                                                            gtank2.dy = 0;
                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                            gtank2.x += gtank2.dx;
                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                                                            {
                                                                                                                gtank2.dy = 0;
                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty3.x + 35)
                                                                                                                {
                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                    gtank2.dx = 0;
                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty3.x + 35)
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0;
                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                    } //wally4
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                                                        {
                                                                                                                            gtank2.dy = 0;
                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                            gtank2.x += gtank2.dx;
                                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                                                            {
                                                                                                                                gtank2.dy = 0;
                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                                            }
                                                                                                                            else
                                                                                                                            {
                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty4.x + 35)
                                                                                                                                {
                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                    gtank2.dx = 0;
                                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                                }
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty4.x + 35)
                                                                                                                                    {
                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                        gtank2.dx = 0;
                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                    } //wally5
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank2.dy = 0;
                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                            gtank2.x += gtank2.dx;
                                                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty5.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty5.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                                    } //default
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 2)
    {

        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < -90 && degree2 > -180)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 0 && degree2 > -90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 180 && degree2 > 90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > 0)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 < 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x += gtank2.dx;
                            gtank2.y -= gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 > 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x += gtank2.dx;
                                gtank2.y -= gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > 90 || degree2 < -90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x += gtank2.dx;
                                    gtank2.y -= gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > -90)
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x += gtank2.dx;
                                        gtank2.y -= gtank2.dy;
                                    } //wallx1

                                    else
                                    {
                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x += gtank2.dx;
                                            gtank2.y -= gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x += gtank2.dx;
                                                gtank2.y -= gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x += gtank2.dx;
                                                    gtank2.y -= gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x += gtank2.dx;
                                                        gtank2.y -= gtank2.dy;
                                                    } //wally2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x += gtank2.dx;
                                                            gtank2.y -= gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x += gtank2.dx;
                                                                gtank2.y -= gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x += gtank2.dx;
                                                                    gtank2.y -= gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x += gtank2.dx;
                                                                        gtank2.y -= gtank2.dy;
                                                                    } //wally3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x += gtank2.dx;
                                                                            gtank2.y -= gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x += gtank2.dx;
                                                                                gtank2.y -= gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty3.x + 35)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x += gtank2.dx;
                                                                                    gtank2.y -= gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty3.x + 35)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x += gtank2.dx;
                                                                                        gtank2.y -= gtank2.dy;
                                                                                    } //wally4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x += gtank2.dx;
                                                                                            gtank2.y -= gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x += gtank2.dx;
                                                                                                gtank2.y -= gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty4.x + 35)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x += gtank2.dx;
                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty4.x + 35)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x += gtank2.dx;
                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                    } //wally5
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                        {
                                                                                                            gtank2.dy = 0;
                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                            gtank2.x += gtank2.dx;
                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                            {
                                                                                                                gtank2.dy = 0;
                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty5.x + 35)
                                                                                                                {
                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                    gtank2.dx = 0;
                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty5.x + 35)
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0;
                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                    } //default
                                                                                                                    else
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 3)
    {

        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < -90 && degree2 > -180)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 0 && degree2 > -90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 180 && degree2 > 90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > 0)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 < 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x += gtank2.dx;
                            gtank2.y -= gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 > 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x += gtank2.dx;
                                gtank2.y -= gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > 90 || degree2 < -90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x += gtank2.dx;
                                    gtank2.y -= gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 90 && degree2 > -90)
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x += gtank2.dx;
                                        gtank2.y -= gtank2.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x += gtank2.dx;
                                            gtank2.y -= gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x += gtank2.dx;
                                                gtank2.y -= gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x += gtank2.dx;
                                                    gtank2.y -= gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x += gtank2.dx;
                                                        gtank2.y -= gtank2.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x += gtank2.dx;
                                                            gtank2.y -= gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x += gtank2.dx;
                                                                gtank2.y -= gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x += gtank2.dx;
                                                                    gtank2.y -= gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x += gtank2.dx;
                                                                        gtank2.y -= gtank2.dy;
                                                                    } //wallx3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx3.y && gtank2.x + 36 > map.wallrectx3.x && gtank2.x + 5 < map.wallrectx3.x + 280)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x += gtank2.dx;
                                                                            gtank2.y -= gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx3.y && gtank2.x + 36 > map.wallrectx3.x && gtank2.x + 5 < map.wallrectx3.x + 280)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x += gtank2.dx;
                                                                                gtank2.y -= gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx3.x + 150)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x += gtank2.dx;
                                                                                    gtank2.y -= gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx3.x + 150)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x += gtank2.dx;
                                                                                        gtank2.y -= gtank2.dy;
                                                                                    } //wallx4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 > 0 && gtank2.y - 5 < map.wallrectx4.y && gtank2.x + 36 > map.wallrectx4.x && gtank2.x + 5 < map.wallrectx4.x + 280)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x += gtank2.dx;
                                                                                            gtank2.y -= gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 < 0 && gtank2.y + 5 > map.wallrectx4.y && gtank2.x + 36 > map.wallrectx4.x && gtank2.x + 5 < map.wallrectx4.x + 280)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x += gtank2.dx;
                                                                                                gtank2.y -= gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrectx4.x + 150)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x += gtank2.dx;
                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrectx4.x + 150)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x += gtank2.dx;
                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                    } //wallx5
                                                                                                    else
                                                                                                    {
                                                                                                                                    
                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank2.dy = 0;
                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                            gtank2.x += gtank2.dx;
                                                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                                    } //wally2
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                        {
                                                                                                                                                            gtank2.dy = 0;
                                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                            gtank2.x += gtank2.dx;
                                                                                                                                                            gtank2.y -= gtank2.dy;
                                                                                                                                                        }
                                                                                                                                                        else
                                                                                                                                                        {
                                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                            {
                                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                                gtank2.x += gtank2.dx;
                                                                                                                                                                gtank2.y -= gtank2.dy;
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 > 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                                                                                                                {
                                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                                    gtank2.x += gtank2.dx;
                                                                                                                                                                    gtank2.y -= gtank2.dy;
                                                                                                                                                                }
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                                                                                                                    {
                                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                                                    } //default
                                                                                                                                                                    else
                                                                                                                                                                    {
                                                                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.x += gtank2.dx;
                                                                                                                                                                        gtank2.y -= gtank2.dy;
                                                                                                                                                                    
                                                                                                                                                                
                                                                                                                                                            
                                                                                                                                                        
                                                                                                                                                    
                                                                                                                                                
                                                                                                                                            
                                                                                                                                        
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tankmovedw1()
{
    //map1 collision of walls
    if (map.cn == 1)
    {

        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 90 && degree1 > 0)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 180 && degree1 > 90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 0 && degree1 > -90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < -90 && degree1 > -180)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 > 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x -= gtank1.dx;
                            gtank1.y += gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 < 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x -= gtank1.dx;
                                gtank1.y += gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty1) == true && (degree1 > -90 && degree1 < 90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x -= gtank1.dx;
                                    gtank1.y += gtank1.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && (degree1 > 90 || degree1 < -90))
                                    {
                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                        gtank1.dx = 0;
                                        gtank1.x -= gtank1.dx;
                                        gtank1.y += gtank1.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x -= gtank1.dx;
                                            gtank1.y += gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank1.dy = 0;
                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                gtank1.x -= gtank1.dx;
                                                gtank1.y += gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x -= gtank1.dx;
                                                    gtank1.y += gtank1.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                        gtank1.dx = 0;
                                                        gtank1.x -= gtank1.dx;
                                                        gtank1.y += gtank1.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x -= gtank1.dx;
                                                            gtank1.y += gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank1.dy = 0;
                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                gtank1.x -= gtank1.dx;
                                                                gtank1.y += gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x -= gtank1.dx;
                                                                    gtank1.y += gtank1.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                        gtank1.dx = 0;
                                                                        gtank1.x -= gtank1.dx;
                                                                        gtank1.y += gtank1.dy;
                                                                    } //wally1
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x -= gtank1.dx;
                                                                            gtank1.y += gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                            {
                                                                                gtank1.dy = 0;
                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                gtank1.x -= gtank1.dx;
                                                                                gtank1.y += gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                    gtank1.dx = 0;
                                                                                    gtank1.x -= gtank1.dx;
                                                                                    gtank1.y += gtank1.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                                                    {
                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                        gtank1.dx = 0;
                                                                                        gtank1.x -= gtank1.dx;
                                                                                        gtank1.y += gtank1.dy;
                                                                                    } //wally2
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x -= gtank1.dx;
                                                                                            gtank1.y += gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                            {
                                                                                                gtank1.dy = 0;
                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                gtank1.x -= gtank1.dx;
                                                                                                gtank1.y += gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                    gtank1.y += gtank1.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                                                    {
                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                        gtank1.dx = 0;
                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                        gtank1.y += gtank1.dy;
                                                                                                    } //wally3
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                                                        {
                                                                                                            gtank1.dy = 0;
                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                            gtank1.y += gtank1.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                                                            {
                                                                                                                gtank1.dy = 0;
                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                gtank1.y += gtank1.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty3.x + 35)
                                                                                                                {
                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                    gtank1.dx = 0;
                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty3.x + 35)
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0;
                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                    } //wally4
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                                                        {
                                                                                                                            gtank1.dy = 0;
                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                                            gtank1.y += gtank1.dy;
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                                                            {
                                                                                                                                gtank1.dy = 0;
                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                                gtank1.y += gtank1.dy;
                                                                                                                            }
                                                                                                                            else
                                                                                                                            {
                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty4.x + 35)
                                                                                                                                {
                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                    gtank1.dx = 0;
                                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                                }
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty4.x + 35)
                                                                                                                                    {
                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                        gtank1.dx = 0;
                                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                                    } //wally5
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank1.dy = 0;
                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                                                            gtank1.y += gtank1.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank1.dy = 0;
                                                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                                                gtank1.y += gtank1.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty5.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty5.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.dx = 0;
                                                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                                                    } //default
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 2)
    {

        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 90 && degree1 > 0)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 180 && degree1 > 90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 0 && degree1 > -90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < -90 && degree1 > -180)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 > 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x -= gtank1.dx;
                            gtank1.y += gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 < 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x -= gtank1.dx;
                                gtank1.y += gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty1) == true && (degree1 > -90 && degree1 < 90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x -= gtank1.dx;
                                    gtank1.y += gtank1.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && (degree1 > 90 || degree1 < -90))
                                    {
                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                        gtank1.dx = 0;
                                        gtank1.x -= gtank1.dx;
                                        gtank1.y += gtank1.dy;
                                    } //wallx1
                                    else
                                    {

                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x -= gtank1.dx;
                                            gtank1.y += gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                            {
                                                gtank1.dy = 0;
                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                gtank1.x -= gtank1.dx;
                                                gtank1.y += gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x -= gtank1.dx;
                                                    gtank1.y += gtank1.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                    {
                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                        gtank1.dx = 0;
                                                        gtank1.x -= gtank1.dx;
                                                        gtank1.y += gtank1.dy;
                                                    } //wally2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x -= gtank1.dx;
                                                            gtank1.y += gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                            {
                                                                gtank1.dy = 0;
                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                gtank1.x -= gtank1.dx;
                                                                gtank1.y += gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x -= gtank1.dx;
                                                                    gtank1.y += gtank1.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                    {
                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                        gtank1.dx = 0;
                                                                        gtank1.x -= gtank1.dx;
                                                                        gtank1.y += gtank1.dy;
                                                                    } //wally3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x -= gtank1.dx;
                                                                            gtank1.y += gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty3.y && gtank1.x + 36 > map.wallrecty3.x && gtank1.x + 5 < map.wallrecty3.x + 70)
                                                                            {
                                                                                gtank1.dy = 0;
                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                gtank1.x -= gtank1.dx;
                                                                                gtank1.y += gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty3.x + 35)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                    gtank1.dx = 0;
                                                                                    gtank1.x -= gtank1.dx;
                                                                                    gtank1.y += gtank1.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty3) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty3.x + 35)
                                                                                    {
                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                        gtank1.dx = 0;
                                                                                        gtank1.x -= gtank1.dx;
                                                                                        gtank1.y += gtank1.dy;
                                                                                    } //wally4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x -= gtank1.dx;
                                                                                            gtank1.y += gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty4.y && gtank1.x + 36 > map.wallrecty4.x && gtank1.x + 5 < map.wallrecty4.x + 70)
                                                                                            {
                                                                                                gtank1.dy = 0;
                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                gtank1.x -= gtank1.dx;
                                                                                                gtank1.y += gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty4.x + 35)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                    gtank1.y += gtank1.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty4) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty4.x + 35)
                                                                                                    {
                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                        gtank1.dx = 0;
                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                        gtank1.y += gtank1.dy;
                                                                                                    } //wally5
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                        {
                                                                                                            gtank1.dy = 0;
                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                            gtank1.y += gtank1.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty5.y && gtank1.x + 36 > map.wallrecty5.x && gtank1.x + 5 < map.wallrecty5.x + 70)
                                                                                                            {
                                                                                                                gtank1.dy = 0;
                                                                                                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                gtank1.y += gtank1.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty5.x + 35)
                                                                                                                {
                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                    gtank1.dx = 0;
                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty5) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty5.x + 35)
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0;
                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                    } //default
                                                                                                                    else
                                                                                                                    {
                                                                                                                        gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 3)
    {
        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 90 && degree1 > 0)
        {
            gtank1.dy = 0;
            gtank1.dx = 0;
            gtank1.x -= gtank1.dx;
            gtank1.y += gtank1.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < 180 && degree1 > 90)
            {
                gtank1.dy = 0;
                gtank1.dx = 0;
                gtank1.x -= gtank1.dx;
                gtank1.y += gtank1.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty1) == true && degree1 < 0 && degree1 > -90)
                {
                    gtank1.dy = 0;
                    gtank1.dx = 0;
                    gtank1.x -= gtank1.dx;
                    gtank1.y += gtank1.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && SDL_HasIntersection(&grect1, &map.borderrecty2) == true && degree1 < -90 && degree1 > -180)
                    {
                        gtank1.dy = 0;
                        gtank1.dx = 0;
                        gtank1.x -= gtank1.dx;
                        gtank1.y += gtank1.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect1, &map.borderrectx1) == true && degree1 > 0)
                        {
                            gtank1.dy = 0;
                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                            gtank1.x -= gtank1.dx;
                            gtank1.y += gtank1.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect1, &map.borderrectx2) == true && degree1 < 0)
                            {
                                gtank1.dy = 0;
                                gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                gtank1.x -= gtank1.dx;
                                gtank1.y += gtank1.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect1, &map.borderrecty2) == true && (degree1 > 90 || degree1 < -90))
                                {
                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                    gtank1.dx = 0;
                                    gtank1.x -= gtank1.dx;
                                    gtank1.y += gtank1.dy;
                                } //wallx1
                                else
                                {
                                    if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                    {
                                        gtank1.dy = 0;
                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                        gtank1.x -= gtank1.dx;
                                        gtank1.y += gtank1.dy;
                                    }
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx1.y && gtank1.x + 36 > map.wallrectx1.x && gtank1.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank1.dy = 0;
                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                            gtank1.x -= gtank1.dx;
                                            gtank1.y += gtank1.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx1.x + 150)
                                            {
                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                gtank1.dx = 0;
                                                gtank1.x -= gtank1.dx;
                                                gtank1.y += gtank1.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect1, &map.wallrectx1) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx1.x + 150)
                                                {
                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                    gtank1.dx = 0;
                                                    gtank1.x -= gtank1.dx;
                                                    gtank1.y += gtank1.dy;
                                                } //wallx2
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                    {
                                                        gtank1.dy = 0;
                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                        gtank1.x -= gtank1.dx;
                                                        gtank1.y += gtank1.dy;
                                                    }
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx2.y && gtank1.x + 36 > map.wallrectx2.x && gtank1.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank1.dy = 0;
                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                            gtank1.x -= gtank1.dx;
                                                            gtank1.y += gtank1.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx2.x + 150)
                                                            {
                                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                gtank1.dx = 0;
                                                                gtank1.x -= gtank1.dx;
                                                                gtank1.y += gtank1.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx2) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx2.x + 150)
                                                                {
                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                    gtank1.dx = 0;
                                                                    gtank1.x -= gtank1.dx;
                                                                    gtank1.y += gtank1.dy;
                                                                } //wallx3
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx3.y && gtank1.x + 36 > map.wallrectx3.x && gtank1.x + 5 < map.wallrectx3.x + 280)
                                                                    {
                                                                        gtank1.dy = 0;
                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                        gtank1.x -= gtank1.dx;
                                                                        gtank1.y += gtank1.dy;
                                                                    }
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx3.y && gtank1.x + 36 > map.wallrectx3.x && gtank1.x + 5 < map.wallrectx3.x + 280)
                                                                        {
                                                                            gtank1.dy = 0;
                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                            gtank1.x -= gtank1.dx;
                                                                            gtank1.y += gtank1.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx3.x + 150)
                                                                            {
                                                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                gtank1.dx = 0;
                                                                                gtank1.x -= gtank1.dx;
                                                                                gtank1.y += gtank1.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx3) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx3.x + 150)
                                                                                {
                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);

                                                                                } //wallx4
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 < 0 && gtank1.y - 5 < map.wallrectx4.y && gtank1.x + 36 > map.wallrectx4.x && gtank1.x + 5 < map.wallrectx4.x + 280)
                                                                                    {
                                                                                        gtank1.dy = 0;
                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                        gtank1.x -= gtank1.dx;
                                                                                        gtank1.y += gtank1.dy;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 > 0 && gtank1.y + 5 > map.wallrectx4.y && gtank1.x + 36 > map.wallrectx4.x && gtank1.x + 5 < map.wallrectx4.x + 280)
                                                                                        {
                                                                                            gtank1.dy = 0;
                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                            gtank1.x -= gtank1.dx;
                                                                                            gtank1.y += gtank1.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrectx4.x + 150)
                                                                                            {
                                                                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                gtank1.dx = 0;
                                                                                                gtank1.x -= gtank1.dx;
                                                                                                gtank1.y += gtank1.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrectx4) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrectx4.x + 150)
                                                                                                {
                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                    gtank1.dx = 0;
                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                    gtank1.y += gtank1.dy;
                                                                                                } //wallx5
                                                                                               
                                                                                                   
                                                                                                                                 //wally1
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                    {
                                                                                                                                        gtank1.dy = 0;
                                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty1.y && gtank1.x + 36 > map.wallrecty1.x && gtank1.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank1.dy = 0;
                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                                                            gtank1.y += gtank1.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty1.x + 35)
                                                                                                                                            {
                                                                                                                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                gtank1.dx = 0;
                                                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                                                gtank1.y += gtank1.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty1) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty1.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                                                } //wally2
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 < 0 && gtank1.y - 5 < map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                    {
                                                                                                                                                        gtank1.dy = 0;
                                                                                                                                                        gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                        gtank1.x -= gtank1.dx;
                                                                                                                                                        gtank1.y += gtank1.dy;
                                                                                                                                                    }
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 0 && gtank1.y + 5 > map.wallrecty2.y && gtank1.x + 36 > map.wallrecty2.x && gtank1.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                        {
                                                                                                                                                            gtank1.dy = 0;
                                                                                                                                                            gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                            gtank1.x -= gtank1.dx;
                                                                                                                                                            gtank1.y += gtank1.dy;
                                                                                                                                                        }
                                                                                                                                                        else
                                                                                                                                                        {
                                                                                                                                                            if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && (degree1 < 90 || degree1 < -90) && gtank1.x > map.wallrecty2.x + 35)
                                                                                                                                                            {
                                                                                                                                                                gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                gtank1.dx = 0;
                                                                                                                                                                gtank1.x -= gtank1.dx;
                                                                                                                                                                gtank1.y += gtank1.dy;
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (SDL_HasIntersection(&grect1, &map.wallrecty2) == true && degree1 > 90 && degree1 > -90 && gtank1.x < map.wallrecty2.x + 35)
                                                                                                                                                                {
                                                                                                                                                                    gtank1.dy = 0.1 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                    gtank1.dx = 0;
                                                                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                                                                } //default
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
                                                                                                                                                                    gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
                                                                                                                                                                    gtank1.x -= gtank1.dx;
                                                                                                                                                                    gtank1.y += gtank1.dy;
                                                                                                                                                                
                                                                                                                                                            
                                                                                                                                                        
                                                                                                                                                    
                                                                                                                                                
                                                                                                                                            
                                                                                                                                        
                                                                                                                                    
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tankmovedw2()
{
    //map1 collision of walls
    if (map.cn == 1)
    {
        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 90 && degree2 > 0)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 180 && degree2 > 90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 0 && degree2 > -90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < -90 && degree2 > -180)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 > 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x -= gtank2.dx;
                            gtank2.y += gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 < 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x -= gtank2.dx;
                                gtank2.y += gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > -90 && degree2 < 90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x -= gtank2.dx;
                                    gtank2.y += gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && (degree2 > 90 || degree2 < -90))
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x -= gtank2.dx;
                                        gtank2.y += gtank2.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x -= gtank2.dx;
                                            gtank2.y += gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x -= gtank2.dx;
                                                gtank2.y += gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x -= gtank2.dx;
                                                    gtank2.y += gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x -= gtank2.dx;
                                                        gtank2.y += gtank2.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x -= gtank2.dx;
                                                            gtank2.y += gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x -= gtank2.dx;
                                                                gtank2.y += gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x -= gtank2.dx;
                                                                    gtank2.y += gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x -= gtank2.dx;
                                                                        gtank2.y += gtank2.dy;
                                                                    } //wally1
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x -= gtank2.dx;
                                                                            gtank2.y += gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x -= gtank2.dx;
                                                                                gtank2.y += gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x -= gtank2.dx;
                                                                                    gtank2.y += gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x -= gtank2.dx;
                                                                                        gtank2.y += gtank2.dy;
                                                                                    } //wally2
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x -= gtank2.dx;
                                                                                            gtank2.y += gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x -= gtank2.dx;
                                                                                                gtank2.y += gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                    gtank2.y += gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                        gtank2.y += gtank2.dy;
                                                                                                    } //wally3
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                                                        {
                                                                                                            gtank2.dy = 0;
                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                            gtank2.y += gtank2.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                                                            {
                                                                                                                gtank2.dy = 0;
                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                gtank2.y += gtank2.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty3.x + 35)
                                                                                                                {
                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                    gtank2.dx = 0;
                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty3.x + 35)
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0;
                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                    } //wally4
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                                                        {
                                                                                                                            gtank2.dy = 0;
                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                                            gtank2.y += gtank2.dy;
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                                                            {
                                                                                                                                gtank2.dy = 0;
                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                                gtank2.y += gtank2.dy;
                                                                                                                            }
                                                                                                                            else
                                                                                                                            {
                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty4.x + 35)
                                                                                                                                {
                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                    gtank2.dx = 0;
                                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                                }
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty4.x + 35)
                                                                                                                                    {
                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                        gtank2.dx = 0;
                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                    } //wally5
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank2.dy = 0;
                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                                                            gtank2.y += gtank2.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                                                gtank2.y += gtank2.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty5.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty5.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                                    } //default
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 2)
    {
        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 90 && degree2 > 0)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 180 && degree2 > 90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 0 && degree2 > -90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < -90 && degree2 > -180)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 > 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x -= gtank2.dx;
                            gtank2.y += gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 < 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x -= gtank2.dx;
                                gtank2.y += gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > -90 && degree2 < 90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x -= gtank2.dx;
                                    gtank2.y += gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && (degree2 > 90 || degree2 < -90))
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x -= gtank2.dx;
                                        gtank2.y += gtank2.dy;
                                    } //wallx1
                                    else
                                    {

                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x -= gtank2.dx;
                                            gtank2.y += gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x -= gtank2.dx;
                                                gtank2.y += gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x -= gtank2.dx;
                                                    gtank2.y += gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x -= gtank2.dx;
                                                        gtank2.y += gtank2.dy;
                                                    } //wally2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x -= gtank2.dx;
                                                            gtank2.y += gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x -= gtank2.dx;
                                                                gtank2.y += gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x -= gtank2.dx;
                                                                    gtank2.y += gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x -= gtank2.dx;
                                                                        gtank2.y += gtank2.dy;
                                                                    } //wally3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x -= gtank2.dx;
                                                                            gtank2.y += gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty3.y && gtank2.x + 36 > map.wallrecty3.x && gtank2.x + 5 < map.wallrecty3.x + 70)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x -= gtank2.dx;
                                                                                gtank2.y += gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty3.x + 35)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x -= gtank2.dx;
                                                                                    gtank2.y += gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty3) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty3.x + 35)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x -= gtank2.dx;
                                                                                        gtank2.y += gtank2.dy;
                                                                                    } //wally4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x -= gtank2.dx;
                                                                                            gtank2.y += gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty4.y && gtank2.x + 36 > map.wallrecty4.x && gtank2.x + 5 < map.wallrecty4.x + 70)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x -= gtank2.dx;
                                                                                                gtank2.y += gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty4.x + 35)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                    gtank2.y += gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty4) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty4.x + 35)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                        gtank2.y += gtank2.dy;
                                                                                                    } //wally5
                                                                                                    else
                                                                                                    {
                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                        {
                                                                                                            gtank2.dy = 0;
                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                            gtank2.y += gtank2.dy;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty5.y && gtank2.x + 36 > map.wallrecty5.x && gtank2.x + 5 < map.wallrecty5.x + 70)
                                                                                                            {
                                                                                                                gtank2.dy = 0;
                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                gtank2.y += gtank2.dy;
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty5.x + 35)
                                                                                                                {
                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                    gtank2.dx = 0;
                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty5) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty5.x + 35)
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0;
                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                    } //default
                                                                                                                    else
                                                                                                                    {
                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (map.cn == 3)
    {

        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 90 && degree2 > 0)
        {
            gtank2.dy = 0;
            gtank2.dx = 0;
            gtank2.x -= gtank2.dx;
            gtank2.y += gtank2.dy;
        }
        else
        {
            if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < 180 && degree2 > 90)
            {
                gtank2.dy = 0;
                gtank2.dx = 0;
                gtank2.x -= gtank2.dx;
                gtank2.y += gtank2.dy;
            }
            else
            {
                if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty1) == true && degree2 < 0 && degree2 > -90)
                {
                    gtank2.dy = 0;
                    gtank2.dx = 0;
                    gtank2.x -= gtank2.dx;
                    gtank2.y += gtank2.dy;
                }
                else
                {
                    if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && SDL_HasIntersection(&grect2, &map.borderrecty2) == true && degree2 < -90 && degree2 > -180)
                    {
                        gtank2.dy = 0;
                        gtank2.dx = 0;
                        gtank2.x -= gtank2.dx;
                        gtank2.y += gtank2.dy;
                    } //wallx1
                    else
                    {

                        if (SDL_HasIntersection(&grect2, &map.borderrectx1) == true && degree2 > 0)
                        {
                            gtank2.dy = 0;
                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                            gtank2.x -= gtank2.dx;
                            gtank2.y += gtank2.dy;
                        }
                        else
                        {
                            if (SDL_HasIntersection(&grect2, &map.borderrectx2) == true && degree2 < 0)
                            {
                                gtank2.dy = 0;
                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                gtank2.x -= gtank2.dx;
                                gtank2.y += gtank2.dy;
                            }
                            else
                            {
                                if (SDL_HasIntersection(&grect2, &map.borderrecty1) == true && (degree2 > -90 && degree2 < 90))
                                {
                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                    gtank2.dx = 0;
                                    gtank2.x -= gtank2.dx;
                                    gtank2.y += gtank2.dy;
                                }
                                else
                                {
                                    if (SDL_HasIntersection(&grect2, &map.borderrecty2) == true && (degree2 > 90 || degree2 < -90))
                                    {
                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                        gtank2.dx = 0;
                                        gtank2.x -= gtank2.dx;
                                        gtank2.y += gtank2.dy;
                                    } //wallx1
                                    else
                                    {
                                        if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                        {
                                            gtank2.dy = 0;
                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                            gtank2.x -= gtank2.dx;
                                            gtank2.y += gtank2.dy;
                                        }
                                        else
                                        {
                                            if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx1.y && gtank2.x + 36 > map.wallrectx1.x && gtank2.x + 5 < map.wallrectx1.x + 280)
                                            {
                                                gtank2.dy = 0;
                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                gtank2.x -= gtank2.dx;
                                                gtank2.y += gtank2.dy;
                                            }
                                            else
                                            {
                                                if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx1.x + 150)
                                                {
                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                    gtank2.dx = 0;
                                                    gtank2.x -= gtank2.dx;
                                                    gtank2.y += gtank2.dy;
                                                }
                                                else
                                                {
                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx1) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx1.x + 150)
                                                    {
                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                        gtank2.dx = 0;
                                                        gtank2.x -= gtank2.dx;
                                                        gtank2.y += gtank2.dy;
                                                    } //wallx2
                                                    else
                                                    {
                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                        {
                                                            gtank2.dy = 0;
                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                            gtank2.x -= gtank2.dx;
                                                            gtank2.y += gtank2.dy;
                                                        }
                                                        else
                                                        {
                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx2.y && gtank2.x + 36 > map.wallrectx2.x && gtank2.x + 5 < map.wallrectx2.x + 280)
                                                            {
                                                                gtank2.dy = 0;
                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                gtank2.x -= gtank2.dx;
                                                                gtank2.y += gtank2.dy;
                                                            }
                                                            else
                                                            {
                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx2.x + 150)
                                                                {
                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                    gtank2.dx = 0;
                                                                    gtank2.x -= gtank2.dx;
                                                                    gtank2.y += gtank2.dy;
                                                                }
                                                                else
                                                                {
                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx2) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx2.x + 150)
                                                                    {
                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                        gtank2.dx = 0;
                                                                        gtank2.x -= gtank2.dx;
                                                                        gtank2.y += gtank2.dy;
                                                                    } //wallx3
                                                                    else
                                                                    {
                                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx3.y && gtank2.x + 36 > map.wallrectx3.x && gtank2.x + 5 < map.wallrectx3.x + 280)
                                                                        {
                                                                            gtank2.dy = 0;
                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                            gtank2.x -= gtank2.dx;
                                                                            gtank2.y += gtank2.dy;
                                                                        }
                                                                        else
                                                                        {
                                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx3.y && gtank2.x + 36 > map.wallrectx3.x && gtank2.x + 5 < map.wallrectx3.x + 280)
                                                                            {
                                                                                gtank2.dy = 0;
                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                gtank2.x -= gtank2.dx;
                                                                                gtank2.y += gtank2.dy;
                                                                            }
                                                                            else
                                                                            {
                                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx3.x + 150)
                                                                                {
                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                    gtank2.dx = 0;
                                                                                    gtank2.x -= gtank2.dx;
                                                                                    gtank2.y += gtank2.dy;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx3) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx3.x + 150)
                                                                                    {
                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                        gtank2.dx = 0;
                                                                                        gtank2.x -= gtank2.dx;
                                                                                        gtank2.y += gtank2.dy;
                                                                                    } //wallx4
                                                                                    else
                                                                                    {
                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 < 0 && gtank2.y - 5 < map.wallrectx4.y && gtank2.x + 36 > map.wallrectx4.x && gtank2.x + 5 < map.wallrectx4.x + 280)
                                                                                        {
                                                                                            gtank2.dy = 0;
                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                            gtank2.x -= gtank2.dx;
                                                                                            gtank2.y += gtank2.dy;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 > 0 && gtank2.y + 5 > map.wallrectx4.y && gtank2.x + 36 > map.wallrectx4.x && gtank2.x + 5 < map.wallrectx4.x + 280)
                                                                                            {
                                                                                                gtank2.dy = 0;
                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                gtank2.x -= gtank2.dx;
                                                                                                gtank2.y += gtank2.dy;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrectx4.x + 150)
                                                                                                {
                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                    gtank2.dx = 0;
                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                    gtank2.y += gtank2.dy;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrectx4) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrectx4.x + 150)
                                                                                                    {
                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                        gtank2.dx = 0;
                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                        gtank2.y += gtank2.dy;
                                                                                                    } //wallx5
                                                                                                    else
                                                                                                    {
                                                                                                       
                                                                                                
                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                        {
                                                                                                                                            gtank2.dy = 0;
                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                                                            gtank2.y += gtank2.dy;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty1.y && gtank2.x + 36 > map.wallrecty1.x && gtank2.x + 5 < map.wallrecty1.x + 70)
                                                                                                                                            {
                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                                                gtank2.y += gtank2.dy;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty1.x + 35)
                                                                                                                                                {
                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty1) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty1.x + 35)
                                                                                                                                                    {
                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                                    } //wally2
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 < 0 && gtank2.y - 5 < map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                        {
                                                                                                                                                            gtank2.dy = 0;
                                                                                                                                                            gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                            gtank2.x -= gtank2.dx;
                                                                                                                                                            gtank2.y += gtank2.dy;
                                                                                                                                                        }
                                                                                                                                                        else
                                                                                                                                                        {
                                                                                                                                                            if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 0 && gtank2.y + 5 > map.wallrecty2.y && gtank2.x + 36 > map.wallrecty2.x && gtank2.x + 5 < map.wallrecty2.x + 70)
                                                                                                                                                            {
                                                                                                                                                                gtank2.dy = 0;
                                                                                                                                                                gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                                gtank2.x -= gtank2.dx;
                                                                                                                                                                gtank2.y += gtank2.dy;
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && (degree2 < 90 || degree2 < -90) && gtank2.x > map.wallrecty2.x + 35)
                                                                                                                                                                {
                                                                                                                                                                    gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                    gtank2.dx = 0;
                                                                                                                                                                    gtank2.x -= gtank2.dx;
                                                                                                                                                                    gtank2.y += gtank2.dy;
                                                                                                                                                                }
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    if (SDL_HasIntersection(&grect2, &map.wallrecty2) == true && degree2 > 90 && degree2 > -90 && gtank2.x < map.wallrecty2.x + 35)
                                                                                                                                                                    {
                                                                                                                                                                        gtank2.dy = 0.1 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.dx = 0;
                                                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                                                    } //default
                                                                                                                                                                    else
                                                                                                                                                                    {
                                                                                                                                                                        gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
                                                                                                                                                                        gtank2.x -= gtank2.dx;
                                                                                                                                                                        gtank2.y += gtank2.dy;
                                                                                                                                                                    
                                                                                                                                                                
                                                                                                                                                            
                                                                                                                                                        
                                                                                                                                                    
                                                                                                                                                
                                                                                                                                        
                                                                                                                                        
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


//control movement and turn
bool Tank(SDL_Event e, bool *quit)
{
 	
    gtank1.ipos = (gtank1.y - 6) / 100;
    gtank1.jpos = (gtank1.x - 6) / 100;
    gtank2.ipos = (gtank2.y - 6) / 100;
    gtank2.jpos = (gtank2.x - 6) / 100;

    SDL_PollEvent(&e);
    if (state[SDL_SCANCODE_LEFT])
        degree2 -= 0.4;
    if (state[SDL_SCANCODE_RIGHT])
        degree2 += 0.4;
    if (state[SDL_SCANCODE_A])
        degree1 -= 0.4;
    if (state[SDL_SCANCODE_D])
        degree1 += 0.4;

    if (degree1 > 180)
        degree1 = -180;
    if (degree1 < -180)
        degree1 = 180;
    if (degree2 > 180)
        degree2 = -180;
    if (degree2 < -180)
        degree2 = 180;

    if (state[SDL_SCANCODE_W])
    {
        tankmoveup1();
    }
    if (state[SDL_SCANCODE_S])
    {
        tankmovedw1();
    }
    if (state[SDL_SCANCODE_UP])
    {
        tankmoveup2();
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        tankmovedw2();
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
    {
        if (gtank1.bullet <= 5)
        {
			Mix_PlayChannel( -1, TB, 0 );
            gtank1.bullet++;
            gbullet1[gtank1.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet1[gtank1.bullet - 1].value = 1;
            gbullet1[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].xdelta = 0.5 * cos(-degree1 * 3.14 / 180);
            gbullet1[gtank1.bullet - 1].ydelta = 0.5 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RSHIFT)
    {
        if (gtank2.bullet <= 5)
        {
			Mix_PlayChannel( -1, TB, 0 );
            gtank2.bullet++;
            gbullet2[gtank2.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet2[gtank2.bullet - 1].value = 1;
            gbullet2[gtank2.bullet - 1].x = gtank2.x + (25 * cos(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].y = gtank2.y - (25 * sin(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].xdelta = 0.5 * cos(-degree2 * 3.14 / 180);
            gbullet2[gtank2.bullet - 1].ydelta = 0.5 * sin(-degree2 * 3.14 / 180);
        }
    }
    if (e.type == SDL_QUIT)
    {
        *quit = true;
    }
	grect1 = {gtank1.x , gtank1.y , 40, 40};
    grect2 = {gtank2.x , gtank2.y , 44, 44};
    return true;
}



void lasericon(Uint32 lasertime)
{
    if (SDL_GetTicks() >= 12000 + lasertime && laserflag == false)
    {
        laserflag = true;
        LaserRect = {(rand() % 9) * 100 + 45, (rand() % 6) * 100 + 45, 25, 25};
    }
}

void BulletIcon(Uint32 lastTimebullet)
{
	if(SDL_GetTicks() >= 12000 + lastTimebullet && EBFlag == false)
	{
        do{
		EBFlag = true;
		BulletRect = {(rand() % 10) * 100 + 100, (rand() % 6) * 100 + 50, 25, 25};
        }while(SDL_HasIntersection(&BulletRect,&map.wallrectx1)==true||SDL_HasIntersection(&BulletRect,&map.wallrectx2)==true||SDL_HasIntersection(&BulletRect,&map.wallrectx3)==true||SDL_HasIntersection(&BulletRect,&map.wallrectx4)==true||SDL_HasIntersection(&BulletRect,&map.wallrecty1)==true||SDL_HasIntersection(&BulletRect,&map.wallrecty2)==true||SDL_HasIntersection(&BulletRect,&map.wallrecty3)==true||SDL_HasIntersection(&BulletRect,&map.wallrecty4)==true||SDL_HasIntersection(&BulletRect,&map.wallrecty5)==true);
	}
}

void BICollision()//BulletIconCollision
{
	if(SDL_HasIntersection(&BulletRect, &grect1) == true)
	{
		Mix_PlayChannel(-1, Reloading, 0);
		gtank1.BulletFlag = true;
		EBFlag = false;
		lastTimebullet = SDL_GetTicks();
		gtank1.bullet = 0;

	}
	else if(SDL_HasIntersection(&BulletRect, &grect2) == true)
	{
		Mix_PlayChannel(-1, Reloading, 0);
		gtank2.BulletFlag = true;
		EBFlag = false;
		lastTimebullet = SDL_GetTicks();
		gtank2.bullet = 0;

	}
}

void Score()
{
	switch (gtank1.score)
	{
	case 0: SDL_RenderCopy(gRenderer, T0, NULL, &scoreRect1);
		break;
	case 1:	SDL_RenderCopy(gRenderer, T1, NULL, &scoreRect1);
		break;
	case 2: SDL_RenderCopy(gRenderer, T2, NULL, &scoreRect1);
		break;
	case 3: SDL_RenderCopy(gRenderer, T3, NULL, &scoreRect1);
		break;
	case 4: SDL_RenderCopy(gRenderer, T4, NULL, &scoreRect1);
		break;
	case 5: SDL_RenderCopy(gRenderer, T5, NULL, &scoreRect1);
		break;
	case 6: SDL_RenderCopy(gRenderer, T6, NULL, &scoreRect1);
		break;
	case 7: SDL_RenderCopy(gRenderer, T7, NULL, &scoreRect1);
		break;
	default: 
		break;
	}
    switch (gtank2.score)
	{
	case 0: SDL_RenderCopy(gRenderer, T0, NULL, &scoreRect2);
		break;
	case 1:	SDL_RenderCopy(gRenderer, T1, NULL, &scoreRect2);
		break;
	case 2: SDL_RenderCopy(gRenderer, T2, NULL, &scoreRect2);
		break;
	case 3: SDL_RenderCopy(gRenderer, T3, NULL, &scoreRect2);
		break;
	case 4: SDL_RenderCopy(gRenderer, T4, NULL, &scoreRect2);
		break;
	case 5: SDL_RenderCopy(gRenderer, T5, NULL, &scoreRect2);
		break;
	case 6: SDL_RenderCopy(gRenderer, T6, NULL, &scoreRect2);
		break;
	case 7: SDL_RenderCopy(gRenderer, T7, NULL, &scoreRect2);
		break;
	default: 
		break;
	}

    if(gtank1.score == 7 )
    {
        SDL_RenderCopy(gRenderer, WinTexture1, NULL, &WinRect);
    }
     else if(gtank2.score == 7 )
    {
        SDL_RenderCopy(gRenderer, WinTexture2, NULL, &WinRect);
    }
}

void close()
{
	// Deallocate surface
	// SDL_FreeSurface( gMap );
	// SDL_FreeSurface( gSurface1);
	// SDL_FreeSurface( gSurface2 );
	// gMap = NULL;
	// gSurface1 = NULL;
	// gSurface2 = NULL;

	// Destroy window
	// SDL_DestroyWindow( gWindow );
	// gWindow = NULL;

	// Quit SDL subsystems
	// SDL_Quit();
}


void lose()
{
    if (gtank1.lose == true || gtank2.lose == true)
    {
        currentTime = SDL_GetTicks();
        if (SDL_GetTicks() > 5000 + lastTime)
        {
            if (gtank1.lose == false)
            {
				gtank1.bullet = 0;
				gtank2.bullet = 0;
                gtank1.score++;
                
            }
            else if (gtank2.lose == false)
            {
				gtank1.bullet = 0;
				gtank2.bullet = 0;
                gtank2.score++;
            }
            gtank1.lose = false;
            gtank2.lose = false;
            for (int i = 0; i < 6; i++)
            {
                gbullet1[i].value = 0;
                gbullet2[i].value = 0;
            }
            gtank1.bullet = 0;
            // gtank1.laserflag = false;
             gtank2.bullet = 0;
            // gtank2.laserflag = false;
            currentTime = 0;
			gtank1.x = 125;
    		gtank1.y = 55;

        	gtank2.x = 1090;
        	gtank2.y = 618;
			degree1=0;
			degree2=180;
			
            lastTime = SDL_GetTicks();
        }
    }
}


int main( int argc, char* args[] )
{
    srand(time(0));
    map.setcn();

	//Start up SDL and create window   
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//For closing the program
		 
		    bool *quit = new bool;
   			*quit = false;
			SDL_Event e;

			//Load media
			while (!*quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						*quit = true;
					}
				}
				loadMedia(map.cn);
				Mix_PlayMusic(gMusic, -1);
				do
				{
					SDL_RenderCopy(gRenderer, gbackgroundT, NULL, &backrect);
					SDL_RenderCopy(gRenderer, gborderx1, NULL, &map.borderrectx1);
					SDL_RenderCopy(gRenderer, gborderx2, NULL, &map.borderrectx2);
					SDL_RenderCopy(gRenderer, gbordery1, NULL, &map.borderrecty1);
					SDL_RenderCopy(gRenderer, gbordery2, NULL, &map.borderrecty2);
					if(map.cn==1)
					{
						SDL_RenderCopy(gRenderer, walltexture_x1, NULL, &map.wallrectx1);
						SDL_RenderCopy(gRenderer, walltexture_x2, NULL, &map.wallrectx2);
						SDL_RenderCopy(gRenderer, walltexture_y1, NULL, &map.wallrecty1);
						SDL_RenderCopy(gRenderer, walltexture_y2, NULL, &map.wallrecty2);
						SDL_RenderCopy(gRenderer, walltexture_y3, NULL, &map.wallrecty3);
						SDL_RenderCopy(gRenderer, walltexture_y4, NULL, &map.wallrecty4);
						SDL_RenderCopy(gRenderer, walltexture_y5, NULL, &map.wallrecty5);
					}
					if(map.cn==2)
					{
						SDL_RenderCopy(gRenderer, walltexture_x1, NULL, &map.wallrectx1);
						SDL_RenderCopy(gRenderer, walltexture_y1, NULL, &map.wallrecty1);
						SDL_RenderCopy(gRenderer, walltexture_y2, NULL, &map.wallrecty2);
						SDL_RenderCopy(gRenderer, walltexture_y3, NULL, &map.wallrecty3);
						SDL_RenderCopy(gRenderer, walltexture_y4, NULL, &map.wallrecty4);
						SDL_RenderCopy(gRenderer, walltexture_y5, NULL, &map.wallrecty5);
					}
					if(map.cn==3)
					{
						SDL_RenderCopy(gRenderer, walltexture_x1, NULL, &map.wallrectx1);
						SDL_RenderCopy(gRenderer, walltexture_x2, NULL, &map.wallrectx2);
						SDL_RenderCopy(gRenderer, walltexture_x3, NULL, &map.wallrectx3);
						SDL_RenderCopy(gRenderer, walltexture_x4, NULL, &map.wallrectx4);
						SDL_RenderCopy(gRenderer, walltexture_x5, NULL, &map.wallrectx5);
						SDL_RenderCopy(gRenderer, walltexture_x6, NULL, &map.wallrectx6);
						SDL_RenderCopy(gRenderer, walltexture_y1, NULL, &map.wallrecty1);
						SDL_RenderCopy(gRenderer, walltexture_y2, NULL, &map.wallrecty2);
					}
					
					
					if (gtank1.lose == false)
						SDL_RenderCopyEx(gRenderer, gTexture1, NULL, &grect1, degree1, NULL, SDL_FLIP_NONE);
					if (gtank2.lose == false)
						SDL_RenderCopyEx(gRenderer, gTexture2, NULL, &grect2, degree2, NULL, SDL_FLIP_NONE);
					if (laserflag == true)
						SDL_RenderCopy(gRenderer, glaser, NULL, &LaserRect);
					if (EBFlag == true)
						SDL_RenderCopy(gRenderer, ammotexture, NULL, &BulletRect);
					BulletIcon(lastTimebullet);
					BICollision();
					Score();
					for (int i = 0; i < 6; i++)
					{
						if (gbullet1[i].value == 1)
							gbullet1[i].move();
						if (gbullet2[i].value == 1)
							gbullet2[i].move();
					}
					lose();
					SDL_RenderPresent(gRenderer);
				} while (Tank(e, quit) && !*quit);
			}
	}
	return 0;
}