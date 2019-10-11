// TetrisC++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include<windows.h>
#include<conio.h>

int main()
{
	Piece p;
	do {
		p.Initial();
		//p.DrawMap();
		p.Prompt_info(3, 1);
		while (!p.gameOver) {
			//p.DrawMap();
			p.Input();
			p.Move();
			Sleep(200);
		}
		p.ShowGameOverInfo();
		while (p.gameOver)
		{
			if (_kbhit())
			{
				switch (_getch())
				{
				case'y':
				case 'Y':
					p.gameOver = false;
					system("cls");
					break;
				case 'n':
				case'N':
					p.gameOver = false;
					p.gameQuit = true;
					break;
				default:
					break;
				}
			}
		}
	} while (!p.gameQuit);
	
}

