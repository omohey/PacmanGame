#include "ghost.h"
#include "game.h"
#include <QDebug>
extern Game *game;

ghost::ghost(QPixmap &ghostName, int column, int gh_type) //takes the pixmap of the ghost (Inky/Pinky/Clyde) and assigns it to the current ghost and sets him at his correct position
{
    if (gh_type% 3 == 0)
        type = Slow;
    else if (gh_type%3 == 1)
        type = Medium;
    else
        type = Fast;
    num =0;
    stop = false;


    ghostName= ghostName.scaledToWidth(30);
    ghostName = ghostName.scaledToHeight(30);
    setPixmap(ghostName);
    col = column;
    row = 14;
    setPos(10+30*col, 20+30*row);

    k="";
    srand(time(NULL));
    max = 0;

       for (int i = 0; i < 31; i++)
           for (int c = 0; c < 28; c++)
               if (max < game->boardData[i][c])
                   max = game->boardData[i][c];
       max++;
       matrix = new int*[max];
       for (int i = 0; i < max; i++)
           matrix[i] = new int[max];
       for (int i = 0; i < max; i++)
           for (int c = 0; c < max; c++)
               matrix[i][c] = 0;

       for (int i = 0; i < max; i++)
       {
           int row, col;

           for (int r = 0; r < 31; r++)
               for (int c = 0; c < 28; c++)
               {
                   if (i == game->boardData[r][c])
                   {
                       row = r;
                       col = c;
                   }
               }
           if (game->boardData[row - 1][col] != -1)
               matrix[i][game->boardData[row - 1][col]] = 1;
           if (game->boardData[row + 1][col] != -1)
               matrix[i][game->boardData[row + 1][col]] = 1;
           if (i == 136)
           {
               matrix[i][161] = 1;
           }
           else
               if (game->boardData[row][col - 1] != -1)
                   matrix[i][game->boardData[row][col - 1]] = 1;
           if (i == 161)
               matrix[i][136] = 1;
           else
               if (game->boardData[row][col + 1] != -1)
                   matrix[i][game->boardData[row][col + 1]] = 1;
       }
}

void ghost::setrow(int x)
{
    row = x;
}
void ghost::setcolumn (int x)
{
    col = x;
}
int ghost::getcolumn()
{
    return col;
}
int ghost::getrow()
{
    return row;
}
void ghost::moveRandomly()      //changes the private variable k to up/down/right/left randomly
{
    int startnode = game->boardData[row][col];
    int goal = game->boardData[game->pacman->getrow()][game->pacman->getcolumn()];
    vector<vector<int>> results = Dijkstra(startnode);
    int next;
    if (results[goal].size()>=2)
        next = results[goal].at(results[goal].size()-2);
    else
    {
        k="";
        next = -10;
    }
    if (next == game->boardData[row-1][col])
        k = "up";
    if (next == game->boardData[row+1][col])
        k = "down";
    if (next == 161 && startnode == 136)
        k = "left";
    else
        if (next == game->boardData[row][col-1])
            k = "left";
    if ((next == 136 && startnode == 161) || next ==  game->boardData[row][col+1])
        k = "right";
}

void ghost::stopghost()
{
    stop = true;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveghost()));
    timer->setSingleShot(true);
    timer->start(2500);
}

void ghost::moveghost()
{
    stop = false;
    delete timer;
    timer = NULL;
}

void ghost::advance(int phase)      //move everytime the signal timeout() is emitted
{                               //makes a random direction and changes row and column according to it
    if (!phase) return;

    if (!(game->pacman->movement())&&!stop)

    {


    bool go = false;
    if (type == Fast)
        if (num%7 != 3)
            go = true;
    if (type == Medium)
        if (num%7 ==0 || num%7==2 || num %7 ==4||num%7==6)
            go = true;
    if (type == Slow)
        if (num%7 ==1 || num %7 == 3|| num%7 == 5)
            go = true;
    num++;
    if (go)
{
    moveRandomly();
    if (k=="up" && game->boardData[row-1][col] != -1)
        row--;

    else if (k=="down" && game->boardData[row+1][col] != -1)
        row++;

    else if (k=="left")
       {
        if(game->boardData[row][col] == 136)       //if ghost is at the is at left portal and wants to go left move him to the other end of the portal
        {
           col=27;
        }else if(game->boardData[row][col-1] != -1)
        {
            col--;
        }
       }
    else if (k== "right" )
    {
        if(game->boardData[row][col] == 161)   //if ghost is at the is at right portal and wants to go right move him to the other end of the portal
        {
           col=0;
        }else if(game->boardData[row][col+1] != -1)
        {
            col++;
        }
    }

    setPos(10+30*col, 20+30*row);
}
    }
}
vector<vector<int>> ghost::Dijkstra(int startNode)
{
    int temp[max][max], costs[max], previous[max];
        bool visited[max];
        // temp
        for (int i = 0; i < max; i++)
            for (int j = 0; j < max; j++)
                if (matrix[i][j] == 0)
                    temp[i][j] = Infinity;
                else
                    temp[i][j] = matrix[i][j];
        // costs, previous, and visited
        for (int i = 0; i < max; i++)
        {
            costs[i] = temp[startNode][i];
            previous[i] = startNode;
            visited[i] = false;
        }
        // startNode
        costs[startNode] = 0;
        visited[startNode] = true;

        int count = 1, nextNode, minimumCost;
        while (count < max)
        {
            // Find the minimum cost in order to visit a node.
            minimumCost = Infinity;
            for (int i = 0; i < max; i++)
                if ((costs[i] < minimumCost) && (visited[i] == false))
                {
                    minimumCost = costs[i];
                    nextNode = i;
                }
            // Visit the node.
            visited[nextNode] = true;
            // Update the costs of the children of the visited node.
            for (int i = 0; i < max; i++)
                if ((minimumCost + temp[nextNode][i] < costs[i]) && (visited[i] == false))
                {
                    costs[i] = minimumCost + temp[nextNode][i];
                    previous[i] = nextNode;
                }
            count++;
        }
        // Fill the paths.
        int j;
        vector<vector<int>> paths;
        paths.resize(max);
        for (int i = 0; i < max; i++)
        {
            paths[i].push_back(i);
            if (i != startNode)
            {
                j = i;
                do
                {
                    j = previous[j];
                    paths[i].push_back(j);
                } while (j != startNode);
            }
        }
        return paths;
}/*
void ghost::getpac(Pacman* pac)
{
    pacman = pac;
}
*/
