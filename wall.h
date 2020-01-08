#include <stdlib.h>
class wall
{
  public:
    int xstart, ystart, xend, yend;
    int flag = 1;
    void random()
    {
        int r = rand() % 100;
        if (r < 40)
            flag = 1;
        else
            flag = 0;
    }
} gwallv[6][8], gwallh[5][9];
