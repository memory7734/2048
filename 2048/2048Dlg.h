
// 2048Dlg.h : ͷ�ļ�
//

#pragma once
#include"global.h"
#include"GameLogic.h"

// CMy2048Dlg �Ի���
class CMy2048Dlg : public CDialogEx
{
// ����
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
private:
	int map[MAX_ROW_COL][MAX_ROW_COL];

protected:
	HICON m_hIcon;		//ϵͳͼ��
	CDC m_dcMem;		//�ڴ�DC
	CDC m_dcBG;			//����DC
	CDC m_dcElement;		//Ԫ���ڴ�DC
	CDC m_dcLogo;		//logo�ڴ�DC


	CPoint m_ptGameTop;	//��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ������꣬��������ڴ��ڿͻ�����
	CSize m_sizeElem;	//Ԫ��ͼƬ�Ĵ�С
	CRect m_rtGameRect;	//��Ϸ�����С��������Ϊ��Ϸ���������С�����ǵ�������ߣ����ܻᳬ��ͼƬһ����Χ��

	int** m_pGameMap;	//��ͼָ��
	bool start;			//��Ϸ��ʼ
	bool win;			//��Ϸ��ʤ
	int score;			//����

	CGameLogic gameLogic;	//��Ϸ������


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//��ʼ��ͼƬԪ��
	void InitElement();
	//���´���
	void UpdateWindow();
	//���µ�ͼ
	void UpdateMap();
public:
	//��ü�����Ϣ 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//������һ������
	bool NewNext();
	//���Ʒ���
	void DrawScore();
	//�����Start New Game��ť���ú���
	afx_msg void OnBnClickedStart();
};
