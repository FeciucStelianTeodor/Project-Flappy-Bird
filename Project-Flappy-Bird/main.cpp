#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

bool esc=false;
typedef obstacle* pipe;
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

void cls(int y, int x)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD newLine = { x, y };
    SetConsoleCursorPosition(hOut, newLine);
}

struct player
{
    unsigned x=12,y=4,type=0;
    bool powerup=false;
};

struct obstacle
{
    unsigned x,y;
    struct obstacle *next, *previous;
};

/*void AddValuePipe(pipe MovingPipe,unsigned value)
{
    if(MovingPipe)
    }*/
//void RandomxOyPipe()

void matricspace(char s[][110])
{
    unsigned i,j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<70; j++)
            s[i][j]=' ';
        s[i][69]='|';
        s[i][0]='|';
    }
    for(j=0; j<70; j++)
    {
        s[0][j]='|';
        s[24][j]='|';
    }
}

void clearbird(int x,int y)
{
    cls(x-1,y-1);
    cout<<"   ";
    cls(x,y-2);
    cout<<"       ";
    cls(x+1,y-2);
    cout<<"        ";
}

void birdprint(int x,int y)
{
    cls(x-1,y-1);
    cout<<"___";
    cls(x,y-2);
    cout<<"/__O\\_";
    cls(x+1,y-2);
    cout<<"\\___/-'";
}

void afisare(player bird, char s[][110])
{
    unsigned i,j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<70; j++)
            cout<<s[i][j];
        cout<<endl;
    }
}

bool mutare(player &bird)
{
    if(kbhit())
    {
        switch(getch())
        {
        case 32:
            bird.x=bird.x-2;
            return true;
            break;
        case 27:
            esc=true;
            return true;
            break;
        default:
            return false;
            break;
        }
    }
    return false;
}

void gameplay(player bird, char s[][110])
{
    afisare(bird,s);
    do
    {
        if(mutare(bird))
        {
            /*cls(bird.x+2,bird.y);
            cout<<" ";
            cls(bird.x,bird.y);
            cout<<"%";*/
            clearbird(bird.x+2,bird.y);
            birdprint(bird.x,bird.y);
        }
        Sleep(250);
        /*cls(bird.x, bird.y);
        cout<<" ";*/
        clearbird(bird.x,bird.y);
        bird.x++;
        /*cls(bird.x, bird.y);
        cout<<"%";*/
        birdprint(bird.x,bird.y);
    }
    while(!esc);
    return;
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    char a[25][110]= {"^^^^","////"};
    player bird;
    hidecursor();
    matricspace(a);
    gameplay(bird,a);
    return 0;
}
