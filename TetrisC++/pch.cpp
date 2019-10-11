#include "pch.h"
#include <iostream>
#include <time.h>
#include<windows.h>
#include<conio.h>

using namespace std;

int Piece::GetRand(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

void Piece::Initial()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置标题
	SetConsoleTitleA("俄罗斯方块");
	COORD dSize = { WINDOW_WIDTH,WINDOW_HEIGHT };
	//设置窗口缓冲区大小
	SetConsoleScreenBufferSize(h, dSize);
	//隐藏光标
	CONSOLE_CURSOR_INFO _cursor = { 1,false };
	SetConsoleCursorInfo(h, &_cursor);

	score = 0;
	gameOver = false;
	gameQuit = false;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if ( i == STAGE_HEIGHT - 1 ||j == 0||  j == STAGE_WIDTH - 1)
			{
				box_map[i][j] = 1;
				SetPos(j, i);
				cout << "#";
			}
			else
			{
				box_map[i][j] = 0;
			}
		}
	}

	//生成随机数种子
	srand((unsigned int)time(0));
	//初始化方块形状
	shape = GetRand(0, 6);
	SetShape(shape, box_shape, size_w, size_h);
	color = GetRand(0, 5);

	next_shape = GetRand(0, 6);
	SetShape(next_shape, next_box_shape, next_size_w, next_size_h);
	next_color = GetRand(0, 5);

	SetPos(73, 11);
	cout << "● 下一个方块：";
	//显示下一个方块
	ShowNext();

	SetColor(0x0F);
	//显示分数
	SetPos(73, 18);
	cout << "● 当前积分：";
	SetPos(90,18);
	cout << score;
}

void Piece::SetPos(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = CORNER_X + x + THICKNESS;
	pos.Y = CORNER_Y + y + THICKNESS;
	SetConsoleCursorPosition(h, pos);
}

void Piece::SetColor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

void Piece::DrawMap()
{
	////清屏操作
	//system("cls");
	//SetColor(COLOR_WALL);

	//for (int i = 0; i < STAGE_HEIGHT; i++)
	//{
	//	SetPos(-THICKNESS - 1, i);
	//	for (int j = 0; j < STAGE_WIDTH + THICKNESS * 2; j++)
	//	{
	//		if (j == 0)
	//		{
	//			cout << "■";
	//		}
	//		else if (j == STAGE_WIDTH + THICKNESS)
	//		{
	//			cout << "■";
	//		}
	//		else
	//		{
	//			cout << " ";
	//		}
	//	}
	//	SetPos(-THICKNESS - 1, STAGE_HEIGHT);
	//	for (int i = 0; i < STAGE_WIDTH / 2 + THICKNESS * 2; i++)
	//	{
	//		cout << "■";
	//	}
	//	cout << endl;
	//}
	//	
	int i, j, line;
	//system("cls");
	for (i = 0; i < STAGE_HEIGHT; i++)
	{
		line = 0;
		SetPos(line, i);
		for (j = 0; j < STAGE_WIDTH; j++)
		{
			switch (box_map[i][j])
			{
			case 0:
				SetColor(COLOR_BG);
				cout << "  ";
				break;
			case 1:
				SetColor(COLOR_WALL);
				cout << "■";
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				SetColor(pieceColors[box_map[i][j] - 2]);
				cout << "■";
				break;
			}
		}
		line++;
	}
}

void Piece::Prompt_info(int x, int y)
{
	SetColor(COLOR_TEXT);
	int initialX = 70;
	int initialY = 0;

	SetPos(x + initialX, y + initialY);
	SetPos(x + initialX, y + initialY);
	cout << "■ 操作说明";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	向左移动：←A";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	向右移动：→D";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	旋转：↑W";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	加速下落：↓S";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	开始游戏：任意方向键";
	initialY++;
	SetPos(x + initialX, y + initialY);
	cout << "		□	退出游戏：X键退出";
	initialY++;
}

void Piece::SetShape(int & cshape, int shape[][4], int & size_w, int & size_h)
{
	//初始化当前形状数组
	int i, j;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			shape[i][j] = 0;
		}
	}

	//设置7中初始形状以及他们的size
	switch (cshape)
	{
		//I形
		case 0:
			size_h = 1;
			size_w = 4;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[0][2] = 1;
			shape[0][3] = 1;
			break;
		//L形
		case 1:
			size_h = 2;
			size_w = 3;
			shape[0][0] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		//J形
		case 2:
			size_h = 2;
			size_w = 3;
			shape[0][2] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		//Z形
		case 3:
			size_h = 2;
			size_w = 3;
			shape[0][1] = 1;
			shape[0][2] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			break;
		//S形
		case 4:
			size_h = 2;
			size_w = 3;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
		//O形
		case 5:
			size_h = 2;
			size_w = 2;
			shape[0][0] = 1;
			shape[0][1] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			break;
		//T形
		case 6:
			size_h = 2;
			size_w = 3;
			shape[0][1] = 1;
			shape[1][0] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			break;
	}


	//设置方块的初始位置
	head_x = STAGE_WIDTH / 2;
	head_y = 1;

	//将方块映射到数组中
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		box_map[head_x + j][head_y + i] = shape[j][i];
	//	}
	//}

	//越界
	if (IsAggin())
	{
		gameOver = true;
	}
}

void Piece::Judge()
{
	int i, j, line = 0;
	bool full;
	for (i = 1; i < STAGE_HEIGHT - 1; i++)
	{
		full = true;
		for (j = 1; j < STAGE_WIDTH - 1; j++)
		{
			if (box_map[i][j] == 0)
			{
				full = false;
			}
		}
		if (full)
		{
			line++;
			score += 50;
			for (j = 1; j < STAGE_WIDTH - 1; j++)
			{
				box_map[i][j] = 0;
			}
		}
	}

	if (line != 0)
	{
		//如果消除了一行 从最底部的行向上找直到找到空行(刚被消除的行)
		for (i = STAGE_HEIGHT - 2; i >= 2; i--)
		{
			int s = i;
			if (!Exsqr(i))
			{
				//从被消除的行开始往上找直到找到第一个非空行
				while (s > 1 && !Exsqr(--s));
				for (j = 1; j < STAGE_WIDTH - 1; j++)
				{
					box_map[i][j] = box_map[s][j];
					box_map[s][j] = 0;
				}
			}
		}
	}
	//重新绘制
	for (int i = 1; i < STAGE_HEIGHT - 1; i++)
	{
		for (int j = 1; j < STAGE_WIDTH - 1; j++)
		{
			/*if (box_map[i][j] == 1) {
				SetPos(j, i);
				SetColor(pieceColors[color]);
				cout << "#";
			}
			else
			{
				SetPos(j, i);
				SetColor(COLOR_BG);
				cout << " ";
			}*/

			if (box_map[i][j] == 0) {
				SetPos(j, i);
				SetColor(COLOR_BG);
				cout << " ";
			}
			else
			{
				SetPos(j, i);
				SetColor(pieceColors[box_map[i][j] - 1]);
				cout << "#";
			}
			
		}
	}
}

void Piece::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		default:
			break;
		}
	}
}

void Piece::Move()
{
	//方块自由下落
	head_y++;
	//碰到底部处理
	if (IsAggin())
	{
		head_y--;
		for(int i = 0; i < size_h; i++)
			for (int j = 0; j < size_w; j++)
			{
				if (box_shape[i][j] == 1)
				{
					box_map[head_y + i][head_x + j] = color + 1;
				}
			}
		Score_Next();
	}
	else
	{
		for(int i = size_h - 1; i >= 0; i--)
			for (int j = 0; j < size_w; j++)
			{
				if (box_shape[i][j] == 1)
				{
					//删除上一帧的图案并绘制当前图案
					SetColor(COLOR_BG);
					SetPos(head_x + j, head_y + i - 1);
					cout << " ";
					SetColor(pieceColors[color]);
					SetPos(head_x + j, head_y + i);
					cout << "#";
				}
			}
	}
	//向左移动
	if (dir == LEFT)
	{
		dir = STOP;
		head_x--;
		if (IsAggin())
		{
			head_x++;
		}
		else {
			for (int i = 0; i < size_h; i++)
			{
				for (int j = 0; j < size_w; j++)
				{
					if (box_shape[i][j] == 1)
					{
						//删除上一帧的图案并绘制当前图案
						SetColor(COLOR_BG);
						SetPos(head_x + j + 1, head_y + i);
						cout << " ";
						SetColor(pieceColors[color]);
						SetPos(head_x + j, head_y + i);
						cout << "#";
					}
				}
			}
		}
	}
	//向右移动
	if (dir == RIGHT)
	{
		dir = STOP;
		head_x++;
		if (IsAggin())
		{
			head_x--;
		}
		else {
			for (int i = size_h - 1; i >= 0; i--)
			{
				for (int j = size_w - 1; j >= 0; j--)
				{
					if (box_shape[i][j] == 1)
					{
						//删除上一帧的图案并绘制当前图案
						SetColor(COLOR_BG);
						SetPos(head_x + j - 1, head_y + i);
						cout << " ";
						SetColor(pieceColors[color]);
						SetPos(head_x + j, head_y + i);
						cout << "#";
					}
				}
			}
		}
	}

	if (dir == DOWN)
	{
		dir = STOP;
		head_y++;
		if (IsAggin())
		{
			head_y--;
			for (int i = 0; i < size_h; i++)
				for (int j = 0; j < size_w; j++)
				{
					if (box_shape[i][j] == 1)
					{
						box_map[head_y + i][head_x + j] = color+1;
					}
				}
			Score_Next();
		}
		else
		{
			for (int i = size_h - 1; i >= 0; i--)
				for (int j = 0; j < size_w; j++)
				{
					if (box_shape[i][j] == 1)
					{
						//删除上一帧的图案并绘制当前图案
						SetColor(COLOR_BG);
						SetPos(head_x + j, head_y + i - 1);
						cout << " ";
						SetColor(pieceColors[color]);
						SetPos(head_x + j, head_y + i);
						cout << "#";
					}
				}
		}

	}

	if (dir == UP)
	{
		Rotate();
		dir = STOP;
	}
		

	if (head_x + size_w + 1 > STAGE_WIDTH)
	{
		head_x = STAGE_WIDTH - size_w - 1;
	}
	if (head_x < 1)
	{
		head_x = 1;
	}
}

void Piece::Rotate()
{
	int temp[4][4] = { 0 };	//临时数组
	int temp_piece[4][4] = { 0 };		
	int tmp_size_w, tmp_size_h;
	int i, j;

	tmp_size_w = size_w;
	tmp_size_h = size_h;

	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			//备份当前数组，当旋转失败恢复原状
			temp_piece[i][j] = box_shape[i][j];
		}
	//斜对角线对称
	for(i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			temp[j][i] = box_shape[i][j];
		}
	//调整size
	int t = size_h;
	size_h = size_w;
	size_w = t;
	for( i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			box_shape[i][j] = 0;
		}
	//左右对称
	for(i = 0; i < size_h; i++)
		for (j = 0; j < size_w; j++)
		{
			box_shape[i][size_w - 1 - j] = temp[i][j];
		}
	
	//如果旋转后的图形不符合条件，恢复原图形
	if (IsAggin())
	{
		for(i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				box_shape[i][j] = temp_piece[i][j];
			}
		size_h = tmp_size_h;
		size_w = tmp_size_w;

	}
	//旋转成功就进行绘制
	else
	{
		//清除原来的图形
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (temp_piece[i][j] == 1)
				{
					SetColor(COLOR_BG);
					SetPos(head_x + j, head_y + i);
					cout << " ";
				}
			}
		}
		//绘制新的图形
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (box_shape[i][j] == 1)
				{
					SetPos(head_x + j, head_y + i);
					SetColor(pieceColors[color]);
					cout << "#";
				}
			}
		}
	}
}

bool Piece::IsAggin()
{
	for(int i = 0 ; i < size_h ; i++)
		for (int j = 0; j < size_w; j++) {
			if (box_shape[i][j] == 1)
			{
				if (head_y + i > STAGE_HEIGHT - 2)
					return true;
				if (head_x + j  > STAGE_WIDTH - 2 || head_x + j - 1 < 0)
					return true;
				if (box_map[head_y + i][head_x + j] != 0)
					return true;
			}
		}
	return false;
}

bool Piece::Exsqr(int row)
{
	for (int i = 1; i < STAGE_WIDTH - 1; i++)
	{
		if (box_map[row][i] != 0)
			return true;
	}
	return false;
}

void Piece::Score_Next()
{
	score += 10;
	Judge();

	//显示分数
	SetColor(0x0F);
	SetPos(90, 18);
	cout << score;

	SetShape(next_shape, box_shape, size_w, size_h);
	color = next_color;

	next_shape = GetRand(0, 6);
	SetShape(next_shape, next_box_shape, next_size_w, next_size_h);
	next_color = GetRand(0, 5);
	
	//显示下一个方块
	ShowNext();
}

void Piece::ShowNext()
{
	//显示下一个方块
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
				SetPos(80 + j, 13 + i);
				cout << " ";
		}
	//显示下一个方块
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (next_box_shape[i][j] == 1)
			{
				SetColor(pieceColors[next_color]);
				SetPos(80 + j, 13 + i);
				cout << "#";
			}
		}
}

void Piece::ShowGameOverInfo()
{
	SetPos(5, 8);
	SetColor(COLOR_TEXT);
	cout << "游戏结束！";
	SetPos(3, 9);
	SetColor(COLOR_TEXT);
	cout << "Y重新开始/N退出";
}
