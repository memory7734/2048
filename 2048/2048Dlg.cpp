
// 2048Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy2048Dlg �Ի���



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


// CMy2048Dlg ��Ϣ�������

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	GetDlgItem(ID_START)->SetWindowPos(NULL, MAP_LEFT + (PADDING + ELEMENT_SIZE) * 3 + PADDING, 152, 0, 0, SWP_NOZORDER | SWP_NOSIZE);	//���ÿ�ʼ��ť��λ�úʹ�С
	InitElement();					//��ʼ��Ԫ��
	UpdateWindow();					//���µ�ͼ
	start = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
						   // TODO: �ڴ˴������Ϣ����������
						   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
		//���ڴ�DC����
		dc.BitBlt(MAP_LEFT, MAP_TOP, MAP_SIZE, MAP_SIZE, &m_dcMem, 0, 0, SRCCOPY);
		//��2048logo����
		dc.BitBlt(MAP_LEFT, 40, 194, 112, &m_dcLogo, 0, 0, SRCCOPY);
		//���Ʒ���
		DrawScore();

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ʼ��ͼƬԪ��
void CMy2048Dlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);

	//����BMPͼƬ��Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(hBmpBG);

	//����BMPͼƬ��Դ
	HANDLE hBmpLogo = ::LoadImage(NULL, _T("theme\\picture\\logo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcLogo.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcLogo.SelectObject(hBmpLogo);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, MAP_SIZE, MAP_SIZE);
	m_dcMem.SelectObject(&bmpMem);


	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, MAP_SIZE, MAP_SIZE, &m_dcBG, 0, 0, SRCCOPY);

	//����BMPͼƬ��Դ
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\2048.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcElement.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcElement.SelectObject(hBmp);


}

//���´���
void CMy2048Dlg::UpdateWindow()
{
	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//��ô��ڴ�С
	this->GetClientRect(rtClient);	//��ÿͻ�����С
									//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//���ô��ڴ�С
	MoveWindow(0, 0, GAME_WIDTH + nSpanWidth, GAME_HEIGHT + nSpanHeight);

	//ʹ���ھ���
	CenterWindow();
}

//���µ�ͼ
void CMy2048Dlg::UpdateMap()
{
	//����ͼƬ�Ķ���������ͼƬ��С
	int nLeft = PADDING;
	int nTop = PADDING;
	int nElemSize = ELEMENT_SIZE;
	m_dcMem.BitBlt(0, 0, MAP_SIZE, MAP_SIZE, &m_dcBG, 0, 0, SRCCOPY);

	//ѭ������ͼƬ
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
	//��ʼ����ͼ
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

	//���½���
	UpdateMap();

	//���´���
	InvalidateRect(FALSE);
}






BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	CString strTitle;
	this->GetWindowTextW(strTitle);
	//��Ϸ��ʼ���м��̰����¼�
	if (start&&pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			//������ӳɹ��������һ���������ж��Ƿ�ʧ��
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
			//������ӳɹ��������һ���������ж��Ƿ�ʧ��
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
			//������ӳɹ��������һ���������ж��Ƿ�ʧ��
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
			//������ӳɹ��������һ���������ж��Ƿ�ʧ��
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
	//�ж��Ƿ�ɹ�
	if ((!win) && gameLogic.JudgeWin(m_pGameMap))
	{
		win = true;
		UpdateMap();
		InvalidateRect(FALSE);
		MessageBox(_T("YOU WIN!"), strTitle);
	}
	//�����µķ���
	gameLogic.NewBlock(m_pGameMap);
	UpdateMap();
	InvalidateRect(FALSE);
	return false;
}


void CMy2048Dlg::DrawScore()
{
	//����DC
	CClientDC dc(this);
	//��������
	CFont font;
	//���������С����
	font.CreatePointFont(200, _T("Clear Sans"));
	dc.SelectObject(&font);
	//����������ɫ�뱳��ɫ
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
