
// getFilePropertyMFC_vs2019Dlg.h: 头文件
//

#pragma once


// CgetFilePropertyMFCvs2019Dlg 对话框
class CgetFilePropertyMFCvs2019Dlg : public CDialogEx
{
// 构造
public:
	CgetFilePropertyMFCvs2019Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETFILEPROPERTYMFC_VS2019_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	void ProcessGetCommand(CString cString);
	bool IsFileExist(CString filePath);

	#define YEAR_MONTH_DAY 1
	#define MONTH_DAY_YEAR 2
	#define DAY_MONTH_YEAR 3
	int globalDateType;
	CString globalStrFileNameAndProperties;
	afx_msg void OnBnClickedRadioYMD();
	afx_msg void OnBnClickedRadioMdy();
	afx_msg void OnBnClickedRadioDmy();
};
