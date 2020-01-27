
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
using namespace std;
class mapdetails{
public:
int cn=1;
void setcn()
{
 cn=rand()%3+1;
}



SDL_Rect wallrectx1={0,0,280,70};
SDL_Rect wallrectx2={0,0,280,70};
SDL_Rect wallrectx3={0,0,280,70};
SDL_Rect wallrectx4={0,0,280,70};
SDL_Rect wallrectx5={0,0,280,70};
SDL_Rect wallrectx6={0,0,280,70};


SDL_Rect wallrecty1={0,0,70,280};
SDL_Rect wallrecty2={0,0,70,280};
SDL_Rect wallrecty3={0,0,70,280};
SDL_Rect wallrecty4={0,0,70,280};
SDL_Rect wallrecty5={0,0,70,280};
SDL_Rect wallrecty6={0,0,70,280};

SDL_Rect borderrectx1={0,0,1280,8};
SDL_Rect borderrectx2={0,712,1280,8};
SDL_Rect borderrecty1={0,0,8,720};
SDL_Rect borderrecty2={1272,0,8,720};
} map;
