
// MyGobang_DHKDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MainGobang.h"

// CMyGobang_DHKDlg �Ի���
class CMyGobang_DHKDlg : public CDialogEx
{
// ����
public:
	CMyGobang_DHKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYGOBANG_DHK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMainGobang gobang;
	CStatic picMain;//��ͼ�ؼ�
	CPoint pt;//�������
	bool bIsReady;//���Կ�ʼhuman vs human
	bool bDrawPieces;//���Կ�ʼ������
	bool bIsMachine;//human vs machine
	bool bWithdraw;//�������
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMachine();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonWithdraw();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
