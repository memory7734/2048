
// 2048Dlg.h : 头文件
//

#pragma once
#include"global.h"
#include"GameLogic.h"

// CMy2048Dlg 对话框
class CMy2048Dlg : public CDialogEx
{
// 构造
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
private:
	int map[MAX_ROW_COL][MAX_ROW_COL];

protected:
	HICON m_hIcon;		//系统图标
	CDC m_dcMem;		//内存DC
	CDC m_dcBG;			//背景DC
	CDC m_dcElement;		//元素内存DC
	CDC m_dcLogo;		//logo内存DC


	CPoint m_ptGameTop;	//游戏区起始点（游戏第一张图片的顶点坐标，坐标相对于窗口客户区）
	CSize m_sizeElem;	//元素图片的大小
	CRect m_rtGameRect;	//游戏区域大小（该区域为游戏更新区域大小，考虑到后面的线，可能会超出图片一定范围）

	int** m_pGameMap;	//地图指针
	bool start;			//游戏开始
	bool win;			//游戏获胜
	int score;			//分数

	CGameLogic gameLogic;	//游戏控制类


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//初始化图片元素
	void InitElement();
	//更新窗口
	void UpdateWindow();
	//更新地图
	void UpdateMap();
public:
	//获得键盘信息 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//产生下一个方块
	bool NewNext();
	//绘制分数
	void DrawScore();
	//当点击Start New Game按钮调用函数
	afx_msg void OnBnClickedStart();
};
