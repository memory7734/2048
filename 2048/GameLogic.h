#pragma once
#include"global.h"

class CGameLogic
{
public:
	CGameLogic();			//构造函数
	~CGameLogic();			//析构函数
	int** InitMap();					//初始化地图
	void ReleaseMap(int** &pGameMap);	//释放地图
	bool MoveLeft(int** &pGameMap);		//向左移动
	bool MoveRight(int** &pGameMap);	//向右移动
	bool MoveUp(int** &pGameMap);		//向上移动
	bool MoveDown(int** &pGameMap);		//向下移动
	bool NewBlock(int** &pGameMap);		//产生一个新的模块
	bool AddLeft(int** &pGameMap, int &score);	//向左相加
	bool AddRight(int** &pGameMap, int &score);	//向右相加
	bool AddUp(int** &pGameMap, int &score);	//向上相加
	bool AddDown(int** &pGameMap, int &score);	//向下相加
	bool JudgeWin(int** &pGameMap);		//判断是否胜利
	bool JudgeLose(int** &pGameMap);	//判断是否失败

};

