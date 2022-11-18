#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailx[100], taily[100];
int ntails;
enum control {STOP = 0, LEFT, UP, RIGHT, DOWN};
control dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0)
                cout << "#";
            if(i == y && j == x)
                cout << "O";
            else if(i == fruitY && j == fruitX)
                cout << "*";
            else
            {
                bool print = false;
                for(int k = 0; k < ntails; k++)
                {
                    if(tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }

            if(j == width-1)
                cout << "#";
        }
        cout << endl;
    }
    for(int i = 0; i < width+2; i++)
        cout << "#";

    cout << "\n" << "Score: " << score << endl;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a' :
                dir = LEFT;
                break;
            case 'd' :
                dir = RIGHT;
                break;
            case 'w' :
                dir = UP;
                break;
            case 's' :
                dir = DOWN;
                break;
            case ' ' :
                gameOver = true;
                break;

        }
    }
}

void Logic()
{
    int prevX = tailx[0];
    int prevY = taily[0];
    int tempX, tempY;
    tailx[0] = x;
    taily[0] = y;
    for(int i = 1; i < ntails; i++)
    {
        tempX = tailx[i];
        tempY = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch(dir)
    {
    case LEFT :
        x--;
        break;
    case RIGHT :
        x++;
        break;
    case UP :
        y--;
        break;
    case DOWN :
        y++;
    default :
        break;
    }
    if(x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    for(int i = 0; i < ntails; i++)
    {
        if(tailx[i] == x && taily[i] == y)
            gameOver = true;
    }
    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntails++;

    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}
