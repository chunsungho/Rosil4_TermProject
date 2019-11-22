#pragma once
#include "NTGraph.h"
#include "GraphDlg.h"
#include "afxwin.h"

#include "SharedMemory.h"
#include "SystemMemory.h"
#include "DataType.h"

#include "ThreadWorker.h"
#include "Comm.h"
#include "CommWork.h"
#include "DeviceListReader.h"



// CGraphDlg 대화 상자입니다.

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGraphDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	
	afx_msg
	virtual void InitNTGraph();
	void OnTimer(UINT_PTR nIDEvent);
	CNTGraph m_ntgPos;
	CNTGraph m_ntgVel;
	CNTGraph m_ntgTorq;
	virtual BOOL OnInitDialog();
	double m_dCnt;
};
