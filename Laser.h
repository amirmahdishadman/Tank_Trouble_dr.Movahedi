double degree1 = 0;
double degree2 = 0;
bool laserflag = false;
Uint32 lasertime = 0;
class laser
{
public:
  float x, y, deltax, deltay;
  bool out;

  // void control1()
  // {
  //   out = true;
  //   if (x <= 6 || x >= 906)
  //     deltax *= -1;
  //   if (y <= 4 || y >= 604)
  //     deltay *= -1;
  //   for (int i = 0; i < 5 && out == true; i++)
  //   {
  //     for (int j = 0; j < 9 && out == true; j++)
  //     {
  //       if (gwallh[i][j].flag == 1)
  //       {
  //         if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y >= gwallh[i][j].ystart - 1 && y < gwallh[i][j].ystart + 2)
  //         {
  //           deltay *= -1;
  //           out = false;
  //         }
  //         else if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y <= gwallh[i][j].ystart + 2 && y > gwallh[i][j].ystart - 1)
  //         {
  //           deltay *= -1;
  //           out = false;
  //         }
  //         else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x >= gwallh[i][j].xstart && x < gwallh[i][j].xstart + 10)
  //           deltax *= -1;
  //         else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x <= gwallh[i][j].xend && x > gwallh[i][j].xend - 10)
  //           deltax *= -1;
  //       }
  //     }
  //   }
  //   out = true;
  //   for (int i = 0; i < 6 && out == true; i++)
  //   {
  //     for (int j = 0; j < 8 && out == true; j++)
  //     {
  //       if (gwallv[i][j].flag == 1)
  //       {
  //         if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x >= gwallv[i][j].xstart - 1 && x < gwallv[i][j].xstart + 2)
  //         {
  //           deltax *= -1;
  //           out = false;
  //         }
  //         else if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x <= gwallv[i][j].xstart + 2 && x > gwallv[i][j].xstart - 1)
  //         {
  //           deltax *= -1;
  //           out = false;
  //         }
  //         else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y >= gwallv[i][j].ystart && y < gwallv[i][j].ystart + 10)
  //           deltay *= -1;
  //         else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y <= gwallv[i][j].yend && y > gwallv[i][j].yend - 10)
  //           deltay *= -1;
  //       }
  //     }
  //   }
  //   if ((x - gtank1.x) * (x - gtank1.x) + (y - gtank1.y) * (y - gtank1.y) <= 18 * 18)
  //   {
  //     gtank1.lose = true;
  //     lasertime = SDL_GetTicks();
  //     lastTime = SDL_GetTicks();
  //   }
  // }
  // void control2()
  // {
  //   out = true;
  //   if (x <= 6 || x >= 906)
  //     deltax *= -1;
  //   if (y <= 4 || y >= 604)
  //     deltay *= -1;
  //   for (int i = 0; i < 5 && out == true; i++)
  //   {
  //     for (int j = 0; j < 9 && out == true; j++)
  //     {
  //       if (gwallh[i][j].flag == 1)
  //       {
  //         if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y >= gwallh[i][j].ystart - 1 && y < gwallh[i][j].ystart + 2)
  //         {
  //           deltay *= -1;
  //           out = false;
  //         }
  //         else if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y <= gwallh[i][j].ystart + 2 && y > gwallh[i][j].ystart - 1)
  //         {
  //           deltay *= -1;
  //           out = false;
  //         }
  //         else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x >= gwallh[i][j].xstart && x < gwallh[i][j].xstart + 10)
  //           deltax *= -1;
  //         else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x <= gwallh[i][j].xend && x > gwallh[i][j].xend - 10)
  //           deltax *= -1;
  //       }
  //     }
  //   }
  //   out = true;
  //   for (int i = 0; i < 6 && out == true; i++)
  //   {
  //     for (int j = 0; j < 8 && out == true; j++)
  //     {
  //       if (gwallv[i][j].flag == 1)
  //       {
  //         if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x >= gwallv[i][j].xstart - 1 && x < gwallv[i][j].xstart + 2)
  //         {
  //           deltax *= -1;
  //           out = false;
  //         }
  //         else if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x <= gwallv[i][j].xstart + 2 && x > gwallv[i][j].xstart - 1)
  //         {
  //           deltax *= -1;
  //           out = false;
  //         }
  //         else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y >= gwallv[i][j].ystart && y < gwallv[i][j].ystart + 10)
  //           deltay *= -1;
  //         else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y <= gwallv[i][j].yend && y > gwallv[i][j].yend - 10)
  //           deltay *= -1;
  //       }
  //     }
  //   }
  //   if ((x - gtank2.x) * (x - gtank2.x) + (y - gtank2.y) * (y - gtank2.y) <= 18 * 18)
  //   {
  //     gtank2.lose = true;
  //     lasertime = SDL_GetTicks();
  //     lastTime = SDL_GetTicks();
  //   }
  // }
  void drawlaser()
  {
    if (gtank1.LaserFlag == true)
    {
      x = gtank1.x;
      y = gtank1.y;
      deltax = cos(-degree1 * 3.14 / 180);
      deltay = sin(-degree1 * 3.14 / 180);
      for (int k = 1; k < 300; k++)
      {
        x += deltax;
        y -= deltay;
        SDL_RenderDrawPoint(gRenderer, x, y);
        //control2();
      }
    }
    else if (gtank2.LaserFlag == true)
    {
      x = gtank2.x;
      y = gtank2.y;
      deltax = cos(-degree2 * 3.14 / 180);
      deltay = sin(-degree2 * 3.14 / 180);
      for (int k = 1; k < 300; k++)
      {
        x += deltax;
        y -= deltay;
        SDL_RenderDrawPoint(gRenderer, x, y);
        //control1();
      }
    }
  }
} tanklaser;