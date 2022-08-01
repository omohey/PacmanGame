#include "pellets.h"
pellets::pellets()  //this is left empty intentionally so that when super pellets inherits and calls the pellets constructor nothing happens
{

}
pellets::pellets(int row, int col)      //initialize each pellet according to row and column provided
{
    QPixmap pel(":/Images/pellet.png");
    pel = pel.scaledToWidth(8);
    pel = pel.scaledToHeight(8);
    setPixmap(pel);
    setPos(22+30*col, 32+30*row);
}
