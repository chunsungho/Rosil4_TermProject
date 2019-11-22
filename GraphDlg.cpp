// GraphDlg.cpp : 구현 파일입니다.
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

// CGraphDlg 대화 상자입니다.

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


// CGraphDlg 메시지 처리기입니다.
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

	m_ntgPos.SetCaption(_T("위치"));
	m_ntgVel.SetCaption(_T("속도"));
	m_ntgTorq.SetCaption(_T("토크"));

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// avr에서 넘어오는 정보를 여기에다가 업데이트 해야한다

	m_dCnt += 0.1;
	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);	//시스템 메모리상에서 데이터를 여기서 공유하는건가
	
	ControlData_t _current;
	GET_SYSTEM_MEMORY("MyMotorCurrentData", _current);

	if (m_dCnt >= 10.0)
	{
		m_ntgPos.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 360.0);	//
		m_ntgVel.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 90.0);	//
		m_ntgTorq.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 1.0);	//
	}
	//두번째 인자에 값을 넣으면 그래프에 값이 들어가서 표시된다.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitNTGraph();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
