#include "superpellets.h"
superPellets::superPellets(int row, int col)  //initialize super pellets according to row and column provided
{
    QPixmap pel(":/Images/pellet.png");
    pel = pel.scaledToWidth(16);
    pel = pel.scaledToHeight(16);
    setPixmap(pel);
    setPos(17+30*col, 27+30*row);
}
