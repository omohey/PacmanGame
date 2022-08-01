#include "ghost.h"
#include "pacman.h"
#include "game.h"
#include <QDebug>
extern Game *game;

Pacman::Pacman()
{

    Right = new QPixmap(":/Images/Pacmani.png");             //setting pacman logo
    *Right= Right->scaledToWidth(30);
    *Right = Right->scaledToHeight(30);
    Left = new QPixmap(":/Images/Pacmanleft.png");
    *Left= Left->scaledToWidth(30);
    *Left = Left->scaledToHeight(30);
    Up = new QPixmap(":/Images/Pacmanup.png");
    *Up= Up->scaledToWidth(30);
    *Up = Up->scaledToHeight(30);
    Down = new QPixmap(":/Images/Pacmandown.png");
    *Down= Down->scaledToWidth(30);
    *Down = Down->scaledToHeight(30);
    this->setPixmap(*Right);

    col = 13;
    row = 23;
    this->setPos(10+30*col, 20+30*row);


    k="";kprev ="";
    lose = false;
    i=0;
    invin = false;
    timer = NULL;


    notinvincible = new QPixmap(":/Images/notinvincible.png");   //setting pixmaps for invincible and normal mode
    *notinvincible = notinvincible->scaledToWidth(30);
    *notinvincible = notinvincible->scaledToHeight(30);
    inv.setPixmap(*notinvincible);
    inv.setPos(600, 955);
    invincible = new QPixmap(":/Images/invincible.png");
    *invincible = invincible->scaledToWidth(30);
    *invincible = invincible->scaledToHeight(30);


    //background = new QSound("pacman_beginning.wav");
    //background->play();
    //background->setLoops(QSound::Infinite);


}
void Pacman::setrow(int x)
{
    row = x;
}
void Pacman::setcolumn (int x)
{
    col = x;
}
int Pacman::getcolumn()
{
    return col;
}
int Pacman::getrow()
{
    return row;
}

void Pacman::setlose()
{
    lose = true;
    k="";
    col = 13;
    row =23;
}

void Pacman::reset()
{
    k="";
    if (pixmap() != *Right)
        setPixmap(*Right);
}

bool Pacman::movement()
{
    if (k =="")
        return true;
    return false;
}
void Pacman::keyPressEvent(QKeyEvent *event)    //every key corresponds to one condition
{

    if (event->key() == Qt::Key_Up )
    {
        kprev= k;
        k= "up";

    }
        else if (event->key() == Qt::Key_Down)
    {
        kprev= k;
        k="down";
    }
    else if (event->key() == Qt::Key_Left)
    {
            kprev= k;
            k= "left";


    }
    else if (event->key() == Qt::Key_Right)
    {
            kprev= k;
            k="right";

    }

}
#include <iostream>
void Pacman::advance(int phase)
{
    if (!lose && !win)      //stop moving if you win or you lose
    {
    if (i==0)   //add invincible item to scene only first time. Could not do it in constructor because pacman was still not linked to the scene
    {
        scene()->addItem(&inv);
        i++;
    }
    if (!phase) return;
    if (k=="up" )   //case user pressed up. other cases will have similar logic
    {
        if (game->boardData[row-1][col] != -1) //if the position above is not a wall then move to it
        {
            row--; kprev = k;
            if (pixmap() != *Up)
                setPixmap(*Up);
        }
        else                        //case that position above is a wall
        {
            if (kprev == "down" && game->boardData[row+1][col] != -1 && game->boardData[row+1][col] != 122 && game->boardData[row+1][col] != 123)    //keep moving in the previous direction until the entered direction is available
                row++;
            else
                if (kprev =="left")
                {if(game->boardData[row][col-1] != -1)
                    col--;
            else if (game->boardData[row][col]==136)
                        col =27;
                }
            else if (kprev =="right" )
                {
                    if (game->boardData[row][col+1] != -1)
                    col++;
                    else if (game->boardData[row][col]==161)
                        col =0;
                }
        }
    }
            else if (k=="down" )
        {
            if (game->boardData[row+1][col] != -1&& game->boardData[row+1][col] != 122 && game->boardData[row+1][col] != 123)
            {
                row++; kprev = k;
                if (pixmap() != *Down)
                    setPixmap(*Down);
            }
            else
            {
                if (kprev == "up" && game->boardData[row-1][col] != -1)
                    row--;
                else
                    if (kprev =="left")
                    {if(game->boardData[row][col-1] != -1)
                        col--;
                else if (game->boardData[row][col]==136)
                            col =27;
                    }
                else if (kprev =="right" )
                    {
                        if (game->boardData[row][col+1] != -1)
                        col++;
                        else if (game->boardData[row][col]==161)
                            col =0;
                    }
            }
        }
        else if (k=="left")
        {
            if (game->boardData[row][col] == 136)
            {
                col= 27; kprev = k;
                if (pixmap() != *Left)
                    setPixmap(*Left);
            }
            else if (game->boardData[row][col-1] != -1)
            {
                col--; kprev = k;
                if (pixmap() != *Left)
                    setPixmap(*Left);
            }
            else
            {
                if (kprev == "down" && game->boardData[row+1][col] != -1 && game->boardData[row+1][col] != 122 && game->boardData[row+1][col] != 123)
                    row++;
                else
                    if (kprev =="up" && game->boardData[row-1][col] != -1)
                        row--;
                else if (kprev =="right" &&game->boardData[row][col+1] != -1)
                        col++;
            }

        }
        else if (k== "right")
        {
            if (game->boardData[row][col] == 161)
            {
                col = 0; kprev = k;
                if (pixmap() != *Right)
                    setPixmap(*Right);
            }
             else if (game->boardData[row][col+1] != -1)
            {
                col++; kprev = k;
                if (pixmap() != *Right)
                    setPixmap(*Right);
            }
            else
            {
                if (kprev == "down" && game->boardData[row+1][col] != -1 && game->boardData[row+1][col] != 122 && game->boardData[row+1][col] != 123)
                    row++;
                else
                    if (kprev =="left"&&game->boardData[row][col-1] != -1)
                        col--;
                else if (kprev =="up" &&game->boardData[row-1][col] != -1)
                        row--;
            }
        }
        QList<QGraphicsItem*> list;     //get colliding items
        list = collidingItems();
        for (int i = 0; i<list.size(); i++)
            if(typeid (*list[i]) == typeid(ghost))
            {
                if (invin)      //if we collide with a ghost and we are invincible
                {
                    game->score->addghost();
                    for (int c = 0; c<3; c++)               //put the ghost back at home
                        if (list[i] == game->ghosts[c])
                        {
                            int col1;
                            if (c== 0)
                                col1 = 13;
                            else if (c==1)
                                col1 = 12;
                            else
                                col1 = 14;
                            game->ghosts[c]->setcolumn(col1);
                            game->ghosts[c]->setrow(14);
                            game->ghosts[c]->setPos(10+30* (game->ghosts[c]->getcolumn()), 20+30*game->ghosts[c]->getrow());
                            game->ghosts[c]->stopghost();
                        }


                }
                else            //if we collide with a ghost and we are not invincible
                {
                    game->lives->decreaselife();
                }


            }


        setPos(10+30*col, 20+30*row);


        for (int i = 0; i<list.size(); i++)
        {
            if (typeid (*list[i]) == typeid(pellets) || typeid (*list[i]) == typeid(superPellets) || typeid (*list[i]) == typeid(Fruit))  //see if we collide with any pellet
            {
                if(typeid (*list[i]) == typeid(pellets))
                {
                    for (int r = 0; r<31; r++)          //if we collide with normal pellet get its pointer from array of pellets pointer and nullify it this will be used to determine if we won
                        for (int c = 0; c<28; c++)
                            if (list[i] == game->pellet[r][c])
                            {
                                game->pellet[r][c] = NULL;
                                game->rowsvec.push_back(r);
                                game->colsvec.push_back(c);
                            }
                    scene()->removeItem(list[i]);
                    delete list[i];         //remove from scene and add score
                    game->score->addpellet();
                }
                else if (typeid (*list[i]) == typeid(superPellets))
                {

                        for (int c = 0; c<4; c++)           // if we collide with the super pellet do same initial step
                            if (list[i] == game->super[c])
                            {
                                game->super[c] = NULL;
                                break;
                            }
                        scene()->removeItem(list[i]);
                    delete list[i];
                    game->score->addsuperpellet();
                    inv.setPixmap(*invincible);                             //make pacman invincible
                    invin = true;
                    if (timer != NULL)                  //if pacman was already invincible start 10 secods from the begining
                        delete timer;
                    timer = new QTimer(this);           //start the timer with 10 seconds to make pacman normal mode again
                    timer->setSingleShot(true);


                        connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));


                        timer->start(10000);
                }
                else
                {
                    delete game->fruit;
                    game->fruit =NULL;
                    game->score->addfruit();
                }
            }
        }
        if (win!=true)
        {
            win = true;
            for (int i = 0; i<31; i++)              //see if all pellets and super pellets are null if thats true we will not execute any of the if and we win
                for (int c = 0; c<28; c++)
                    if(game->pellet[i][c] != NULL)
                    {
                        win = false;
                        break;
                    }
            for (int i = 0; i<4; i++)
                if(game->super[i] != NULL)
                {
                    win = false;
                    break;
                }
            if (win)
            {
                k ="";                                          //if we win stop moving and display message box that we won and close the game
                game->player->stop();
                msgBox.setText("Congratulations, you won!");
                msgBox.exec();
                exit(0);

                //Win.setPlainText("You Win");                    //code to display display that we won. it is not necessary since we did message box but it's here as it was a requirement on the word document
                //Win.setDefaultTextColor(Qt::white);
                //Win.setPos(700, 960);
                //Win.setFont(QFont ("Arial", 16));
                //scene()->addItem(&Win);

            }
        }

}
}
void Pacman::MyTimerSlot()  //after the time for invincibility ends delete timer and stop invincible mode
{

    delete timer;
    timer =NULL;
    invin = false;
    inv.setPixmap(*notinvincible);
}
