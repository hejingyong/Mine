// mineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mine.h"
#include "mineDlg.h"
#include<time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmineDlg 对话框




CmineDlg::CmineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CmineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_MYBUTTON,IDC_MYBUTTON+480,OnMybutton)     //单击按钮响应消息
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CmineDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_COMMAND(ID_32774, OnEasy)
	ON_COMMAND(ID_32776, OnCommon)
	ON_COMMAND(ID_32777, OnDifficult)
	ON_COMMAND(ID_32778, OnMyHelp)
	ON_COMMAND(ID_32779, OnMyAbout)
END_MESSAGE_MAP()


// CmineDlg 消息处理程序

BOOL CmineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	this->MoveWindow(400,200,240,333);  //设置主窗口位置和大小
	HBITMAP hBmp;

	//动态创建按钮和在按钮上添加图标
	for(int i=0;i<but_x;i++)
	{
		for(int j=0;j<but_y;j++)
		{
			button[i][j] = new CButton();
			button[i][j]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(i*25,j*25+50,25+i*25,25+j*25+50),this,IDC_MYBUTTON+but_y*i+j);
			button[i][j]->ShowWindow(SW_SHOW);
			hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_blank)); 
			button[i][j]->SetBitmap(hBmp);
		}
	}

	//创建静态文本并设置位置和大小
	static1 = new CStatic();
	static1->Create(_T("雷:"),WS_VISIBLE | WS_CHILD | SS_CENTER,CRect(2,23,40,43),this);
	static2 = new CStatic();
	static2->Create(_T("时:"),WS_VISIBLE | WS_CHILD | SS_CENTER,CRect(148,23,186,43),this);

	//获取“开始游戏”按钮的句柄并通过句柄设置大小和位置
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->MoveWindow(78,20,65,23);

	//设置显示时间和地雷数量的按钮--用按钮作为载体添加图片
	for(int i=0;i<5;i++)
	{
		picture[i] = new CButton();
	}
	picture[0]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(40,20,53,43),this,IDC_MYPICTURE+1);
	picture[1]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(53,20,66,43),this,IDC_MYPICTURE+2);
	picture[2]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(185,20,198,43),this,IDC_MYPICTURE+3);
	picture[3]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(198,20,211,43),this,IDC_MYPICTURE+4);
	picture[4]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(211,20,224,43),this,IDC_MYPICTURE+5);

	//加载图片
	hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d1));   
	picture[0]->SetBitmap(hBmp);
	hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0)); 
	picture[1]->SetBitmap(hBmp);
	picture[2]->SetBitmap(hBmp);
	picture[3]->SetBitmap(hBmp);
	picture[4]->SetBitmap(hBmp);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmineDlg::OnPaint()
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
		CDialog::OnPaint();
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//按钮单击响应函数
void CmineDlg::OnMybutton(UINT nID)
{
	start++;     //计算点击按钮的次数
	int number;
	number = nID-IDC_MYBUTTON;     //计算该按钮在数组中的位置

	if(start==1)     //如果第一次点击按钮就创建地雷和创建定时器
	{
		CreateMine(number);
		SetTimer(1,1000,NULL);
	}

	//如果点中地雷就游戏结束
	if(mineNum[number]==1 && mineFlag[number]==0)
	{
		int x,y;
		x = number/but_y;
		y = number%but_y;
		HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_blood));   
		button[x][y]->SetBitmap(hBmp);
		mineFlag[number] = 1;
		GameOver();
	}

	//如果该砖块没被点过
	 else if(mineFlag[number]==0)
	{
		int count = MineCount(number);
		if(count == 0)         //如果该砖块周围没有地雷就进入队列打开周围砖块
		{
			stack->top = 0;
			stack->end = 0;
			Clear(number);
		}
	}
}

int CmineDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//初始化数据
	start = 0;
	bannerNum = 0;
	timeflag = 0;
	stack = new mineStack;
	stack->top = 0;
	stack->end = 0;
	NUM = 10;           //设置地雷数量为10
	brickNumber = 81;   //设置砖块数量为81
	level = 1;          //等级设置为简单
	but_x = 9;          //设置行
	but_y = 9;			//设置列

	for(int i=0;i<brickNumber;i++)   //初始化数组
	{
		mineNum[i] = 0;
		mineFlag[i] = 0;
	}
	
	return 0;
}



BOOL CmineDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message==WM_RBUTTONDOWN)       //鼠标右击消息
	{
		POINT pt;
		::GetCursorPos(&pt);             //得到鼠标动作的位置
		
		for(int i=0;i<brickNumber;i++)
		{
			CRect r;
			::GetWindowRect(GetDlgItem(IDC_MYBUTTON+i)->GetSafeHwnd(),&r);   //得到button所在的rect

			if (PtInRect(&r,pt) && bannerNum<NUM && mineFlag[i]!=1)        //判断鼠标动作是否在button范围之内     
			{
				int x,y,j,k;
				x = i/but_y;
				y = i%but_y;
				HBITMAP hBmp;
				if(mineFlag[i]==0) //如果砖块没被点过，设置图标为红旗
				{
					hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP1));   
					button[x][y]->SetBitmap(hBmp);

					mineFlag[i] = 2;
					bannerNum++;
					j = (NUM-bannerNum)/10;
					k = (NUM-bannerNum)%10;
					
					hBmp = pictureShow(j);
					picture[0]->SetBitmap(hBmp);
					hBmp = pictureShow(k);
					picture[1]->SetBitmap(hBmp);
					break;
				}
				else if(mineFlag[i]==2)  //如果砖块已经被插旗，设置图标为问号
				{
					hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_ask));   
					button[x][y]->SetBitmap(hBmp);
					mineFlag[i] = 3;

					bannerNum--;
					j = (NUM-bannerNum)/10;
					k = (NUM-bannerNum)%10;
					
					hBmp = pictureShow(j);
					picture[0]->SetBitmap(hBmp);
					hBmp = pictureShow(k);
					picture[1]->SetBitmap(hBmp);
					break;
				}
				else if(mineFlag[i]==3)  //如果砖块为问号，设置为空白砖块
				{
					hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_blank));   
					button[x][y]->SetBitmap(hBmp);
					mineFlag[i] = 0;
				}
			}
		}
		
	}

	if(pMsg->message==WM_LBUTTONDBLCLK)       //鼠标左键双击消息
	{
		POINT pt;
		::GetCursorPos(&pt);
		for(int i=0;i<brickNumber;i++)
		{
			CRect r;
			::GetWindowRect(GetDlgItem(IDC_MYBUTTON+i)->GetSafeHwnd(),&r);   //得到button所在的rect

			if (PtInRect(&r,pt) && mineFlag[i]==1) //双击有效的砖块必须被点过
			{
				if(MineCount(i)<=BannerCount(i))   //双击有效如果插旗数量等于地雷数量
				{
					stack->top = 0;
					stack->end = 0;
					DoubleClear(i);         //清除周围砖块
				}			
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


//计算周围插旗的数量
int CmineDlg::BannerCount(int number)
{
	int count = 0;
	int x,y;
	int numberFlag;
	x = number/but_y;
	y = number%but_y;
	numberFlag = (x-1)*but_y+y-1;
	if(x-1>=0 && y-1>=0 && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = (x-1)*but_y+y;
	if(x-1>=0 && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = (x-1)*but_y+y+1;
	if(x-1>=0 && y+1<but_y && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = x*but_y+y-1;
	if(y-1>=0 && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = x*but_y+y+1;
	if(y+1<but_y && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y-1;
	if(x+1<but_x && y-1>=0 && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y;
	if(x+1<but_x && mineFlag[numberFlag]==2)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y+1;
	if(x+1<but_x && y+1<but_y && mineFlag[numberFlag]==2)
	{
		count++;
	}
	return count;
}


//计算周围地雷的数量并根据地雷数量在该砖块上添加相应数值图片
int CmineDlg::MineCount(int number)
{
	int count = 0;
	int x,y;
	x = number/but_y;
	y = number%but_y;
	int numberFlag;
	numberFlag = (x-1)*but_y+y-1;
	if(x-1>=0 && y-1>=0 && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = (x-1)*but_y+y;
	if(x-1>=0 && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = (x-1)*but_y+y+1;
	if(x-1>=0 && y+1<but_y && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = x*but_y+y-1;
	if(y-1>=0 && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = x*but_y+y+1;
	if(y+1<but_y && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y-1;
	if(x+1<but_x && y-1>=0 && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y;
	if(x+1<but_x && mineNum[numberFlag]==1)
	{
		count++;
	}

	numberFlag = (x+1)*but_y+y+1;
	if(x+1<but_x && y+1<but_y && mineNum[numberFlag]==1)
	{
		count++;
	}

	HBITMAP hBmp;
	switch(count)
	{
	case 0:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_0));
		break;
	case 1:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_1));
		break;
	case 2:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_2));
		break;
	case 3:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_3));
		break;
	case 4:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_4));
		break;
	case 5:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_5));
		break;
	case 6:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_6));
		break;
	case 7:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_7));
		break;
	case 8:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_8));
		break;
	}
	button[x][y]->SetBitmap(hBmp);	
	mineFlag[number] = 1;         //设置该砖块已被点过
	return count;
}

//游戏结束处理，显示所有未找出和找错的地雷
void CmineDlg::GameOver()
{
	int x,y;
	for(int i=0;i<brickNumber;i++)
	{
		
		if(mineNum[i]==1 && mineFlag[i]==0) //显示未找出的地雷
		{
			x = i/but_y;
			y = i%but_y;
			HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_mine));   
			button[x][y]->SetBitmap(hBmp);
			
		}
		if(mineFlag[i]==2 && mineNum[i]==0)  //显示找错的地雷
		{
			x = i/but_y;
			y = i%but_y;
			HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_error));   
			button[x][y]->SetBitmap(hBmp);
		}
		mineFlag[i]=1;
	}
	KillTimer(1);  //停止计时
}

//重新开始游戏
void CmineDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP hBmp;

	//销毁所有砖块
	for(int i=0;i<but_x;i++)
	{
		for(int j=0;j<but_y;j++)
		{
			delete button[i][j];
			button[i][j] = NULL;
		}
	}
	
	for(int i=0;i<but_x;i++)
	{
		for(int j=0;j<but_y;j++)
		{
			button[i][j] = new CButton();
			button[i][j]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(i*25,j*25+50,25+i*25,25+j*25+50),this,IDC_MYBUTTON+but_y*i+j);
			button[i][j]->ShowWindow(SW_SHOW);
			hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_blank)); 
			button[i][j]->SetBitmap(hBmp);
		}
	}

	for(int i=0;i<brickNumber;i++)
	{
		mineFlag[i] = 0;
		mineNum[i] = 0;
	}
	start = 0;
	bannerNum = 0;
	timeflag = 0;
	KillTimer(1);
 
	//根据等级显示地雷个数
	if(level==1)
	{
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d1));   
		picture[0]->SetBitmap(hBmp);
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0)); 
		picture[1]->SetBitmap(hBmp);
	}	
	else if(level==2)
	{
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d4));   
		picture[0]->SetBitmap(hBmp);
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0)); 
		picture[1]->SetBitmap(hBmp);
	}
	else
	{
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d9));   
		picture[0]->SetBitmap(hBmp);
		picture[1]->SetBitmap(hBmp);
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0)); 		
	}
	picture[2]->SetBitmap(hBmp);
	picture[3]->SetBitmap(hBmp);
	picture[4]->SetBitmap(hBmp);
}

//清除周围没有地雷砖块周围的砖块
void CmineDlg::Clear(int number)
{
	int x,y;
	stack->mineList[stack->top] = number;
	stack->top++;
	while((stack->top-stack->end)>0)
	{
		x = stack->mineList[stack->end] / but_y;
		y = stack->mineList[stack->end] % but_y;
		if(x-1>=0 && y-1>=0)
		{
			number = (x-1)*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(x-1>=0)
		{
			number = (x-1)*but_y+y;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(x-1>=0 && y+1<but_y)
		{
			number = (x-1)*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(y-1>=0)
		{
			number = x*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(y+1<but_y)
		{
			number = x*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(x+1<but_x && y-1>=0)
		{
			number = (x+1)*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(x+1<but_x)
		{
			number = (x+1)*but_y+y;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}
		if(x+1<but_x && y+1<but_y)
		{
			number = (x+1)*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
		}

		stack->end++;
	}
}

//双击时清除周围砖块
void CmineDlg::DoubleClear(int number)
{
	int x,y;
	stack->mineList[stack->top] = number;
	stack->top++;
	while((stack->top-stack->end)>0)
	{
		x = stack->mineList[stack->end] / but_y;
		y = stack->mineList[stack->end] % but_y;
		if(x-1>=0 && y-1>=0)
		{
			number = (x-1)*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)    //如果该砖块周围没有地雷就进入队列
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)     //如果其中有地雷就游戏结束
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)      //如果其中插旗错误就游戏结束
			{
				GameOver();
			}
		}
		if(x-1>=0)
		{
			number = (x-1)*but_y+y;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(x-1>=0 && y+1<but_y)
		{
			number = (x-1)*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(y-1>=0)
		{
			number = x*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(y+1<but_y)
		{
			number = x*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(x+1<but_x && y-1>=0)
		{
			number = (x+1)*but_y+y-1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(x+1<but_x)
		{
			number = (x+1)*but_y+y;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}
		if(x+1<but_x && y+1<but_y)
		{
			number = (x+1)*but_y+y+1;
			if(mineFlag[number]==0 && MineCount(number)==0)
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)
			{
				GameOver();
			}
		}

		stack->end++;
	}
}


//创建地雷
void CmineDlg::CreateMine(int number)
{
	srand((unsigned)time( NULL ));
	int k;
	for(int i=0;i<NUM;i++)
	{
		k = rand()%(brickNumber-1);
		if(mineNum[k]==0 && k!=number)
		{
			mineNum[k] = 1;
		}
		else
		{
			i--;
		}
	}
}

//定时器响应函数用来显示时间和判断游戏是否结束
void CmineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	timeflag++;
	int i,j,k,timeNum;
	timeNum = timeflag;
	i = timeNum/100;
	timeNum = timeNum - (i*100);
	j = timeNum/10;
	timeNum =timeNum -(j*10);
	k =timeNum;
	HBITMAP hBmp;
	 
	hBmp = pictureShow(i);
	picture[2]->SetBitmap(hBmp);

	hBmp = pictureShow(j);
	picture[3]->SetBitmap(hBmp);

	hBmp = pictureShow(k);
	picture[4]->SetBitmap(hBmp);

	int count = 0;
	for(int i=0;i<brickNumber;i++)
	{
		if(mineFlag[i]!=0)
		{
			count++;
		}
	}
	if(count==brickNumber)
	{
		KillTimer(1);
	}
	CDialog::OnTimer(nIDEvent);
}

HBITMAP CmineDlg::pictureShow(int number)
{
	HBITMAP hBmp;
	switch(number)
	{
	case 0:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0));
		break;
	case 1:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d1));
		break;
	case 2:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d2));
		break;
	case 3:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d3));
		break;
	case 4:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d4));
		break;
	case 5:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d5));
		break;
	case 6:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d6));
		break;
	case 7:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d7));
		break;
	case 8:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d8));
		break;
	case 9:
		hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d9));
		break;
	}
	return hBmp;
}

//菜单栏“简单”菜单项响应函数
void CmineDlg::OnEasy()
{
	
	
}

//菜单栏“一般”菜单项的响应函数
void CmineDlg::OnCommon()
{
	
}

//菜单栏“困难”菜单项的响应函数
void CmineDlg::OnDifficult()
{
	
	
}

//菜单栏“帮助”菜单项的响应函数
void CmineDlg::OnMyHelp()
{

}

//菜单栏“关于”菜单项的响应函数
void CmineDlg::OnMyAbout()
{

}