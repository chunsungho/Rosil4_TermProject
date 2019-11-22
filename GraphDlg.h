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



// CGraphDlg ��ȭ �����Դϴ�.

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGraphDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
