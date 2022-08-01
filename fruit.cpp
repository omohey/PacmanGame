#include "fruit.h"

Fruit::Fruit(int row,int col)
{
    QPixmap fruitpixmap(":/Images/fruit.png");
    fruitpixmap = fruitpixmap.scaledToWidth(30);
    fruitpixmap = fruitpixmap.scaledToHeight(30);

    setPixmap(fruitpixmap);
    setPos(10+30*col, 20+30*row);
}
