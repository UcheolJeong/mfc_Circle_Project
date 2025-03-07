
// mfc_Circle_ProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfc_Circle_Project.h"
#include "mfc_Circle_ProjectDlg.h"
#include "afxdialogex.h"
#include<thread>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CmfcCircleProjectDlg 대화 상자



CmfcCircleProjectDlg::CmfcCircleProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CIRCLE_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcCircleProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcCircleProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_USER + 1, &CmfcCircleProjectDlg::UpdateUI)
	ON_BN_CLICKED(IDC_Btn_Random, &CmfcCircleProjectDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_Btn_Reset, &CmfcCircleProjectDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CmfcCircleProjectDlg 메시지 처리기

BOOL CmfcCircleProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_radius = 0;
	m_Click_Count = 0;
	CEdit* InputRadius = (CEdit*)GetDlgItem(IDC_EDIT_inputRadius);
	InputRadius->SetLimitText(3);
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcCircleProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcCircleProjectDlg::OnPaint()
{
	
	CPaintDC dc(this);

	for (int i = 0; i < m_Click_Count; i++) {
		dc.SelectObject(&CBrush(RGB(0, 0, 255)));
		dc.Ellipse(m_UserClickPoints[i].x - m_radius , m_UserClickPoints[i].y - m_radius ,
			         m_UserClickPoints[i].x + m_radius , m_UserClickPoints[i].y + m_radius);
	}

	if (m_Click_Count == 3) {
		dc.SelectStockObject(NULL_BRUSH);

		CalculatePoint(m_UserClickPoints[0], m_UserClickPoints[1], m_UserClickPoints[2]);

		dc.SelectObject(&CBrush(RGB(255,143,155)));

		dc.Ellipse(m_CircleCenter.x - m_circleRadius, m_CircleCenter.y - m_circleRadius, m_CircleCenter.x + m_circleRadius, m_CircleCenter.y + m_circleRadius);
	}

	
		CDialogEx::OnPaint();

		//if (IsIconic())
		//{
		//	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//	// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		//	int cxIcon = GetSystemMetrics(SM_CXICON);
		//	int cyIcon = GetSystemMetrics(SM_CYICON);
		//	CRect rect;
		//	GetClientRect(&rect);
		//	int x = (rect.Width() - cxIcon + 1) / 2;
		//	int y = (rect.Height() - cyIcon + 1) / 2;

		//	// 아이콘을 그립니다.
		//	dc.DrawIcon(x, y, m_hIcon);
		//}
		//else
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcCircleProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfcCircleProjectDlg::CalculatePoint(CPoint point1, CPoint point2, CPoint point3) {

	double x1 = point1.x, y1 = point1.y;
	double x2 = point2.x, y2 = point2.y;
	double x3 = point3.x, y3 = point3.y;

	
	double a = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));  
	double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2)); 
	double c = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); 

	
	double s = (a + b + c) / 2; 
	double area = sqrt(s * (s - a) * (s - b) * (s - c)); 

	
	double R = (a * b * c) / (4 * area);

	
	double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)); 

	double cx = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
	double cy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;


	m_CircleCenter = CPoint(static_cast<int>(cx), static_cast<int>(cy));
	m_circleRadius = static_cast<int>(R);

}

bool CmfcCircleProjectDlg::RadiusCheck() {

	CEdit* EditRadius = (CEdit*)GetDlgItem(IDC_EDIT_inputRadius);
	CString strRadius;
	EditRadius->GetWindowText(strRadius);
	m_radius = _ttoi(strRadius);

	return true;
	
}

void CmfcCircleProjectDlg::OnLButtonDown(UINT flag , CPoint point) {

	//if (!RadiusCheck()) return;

	for (int i = 0; i < m_Click_Count; i++) {
		int dx = point.x - m_UserClickPoints[i].x;
		int dy = point.y - m_UserClickPoints[i].y;

		if (dx * dx + dy * dy <= m_radius * m_radius) {
			m_UseDrag = true;
			m_dragIndex = i;
			break;
		}

	}

	if (m_Click_Count < 3 && m_UseDrag == false) {
		m_UserClickPoints[m_Click_Count] = point;
		m_Click_Count++;
	}
	else if (m_Click_Count == 3 && !m_UseDrag) {
		CEdit* EditRadius = (CEdit*)GetDlgItem(IDC_EDIT_inputRadius);
		CString strRadius;
		EditRadius->GetWindowText(strRadius);
		m_radius = _ttoi(strRadius);
		if (m_radius <= 0 || strRadius.IsEmpty()) {
			AfxMessageBox(_T("반지름을 입력해주세요"));
			return;
		}
		else Invalidate();
	}
	
	/*CString  _str;
	_str.Format(_T("클릭 위치: (%d , %d)"), point.x, point.y);
	AfxMessageBox(_str);
	CDialogEx::OnLButtonDown(flag, point);*/

	CDialogEx::OnLButtonDown(flag, point);

}

void CmfcCircleProjectDlg::OnMouseMove(UINT flag, CPoint point) {
	if (m_UseDrag) {

		m_UserClickPoints[m_dragIndex] = point;
		Invalidate();
	}
	CDialogEx::OnMouseMove(flag, point);
}
void CmfcCircleProjectDlg::OnLButtonUp(UINT flag, CPoint point) {
	m_UseDrag = false;
	CDialogEx::OnLButtonUp(flag, point);
}

void CmfcCircleProjectDlg::StartRandom() {
	
	srand(static_cast<unsigned int>(time(NULL)));
	m_UseThread = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++) {
			m_UserClickPoints[j].x = rand() % 500;
			m_UserClickPoints[j].y = rand() % 500;
		}
		CalculatePoint(m_UserClickPoints[0], m_UserClickPoints[1], m_UserClickPoints[2]);
		PostMessage(WM_USER + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	m_UseThread = false;
	
}

afx_msg LRESULT CmfcCircleProjectDlg::UpdateUI(WPARAM wParam, LPARAM lParam)
{
	Invalidate();  // 화면을 갱신합니다.
	return 0;  // LRESULT 반환
}

void CmfcCircleProjectDlg::OnBnClickedBtnRandom()
{
	if (m_UseThread) return;

	if (m_randomThread.joinable()) {
		m_randomThread.join();
	}

	m_randomThread = std::thread(&CmfcCircleProjectDlg::StartRandom, this);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CmfcCircleProjectDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
	}
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CmfcCircleProjectDlg::OnBnClickedBtnReset()
{
	m_Click_Count = 0;
	m_radius = 0;
	m_circleRadius = 0;
	m_CircleCenter = 0;
	m_UseDrag = false;
	m_dragIndex = -1;

	Invalidate();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
