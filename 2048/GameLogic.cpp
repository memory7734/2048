#include "stdafx.h"
#include "GameLogic.h"

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

int** CGameLogic::InitMap()			//��ʼ����ͼ
{
	//�����ڴ�����
	int** pGameMap = new int*[MAX_ROW_COL];
	if (pGameMap == NULL)		//����ʧ�ܷ��ش���
	{
		//throw new CGameException("�ڴ�����쳣�� \n");
		return 0;
	}
	else
	{
		for (int i = 0; i < MAX_ROW_COL; i++)
		{
			pGameMap[i] = new int[MAX_ROW_COL];
			if (pGameMap[i] == NULL)		//����ʧ�ܷ��ش���
			{
				//throw new CGameException("�ڴ�����쳣�� \n");
				return 0;
			}
			memset(pGameMap[i], BLANK, sizeof(int)*MAX_ROW_COL);	//��ʼ������
		}
	}
	//��������
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


	// ������⽻����������
	int nVertexNum = MAX_ROW_COL*MAX_ROW_COL;
	for (int i = 0; i < nVertexNum; i++)
	{
		//����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;

		//����������ֵ
		int nTmp = pGameMap[nIndex1 / MAX_ROW_COL][nIndex1%MAX_ROW_COL];
		pGameMap[nIndex1 / MAX_ROW_COL][nIndex1%MAX_ROW_COL] = pGameMap[nIndex2 / MAX_ROW_COL][nIndex2%MAX_ROW_COL];
		pGameMap[nIndex2 / MAX_ROW_COL][nIndex2%MAX_ROW_COL] = nTmp;
	}
	//���ص�ͼָ��
	return pGameMap;
}

void CGameLogic::ReleaseMap(int** &pGameMap)	//�ͷŵ�ͼ
{
	//�ͷŵ�ͼ�ռ�
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;

}


bool CGameLogic::NewBlock(int** &pGameMap)
{
	//��������
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
	//�����ƶ�
	bool moved = MoveDown(pGameMap);
	//���ڵ�����ģ�����������ӣ����������
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
	//�ж��Ƿ��ڷ����г���2048
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
	//�����Ƿ��пշ���
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			if (pGameMap[i][j] == BLANK)
				return false;
		}
	}
	//�����Ƿ�������������ڷ���ʵ�����
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
