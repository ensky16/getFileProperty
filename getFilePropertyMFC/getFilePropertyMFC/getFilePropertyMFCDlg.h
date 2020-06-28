
// getFilePropertyMFCDlg.h : header file
//

#pragma once


// CgetFilePropertyMFCDlg dialog
class CgetFilePropertyMFCDlg : public CDialogEx
{
// Construction
public:
	CgetFilePropertyMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GETFILEPROPERTYMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void SetClipBoardData(CString strText);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void SetOneFileNameAndProToClip(CString filePath);
	CString GetFileNameAndProperties(CString filePath, int dateType);
	void processGetCommand(CString cString);
	
	#define YEAR_MONTH_DAY 1
	#define MONTH_DAY_YEAR 2
	#define DAY_MONTH_YEAR 3
	int globalDateType;
	CString globalStrFileNameAndProperties;
	afx_msg void OnBnClickedRadioYMD();
	afx_msg void OnBnClickedRadioMdy();
	afx_msg void OnBnClickedRadioDmy();
};
