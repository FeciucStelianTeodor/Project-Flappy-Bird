#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
using namespace std;
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
unsigned TimeOfStart;
void cls(int y, int x)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD newLine = { x, y };
    SetConsoleCursorPosition(hOut, newLine);
}

struct player
{
    unsigned x=12,y=6,type=0;
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
unsigned GetMenuPressedKey(unsigned ButtonPressed)
{ unsigned AlegereFacuta;
        switch(ButtonPressed)
        {
        case 49:
            return 1;
            break;
        case 50:
            AlegereFacuta=2;
            break;
        case 51:
            AlegereFacuta=3;
            break;
        case 52:
            AlegereFacuta=4;
            break;
        default:
            AlegereFacuta=0;
            break;
        }
}

void PrintMenu()
{
    system("cls");
    cout<<" --------------------------------------------------------------------------------"<<'\n';
    cout<<"|   .d    |  .dP*Y8 888888    db    88**Yb 888888                                |"<<'\n';
    cout<<"| .d88    |   `Ybo.*   88     dPYb   88__dP   88                                 |"<<'\n';
    cout<<"|   88    |   o.`Y8b   88    dP__Yb  88*Yb    88                                 |"<<'\n';
    cout<<"|   88    |   8bodP`   88   dP****Yb 88  Yb   88                                 |"<<'\n';
    cout<<" --------------------------------------------------------------------------------"<<'\n';
    cout<<"| oP*Yb.  |   88  88 88  dP**b8 88  88     .dP*Y8  dP**b8  dP*Yb  88**Yb 888888  |"<<'\n';
    cout<<"| *` dP`  |   88  88 88 dP   `* 88  88     `Ybo.* dP   `* dP   Yb 88__dP 88__    |"<<'\n';
    cout<<"|   dP`   |   888888 88 Yb  *88 888888     o.`Y8b Yb      Yb   dP 88*Yb  88**    |"<<'\n';
    cout<<"| .d8888  |   88  88 88  YboodP 88  88     8bodP`  YboodP  YbodP  88  Yb 888888  |"<<'\n';
    cout<<" --------------------------------------------------------------------------------"<<'\n';
    cout<<"| 88888   |   88  88 888888 88     88**Yb                                        |"<<'\n';
    cout<<"|   .dP   |   88  88 88__   88     88__dP                                        |"<<'\n';
    cout<<"| o `Yb   |   888888 88**   88  .o 88***                                         |"<<'\n';
    cout<<"| YbodP   |   88  88 888888 88ood8 88                                            |"<<'\n';
    cout<<" --------------------------------------------------------------------------------"<<'\n';
    cout<<"|   dP88  |   888888 Yb  dP 88 888888                                            |"<<'\n';
    cout<<"|  dP 88  |   88__    YbdP  88   88                                              |"<<'\n';
    cout<<"| d888888 |   88**    dPYb  88   88                                              |"<<'\n';
    cout<<"|     88  |   888888 dP  Yb 88   88                                              |"<<'\n';
    cout<<" --------------------------------------------------------------------------------"<<'\n';
}

void PrintGameOver()
{
    system("cls");
    cout<<" .d8888b.                                         .d88888b.                            "<<'\n';
    cout<<"d88P  Y88b                                       d88P* *Y88b                           "<<'\n';
    cout<<"888    888                                       888     888                           "<<'\n';
    cout<<"888         8888b.  88888b.d88b.   .d88b.        888     888 888  888  .d88b.  888d888 "<<'\n';
    cout<<"888  88888     *88b 888 *888 *88b d8P  Y8b       888     888 888  888 d8P  Y8b 888P*   "<<'\n';
    cout<<"888    888 .d888888 888  888  888 88888888       888     888 Y88  88P 88888888 888     "<<'\n';
    cout<<"Y88b  d88P 888  888 888  888  888 Y8b.           Y88b. .d88P  Y8bd8P  Y8b.     888     "<<'\n';
    cout<<" *Y8888P88 *Y888888 888  888  888  *Y8888         *Y88888P*    Y88P    *Y8888  888     "<<'\n';
    cout<<"                                                                                       "<<'\n';
    cout<<"                                                                                       "<<'\n';
    cout<<"                                                                                       "<<'\n';
}

void RandomPositionObstacle(ObstacleQueue &Pipe)
{
    unsigned xPipeUp,xPipeDown,yPipeUp,yPipeDown,lengthPipeUp,lengthPipeDown;
    srand(clock());
    xPipeDown=19;
    xPipeUp=4;
    yPipeDown=yPipeUp=49;
    lengthPipeDown=rand()%6+1;
    lengthPipeUp=6-lengthPipeDown;
    AddPositionObstacleQueue(Pipe,xPipeDown,yPipeDown,lengthPipeDown);
    AddPositionObstacleQueue(Pipe,xPipeUp,yPipeUp,lengthPipeUp);
}

void MoveObstacle(ObstacleQueue &Pipe)
{
    node* AuxNode=Pipe.first;
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

bool EndGame(unsigned xBird, unsigned lengthObstacle1, unsigned yObstacle, unsigned lengthObstacle2)
{
    if(xBird==0||xBird>=22)
        return true;
    if(yObstacle>17)
        return false;
    if(18-lengthObstacle1<=xBird||5+lengthObstacle2>=xBird)
        return true;
    return false;
}

void matricspace(char s[][110])
{
    unsigned i,j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<50; j++)
            s[i][j]=' ';
        s[i][49]='|';
        s[i][0]='|';
    }
    for(j=0; j<50; j++)
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

bool esc=false;
void afisare(player bird, char s[][110])
{
    unsigned i,j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<50; j++)
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
            if(bird.x>5)
                bird.x=bird.x-4;
            if(bird.x<=2)
                esc=true;
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
    system("cls");
    afisare(bird,s);
    unsigned score=0;
    unsigned TimePassedInGame=clock()-TimeOfStart,seconds=0;
    cls(15,70);
    cout<<"SCORE: "<<score;
    cls(17,70);
    cout<<"TIME IN SECONDS : "<<(clock()-TimeOfStart)/CLOCKS_PER_SEC;
    RandomPositionObstacle(Pipe);
    do
    {
        if(mutare(bird))
        {
            if(EndGame(bird.x,Pipe.first->obstacleLenght,Pipe.first->y,Pipe.first->next->obstacleLenght))
            {
                esc=true;
                break;
            }
            clearbird(bird.x+4,bird.y);
            birdprint(bird.x,bird.y);
            if(Pipe.first->y==6)
            {
                ClearObstacle(Pipe);
                score++;
                cls(15,77);
                cout<<score;
            }
            MoveObstacle(Pipe);
            PrintObstacle(Pipe);
        }
        Sleep(100);
        cls(17,87;
        cout<<(clock()-TimeOfStart)/CLOCKS_PER_SEC;
        if(Pipe.first->y==6)
        {
            ClearObstacle(Pipe);
            score++;
            cls(15,77);
            cout<<score;
        }
        MoveObstacle(Pipe);
        PrintObstacle(Pipe);
        clearbird(bird.x,bird.y);
        bird.x++;
        if(EndGame(bird.x,Pipe.first->obstacleLenght,Pipe.first->y,Pipe.first->next->obstacleLenght))
        {
            esc=true;
            break;
        }
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

void Menu(char s[][110],ObstacleQueue &Pipe, player bird)
{   PrintMenu();
    unsigned ButtonPressed;
    do{ButtonPressed=getch();
    }while(ButtonPressed>'4'||ButtonPressed<'1');
    ButtonPressed=GetMenuPressedKey(ButtonPressed);
    if(ButtonPressed==1)
    {   TimeOfStart=clock();
        gameplay(bird,s,Pipe);
        return;
    }
    else if(ButtonPressed==4)
    {
        esc=true;
        return;
    }
}

int main()
{
    char a[25][110];
    unsigned b;
    player bird;
    hidecursor();
    matricspace(a);
    ObstacleQueue Pipe;
    InitializeObstacleQueueu(Pipe);
    Menu(a,Pipe,bird);
    //gameplay(bird,a,Pipe);
    //birdprint(bird.x,bird.y);
    //AddPositionObstacleQueue(Pipe,19,69,2);
    //AddPositionObstacleQueue(Pipe,4,69,8);
    //RandomPositionObstacle(Pipe);
    //PrintObstacle(Pipe);
    //MoveObstacle(Pipe);
    //MoveObstacle(Pipe);
    //PrintObstacle(Pipe);
    PrintGameOver();
    return 0;
}
