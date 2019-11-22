
// RobotExp_4Dlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CRobotExp_4Dlg ��ȭ ����



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


// CRobotExp_4Dlg �޽��� ó����

BOOL CRobotExp_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRobotExp_4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDeviceListReader reader;
	std::vector<std::string> list;

	//Combo Box �ʱ�ȭ
	m_ComboPort.ResetContent();

	//��ǻ�Ϳ� ����� �ø��� ��� ����Ʈ�� ����
	reader.UpdateDeviceList("SERIALCOMM");
	reader.GetDeviceList(list);

	//Combo Box�� list �߰�
	for (int i = 0; i < list.size(); i++) {
		m_ComboPort.AddString(list[i].c_str());
	}

}

void CRobotExp_4Dlg::OnBnClickedCheckOpen()
{

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//��ư�� üũ ���� Ȯ��
	if (m_CheckOpen.GetCheck()) {
		//üũ �� ���
		//���õ� ��Ʈ�̸��� ��żӵ��� ������
		CString port, baud;
		m_ComboPort.GetLBText(m_ComboPort.GetCurSel(), port);
		m_ComboBaud.GetLBText(m_ComboBaud.GetCurSel(), baud);
		int nTmp = atoi(baud.GetBuffer());

		//��Ʈ ���� �õ�
		if (((CCommWork*)_commWorker.GetWork())->OpenPort(port.GetBuffer(),nTmp)) {

			//�����ϸ� ��ư�� �ؽ�Ʈ�� Close�� ����
			_commWorker.StartWork();
			m_CheckOpen.SetWindowText("Close");

			
		}
		else {
			//���н� ���� �޼����� ���� �ʱ�ȭ
			AfxMessageBox("Can't open port");
			m_CheckOpen.SetCheck(false);
		}
	}
	else {
		//üũ ������ ���
		//��Ʈ�� �ݰ� ��ư �ؽ�Ʈ�� Open���� ����
		_commWorker.StopWork();
		((CCommWork*)_commWorker.GetWork())->ClosePort();
		m_CheckOpen.SetWindowText("Open");
		//bFlagConnect = FALSE;
	}
}

void CRobotExp_4Dlg::OnBnClickedBtnSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//��Ʈ�� ������ Ȯ��
	if (m_comm.isOpen())
	{
		CString str;
		m_EditSend.GetWindowText(str);

		//���ڿ� ����
		//���⼭ size�� ���� ���ڿ� ������ ��ȯ�ɵ�
		int size = m_comm.Write(str.GetBuffer(), str.GetLength());
		
		//Edit Control ���ڿ� ����
		m_EditSend.SetWindowText("");

	}
	else
		return;
	
}

void CRobotExp_4Dlg::OnBnClickedBtnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_EditSend.SetWindowText("");
	m_EditRecv.SetWindowText("");
}

// Dialog�� ȸ�� �ڽ� �ǽð� ������Ʈ �ϴºκ� 
void CRobotExp_4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//������� ���� ���� ��
	if (m_comm.isOpen()) {

		//������ �۽��ϴ� �κ�
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

	//Q.cur : joint ��ǥ��, joint�� ����
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

	//Pcur : ��ī��Ʈ ��ǥ��, end effector �� ��ǥ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char cTmpPos[10];
	double dTmpPos[2];
	char cTmpVel[10];
	double dTmpVel[1];
	char cTmpTorq[10];
	double dTmpTorq[1];

	m_editTARPOS1.GetWindowTextA(cTmpPos, 10);	//Target Pos�� ���� �޾ƿ�
	dTmpPos[0] = atof(cTmpPos);
	m_editTarPos2.GetWindowTextA(cTmpPos, 10);
	dTmpPos[1] = atof(cTmpPos);

	m_editTarVel.GetWindowTextA(cTmpVel, 10);	//Target Vel�� ���� �޾ƿ�
	dTmpVel[0] = atof(cTmpVel);

	m_editTarTorq.GetWindowTextA(cTmpTorq, 10);	//Target Torq�� ���� �޾ƿ�
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	char cTmp[10];
	double dTmp[3];

	//�̰� ������ �̻��ѵ�
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnBnClickedButtonGraph()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bCheck = m_pGraphDlg->IsWindowVisible();
	if (bCheck) m_pGraphDlg->ShowWindow(SW_HIDE);
	else m_pGraphDlg->ShowWindow(SW_SHOW);

}


void CRobotExp_4Dlg::OnEnChangeEditSend()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnEnChangeEditRecv()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnEnChangeEditTarPos1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnEnChangeEditTarY()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnBnClickedButtonSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ControlData_t motor_data;
	DataType_t ode_data;

}
