#include "stdafx.h"


using namespace std;

const int ROW = 4;
const int COL = 4;
int pix[ROW][COL] = { 0 };

//上下左右  
int const UP = 1;
int const DOWN = 2;
int const LEFT = 3;
int const RIGHT = 4;

//游戏所处的状态  
int const GAME_OVER = 1;
int const GAME_WIN = 2;
int const GAME_CONTINUE = 3;



enum Num {
	Num_2 = 2,
	Num_4 = 4,
	Num_8 = 8,
	Num_16 = 16,
	Num_32 = 32,
	Num_64 = 64,
	Num_128 = 128,
	Num_256 = 256,
	Num_512 = 512,
	Num_1024 = 1024,
	Num_2048 = 2048,


};
void Print(void)
{
	system("cls");
	cout << "************* 2048 控制台程序**************" << endl << endl;
	cout << "*********** by HUSTer 2018-2-7*************" << endl << endl;
	cout << endl << endl;
	for (int i = 0; i< ROW; i++)
	{
		cout << "---------------------------------" << endl;
		for (int j = 0; j<COL; j++)
		{
			if (pix[i][j] == 0)
			{
				cout << "|    \t";

			}
			else {
				cout << "|   " << pix[i][j] << "\t";
			}
		}
		cout << "|" << endl;
	}
	cout << "---------------------------------" << endl;

}

bool CreatNumber()
{
	int RandNum = rand() % 3;
	int r = 0;
	vector<int> index;  //记录空白格

	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if (!pix[i][j])
			{
				index.push_back(i * 4 + j);  //记录记录空白格的索引
			}
		}
	if (index.empty())
	{
		return false;
	}
	else {                    //找到空白点
		Num CreatNum;
		r = rand() % index.size();   //index.size = 16 
		if (RandNum == 0)
		{
			CreatNum = Num_4;  //1/3概率是4

		}
		else {
			CreatNum = Num_2;   //2/3概率是2
		}
		pix[index[r] / 4][index[r] % 4] = CreatNum; //给空白处一个数据
	}
	return true;
}

int Input()
{
	//读取上下左右四个方向键  
	int upArrow = 0;
	int downArrow = 0;
	int leftArrow = 0;
	int rightArrow = 0;
	int direction = 0;
	while (true)
	{
		upArrow = GetAsyncKeyState(VK_UP);
		downArrow = GetAsyncKeyState(VK_DOWN);
		leftArrow = GetAsyncKeyState(VK_LEFT);
		rightArrow = GetAsyncKeyState(VK_RIGHT);

		if (upArrow)
		{
			direction = UP;
			break;
		}
		else if (downArrow)
		{
			direction = DOWN;
			break;
		}
		else if (leftArrow)
		{
			direction = LEFT;
			break;
		}
		else if (rightArrow)
		{
			direction = RIGHT;
			break;
		}

		Sleep(100);
	}

	return direction;
}

void Process(int dir)
{
	switch (dir)      //根据按键指示进行处理
	{                //感觉还有进一步提升的空间
	case UP:
		for (int i = 1; i < ROW; i++)
			for (int j = 1; j < ROW; j++)
				for (int k = 0; k < COL; k++)
				{
					if (pix[j - 1][k] == pix[j][k])
					{
						pix[j - 1][k] *= 2;
						pix[j][k] = 0;
					}
					else
					{
						if (pix[j - 1][k] == 0)
						{
							pix[j - 1][k] = pix[j][k];
							pix[j][k] = 0;
						}
					}
				}
		break;
	case DOWN:
		for (int i = ROW - 1; i > 0; i--)
			for (int j = ROW - 1; j >0; j--)
				for (int k = 0; k < COL; k++)
				{
					if (pix[j][k] == pix[j - 1][k])
					{
						pix[j][k] *= 2;
						pix[j - 1][k] = 0;
					}
					else
					{
						if (pix[j][k] == 0)
						{
							pix[j][k] = pix[j - 1][k];
							pix[j - 1][k] = 0;
						}
					}
				}
		break;
	case LEFT:
		for (int i = 1; i < COL; i++)
			for (int j = 1; j < COL; j++)
				for (int k = 0; k < ROW; k++)
				{
					if (pix[k][j - 1] == pix[k][j])
					{
						pix[k][j - 1] *= 2;
						pix[k][j] = 0;
					}
					else
					{
						if (pix[k][j - 1] == 0)
						{
							pix[k][j - 1] = pix[k][j];
							pix[k][j] = 0;
						}
					}
				}
		break;
	case RIGHT:
		for (int i = COL - 1; i > 0; i--)
			for (int j = COL - 1; j >0; j--)
				for (int k = 0; k < ROW; k++)
				{
					if (pix[k][j] == pix[k][j - 1])
					{
						pix[k][j] *= 2;
						pix[k][j - 1] = 0;
					}
					else
					{
						if (pix[k][j] == 0)
						{
							pix[k][j] = pix[k][j - 1];
							pix[k][j - 1] = 0;
						}
					}
				}
		break;
	default:break;
	}



}
int Judge()
{

	//赢得游戏  
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (pix[i][j] == 2048)
			{
				return GAME_WIN;
				break;
			}
		}
	}

	//横向检查  
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL - 1; ++j)
		{
			if (!pix[i][j] || (pix[i][j] == pix[i][j + 1]))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//纵向检查  
	for (int j = 0; j< COL; ++j)
	{
		for (int i = 0; i < ROW - 1; ++i)
		{
			if (!pix[i][j] || (pix[i][j] == pix[i + 1][j]))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}

	//不符合上述两种状况，游戏结束  
	return GAME_OVER;

}
int main()
{
	int Direction = 0;
	int Gamstate = 0;
	srand((unsigned int)time(0));
	CreatNumber();
	CreatNumber();

	Print(); //打印控制面板

	while (1)
	{
		Gamstate = Judge();
		if (Gamstate == GAME_CONTINUE)
		{
			Direction = Input();
			Process(Direction);
			if (CreatNumber() == 0)
			{
				Gamstate = GAME_OVER;
			}

			Print();
			Sleep(100);
		}
		else if (Gamstate == GAME_WIN) {
			Print();
			cout << "Congratulation  " << "You Win！" << endl;
			break;
		}
		if (Gamstate == GAME_OVER) {
			Print();
			cout << "Sorry  " << "You lose the chance!" << endl;
			Sleep(1000);
			break;
		}
	}
	return 0;
}
