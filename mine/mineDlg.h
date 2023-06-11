// mineDlg.h : ͷ�ļ�
//
#pragma once

#define IDC_MYBUTTON 10000
#define IDC_MYPICTURE 10200


// CmineDlg �Ի���
class CmineDlg : public CDialog
{
// ����
public:
	CmineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CButton *button[30][16];
	CButton *picture[5];
	CStatic *static1,*static2;
	int mineNum[480];  //��־���׵�λ��
	int mineFlag[480]; //��־��ש������ķ�ʽ��1-��������2-����һ�1�Σ�3-����һ�2��
	int bannerNum;     //��������
	int start;        //�������ױ�־
	int timeflag;     //ʱ��
	int level;         //�ȼ���־
	int NUM;           //��������
	int brickNumber;   //ש������
	int but_x;
	int but_y;

	struct mineStack   //��������հ�ש��
	{
		int mineList[480];
		int top;
		int end;
	}*stack;

	// ���ɵ���Ϣӳ�亯��
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
	int MineCount(int number);  //�ҳ������ש��Χ���׵ĸ���
	void GameOver();
	void Clear(int number);  //����հ׵�ש
	void DoubleClear(int number); //˫�����
	void CreateMine(int number);   //��������
	HBITMAP pictureShow(int number);
	int BannerCount(int number);   //������Χ����ĸ���
};
