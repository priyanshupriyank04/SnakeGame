#include <iostream>
#include <cstdlib>
#include <unistd.h>         //needed to slow down the game loop
using namespace std;

bool gameOver;
const int width = 20;               //dimensions of the play area set as 20 x 20 
const int height = 20;
int x, y;                            //coords to keep track of the snake head
int fruitX, fruitY;                 //coords to keep track of fruit location which snake eats 
int score;                          //game score keeping and updation     
int tailX[100], tailY[100];
int ntail;
enum eDirection { STOP = 0, LEFT, RIGHT , UP , DOWN};        //to keep note of the direction of snake head
eDirection dir;             //variable created to store the present direction of the snake head

void setup()
{
    gameOver = false;
    dir = STOP;         //initially before game start snake will be in the STOP state 
    x = width / 2;        //initially the snake head will be centered
    y = height / 2;
    fruitX = rand() % width;            //initiate any random coords for the fruit using rand() function 
    fruitY = rand() % height;
    score = 0;              //score would be set to 0 to begin with
}

void draw()
{
    system("clear");        //clears the screen of the console to start the game with blank screen 
    for (int i = 0; i < width + 2; i++)            //creates border 1st row 
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)             //creates height-based border 
    {
        cout << "#";           // Left border
        for (int j = 0; j < width; j++)
        {
            if (i == y && j == x)                //if coords equal to snake head print snake head
            {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)     //if coords equal to fruit print fruit
            {
                cout << "F";
            }
            else
            {
                bool print =false;
                for(int k = 0;k<ntail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print)
                {
                    cout<<" ";
                }
            }
        }
        cout << "#";           // Right border
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)           //creates border last row 
    {
        cout << "#";
    }
    cout << endl;
    cout<<"Score"<<score<<endl;
}

char getInput()
{
    system("stty raw");         //set terminal to block line buffering and capture key press without enter key 
    char input = getchar();     //getchar() to take input char 
    system("stty cooked");      //set terminal type back to default settings
    return input;
}

void input()
{
    char ch = getInput();       // Store the input character 

    switch (ch) {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i =1;i<ntail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {              //based on value of dir move the snake head in that direction 
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x>width || x<0 || y<0 || y>height)           //condition of out of bounds to terminate the game if bounds crossed 
    {
        gameOver = true;
    }
    for(int i =0;i<ntail;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
        {
            gameOver = true;                    //if at any moment any tail part coincides with the snake head collision detected and game over 
        }
    }
    if(x==fruitX || y==fruitY)
    {
        score+=10;
        fruitX = rand() %width;
        fruitY = rand() %height;
        ntail++;
    }
}

int main()
{
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        usleep(100000);   // Slow down game loop
    }
    return 0;
}
