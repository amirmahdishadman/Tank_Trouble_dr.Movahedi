
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
SDL_Renderer* gRenderer = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Surface for loading png images (except map)
SDL_Surface* gSurface1 = NULL;
SDL_Surface* gSurface2 = NULL;

//The image we will load and show on the screen
SDL_Surface* gMap= NULL;
SDL_Surface* background=NULL;

//Textures
SDL_Texture* gTexture1 = NULL, * gTexture2 = NULL;

//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//rects
SDL_Rect grect1; //Tank1 rect
SDL_Rect grect2; //Tank2 rect

//Events
SDL_Event e;


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
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
		    gScreenSurface = SDL_GetWindowSurface( gWindow );
			gSurface1 = SDL_LoadBMP("tank1.bmp");
   			gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface1);
	    	 
    		gSurface2 = SDL_LoadBMP("tank2.bmp");
  			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface2);
    		//gSurface = IMG_Load("laser.png");
    		// glaser = SDL_CreateTextureFromSurface(gRenderer, gSurface);
	  		 gtank1.x = -1 * rand()%1280+1;
    		 gtank1.y = -1 * rand()%790+1;
			 grect1 = {gtank1.x, gtank1.y, 1280, 790};
    		 do
    		 {
        	 	gtank2.x = -1 * rand()%1280+1;
        	 	gtank2.y = -1 * rand()%790+1;
    		 } while (gtank1.x == gtank2.x && gtank1.y == gtank2.y);
			 grect2 = {gtank2.x,gtank2.y,1280,790};
		}
	}

	return success;
}

bool loadMedia(int cn)
{
	//Loading success flag
	bool success = true;

	//Load random image
    background = SDL_LoadBMP("background.bmp");
 	if(cn==1)
    {gMap = SDL_LoadBMP("map1.bmp");}
    if(cn==2)
    {gMap = SDL_LoadBMP("map2.bmp");}
    if(cn==3)
    {gMap = SDL_LoadBMP("map3.bmp");}
	
	if( gMap == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "map.bmp", SDL_GetError() );
		success = false;
	}

	return success;
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
			
				do{
				if( !loadMedia(cn) )
				{
				printf( "Failed to load media!\n" );
				}
				else
				{
					while (!*quit)
   			 {
			     while (SDL_PollEvent(&e) != 0)
      		    {
            		if (e.type == SDL_QUIT)
           		   {
                	*quit = true;
         		   }
       			 }
				//Apply the image
				SDL_BlitSurface( background, NULL, gScreenSurface, NULL );
				SDL_BlitSurface( gMap, NULL, gScreenSurface, NULL );
				
				SDL_BlitSurface( gSurface1, &grect1, gScreenSurface, NULL );
				SDL_BlitSurface( gSurface2, &grect2, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );

				
				}
				}
			
				
	}while(!*quit);
	close();

	}
	return 0;
}

   

