
// 2048Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy2048Dlg 对话框



CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY2048_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, &CMy2048Dlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CMy2048Dlg 消息处理程序

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	GetDlgItem(ID_START)->SetWindowPos(NULL, MAP_LEFT + (PADDING + ELEMENT_SIZE) * 3 + PADDING, 152, 0, 0, SWP_NOZORDER | SWP_NOSIZE);	//设置开始按钮的位置和大小
	InitElement();					//初始化元素
	UpdateWindow();					//更新地图
	start = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
						   // TODO: 在此处添加消息处理程序代码
						   // 不为绘图消息调用 CDialogEx::OnPaint()
		//将内存DC绘入
		dc.BitBlt(MAP_LEFT, MAP_TOP, MAP_SIZE, MAP_SIZE, &m_dcMem, 0, 0, SRCCOPY);
		//将2048logo绘入
		dc.BitBlt(MAP_LEFT, 40, 194, 112, &m_dcLogo, 0, 0, SRCCOPY);
		//绘制分数
		DrawScore();

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化图片元素
void CMy2048Dlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建于视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(hBmpBG);

	//加载BMP图片资源
	HANDLE hBmpLogo = ::LoadImage(NULL, _T("theme\\picture\\logo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建于视频内存兼容的内存DC
	m_dcLogo.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcLogo.SelectObject(hBmpLogo);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, MAP_SIZE, MAP_SIZE);
	m_dcMem.SelectObject(&bmpMem);


	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, MAP_SIZE, MAP_SIZE, &m_dcBG, 0, 0, SRCCOPY);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\2048.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建于视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);


}

//更新窗口
void CMy2048Dlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetClientRect(rtClient);	//获得客户区大小
									//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, GAME_WIDTH + nSpanWidth, GAME_HEIGHT + nSpanHeight);

	//使窗口居中
	CenterWindow();
}

//更新地图
void CMy2048Dlg::UpdateMap()
{
	//计算图片的顶点坐标与图片大小
	int nLeft = PADDING;
	int nTop = PADDING;
	int nElemSize = ELEMENT_SIZE;
	m_dcMem.BitBlt(0, 0, MAP_SIZE, MAP_SIZE, &m_dcBG, 0, 0, SRCCOPY);

	//循环绘制图片
	for (int i = 0; i < MAX_ROW_COL; i++)
	{
		for (int j = 0; j < MAX_ROW_COL; j++)
		{
			int nElemVal = m_pGameMap[i][j];
			if (nElemVal == BLANK) continue;
			m_dcMem.BitBlt(nLeft + j*(nElemSize + PADDING), nTop + i*(nElemSize + PADDING), nElemSize, nElemSize, &m_dcElement, 0, nElemSize*(nElemVal - 1), SRCCOPY);

		}
	}
}

void CMy2048Dlg::OnBnClickedStart()
{
	//初始化地图
	if (m_pGameMap == NULL)
		m_pGameMap = gameLogic.InitMap();
	else
	{
		gameLogic.ReleaseMap(m_pGameMap);
		m_pGameMap = gameLogic.InitMap();
	}
	start = true;
	win = false;
	score = 0;

	//更新界面
	UpdateMap();

	//更新窗口
	InvalidateRect(FALSE);
}






BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	CString strTitle;
	this->GetWindowTextW(strTitle);
	//游戏开始且有键盘按键事件
	if (start&&pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			//向左相加成功则产生下一个，否则判断是否失败
			if (gameLogic.AddLeft(m_pGameMap, score))
			{
				NewNext();
			}
			else if (gameLogic.JudgeLose(m_pGameMap))
			{
				MessageBox(_T("GAME OVER!"), strTitle);
			}
			break;
		case VK_RIGHT:
			//向右相加成功则产生下一个，否则判断是否失败
			if (gameLogic.AddRight(m_pGameMap, score))
			{
				NewNext();
			}
			else if (gameLogic.JudgeLose(m_pGameMap))
			{
				MessageBox(_T("GAME OVER!"), strTitle);
			}
			break;
		case VK_UP:
			//向上相加成功则产生下一个，否则判断是否失败
			if (gameLogic.AddUp(m_pGameMap, score))
			{
				NewNext();
			}
			else if (gameLogic.JudgeLose(m_pGameMap))
			{
				MessageBox(_T("GAME OVER!"), strTitle);
			}
			break;
		case VK_DOWN:
			//向下相加成功则产生下一个，否则判断是否失败
			if (gameLogic.AddDown(m_pGameMap, score))
			{
				NewNext();
			}
			else if (gameLogic.JudgeLose(m_pGameMap))
			{
				MessageBox(_T("GAME OVER!"), strTitle);
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


bool CMy2048Dlg::NewNext()
{
	CString strTitle;
	this->GetWindowTextW(strTitle);
	//判断是否成功
	if ((!win) && gameLogic.JudgeWin(m_pGameMap))
	{
		win = true;
		UpdateMap();
		InvalidateRect(FALSE);
		MessageBox(_T("YOU WIN!"), strTitle);
	}
	//产生新的方块
	gameLogic.NewBlock(m_pGameMap);
	UpdateMap();
	InvalidateRect(FALSE);
	return false;
}


void CMy2048Dlg::DrawScore()
{
	//创建DC
	CClientDC dc(this);
	//创建字体
	CFont font;
	//设置字体大小字体
	font.CreatePointFont(200, _T("Clear Sans"));
	dc.SelectObject(&font);
	//设置字体颜色与背景色
	dc.SetBkColor(RGB(187, 173, 160));
	dc.SetTextColor(RGB(119, 110, 101));

	CString string = _T(" score ");
	CString num;
	num.Format(_T("%d "), score);
	string = string + num;

	CRect rect;
	rect.top = 48;
	rect.left = 400;
	rect.bottom = 120;
	rect.right = 550;
	dc.DrawText(string, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	CFont nfont;
	nfont.CreatePointFont(130, _T("Clear Sans"));
	dc.SelectObject(&nfont);
	dc.SetBkColor(RGB(255, 255, 255));
	string = _T("Join the numbers and get to the 2048 tile!");
	dc.TextOutW(MAP_LEFT, 152, string);

}
