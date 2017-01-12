#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <string.h>
using namespace std;
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
unsigned TimeOfStart, HighScoresSorted[11], TimeSorted[11], PositionHighScore = 0, NewScore = 0, NewTime = 0;
bool ScoreHasBeenReaden = false;
char HighScoresNameSorted[11][20], NewName[20];
void MoveCursorTo(int y, int x)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD newLine = { x, y };
	SetConsoleCursorPosition(hOut, newLine);
}

struct player
{
	unsigned x = 12, y = 6, type = 0;
	bool powerup = false;
};

struct nodeTree
{
	char name[20];
	unsigned score, time;
	struct nodeTree *left;
	struct nodeTree *right;
};

typedef nodeTree* Tree;

struct node
{
	unsigned x, y, obstacleLenght;
	node* next;
	node* previous;
};

struct ObstacleQueue
{
	node* first;
	node* last;
	unsigned int lenght;
};

void Menu(char s[][110], ObstacleQueue &Pipe, player bird);

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
		ObstacleAux.first->y = PositionY;
		ObstacleAux.first->obstacleLenght = LenghtOfObstacle;
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
		NodeAux->obstacleLenght = LenghtOfObstacle;
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
{
	unsigned AlegereFacuta;
	switch (ButtonPressed)
	{
	case 49:
		return 1;
		break;
	case 50:
		AlegereFacuta = 2;
		break;
	case 51:
		AlegereFacuta = 3;
		break;
	case 52:
		AlegereFacuta = 4;
		break;
	default:
		AlegereFacuta = 0;
		break;
	}
}

void PrintMenu()
{
#if (defined (_WIN32) || defined (_WIN64))
	system("cls");
#elif (defined (LINUX) || defined (__linux__))
	system("clear");
#endif
	cout << " --------------------------------------------------------------------------------" << '\n';
	cout << "|   .d    |  .dP*Y8 888888    db    88**Yb 888888                                |" << '\n';
	cout << "| .d88    |   `Ybo.*   88     dPYb   88__dP   88                                 |" << '\n';
	cout << "|   88    |   o.`Y8b   88    dP__Yb  88*Yb    88                                 |" << '\n';
	cout << "|   88    |   8bodP`   88   dP****Yb 88  Yb   88                                 |" << '\n';
	cout << " --------------------------------------------------------------------------------" << '\n';
	cout << "| oP*Yb.  |   88  88 88  dP**b8 88  88     .dP*Y8  dP**b8  dP*Yb  88**Yb 888888  |" << '\n';
	cout << "| *` dP`  |   88  88 88 dP   `* 88  88     `Ybo.* dP   `* dP   Yb 88__dP 88__    |" << '\n';
	cout << "|   dP`   |   888888 88 Yb  *88 888888     o.`Y8b Yb      Yb   dP 88*Yb  88**    |" << '\n';
	cout << "| .d8888  |   88  88 88  YboodP 88  88     8bodP`  YboodP  YbodP  88  Yb 888888  |" << '\n';
	cout << " --------------------------------------------------------------------------------" << '\n';
	cout << "| 88888   |   88  88 888888 88     88**Yb                                        |" << '\n';
	cout << "|   .dP   |   88  88 88__   88     88__dP                                        |" << '\n';
	cout << "| o `Yb   |   888888 88**   88  .o 88***                                         |" << '\n';
	cout << "| YbodP   |   88  88 888888 88ood8 88                                            |" << '\n';
	cout << " --------------------------------------------------------------------------------" << '\n';
	cout << "|   dP88  |   888888 Yb  dP 88 888888                                            |" << '\n';
	cout << "|  dP 88  |   88__    YbdP  88   88                                              |" << '\n';
	cout << "| d888888 |   88**    dPYb  88   88                                              |" << '\n';
	cout << "|     88  |   888888 dP  Yb 88   88                                              |" << '\n';
	cout << " --------------------------------------------------------------------------------" << '\n';
}

void PrintGameOver()
{
#if (defined (_WIN32) || defined (_WIN64))
	system("cls");
#elif (defined (LINUX) || defined (__linux__))
	system("clear");
#endif
	cout << " .d8888b.                                         .d88888b.                            " << '\n';
	cout << "d88P  Y88b                                       d88P* *Y88b                           " << '\n';
	cout << "888    888                                       888     888                           " << '\n';
	cout << "888         8888b.  88888b.d88b.   .d88b.        888     888 888  888  .d88b.  888d888 " << '\n';
	cout << "888  88888     *88b 888 *888 *88b d8P  Y8b       888     888 888  888 d8P  Y8b 888P*   " << '\n';
	cout << "888    888 .d888888 888  888  888 88888888       888     888 Y88  88P 88888888 888     " << '\n';
	cout << "Y88b  d88P 888  888 888  888  888 Y8b.           Y88b. .d88P  Y8bd8P  Y8b.     888     " << '\n';
	cout << " *Y8888P88 *Y888888 888  888  888  *Y8888         *Y88888P*    Y88P    *Y8888  888     " << '\n';
	cout << "                                                                                       " << '\n';
	cout << "                                                                                       " << '\n';
	cout << "                                                                                       " << '\n';
}

void RandomPositionObstacle(ObstacleQueue &Pipe)
{
	unsigned xPipeUp, xPipeDown, yPipeUp, yPipeDown, lengthPipeUp, lengthPipeDown;
	srand(clock());
	xPipeDown = 19;
	xPipeUp = 4;
	yPipeDown = yPipeUp = 49;
	lengthPipeDown = rand() % 6 + 1;
	lengthPipeUp = 6 - lengthPipeDown;
	AddPositionObstacleQueue(Pipe, xPipeDown, yPipeDown, lengthPipeDown);
	AddPositionObstacleQueue(Pipe, xPipeUp, yPipeUp, lengthPipeUp);
}

void MoveObstacle(ObstacleQueue &Pipe)
{
	node* AuxNode = Pipe.first;
	ObstacleQueue AuxObstacle;
	InitializeObstacleQueueu(AuxObstacle);
	unsigned i = 0, LengthOfPipe = Pipe.lenght;
	while (i < LengthOfPipe)
	{
		AddPositionObstacleQueue(AuxObstacle, AuxNode->x, AuxNode->y - 1, AuxNode->obstacleLenght);
		AuxNode = AuxNode->next;
		i++;
	}
	Pipe = AuxObstacle;
}

void ClearObstacle(ObstacleQueue &Pipe)
{
	node* AuxNode = Pipe.first;
	int i;
	while (AuxNode != NULL)
	{
		for (i = 23; i >= 19 - AuxNode->obstacleLenght; i--)
		{
			MoveCursorTo(i, AuxNode->y - 5);
			cout << "      ";
		}
		AuxNode = AuxNode->next;
		for (i = 1; i <= 4 + AuxNode->obstacleLenght; i++)
		{
			MoveCursorTo(i, AuxNode->y - 5);
			cout << "      ";
		}
		AuxNode = AuxNode->next;
	}
	ObstacleQueue AuxPipe;
	InitializeObstacleQueueu(AuxPipe);
	RandomPositionObstacle(AuxPipe);
	Pipe = AuxPipe;
}

void PrintObstacle(ObstacleQueue Pipe)
{
	node* AuxNode = Pipe.first;
	int i;
	while (AuxNode != NULL)
	{
		for (i = 23; i >= 19 - AuxNode->obstacleLenght; i--)
		{
			MoveCursorTo(i, AuxNode->y - 4);
			cout << "     ";
			MoveCursorTo(i, AuxNode->y - 5);
			cout << "*****";
		}
		AuxNode = AuxNode->next;
		for (i = 1; i <= 4 + AuxNode->obstacleLenght; i++)
		{
			MoveCursorTo(i, AuxNode->y - 4);
			cout << "     ";
			MoveCursorTo(i, AuxNode->y - 5);
			cout << "*****";
		}
		AuxNode = AuxNode->next;
	}
}

bool EndGame(unsigned xBird, unsigned lengthObstacle1, unsigned yObstacle, unsigned lengthObstacle2)
{
	if (xBird == 0 || xBird >= 22)
		return true;
	if (yObstacle > 17)
		return false;
	if (18 - lengthObstacle1 <= xBird || 5 + lengthObstacle2 >= xBird)
		return true;
	return false;
}

void MatricSpace(char Map[][110])
{
	unsigned i, j;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 50; j++)
			Map[i][j] = ' ';
		Map[i][49] = '|';
		Map[i][0] = '|';
	}
	for (j = 0; j < 50; j++)
	{
		Map[0][j] = '|';
		Map[24][j] = '|';
	}
}

void ClearBird(int x, int y)
{
	MoveCursorTo(x - 1, y - 1);
	cout << "   ";
	MoveCursorTo(x, y - 2);
	cout << "       ";
	MoveCursorTo(x + 1, y - 2);
	cout << "        ";
}

void PrintBird(int x, int y)
{
	MoveCursorTo(x - 1, y - 1);
	cout << "___";
	MoveCursorTo(x, y - 2);
	cout << "/__O\\_";
	MoveCursorTo(x + 1, y - 2);
	cout << "\\___/-'";
}

bool esc = false;
void PrintMap(player bird, char Map[][110])
{
	unsigned i, j;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 50; j++)
			cout << Map[i][j];
		cout << endl;
	}
}

bool movement(player &bird)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 32:
			if (bird.x > 5)
				bird.x = bird.x - 4;
			if (bird.x <= 2)
				esc = true;
			return true;
			break;
		case 27:
			esc = true;

			return true;
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}

void gameplay(player bird, char Map[][110], ObstacleQueue &Pipe)
{
#if (defined (_WIN32) || defined (_WIN64))
	system("cls");
#elif (defined (LINUX) || defined (__linux__))
	system("clear");
#endif
	PrintMap(bird, Map);
	unsigned CurrentScore = 0;
	unsigned TimePassedInGame = clock() - TimeOfStart, seconds = 0;
	MoveCursorTo(15, 70);
	cout << "SCORE: " << CurrentScore;
	MoveCursorTo(17, 70);
	cout << "TIME IN SECONDS: " << '0';
	RandomPositionObstacle(Pipe);
	do
	{
		if (movement(bird))
		{
			if (EndGame(bird.x, Pipe.first->obstacleLenght, Pipe.first->y, Pipe.first->next->obstacleLenght))
			{
				esc = true;
				break;
			}
			ClearBird(bird.x + 4, bird.y);
			PrintBird(bird.x, bird.y);
			if (Pipe.first->y == 6)
			{
				ClearObstacle(Pipe);
				CurrentScore++;
				MoveCursorTo(15, 77);
				cout << CurrentScore;
			}
			MoveObstacle(Pipe);
			PrintObstacle(Pipe);
		}
		Sleep(100);
		MoveCursorTo(17, 87);
		cout << (clock() - TimeOfStart) / CLOCKS_PER_SEC;
		if (Pipe.first->y == 6)
		{
			ClearObstacle(Pipe);
			CurrentScore++;
			MoveCursorTo(15, 77);
			cout << CurrentScore;
		}
		MoveObstacle(Pipe);
		PrintObstacle(Pipe);
		ClearBird(bird.x, bird.y);
		bird.x++;
		if (EndGame(bird.x, Pipe.first->obstacleLenght, Pipe.first->y, Pipe.first->next->obstacleLenght))
		{
			esc = true;
			break;
		}
		PrintBird(bird.x, bird.y);
	} while (!esc);
	NewTime = TimePassedInGame;
	NewScore = CurrentScore;
	return;
}

void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

bool AddBinarySearchElement(Tree &HighScore, char StreamName[], unsigned StreamScore, unsigned StreamTime)
{
	if (HighScore == NULL)
	{
		HighScore = new nodeTree;
		if (HighScore == NULL)
			return false;
		HighScore->score = StreamScore;
		HighScore->time = StreamTime;
		strcpy_s(HighScore->name, StreamName);
		HighScore->left = NULL;
		HighScore->right = NULL;
		return true;
	}
	else
	{
		if (StreamScore <= HighScore->score)
		{
			if (StreamScore == HighScore->score)
			{
				if (StreamTime < HighScore->time)
					return AddBinarySearchElement(HighScore->left, StreamName, StreamScore, StreamTime);
				else
					return AddBinarySearchElement(HighScore->right, StreamName, StreamScore, StreamTime);
			}
			else
				return AddBinarySearchElement(HighScore->left, StreamName, StreamScore, StreamTime);
		}
		else
			return AddBinarySearchElement(HighScore->right, StreamName, StreamScore, StreamTime);
	}
}


void BinarySearchTreePostOrder(Tree HighScore)
{
	if (HighScore == NULL)
		return;
	BinarySearchTreePostOrder(HighScore->right);
	HighScoresSorted[PositionHighScore] = HighScore->score;
	TimeSorted[PositionHighScore] = HighScore->time;
	strcpy_s(HighScoresNameSorted[PositionHighScore++], HighScore->name);
	BinarySearchTreePostOrder(HighScore->left);
}

void ReadHighScores(Tree &HighScore)
{
	ifstream ReadHighScore("highscore.in");
	unsigned StreamScore, StreamTime;
	char StreamName[20];
	while (ReadHighScore >> StreamScore)
	{
		ReadHighScore >> StreamTime;
		ReadHighScore >> StreamName;
		AddBinarySearchElement(HighScore, StreamName, StreamScore, StreamTime);
	}
	ReadHighScore.close();
}

void UpdateHighScore()
{
	Tree HighScore = NULL;
	ReadHighScores(HighScore);
	AddBinarySearchElement(HighScore, NewName, NewScore, NewTime);
	PositionHighScore = 0;
	ofstream ReadAndWriteHighScore("highscore.in");
	BinarySearchTreePostOrder(HighScore);
	unsigned i;
	for (i = 0; i < PositionHighScore && i < 10; i++)
	{
		ReadAndWriteHighScore << HighScoresSorted[i] << " ";
		ReadAndWriteHighScore << TimeSorted[i] << " ";
		ReadAndWriteHighScore << HighScoresNameSorted[i] << " ";
		ReadAndWriteHighScore << endl;
	}
	ReadAndWriteHighScore.close();
}

void PrintHighScores(char map[][110], ObstacleQueue Pipe, player bird)
{
	Tree HighScore = NULL;
	PositionHighScore = 0;
	ReadHighScores(HighScore);
	BinarySearchTreePostOrder(HighScore);
#if (defined (_WIN32) || defined (_WIN64))
	system("cls");
#elif (defined (LINUX) || defined (__linux__))
	system("clear");
#endif
	MoveCursorTo(1, 1);
	cout << " ---------------------------------------------------- ";
	MoveCursorTo(2, 1);
	cout << "| RANK |         NAME         |   TIME   |   SCORE   |";
	MoveCursorTo(3, 1);
	cout << " ---------------------------------------------------- ";
	unsigned i;
	for (i = 0; i < PositionHighScore&&i < 10; i++)
	{
		MoveCursorTo(4 + 2 * i, 1);
		cout << "|   " << i + 1;
		MoveCursorTo(4 + 2 * i, 8);
		cout << "| " << HighScoresNameSorted[i];
		MoveCursorTo(4 + 2 * i, 31);
		cout << "| " << TimeSorted[i];
		MoveCursorTo(4 + 2 * i, 42);
		cout << "| " << HighScoresSorted[i];
		MoveCursorTo(4 + 2 * i, 54);
		cout << "|";
		MoveCursorTo(5 + 2 * i, 1);
		cout << " ---------------------------------------------------- ";
	}
	cout << endl;
	cout << "Do you want to return to the menu? Press '1' if you want or '2' if you want to exit the game.";
	char ButtonPressed;
	do
	{
		ButtonPressed = _getch();
	} while (ButtonPressed<'1' || ButtonPressed>'2');
	if (ButtonPressed == '1')
		Menu(map, Pipe, bird);
	else
		return;
}

void Menu(char Map[][110], ObstacleQueue &Pipe, player bird)
{
	PrintMenu();
	char ButtonPressed;
	do
	{
		ButtonPressed = _getch();
	} while (ButtonPressed > '4' || ButtonPressed < '1');
	ButtonPressed = GetMenuPressedKey(ButtonPressed);
	if (ButtonPressed == 1)
	{
#if (defined (_WIN32) || defined (_WIN64))
		system("cls");
#elif (defined (LINUX) || defined (__linux__))
		system("clear");
#endif
		cout << "What player name do you want? (the name should be shorter than 20 character) : ";
		cin.get(NewName, 19);
		TimeOfStart = clock();
		gameplay(bird, Map, Pipe);
		NewTime = (clock() - TimeOfStart) / CLOCKS_PER_SEC;
		UpdateHighScore();
		return;
	}
	else if (ButtonPressed == '2')
	{
		PrintHighScores(Map, Pipe, bird);
	}
	else if (ButtonPressed == 4)
	{
		esc = true;
		return;
	}
}


int main()
{
	char map[25][110];
	unsigned b;
	player bird;
	HideCursor();
	MatricSpace(map);
	ObstacleQueue Pipe;
	InitializeObstacleQueueu(Pipe);
	Menu(map, Pipe, bird);
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
	Sleep(1000);
	return 0;
}
