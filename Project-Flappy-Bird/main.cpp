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

struct node
{
    unsigned x,y,obstacleLenght;
    node* next;
    node* previous;
};

struct ObstacleQueue
{
    node* first;
    node* last;
    unsigned int lenght;
};

void InitializeObstacleQueueu(ObstacleQueue& ObstacleAux)
{
    ObstacleAux.lenght = 0;
    ObstacleAux.first = NULL;
    ObstacleAux.last = NULL;
}

void AddPositionObstacleQueue(ObstacleQueue& ObstacleAux, unsigned PositionX, unsigned PositionY, unsigned LenghtOfObstacle)
{
    if (ObstacleAux.lenght == 0)
    {
        ObstacleAux.first = new node;
        ObstacleAux.first->x = PositionX;
        ObstacleAux.first->y=PositionY;
        ObstacleAux.first->obstacleLenght=LenghtOfObstacle;
        ObstacleAux.first->next = NULL;
        ObstacleAux.first->previous = NULL;
        ObstacleAux.last = ObstacleAux.first;
        ObstacleAux.lenght++;
    }
    else
    {
        node* NodeAux;
        NodeAux = new node;
        NodeAux->x = PositionX;
        NodeAux->y = PositionY;
        NodeAux->obstacleLenght=LenghtOfObstacle;
        NodeAux->next = NULL;
        NodeAux->previous = ObstacleAux.last;
        ObstacleAux.lenght++;
        ObstacleAux.last->next = NodeAux;
        ObstacleAux.last = NodeAux;
    }
}

void DeletePositionObstacleQueue(ObstacleQueue ObstacleAux, unsigned elementPosition)
{
    node* NodeAux1 = ObstacleAux.first;
    node* NodeAux2;
    node* NodeAux3;
    unsigned i;
    for (i = 1; i <= elementPosition - 1; i++)
        NodeAux1 = NodeAux1->next;
    NodeAux2 = NodeAux1->previous;
    NodeAux3 = NodeAux1->next;
    NodeAux2->next = NodeAux3;
    NodeAux3->previous = NodeAux2;
    delete NodeAux1;
    ObstacleAux.lenght--;
}

void RandomPositionObstacle(ObstacleQueue &Pipe)
{
    unsigned xPipeUp,xPipeDown,yPipeUp,yPipeDown,lengthPipeUp,lengthPipeDown;
    xPipeDown=19;
    xPipeUp=4;
    yPipeDown=yPipeUp=69;
    lengthPipeDown=rand()%7+1;
    lengthPipeUp=7-lengthPipeDown;
    AddPositionObstacleQueue(Pipe,xPipeDown,yPipeDown,lengthPipeDown);
    AddPositionObstacleQueue(Pipe,xPipeUp,yPipeUp,lengthPipeUp);
}

void MoveObstacle(ObstacleQueue &Pipe)
{   node* AuxNode=Pipe.first;
    ObstacleQueue AuxObstacle;
    InitializeObstacleQueueu(AuxObstacle);
    unsigned i=0,LengthOfPipe=Pipe.lenght;
    while(i<LengthOfPipe)
    {
        AddPositionObstacleQueue(AuxObstacle,AuxNode->x,AuxNode->y-1,AuxNode->obstacleLenght);
        AuxNode=AuxNode->next;
        i++;
    }
    Pipe=AuxObstacle;
}

void ClearObstacle(ObstacleQueue &Pipe)
{
    node* AuxNode=Pipe.first;
    int i;
    while(AuxNode!=NULL)
    {
        for(i=23; i>=19-AuxNode->obstacleLenght; i--)
        {
            cls(i,AuxNode->y-5);
            cout<<"      ";
        }
        AuxNode=AuxNode->next;
        for(i=1; i<=4+AuxNode->obstacleLenght; i++)
        {
            cls(i,AuxNode->y-5);
            cout<<"      ";
        }
        AuxNode=AuxNode->next;
    }
    ObstacleQueue AuxPipe;
    InitializeObstacleQueueu(AuxPipe);
    RandomPositionObstacle(AuxPipe);
    Pipe=AuxPipe;
}

void PrintObstacle(ObstacleQueue Pipe)
{
    node* AuxNode=Pipe.first;
    int i;
    while(AuxNode!=NULL)
    {
        for(i=23; i>=19-AuxNode->obstacleLenght; i--)
        {
            cls(i,AuxNode->y-4);
            cout<<"     ";
            cls(i,AuxNode->y-5);
            cout<<"*****";
        }
        AuxNode=AuxNode->next;
        for(i=1; i<=4+AuxNode->obstacleLenght; i++)
        {
            cls(i,AuxNode->y-4);
            cout<<"     ";
            cls(i,AuxNode->y-5);
            cout<<"*****";
        }
        AuxNode=AuxNode->next;
    }
}

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

void gameplay(player bird, char s[][110],ObstacleQueue &Pipe)
{
    afisare(bird,s);
    RandomPositionObstacle(Pipe);
    do
    {
        if(mutare(bird))
        {
            clearbird(bird.x+4,bird.y);
            birdprint(bird.x,bird.y);
            if(Pipe.first->y==6)
                ClearObstacle(Pipe);
            MoveObstacle(Pipe);
            PrintObstacle(Pipe);
        }
        Sleep(100);
        if(Pipe.first->y==6)
            ClearObstacle(Pipe);
        MoveObstacle(Pipe);
        PrintObstacle(Pipe);
        clearbird(bird.x,bird.y);
        bird.x++;
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
    char a[25][110];
    player bird;
    hidecursor();
    matricspace(a);
    ObstacleQueue Pipe;
    InitializeObstacleQueueu(Pipe);
    gameplay(bird,a,Pipe);
    return 0;
}
