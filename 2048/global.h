#pragma once
#define MAX_ROW_COL		4		//地图的行数和列数
#define PROBABILITY		8		//新种子中出现2的概率
#define GAME_WIDTH		600		//游戏界面宽度
#define GAME_HEIGHT		800		//游戏界面高度
#define MAP_LEFT		50		//地图起始点x坐标
#define MAP_TOP			200		//地图起始点y坐标
#define ELEMENT_SIZE	107		//元素宽度
#define MAP_SIZE	ELEMENT_SIZE*MAX_ROW_COL+70			//元素宽度
#define PADDING			14		//边界宽度
#define BLANK			-1		//空白元素
#define GAMEWIN			1		//游戏获胜
#define GAMING			0		//游戏进行
#define GAMELOSE		-1		//游戏失败