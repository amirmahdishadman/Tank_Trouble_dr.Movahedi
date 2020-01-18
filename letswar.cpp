
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>

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

//The image we will load and show on the screen
SDL_Surface* gMap= NULL;


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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia(int cn)
{
	//Loading success flag
	bool success = true;

	//Load splash image
    
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
	gMap = NULL;

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
		
       while(true)
		{
		//Load media
		if( !loadMedia(cn) )
		{
			printf( "Failed to load media!\n" );
			break;
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gMap, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			SDL_Delay(5000);
		}

	}
    }
	


	return 0;
}