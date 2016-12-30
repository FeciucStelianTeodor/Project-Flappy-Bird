#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
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
typedef obstacle* pipe;
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
        for(j=0; j<25; j++)
            s[i][j]=' ';
        s[i][24]='/';
        s[i][0]='/';
        s[0][i]='/';
        s[24][i]='/';
    }
    s[12][4]='%';
}
bool esc=false;
void afisare(player bird, char s[][110])
{
    unsigned i,j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<25; j++)
            if(bird.x==i&&j==bird.y)
                cout<<"%";
            else
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
            system("cls");
            afisare(bird,s);
        }
        Sleep(250);
        bird.x++;
        system("cls");
        afisare(bird,s);
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
