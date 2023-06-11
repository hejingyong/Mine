// mineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mine.h"
#include "mineDlg.h"
#include<time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmineDlg �Ի���




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
	ON_COMMAND_RANGE(IDC_MYBUTTON,IDC_MYBUTTON+480,OnMybutton)     //������ť��Ӧ��Ϣ
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


// CmineDlg ��Ϣ�������

BOOL CmineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	this->MoveWindow(400,200,240,333);  //����������λ�úʹ�С
	HBITMAP hBmp;

	//��̬������ť���ڰ�ť�����ͼ��
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

	//������̬�ı�������λ�úʹ�С
	static1 = new CStatic();
	static1->Create(_T("��:"),WS_VISIBLE | WS_CHILD | SS_CENTER,CRect(2,23,40,43),this);
	static2 = new CStatic();
	static2->Create(_T("ʱ:"),WS_VISIBLE | WS_CHILD | SS_CENTER,CRect(148,23,186,43),this);

	//��ȡ����ʼ��Ϸ����ť�ľ����ͨ��������ô�С��λ��
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->MoveWindow(78,20,65,23);

	//������ʾʱ��͵��������İ�ť--�ð�ť��Ϊ�������ͼƬ
	for(int i=0;i<5;i++)
	{
		picture[i] = new CButton();
	}
	picture[0]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(40,20,53,43),this,IDC_MYPICTURE+1);
	picture[1]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(53,20,66,43),this,IDC_MYPICTURE+2);
	picture[2]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(185,20,198,43),this,IDC_MYPICTURE+3);
	picture[3]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(198,20,211,43),this,IDC_MYPICTURE+4);
	picture[4]->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_BITMAP,CRect(211,20,224,43),this,IDC_MYPICTURE+5);

	//����ͼƬ
	hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d1));   
	picture[0]->SetBitmap(hBmp);
	hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_d0)); 
	picture[1]->SetBitmap(hBmp);
	picture[2]->SetBitmap(hBmp);
	picture[3]->SetBitmap(hBmp);
	picture[4]->SetBitmap(hBmp);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmineDlg::OnPaint()
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
		CDialog::OnPaint();
		
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ť������Ӧ����
void CmineDlg::OnMybutton(UINT nID)
{
	start++;     //��������ť�Ĵ���
	int number;
	number = nID-IDC_MYBUTTON;     //����ð�ť�������е�λ��

	if(start==1)     //�����һ�ε����ť�ʹ������׺ʹ�����ʱ��
	{
		CreateMine(number);
		SetTimer(1,1000,NULL);
	}

	//������е��׾���Ϸ����
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

	//�����ש��û�����
	 else if(mineFlag[number]==0)
	{
		int count = MineCount(number);
		if(count == 0)         //�����ש����Χû�е��׾ͽ�����д���Χש��
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

	// TODO:  �ڴ������ר�õĴ�������

	//��ʼ������
	start = 0;
	bannerNum = 0;
	timeflag = 0;
	stack = new mineStack;
	stack->top = 0;
	stack->end = 0;
	NUM = 10;           //���õ�������Ϊ10
	brickNumber = 81;   //����ש������Ϊ81
	level = 1;          //�ȼ�����Ϊ��
	but_x = 9;          //������
	but_y = 9;			//������

	for(int i=0;i<brickNumber;i++)   //��ʼ������
	{
		mineNum[i] = 0;
		mineFlag[i] = 0;
	}
	
	return 0;
}



BOOL CmineDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message==WM_RBUTTONDOWN)       //����һ���Ϣ
	{
		POINT pt;
		::GetCursorPos(&pt);             //�õ���궯����λ��
		
		for(int i=0;i<brickNumber;i++)
		{
			CRect r;
			::GetWindowRect(GetDlgItem(IDC_MYBUTTON+i)->GetSafeHwnd(),&r);   //�õ�button���ڵ�rect

			if (PtInRect(&r,pt) && bannerNum<NUM && mineFlag[i]!=1)        //�ж���궯���Ƿ���button��Χ֮��     
			{
				int x,y,j,k;
				x = i/but_y;
				y = i%but_y;
				HBITMAP hBmp;
				if(mineFlag[i]==0) //���ש��û�����������ͼ��Ϊ����
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
				else if(mineFlag[i]==2)  //���ש���Ѿ������죬����ͼ��Ϊ�ʺ�
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
				else if(mineFlag[i]==3)  //���ש��Ϊ�ʺţ�����Ϊ�հ�ש��
				{
					hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_blank));   
					button[x][y]->SetBitmap(hBmp);
					mineFlag[i] = 0;
				}
			}
		}
		
	}

	if(pMsg->message==WM_LBUTTONDBLCLK)       //������˫����Ϣ
	{
		POINT pt;
		::GetCursorPos(&pt);
		for(int i=0;i<brickNumber;i++)
		{
			CRect r;
			::GetWindowRect(GetDlgItem(IDC_MYBUTTON+i)->GetSafeHwnd(),&r);   //�õ�button���ڵ�rect

			if (PtInRect(&r,pt) && mineFlag[i]==1) //˫����Ч��ש����뱻���
			{
				if(MineCount(i)<=BannerCount(i))   //˫����Ч��������������ڵ�������
				{
					stack->top = 0;
					stack->end = 0;
					DoubleClear(i);         //�����Χש��
				}			
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


//������Χ���������
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


//������Χ���׵����������ݵ��������ڸ�ש���������Ӧ��ֵͼƬ
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
	mineFlag[number] = 1;         //���ø�ש���ѱ����
	return count;
}

//��Ϸ����������ʾ����δ�ҳ����Ҵ�ĵ���
void CmineDlg::GameOver()
{
	int x,y;
	for(int i=0;i<brickNumber;i++)
	{
		
		if(mineNum[i]==1 && mineFlag[i]==0) //��ʾδ�ҳ��ĵ���
		{
			x = i/but_y;
			y = i%but_y;
			HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_mine));   
			button[x][y]->SetBitmap(hBmp);
			
		}
		if(mineFlag[i]==2 && mineNum[i]==0)  //��ʾ�Ҵ�ĵ���
		{
			x = i/but_y;
			y = i%but_y;
			HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_error));   
			button[x][y]->SetBitmap(hBmp);
		}
		mineFlag[i]=1;
	}
	KillTimer(1);  //ֹͣ��ʱ
}

//���¿�ʼ��Ϸ
void CmineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HBITMAP hBmp;

	//��������ש��
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
 
	//���ݵȼ���ʾ���׸���
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

//�����Χû�е���ש����Χ��ש��
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

//˫��ʱ�����Χש��
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
			if(mineFlag[number]==0 && MineCount(number)==0)    //�����ש����Χû�е��׾ͽ������
			{
				
				stack->mineList[stack->top] = number;
				stack->top++;
			}
			if(mineNum[number]==1 && mineFlag[number]!=2)     //��������е��׾���Ϸ����
			{
				mineFlag[number] = 0;
				GameOver();
			}
			if(mineNum[number]==0 && mineFlag[number]==2)      //������в���������Ϸ����
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


//��������
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

//��ʱ����Ӧ����������ʾʱ����ж���Ϸ�Ƿ����
void CmineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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

//�˵������򵥡��˵�����Ӧ����
void CmineDlg::OnEasy()
{
	
	
}

//�˵�����һ�㡱�˵������Ӧ����
void CmineDlg::OnCommon()
{
	
}

//�˵��������ѡ��˵������Ӧ����
void CmineDlg::OnDifficult()
{
	
	
}

//�˵������������˵������Ӧ����
void CmineDlg::OnMyHelp()
{

}

//�˵��������ڡ��˵������Ӧ����
void CmineDlg::OnMyAbout()
{

}