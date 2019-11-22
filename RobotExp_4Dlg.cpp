
// RobotExp_4Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RobotExp_4.h"
#include "RobotExp_4Dlg.h"
#include "afxdialogex.h"
#include "DataType.h"
#include "SystemMemory.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define LINK_1 1.0
#define LINK_2 0.5

#define DIALOG_TIMER_ID 1001
#define DIALOG_TIMER_PERIOD_ms 100

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


// CRobotExp_4Dlg 대화 상자



CRobotExp_4Dlg::CRobotExp_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROBOTEXP_4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CRobotExp_4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboPort);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_ComboBaud);
	DDX_Control(pDX, IDC_CHECK_OPEN, m_CheckOpen);
	DDX_Control(pDX, IDC_EDIT_SEND, m_EditSend);
	DDX_Control(pDX, IDC_EDIT_RECV, m_EditRecv);
	DDX_Control(pDX, IDC_EDIT_TAR_POS_1, m_editTARPOS1);
	DDX_Control(pDX, IDC_EDIT_CUR_POS_1, m_editCurPos1);
	DDX_Control(pDX, IDC_EDIT_TAR_POS_2, m_editTarPos2);
	DDX_Control(pDX, IDC_EDIT_TAR_VEL, m_editTarVel);
	DDX_Control(pDX, IDC_EDIT_TAR_TOR, m_editTarTorq);
	DDX_Control(pDX, IDC_EDIT_CUR_POS_2, m_editCurPos2);
	DDX_Control(pDX, IDC_EDIT_CUR_VEL, m_editCurVel);
	DDX_Control(pDX, IDC_EDIT_CUR_TOR, m_editCurTorq);
	DDX_Control(pDX, IDC_EDIT_CUR_X, m_editCurX);
	DDX_Control(pDX, IDC_EDIT_CUR_Y, m_editCurY);
	DDX_Control(pDX, IDC_EDIT_CUR_Z, m_editCurZ);
	DDX_Control(pDX, IDC_EDIT_TAR_X, m_editTarX);
	DDX_Control(pDX, IDC_EDIT_TAR_Y, m_editTarY);
	DDX_Control(pDX, IDC_EDIT_TAR_Z, m_editTarZ);
}

BEGIN_MESSAGE_MAP(CRobotExp_4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO_PORT, &CRobotExp_4Dlg::OnCbnDropdownComboPort)
	ON_BN_CLICKED(IDC_CHECK_OPEN, &CRobotExp_4Dlg::OnBnClickedCheckOpen)
	ON_BN_CLICKED(IDC_BTN_ClEAR, &CRobotExp_4Dlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_SEND, &CRobotExp_4Dlg::OnBnClickedBtnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CRobotExp_4Dlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CRobotExp_4Dlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_INVERSE, &CRobotExp_4Dlg::OnBnClickedButtonInverse)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, &CRobotExp_4Dlg::OnBnClickedButtonGraph)
	ON_EN_CHANGE(IDC_EDIT_SEND, &CRobotExp_4Dlg::OnEnChangeEditSend)
	ON_EN_CHANGE(IDC_EDIT_RECV, &CRobotExp_4Dlg::OnEnChangeEditRecv)
	ON_EN_CHANGE(IDC_EDIT_TAR_POS_1, &CRobotExp_4Dlg::OnEnChangeEditTarPos1)
	ON_EN_CHANGE(IDC_EDIT_TAR_Y, &CRobotExp_4Dlg::OnEnChangeEditTarY)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CRobotExp_4Dlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CRobotExp_4Dlg 메시지 처리기

BOOL CRobotExp_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTimer(DIALOG_TIMER_ID, DIALOG_TIMER_PERIOD_ms, NULL);
	
	m_editTARPOS1.SetWindowText("0");
	m_editTarPos2.SetWindowText("0");

	m_editTarVel.SetWindowText("10");
	m_editTarTorq.SetWindowText("0.1");

	m_editTarX.SetWindowText("0.0");
	m_editTarY.SetWindowText("0.0");
	m_editTarZ.SetWindowText("0.0");

	m_pGraphDlg = new CGraphDlg;
	m_pGraphDlg->Create(IDD_GRAPH_DIALOG);

	_commWorker.SetPeriod(0.01);
	_commWorker.SetWork(CreateWork<CCommWork>("Comm1Work"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRobotExp_4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRobotExp_4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRobotExp_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRobotExp_4Dlg::SolveForwardKinematics(double dAngle, double dAngle2, double* pdPos)
{
	pdPos[0] = LINK_1 * sin(dAngle) + LINK_2 * (sin(dAngle)*cos(dAngle) + sin(dAngle2)*cos(dAngle2));
	pdPos[1] = -LINK_1 * cos(dAngle) - LINK_2 * (cos(dAngle)*cos(dAngle2) - sin(dAngle)*cos(dAngle2));
	pdPos[2] = 0;
}


void CRobotExp_4Dlg::SolveInverseKinematics(double dX, double dY, double dZ, double* pdAngle)
{
	double dCos2 = (_SQR(dX) + _SQR(dY) - (_SQR(LINK_1) + _SQR(LINK_2))) / (2.0 * LINK_1*LINK_2);
	double dSin2 = sqrt(1.0 - _SQR(dCos2));

	double dDen = (LINK_1*LINK_2*dCos2)*(LINK_1*LINK_2*dCos2) + (LINK_1*dSin2)*(LINK_1*dSin2);

	double dCos1 = (LINK_2*dSin2*dX - (LINK_1 + LINK_2 * dCos2)*dY) / dDen;
	double dSin1 = ((LINK_1 + LINK_2 * dCos2)*dX + LINK_2 * dSin2*dY) / dDen;

	pdAngle[0] = atan2(dSin1, dCos1);
	pdAngle[1] = atan2(dSin2, dCos2);
}
void CRobotExp_4Dlg::OnCbnDropdownComboPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDeviceListReader reader;
	std::vector<std::string> list;

	//Combo Box 초기화
	m_ComboPort.ResetContent();

	//컴퓨터에 연결된 시리얼 장비 리스트를 얻어옴
	reader.UpdateDeviceList("SERIALCOMM");
	reader.GetDeviceList(list);

	//Combo Box에 list 추가
	for (int i = 0; i < list.size(); i++) {
		m_ComboPort.AddString(list[i].c_str());
	}

}

void CRobotExp_4Dlg::OnBnClickedCheckOpen()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//버튼의 체크 여부 확인
	if (m_CheckOpen.GetCheck()) {
		//체크 된 경우
		//선택된 포트이름과 통신속도를 가져옴
		CString port, baud;
		m_ComboPort.GetLBText(m_ComboPort.GetCurSel(), port);
		m_ComboBaud.GetLBText(m_ComboBaud.GetCurSel(), baud);
		int nTmp = atoi(baud.GetBuffer());

		//포트 열기 시도
		if (((CCommWork*)_commWorker.GetWork())->OpenPort(port.GetBuffer(),nTmp)) {

			//성공하면 버튼의 텍스트를 Close로 변경
			_commWorker.StartWork();
			m_CheckOpen.SetWindowText("Close");

			
		}
		else {
			//실패시 에러 메세지를 띄우고 초기화
			AfxMessageBox("Can't open port");
			m_CheckOpen.SetCheck(false);
		}
	}
	else {
		//체크 해제된 경우
		//포트를 닫고 버튼 텍스트를 Open으로 변경
		_commWorker.StopWork();
		((CCommWork*)_commWorker.GetWork())->ClosePort();
		m_CheckOpen.SetWindowText("Open");
		//bFlagConnect = FALSE;
	}
}

void CRobotExp_4Dlg::OnBnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//포트가 열린지 확인
	if (m_comm.isOpen())
	{
		CString str;
		m_EditSend.GetWindowText(str);

		//문자열 전송
		//여기서 size로 보낸 문자열 사이즈 반환될듯
		int size = m_comm.Write(str.GetBuffer(), str.GetLength());
		
		//Edit Control 문자열 제거
		m_EditSend.SetWindowText("");

	}
	else
		return;
	
}

void CRobotExp_4Dlg::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_EditSend.SetWindowText("");
	m_EditRecv.SetWindowText("");
}

// Dialog에 회색 박스 실시간 업데이트 하는부분 
void CRobotExp_4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//통신으로 받은 현재 값
	if (m_comm.isOpen()) {

		//데이터 송신하는 부분
	}

	ControlData_t motor_data;
	DataType_t ode_data;
	ControlData_t _current;

	GET_SYSTEM_MEMORY("JointData", ode_data);
	GET_SYSTEM_MEMORY("Comm1Work_Controller_Current", motor_data);
	GET_SYSTEM_MEMORY("MyMotorCurrentData", _current);

	CString str;

	//ODE
	/*str.Format("%.4f", ode_data.Q_cur[0] * RAD2DEG);
	m_editCurPos1.SetWindowText(str);*/

	//Q.cur : joint 좌표계, joint의 각도
	str.Format("%.4f", ode_data.Q_cur[1] * RAD2DEG);
	m_editCurPos2.SetWindowText(str);


	//Motor
	str.Format("%.4f", _current.position);
	m_editCurPos1.SetWindowText(str);

	str.Format("%.4f", motor_data.velocity * RAD2DEG);
	m_editCurVel.SetWindowText(str);

	str.Format("%.4f", motor_data.current * RAD2DEG);
	m_editCurTorq.SetWindowText(str);

	//Forword Kinematics
	double Pcur[3] = { 0, };
	SolveForwardKinematics(ode_data.Q_cur[0], ode_data.Q_cur[1], Pcur);

	//Pcur : 데카르트 좌표계, end effector 의 좌표
	str.Format("%.4f", Pcur[0]);
	m_editCurX.SetWindowText(str);

	str.Format("%.4f", Pcur[1]);
	m_editCurY.SetWindowText(str);

	str.Format("%.4f", Pcur[2]);
	m_editCurZ.SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
	
}


void CRobotExp_4Dlg::OnBnClickedButtonInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_editTarX.SetWindowText("0");
	m_editTarY.SetWindowText("0");
	m_editTarZ.SetWindowText("0");

	m_editTARPOS1.SetWindowText("0");
	m_editTarPos2.SetWindowText("0");

	m_editTarVel.SetWindowText("10");
	m_editTarTorq.SetWindowText("0.1");

	ControlData_t motor_data;
	DataType_t ode_data;

	GET_SYSTEM_MEMORY("JointData", ode_data);

	ode_data.Q_tar[0] = ode_data.Q_tar[1] = 0.;
	SET_SYSTEM_MEMORY("JointData", ode_data);

	motor_data.position = 0.;
	motor_data.velocity = 10 * DEG2RAD;
	motor_data.current = 0.1 / 0.0683;
	SET_SYSTEM_MEMORY("Comm1Work_Controller_Target", motor_data);
}



void CRobotExp_4Dlg::OnBnClickedButtonForward()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char cTmpPos[10];
	double dTmpPos[2];
	char cTmpVel[10];
	double dTmpVel[1];
	char cTmpTorq[10];
	double dTmpTorq[1];

	m_editTARPOS1.GetWindowTextA(cTmpPos, 10);	//Target Pos의 값을 받아옴
	dTmpPos[0] = atof(cTmpPos);
	m_editTarPos2.GetWindowTextA(cTmpPos, 10);
	dTmpPos[1] = atof(cTmpPos);

	m_editTarVel.GetWindowTextA(cTmpVel, 10);	//Target Vel의 값을 받아옴
	dTmpVel[0] = atof(cTmpVel);

	m_editTarTorq.GetWindowTextA(cTmpTorq, 10);	//Target Torq의 값을 받아옴
	dTmpTorq[0] = atof(cTmpTorq);

	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	jointData.Q_tar[0] = dTmpPos[0] * DEG2RAD;
	jointData.Q_tar[1] = dTmpVel[0] * DEG2RAD;
	jointData.Q_tar[2] = dTmpTorq[0] * DEG2RAD;

	SET_SYSTEM_MEMORY("JointData", jointData);

	double dPos[3] = { 0, 0, 0 };

	SolveForwardKinematics(dTmpPos[0] * DEG2RAD , dTmpPos[1] * DEG2RAD, dPos);

	char pszTmp[512];
	sprintf(pszTmp, "%.2lf", dPos[0]);
	m_editTarX.SetWindowTextA(pszTmp);
	sprintf(pszTmp, "%.2lf", dPos[1]);
	m_editTarY.SetWindowTextA(pszTmp);
	sprintf(pszTmp, "%.2lf", dPos[2]);
	m_editTarZ.SetWindowTextA(pszTmp);

}


void CRobotExp_4Dlg::OnBnClickedButtonInverse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char cTmp[10];
	double dTmp[3];

	//이거 순서가 이상한데
	m_editTarX.GetWindowTextA(cTmp, 10);
	dTmp[0] = atof(cTmp);
	dTmp[0] = 30;
	m_editTarY.GetWindowTextA(cTmp, 10);
	dTmp[1] = atof(cTmp) * -1;
	m_editTarZ.GetWindowTextA(cTmp, 10);
	dTmp[2] = atof(cTmp);

	double dAngle[2] = { 0, 0 };
	SolveInverseKinematics(dTmp[0], dTmp[1], dTmp[2], dAngle);

	char pszTmp[512];
	sprintf(pszTmp, "%.2lf", dAngle[0] * RAD2DEG);
	m_editTARPOS1.SetWindowTextA(pszTmp);
	sprintf(pszTmp, "%.2lf", dAngle[1] * RAD2DEG);
	m_editTarPos2.SetWindowTextA(pszTmp);

	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	jointData.Q_tar[0] = dAngle[0];
	jointData.Q_tar[1] = dAngle[1];

	SET_SYSTEM_MEMORY("JointData", jointData);

}


void CRobotExp_4Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete m_pGraphDlg;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CRobotExp_4Dlg::OnBnClickedButtonGraph()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_pGraphDlg->IsWindowVisible();
	if (bCheck) m_pGraphDlg->ShowWindow(SW_HIDE);
	else m_pGraphDlg->ShowWindow(SW_SHOW);

}


void CRobotExp_4Dlg::OnEnChangeEditSend()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRobotExp_4Dlg::OnEnChangeEditRecv()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRobotExp_4Dlg::OnEnChangeEditTarPos1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRobotExp_4Dlg::OnEnChangeEditTarY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRobotExp_4Dlg::OnBnClickedButtonSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ControlData_t motor_data;
	DataType_t ode_data;

}
