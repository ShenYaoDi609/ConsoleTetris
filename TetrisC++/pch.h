#ifndef PCH_H
#define PCH_H

#define STAGE_WIDTH 20	
#define STAGE_HEIGHT 30
#define WINDOW_WIDTH 90
#define WINDOW_HEIGHT 30
#define CORNER_X 1
#define CORNER_Y -1
#define THICKNESS 1
#define COLOR_WALL 0x06
#define COLOR_TEXT 0x0F
#define COLOR_BG 0x00

enum eDirection {
	STOP = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4,
};



class Piece {
public:
	int score;	//得分
	int shape;	//当前方块的形状
	int next_shape;		//下一个方块的形状

	int head_x;	//	当前方块首个box的位置
	int head_y;

	int size_h;		//当前方块的size
	int size_w;
	int color;

	int next_size_h;	//下一个方块的size
	int next_size_w;
	int next_color;

	int box_shape[4][4];	//当前方块形状的4*4数组
	int next_box_shape[4][4];	//下一个方块形状的4*4数组

	int box_map[STAGE_HEIGHT][STAGE_WIDTH];	//游戏框内的box
	
	bool gameOver;
	bool gameQuit;

	eDirection dir;
	//0:蓝	1:绿	2:浅绿	3:红	4:紫	5:黄
	int pieceColors[6] ={0x01,0x02,0x03,0x04,0x05,0x06};

public:
	int GetRand(int min, int max);//生成位于[min,max]之间的随机数
	void Initial();	//初始化
	void SetPos(int x, int y);	//设置光标位置
	void SetColor(int color);
	void DrawMap();
	void Prompt_info(int x, int y);
	void SetShape(int &cshape, int shape[][4], int &size_w, int &size_h);		//设置方块形状
	void Judge();	//判断是否有可以消的行
	void Input();	//获取输入
	void Move();	//移动方块
	void Rotate();	//旋转方块
	bool IsAggin();	//判断方块的下一次移动是否会越界或重合
	bool Exsqr(int row);		//判断当前行是否为空
	void Score_Next();
	void ShowNext();	//显示下一个方块
	void ShowGameOverInfo();	//显示游戏结束信息
};

#endif
