// mineDlg.h : 头文件
//
#pragma once

#define IDC_MYBUTTON 10000
#define IDC_MYPICTURE 10200


// CmineDlg 对话框
class CmineDlg : public CDialog
{
// 构造
public:
	CmineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CButton *button[30][16];
	CButton *picture[5];
	CStatic *static1,*static2;
	int mineNum[480];  //标志地雷的位置
	int mineFlag[480]; //标志地砖被点击的方式：1-鼠标左击，2-鼠标右击1次，3-鼠标右击2次
	int bannerNum;     //插旗数量
	int start;        //创建地雷标志
	int timeflag;     //时间
	int level;         //等级标志
	int NUM;           //地雷数量
	int brickNumber;   //砖块数量
	int but_x;
	int but_y;

	struct mineStack   //用来清除空白砖块
	{
		int mineList[480];
		int top;
		int end;
	}*stack;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnMybutton(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEasy();
	afx_msg void OnCommon();
	afx_msg void OnMyHelp();
	afx_msg void OnDifficult();
	afx_msg void OnMyAbout();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int MineCount(int number);  //找出所点地砖周围地雷的个数
	void GameOver();
	void Clear(int number);  //清除空白地砖
	void DoubleClear(int number); //双击清除
	void CreateMine(int number);   //创建地雷
	HBITMAP pictureShow(int number);
	int BannerCount(int number);   //计算周围插旗的个数
};
