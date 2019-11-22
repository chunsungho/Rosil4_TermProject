
// RobotExp_4Dlg.h : ��� ����
//

#pragma once

#include "GraphDlg.h"
#include "afxwin.h"

#include "SharedMemory.h"
#include "SystemMemory.h"
#include "DataType.h"

#include "ThreadWorker.h"
#include "Comm.h"
#include "CommWork.h"
#include "DeviceListReader.h"

#define		_SQR(a)		((a)*(a))

// CRobotExp_4Dlg ��ȭ ����
class CRobotExp_4Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRobotExp_4Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.


// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROBOTEXP_4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


public:
	void SolveForwardKinematics(double dAngle, double dAngle2, double* pdPos);
	void SolveInverseKinematics(double dX, double dY, double dZ, double* pdAngle);

private:
	CGraphDlg* m_pGraphDlg;

// �����Դϴ�.
protected:
	HICON m_hIcon;
	CComm m_comm;
	CThreadedWorker _commWorker;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboPort;
	CComboBox m_ComboBaud;
	CButton m_CheckOpen;
	afx_msg void OnCbnDropdownComboPort();
	afx_msg void OnBnClickedCheckOpen();
	CEdit m_EditSend;
	CEdit m_EditRecv;
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_editTARPOS1;
	CEdit m_editCurPos1;
	CEdit m_editTarPos2;
	CEdit m_editTarVel;
	CEdit m_editTarTorq;
	CEdit m_editCurPos2;
	CEdit m_editCurVel;
	CEdit m_editCurTorq;
	CEdit m_editCurX;
	CEdit m_editCurY;
	CEdit m_editCurZ;
	CEdit m_editTarX;
	CEdit m_editTarY;
	CEdit m_editTarZ;
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonInverse();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonGraph();
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnEnChangeEditRecv();
	afx_msg void OnEnChangeEditTarPos1();
	afx_msg void OnEnChangeEditTarY();
	afx_msg void OnBnClickedButtonSet();
};