
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
SDL_Surface* Wallsurface= NULL;
SDL_Surface* background=NULL;

//Textures

SDL_Texture* gTexture1 = NULL, * gTexture2 = NULL;
SDL_Texture* glaser = NULL;
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




//keyboard states
const Uint8 *state = SDL_GetKeyboardState(NULL);

//rects
SDL_Rect grect1;
SDL_Rect grect2; 
SDL_Rect LaserRect;
// SDL_Rect borderrectx1={0,0,1280,8};
// SDL_Rect borderrectx2={0,712,1280,8};
// SDL_Rect borderrecty1={0,0,8,720};
// SDL_Rect borderrecty2={1272,0,8,720};

// SDL_Rect wallrectx1={0,0,280,70};
// SDL_Rect wallrectx2={0,0,280,70};
// SDL_Rect wallrectx3={0,0,280,70};
// SDL_Rect wallrectx4={0,0,280,70};
// SDL_Rect wallrectx5={0,0,280,70};
// SDL_Rect wallrectx6={0,0,280,70};


// SDL_Rect wallrecty1={0,0,70,280};
// SDL_Rect wallrecty2={0,0,70,280};
// SDL_Rect wallrecty3={0,0,70,280};
// SDL_Rect wallrecty4={0,0,70,280};
// SDL_Rect wallrecty5={0,0,70,280};
// SDL_Rect wallrecty6={0,0,70,280};

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
	//Loading success flag


 	
	//Load random image
  			background = SDL_LoadBMP("background.bmp");
   			gbackgroundT = SDL_CreateTextureFromSurface(gRenderer, background);
			background=SDL_LoadBMP("xborder.bmp");
			gborderx1 = SDL_CreateTextureFromSurface(gRenderer, background);
			gborderx2 = SDL_CreateTextureFromSurface(gRenderer, background);
			background=SDL_LoadBMP("yborder.bmp");
			gbordery1 = SDL_CreateTextureFromSurface(gRenderer, background);
			gbordery2 = SDL_CreateTextureFromSurface(gRenderer, background);
 	if(cn==1)
	 {


		 	map.wallrecty1.h=200;
		    map.wallrecty2.h=200;

			map.wallrecty4.h=200;
		    map.wallrecty5.h=200;
			map.wallrecty3.h=210;

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

			map.wallrectx1.x=500;
			map.wallrectx1.y=75;

			map.wallrectx2.x=500;
			map.wallrectx2.y=575;

			map.wallrecty1.x=215;
			map.wallrecty1.y=106.7;

			map.wallrecty2.x=215;
			map.wallrecty2.y=413.4;

			map.wallrecty3.x=605;
			map.wallrecty3.y=255;

			map.wallrecty4.x=995;
			map.wallrecty4.y=106.7;;

			map.wallrecty5.x=995;
			map.wallrecty5.y=413.4;
	}
 		
    if(cn==2)
	{
			map.wallrecty1.h=200;
		    map.wallrecty2.h=200;

			map.wallrecty4.h=200;
		    map.wallrecty5.h=200;

			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			
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

			map.wallrectx1.x=500;
			map.wallrectx1.y=325;

			map.wallrecty1.x=215;
			map.wallrecty1.y=106.7;

			map.wallrecty2.x=215;
			map.wallrecty2.y=413.4;

			map.wallrecty3.x=605;
			map.wallrecty3.y=220;

			map.wallrecty4.x=995;
			map.wallrecty4.y=106.7;;

			map.wallrecty5.x=995;
			map.wallrecty5.y=413.4;

	}
    		
    if(cn==3)
 	{
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x3 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x4 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x5 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wallx.bmp");
   			walltexture_x6 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			
			Wallsurface = SDL_LoadBMP("wally.bmp");
   			walltexture_y1 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);
			Wallsurface = SDL_LoadBMP("wally.bmp");
   			walltexture_y2 = SDL_CreateTextureFromSurface(gRenderer, Wallsurface);

			map.wallrectx1.x=220;
			map.wallrectx1.y=220;

			map.wallrectx2.x=500;
			map.wallrectx2.y=220;

			map.wallrectx3.x=780;
			map.wallrectx3.y=220;

			map.wallrectx4.x=220;
			map.wallrectx4.y=430;

			map.wallrectx5.x=500;
			map.wallrectx5.y=430;
			
			map.wallrectx6.x=780;
			map.wallrectx6.y=430;

			map.wallrecty1.x=150;
			map.wallrecty1.y=220;

			map.wallrecty2.x=1060;
			map.wallrecty2.y=220;
			
	}
	
	


}
















//movement of tanks

void tankmoveup1()
{
	 gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
     gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
	 gtank1.x -= gtank1.dx;
     gtank1.y += gtank1.dy;
}
void tankmovedw1()
{
	 gtank1.dy = 0.2 * sin(-degree1 * 3.14 / 180);
     gtank1.dx = 0.2 * cos(-degree1 * 3.14 / 180);
	 gtank1.x += gtank1.dx;
     gtank1.y -= gtank1.dy;
     
}
void tankmoveup2()
{
	 gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
     gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
	 gtank2.x -= gtank2.dx;
     gtank2.y += gtank2.dy;
}
void tankmovedw2()
{
	 gtank2.dy = 0.2 * sin(-degree2 * 3.14 / 180);
     gtank2.dx = 0.2 * cos(-degree2 * 3.14 / 180);
	 gtank2.x += gtank2.dx;
     gtank2.y -= gtank2.dy;
     
}




























//control movement and turn
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
        tankmovedw1();
    }
    if (state[SDL_SCANCODE_S])
    {
        tankmoveup1();
    }
 if (state[SDL_SCANCODE_UP])
    {
        tankmovedw2();
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        tankmoveup2();
    }
    
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2)
    {
        if (gtank1.bullet <= 5)
        {
            gtank1.bullet++;
            gbullet1[gtank1.bullet - 1].lastTimeball = SDL_GetTicks();
            gbullet1[gtank1.bullet - 1].value = 1;
            gbullet1[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gbullet1[gtank1.bullet - 1].xdelta = 0.5 * cos(-degree1 * 3.14 / 180);
            gbullet1[gtank1.bullet - 1].ydelta = 0.5 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_0)
    {
        if (gtank2.bullet <= 7)
        {
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
                gtank1.score++;
               // gtank1.convert(gtank1.score, gtank1.number);
               // gSurface = TTF_RenderText_Solid(font, gtank1.number, color);
                //gTexture11 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
            }
            else if (gtank2.lose == false)
            {
                gtank2.score++;
                //gtank2.convert(gtank2.score, gtank2.number);
                //gSurface = TTF_RenderText_Solid(font, gtank2.number, color);
                //gTexture22 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
            }
            gtank1.lose = false;
            gtank2.lose = false;
           // gtank1.x = 100 * (rand() % 9) + 50;
            //gtank1.y = 100 * (rand() % 6) + 50;
            //do
           // {
                //gtank2.x = 100 * (rand() % 9) + 50;
               // gtank2.y = 100 * (rand() % 6) + 50;
           // } while (gtank1.x == gtank2.x && gtank1.y == gtank2.y);
           // InitMap();
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