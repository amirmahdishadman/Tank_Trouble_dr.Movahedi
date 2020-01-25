
//Using SDL and standard IO
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
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

//Renders


//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Surface for loading png images (except map)
SDL_Surface* gSurface1 = NULL;
SDL_Surface* gSurface2 = NULL;
SDL_Surface* gSurface3 = NULL;

//The image we will load and show on the screen
SDL_Surface* gMap= NULL;
SDL_Surface* background=NULL;

//Textures
SDL_Texture* gTexture1 = NULL, * gTexture2 = NULL;
SDL_Texture* glaser = NULL;
SDL_Texture* gbackgroundT = NULL;
SDL_Texture* gmapT = NULL;



//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//rects
SDL_Rect grect1;
SDL_Rect grect2; 
SDL_Rect LaserRect;
SDL_Rect maprect={0,0,1280,790};
SDL_Rect backrect={0,0,1280,790};

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

	  		gtank1.x = 125;
    		gtank1.y = 55;
			grect1.x = gtank1.x;
			grect1.y = gtank1.y;
    
        	gtank2.x = 1062;
        	gtank2.y = 618;
			grect2.x = gtank2.x;
			grect2.y = gtank2.y;
		}
	}

	return success;
}

void loadMedia(int cn)
{
	//Loading success flag


 	
	//Load random image
  			background = SDL_LoadBMP("background.bmp");
   			gbackgroundT = SDL_CreateTextureFromSurface(gRenderer, background);
 	if(cn==1)
 			gMap = SDL_LoadBMP("map1.bmp");
   			gmapT = SDL_CreateTextureFromSurface(gRenderer, gMap);
    if(cn==2)
    		gMap = SDL_LoadBMP("map2.bmp");
   			gmapT = SDL_CreateTextureFromSurface(gRenderer, gMap);
    if(cn==3)
 			gMap = SDL_LoadBMP("map3.bmp");
   			gmapT = SDL_CreateTextureFromSurface(gRenderer, gMap);
	
	

	
}

bool Tank(SDL_Event e, bool *quit)
{
 	float a,b,c,d;
    double f;
    int k,t;
    gtank1.ipos = (gtank1.y - 6) / 100;
    gtank1.jpos = (gtank1.x - 6) / 100;
    gtank2.ipos = (gtank2.y - 6) / 100;
    gtank2.jpos = (gtank2.x - 6) / 100;

    SDL_PollEvent(&e);
    if (state[SDL_SCANCODE_LEFT])
        degree1 -= 5;
    if (state[SDL_SCANCODE_RIGHT])
        degree1 += 5.2;
    if (state[SDL_SCANCODE_A])
        degree2 -= 5.2;
    if (state[SDL_SCANCODE_D])
        degree2 += 5.2;

    if (degree1 > 180)
        degree1 = -180;
    if (degree1 < -180)
        degree1 = 180;
    if (degree2 > 180)
        degree2 = -180;
    if (degree2 < -180)
        degree2 = 180;
    
    
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_0)
    {
        if (gtank1.bullet <= 5)
        {
            gtank1.bullet++;
            gbullet1[gtank1.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet1[gtank1.bullet - 1].value = 1;
            gbullet1[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].xdelta = 0.1 * cos(-degree1 * 3.14 / 180);
            gbullet1[gtank1.bullet - 1].ydelta = 0.1 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2)
    {
        if (gtank2.bullet <= 5)
        {
            gtank2.bullet++;
            gbullet2[gtank2.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet2[gtank2.bullet - 1].value = 1;
            gbullet2[gtank2.bullet - 1].x = gtank2.x + (25 * cos(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].y = gtank2.y - (25 * sin(-degree2 * 3.14 / 180));
            gbullet2[gtank2.bullet - 1].xdelta = 0.1 * cos(-degree2 * 3.14 / 180);
            gbullet2[gtank2.bullet - 1].ydelta = 0.1 * sin(-degree2 * 3.14 / 180);
        }
    }
    if (e.type == SDL_QUIT)
    {
        *quit = true;
    }
	grect1 = {gtank1.x , gtank1.y , 50, 50};
    grect2 = {gtank2.x , gtank2.y , 50, 50};
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

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gMap );
	//SDL_FreeSurface( gSurface1);
	//SDL_FreeSurface( gSurface2 );
	gMap = NULL;
	//gSurface1 = NULL;
	//gSurface2 = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
    srand(time(0));
    int cn=rand()%3+1;

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
			     			
				do
				{
					while (SDL_PollEvent(&e) != 0)
      		    			{
            					if (e.type == SDL_QUIT)
           		   				{
                					*quit = true;
         		   				}
       						}
					
					
					
						 	loadMedia(cn);
							//Apply the image
							//SDL_BlitSurface( background, NULL, gScreenSurface, NULL );
							//SDL_BlitSurface( gMap, NULL, gScreenSurface, NULL );
							//SDL_BlitSurface( gSurface1, NULL, gScreenSurface, &grect1 );
							//SDL_BlitSurface( gSurface2, NULL, gScreenSurface, &grect2 );
								SDL_RenderCopy(gRenderer, gbackgroundT, NULL, &backrect);
								SDL_RenderCopy(gRenderer, gmapT, NULL, &maprect);
							if (gtank1.lose == false)
                				SDL_RenderCopyEx(gRenderer, gTexture1, NULL, &grect1, degree1, NULL, SDL_FLIP_NONE);
          					if(gtank2.lose == false)
                				SDL_RenderCopyEx(gRenderer, gTexture2, NULL, &grect2, degree2, NULL, SDL_FLIP_NONE);
							if (laserflag == true)
                				SDL_RenderCopy(gRenderer, glaser, NULL, &LaserRect);
							//Update the surface
							//SDL_UpdateWindowSurface( gWindow );
							SDL_RenderPresent(gRenderer);
					
					
					// for (int i = 0; i < 6; i++)
          			// {
               		// 	if(gbullet1[i].value == 1)
                   	// 		gbullet1[i].move();
              		// 	if(gbullet2[i].value == 1)
             		//        	gbullet2[i].move();
          			// }
					
				
					}while(!Tank(e,quit) && !*quit);
			}
		close();
	}
	return 0;
}