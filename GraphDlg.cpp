// GraphDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RobotExp_4.h"
#include "GraphDlg.h"
#include "afxdialogex.h"
#include "NTGraph.h"

#define RED RGB(255, 0, 0)
#define BLUE RGB(0, 0, 255)
#define GREEN RGB(0, 255, 0)

#define WHITE RGB(255, 255, 255)
#define GRAPH_TIMER_ID 1
#define GRAPH_TIMER_PERIOD_ms 100

// CGraphDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{
	/*CREATE_SYSTEM_MEMORY("MyAVRdata", ControlData_t);
	CREATE_SYSTEM_MEMORY("MyMotorCurrentData", _current);*/
}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_NTGRAPH_POS,  m_ntgPos);
	DDX_Control(pDX, IDC_NTGRAPH_VEL,  m_ntgVel);
	DDX_Control(pDX, IDC_NTGRAPH_TORQ,  m_ntgTorq);
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGraphDlg �޽��� ó�����Դϴ�.
void CGraphDlg::InitNTGraph()
{
	

	m_dCnt = 0.0;
	m_ntgPos.ClearGraph();
	m_ntgVel.ClearGraph();
	m_ntgTorq.ClearGraph();

	m_ntgPos.SetFrameStyle(0);
	m_ntgVel.SetFrameStyle(0);
	m_ntgTorq.SetFrameStyle(0);

	m_ntgPos.SetPlotAreaColor(WHITE);
	m_ntgVel.SetPlotAreaColor(WHITE);
	m_ntgTorq.SetPlotAreaColor(WHITE);

	m_ntgPos.SetShowGrid(TRUE);
	m_ntgVel.SetShowGrid(TRUE);
	m_ntgTorq.SetShowGrid(TRUE);

	m_ntgPos.SetFormatAxisBottom(_T("%.2f"));
	m_ntgVel.SetFormatAxisBottom(_T("%.2f"));
	m_ntgTorq.SetFormatAxisBottom(_T("%.2f"));

	m_ntgPos.SetCaption(_T("��ġ"));
	m_ntgVel.SetCaption(_T("�ӵ�"));
	m_ntgTorq.SetCaption(_T("��ũ"));

	m_ntgPos.SetXLabel(_T("Time[s]"));
	m_ntgVel.SetXLabel(_T("Time[s]"));
	m_ntgTorq.SetXLabel(_T("Time[s]"));

	m_ntgPos.SetYLabel(_T("Degree[deg]"));
	m_ntgVel.SetYLabel(_T("Velocity[deg/s]"));
	m_ntgTorq.SetYLabel(_T("Torque[Nm]"));

	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(3);
	m_ntgPos.SetElementLineColor(RED);// Target
	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(3);
	m_ntgPos.SetElementLineColor(BLUE); // Current

	m_ntgPos.SetRange(0.0, 10.0, 0.0, 360.0);
	m_ntgPos.SetYGridNumber(4);

	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(4);
	m_ntgVel.SetElementLineColor(RED);// Target
	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(3);
	m_ntgVel.SetElementLineColor(BLUE); // Current

	m_ntgTorq.AddElement();
	m_ntgTorq.SetElementWidth(4);
	m_ntgTorq.SetElementLineColor(RED);// Target
	m_ntgTorq.AddElement();
	m_ntgTorq.SetElementWidth(3);
	m_ntgTorq.SetElementLineColor(BLUE); // Current

	SetTimer(GRAPH_TIMER_ID, GRAPH_TIMER_PERIOD_ms, NULL);
}


void CGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// avr���� �Ѿ���� ������ ���⿡�ٰ� ������Ʈ �ؾ��Ѵ�

	m_dCnt += 0.1;
	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);	//�ý��� �޸𸮻󿡼� �����͸� ���⼭ �����ϴ°ǰ�
	
	ControlData_t _current;
	GET_SYSTEM_MEMORY("MyMotorCurrentData", _current);

	if (m_dCnt >= 10.0)
	{
		m_ntgPos.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 360.0);	//
		m_ntgVel.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 90.0);	//
		m_ntgTorq.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 1.0);	//
	}
	//�ι�° ���ڿ� ���� ������ �׷����� ���� ���� ǥ�õȴ�.
	m_ntgPos.PlotXY(m_dCnt, jointData.Q_tar[0] , 1);
	
	m_ntgPos.PlotXY(m_dCnt, _current.position , 2);

	//m_ntgVel.PlotXY(m_dCnt, jointData.Q_tar[1] * RAD2DEG, 1);
	m_ntgVel.PlotXY(m_dCnt, jointData.Q_cur[1] * RAD2DEG, 2);
	
	//m_ntgTorq.PlotXY(m_dCnt, jointData.Q_tar[2] * RAD2DEG, 1);
	m_ntgTorq.PlotXY(m_dCnt, jointData.Q_cur[2] * RAD2DEG, 2);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitNTGraph();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
