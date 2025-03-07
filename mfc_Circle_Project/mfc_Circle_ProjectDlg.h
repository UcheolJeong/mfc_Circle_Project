
// mfc_Circle_ProjectDlg.h: 헤더 파일
//

#pragma once
#include<thread>

// CmfcCircleProjectDlg 대화 상자
class CmfcCircleProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfcCircleProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CIRCLE_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
private:
	HICON m_hIcon;
	CPoint m_CircleCenter;
	CPoint m_UserClickPoints[3];
	int m_circleRadius;
	int  m_radius = 3;
	int m_Click_Count;
	int m_border = 3;
	int m_dragIndex;
	void CalculatePoint(CPoint Point1, CPoint Point2, CPoint Point3);
	void StartRandom();
	afx_msg LRESULT UpdateUI(WPARAM wParam, LPARAM lParam);
	bool RadiusCheck();
	bool m_UseDrag;
	bool m_UseThread;
	std::thread m_randomThread;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nflag, CPoint point);
	afx_msg void OnLButtonUp(UINT nflag, CPoint point);
	afx_msg void OnMouseMove(UINT nflag, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRandom();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnReset();
};
