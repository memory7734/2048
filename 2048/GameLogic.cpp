#include "stdafx.h"
#include "GameLogic.h"

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

int** CGameLogic::InitMap()			//初始化地图
{
	//开辟内存区域
	int** pGameMap = new int*[MAX_ROW_COL];
	if (pGameMap == NULL)		//开辟失败返回错误
	{
		//throw new CGameException("内存操作异常！ \n");
		return 0;
	}
	else
	{
		for (int i = 0; i < MAX_ROW_COL; i++)
		{
			pGameMap[i] = new int[MAX_ROW_COL];
			if (pGameMap[i] == NULL)		//开辟失败返回错误
			{
				//throw new CGameException("内存操作异常！ \n");
				return 0;
			}
			memset(pGameMap[i], BLANK, sizeof(int)*MAX_ROW_COL);	//初始化数组
		}
	}
	//设置种子
	srand((int)time(NULL));

	if ((rand() % 10) <= PROBABILITY)
	{
		pGameMap[0][0] = 1;
		pGameMap[0][1] = 1;
	}
	else
	{
		pGameMap[0][0] = 1;
		pGameMap[0][1] = 2;
	}


	// 随机任意交换两个数字
	int nVertexNum = MAX_ROW_COL*MAX_ROW_COL;
	for (int i = 0; i < nVertexNum; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;

		//交换两个数值
		int nTmp = pGameMap[nIndex1 / MAX_ROW_COL][nIndex1%MAX_ROW_COL];
		pGameMap[nIndex1 / MAX_ROW_COL][nIndex1%MAX_ROW_COL] = pGameMap[nIndex2 / MAX_ROW_COL][nIndex2%MAX_ROW_COL];
		pGameMap[nIndex2 / MAX_ROW_COL][nIndex2%MAX_ROW_COL] = nTmp;
	}
	//返回地图指针
	return pGameMap;
}

void CGameLogic::ReleaseMap(int** &pGameMap)	//释放地图
{
	//释放地图空间
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;

}


bool CGameLogic::NewBlock(int** &pGameMap)
{
	//设置种子
	srand((int)time(NULL));

	int i = rand() % MAX_ROW_COL;
	int j = rand() % MAX_ROW_COL;
	while (pGameMap[i][j] != BLANK)
	{
		i = rand() % MAX_ROW_COL;
		j = rand() % MAX_ROW_COL;
	}
	if (rand() % 10 <= PROBABILITY)
		pGameMap[i][j] = 1;
	else
		pGameMap[i][j] = 2;
	return true;
}


bool CGameLogic::MoveLeft(int** &pGameMap)
{
	bool moved = false;
	for (int n = 0; n < MAX_ROW_COL; n++)
	{
		for (int i = 0; i < MAX_ROW_COL; i++)
		{
			for (int j = 0; j < MAX_ROW_COL - 1; j++)
			{
				if (pGameMap[i][j] != BLANK)
					continue;
				if (pGameMap[i][j + 1] != BLANK)
				{
					pGameMap[i][j] = pGameMap[i][j + 1];
					pGameMap[i][j + 1] = BLANK;
					moved = true;
				}
			}
		}
	}
	return moved;
}
bool CGameLogic::MoveRight(int** &pGameMap)
{
	bool moved = false;
	for (int n = 0; n < MAX_ROW_COL; n++)
	{
		for (int i = MAX_ROW_COL - 1; i >= 0; i--)
		{
			for (int j = MAX_ROW_COL - 1; j > 0; j--)
			{
				if (pGameMap[i][j] != BLANK)
					continue;
				if (pGameMap[i][j - 1] != BLANK)
				{
					pGameMap[i][j] = pGameMap[i][j - 1];
					pGameMap[i][j - 1] = BLANK;
					moved = true;
				}
			}
		}
	}
	return moved;
}
bool CGameLogic::MoveUp(int** &pGameMap)
{
	bool moved = false;
	for (int n = 0; n < MAX_ROW_COL; n++)
	{
		for (int i = 0; i < MAX_ROW_COL - 1; i++)
		{
			for (int j = 0; j < MAX_ROW_COL; j++)
			{
				if (pGameMap[i][j] != BLANK)
					continue;
				if (pGameMap[i + 1][j] != BLANK)
				{
					pGameMap[i][j] = pGameMap[i + 1][j];
					pGameMap[i + 1][j] = BLANK;
					moved = true;
				}

			}
		}
	}
	return moved;
}
bool CGameLogic::MoveDown(int** &pGameMap)
{
	bool moved = false;
	for (int n = 0; n < MAX_ROW_COL; n++)
	{
		for (int i = MAX_ROW_COL - 1; i > 0; i--)
		{
			for (int j = MAX_ROW_COL - 1; j >= 0; j--)
			{
				if (pGameMap[i][j] != BLANK)
					continue;
				if (pGameMap[i - 1][j] != BLANK)
				{
					pGameMap[i][j] = pGameMap[i - 1][j];
					pGameMap[i - 1][j] = BLANK;
					moved = true;
				}

			}
		}
	}
	return moved;
}


bool CGameLogic::AddLeft(int** &pGameMap, int &score)
{
	bool moved = MoveLeft(pGameMap);
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL - 1; j++)
		{
			if (pGameMap[i][j] == BLANK)
				continue;
			if (pGameMap[i][j] == pGameMap[i][j + 1])
			{
				pGameMap[i][j]++;
				pGameMap[i][j + 1] = BLANK;
				score += (1 << pGameMap[i][j]);
				moved = true;
			}
		}
	}
	if (moved)
		MoveLeft(pGameMap);
	else
		moved = MoveLeft(pGameMap);
	return moved;
}
bool CGameLogic::AddRight(int** &pGameMap, int &score)
{
	bool moved = MoveRight(pGameMap);
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = MAX_ROW_COL - 1; j >0; j--)
		{
			if (pGameMap[i][j] == BLANK)
				continue;
			if (pGameMap[i][j] == pGameMap[i][j - 1])
			{
				pGameMap[i][j]++;
				pGameMap[i][j - 1] = BLANK;
				score += (1 << pGameMap[i][j]);
				moved = true;
			}
		}
	}
	if (moved)
		MoveRight(pGameMap);
	else
		moved = MoveRight(pGameMap);
	return moved;
}
bool CGameLogic::AddUp(int** &pGameMap, int &score)
{
	bool moved = MoveUp(pGameMap);
	for (int i = 0; i < MAX_ROW_COL - 1; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == BLANK)
				continue;
			if (pGameMap[i][j] == pGameMap[i + 1][j])
			{
				pGameMap[i][j]++;
				pGameMap[i + 1][j] = BLANK;
				score += (1 << pGameMap[i][j]);
				moved = true;
			}
		}
	}
	if (moved)
		MoveUp(pGameMap);
	else
		moved = MoveUp(pGameMap);
	return moved;
}
bool CGameLogic::AddDown(int** &pGameMap, int &score)
{
	//向下移动
	bool moved = MoveDown(pGameMap);
	//相邻的两个模块如果可以相加，则向下相加
	for (int i = MAX_ROW_COL - 1; i >0; i--)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == BLANK)
				continue;
			if (pGameMap[i][j] == pGameMap[i - 1][j])
			{
				pGameMap[i][j]++;
				pGameMap[i - 1][j] = BLANK;
				score += (1 << pGameMap[i][j]);
				moved = true;
			}
		}
	}
	if (moved)
		MoveDown(pGameMap);
	else
		moved = MoveDown(pGameMap);
	return moved;
}


bool CGameLogic::JudgeWin(int** &pGameMap)
{
	//判断是否在方块中出现2048
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == 11)
				return true;
		}
	}
	return false;
}
bool CGameLogic::JudgeLose(int** &pGameMap)
{
	//查找是否有空方块
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == BLANK)
				return false;
		}
	}
	//查找是否可以有两个相邻方块实现相加
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL - 1; j++)
		{
			if (pGameMap[i][j] == pGameMap[i][j + 1])
				return false;
		}
	}
	for (int i = 0; i < MAX_ROW_COL - 1; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == pGameMap[i + 1][j])
				return false;
		}
	}
	return true;
}
