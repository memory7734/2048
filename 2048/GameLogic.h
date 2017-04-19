#pragma once
#include"global.h"

class CGameLogic
{
public:
	CGameLogic();			//���캯��
	~CGameLogic();			//��������
	int** InitMap();					//��ʼ����ͼ
	void ReleaseMap(int** &pGameMap);	//�ͷŵ�ͼ
	bool MoveLeft(int** &pGameMap);		//�����ƶ�
	bool MoveRight(int** &pGameMap);	//�����ƶ�
	bool MoveUp(int** &pGameMap);		//�����ƶ�
	bool MoveDown(int** &pGameMap);		//�����ƶ�
	bool NewBlock(int** &pGameMap);		//����һ���µ�ģ��
	bool AddLeft(int** &pGameMap, int &score);	//�������
	bool AddRight(int** &pGameMap, int &score);	//�������
	bool AddUp(int** &pGameMap, int &score);	//�������
	bool AddDown(int** &pGameMap, int &score);	//�������
	bool JudgeWin(int** &pGameMap);		//�ж��Ƿ�ʤ��
	bool JudgeLose(int** &pGameMap);	//�ж��Ƿ�ʧ��

};

