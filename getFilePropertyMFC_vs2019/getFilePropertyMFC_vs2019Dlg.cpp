
// getFilePropertyMFC_vs2019Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "getFilePropertyMFC_vs2019.h"
#include "getFilePropertyMFC_vs2019Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CgetFilePropertyMFCvs2019Dlg 对话框



CgetFilePropertyMFCvs2019Dlg::CgetFilePropertyMFCvs2019Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETFILEPROPERTYMFC_VS2019_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgetFilePropertyMFCvs2019Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgetFilePropertyMFCvs2019Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CgetFilePropertyMFCvs2019Dlg::OnBnClickedButton1)
	ON_WM_DROPFILES()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_RADIO_Y_M_D, &CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioYMD)
	ON_BN_CLICKED(IDC_RADIO_MDY, &CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioMdy)
	ON_BN_CLICKED(IDC_RADIO_DMY, &CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioDmy)
END_MESSAGE_MAP()


// CgetFilePropertyMFCvs2019Dlg 消息处理程序

BOOL CgetFilePropertyMFCvs2019Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CheckRadioButton(IDD_GETFILEPROPERTYMFC_VS2019_DIALOG,IDC_RADIO_DMY,IDC_RADIO_DMY);
	globalDateType=DAY_MONTH_YEAR;

	if(!globalStrFileNameAndProperties.IsEmpty())
	{
		SetDlgItemText(IDC_EDIT1, globalStrFileNameAndProperties);	
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CgetFilePropertyMFCvs2019Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgetFilePropertyMFCvs2019Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgetFilePropertyMFCvs2019Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void  CgetFilePropertyMFCvs2019Dlg::SetClipBoardData(CString cStringText)
{
    if (::OpenClipboard(m_hWnd) &&::EmptyClipboard())
    {
        size_t cStringTextLength = (cStringText.GetLength() + 1) * sizeof(TCHAR);

        HGLOBAL allocHeapMemory = GlobalAlloc(GMEM_MOVEABLE, cStringTextLength);

        if (allocHeapMemory == NULL)
        {
            CloseClipboard();
            return;
        }

        LPTSTR lptstrDst = (LPTSTR)GlobalLock(allocHeapMemory);

        memcpy_s(lptstrDst, cStringTextLength, cStringText.LockBuffer(), cStringTextLength);
        cStringText.UnlockBuffer();

        GlobalUnlock(allocHeapMemory);
 
        UINT uintFormat = (sizeof(TCHAR) == sizeof(WCHAR))?CF_UNICODETEXT:CF_TEXT;
        
        if(SetClipboardData(uintFormat, allocHeapMemory) == NULL)
        {
            CloseClipboard();
            return;
        }

        CloseClipboard();
    }
}


void CgetFilePropertyMFCvs2019Dlg::SetOneFileNameAndProToClip(CString strFilePath)
{
	FILETIME fileCreateDate, fileModifyDate, fileAccessDate;
	CString strCreateTime, strModifyTime, strAccessTime;
	SYSTEMTIME systemTimeLocal;
	CString firstFileName;
	CString finalResult;
	
	firstFileName = strFilePath.Right(strFilePath.GetLength()-strFilePath.ReverseFind('\\')-1); 
	
	/***************get file date start************************************/
	HANDLE hFile = CreateFile(strFilePath, GENERIC_READ,          // open for reading
	FILE_SHARE_READ,       // share for reading
	NULL,                            // default security
	OPEN_EXISTING,          // existing file only
	FILE_FLAG_BACKUP_SEMANTICS , // normal file
	NULL);
	if (!GetFileTime(hFile, &fileCreateDate, &fileAccessDate, &fileModifyDate))
	{
		return;
	}

	ZeroMemory(&systemTimeLocal, sizeof(SYSTEMTIME));
	FileTimeToSystemTime(&fileCreateDate, &systemTimeLocal);
	strCreateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), systemTimeLocal.wYear, systemTimeLocal.wMonth, systemTimeLocal.wDay,  systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond);   
	ZeroMemory(&systemTimeLocal, sizeof(SYSTEMTIME));
	FileTimeToSystemTime(&fileModifyDate, &systemTimeLocal);
	strModifyTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), systemTimeLocal.wYear, systemTimeLocal.wMonth, systemTimeLocal.wDay,  systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 
	ZeroMemory(&systemTimeLocal, sizeof(SYSTEMTIME));
	FileTimeToSystemTime(&fileAccessDate, &systemTimeLocal);
	strAccessTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), systemTimeLocal.wYear, systemTimeLocal.wMonth, systemTimeLocal.wDay,  systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 

	finalResult=firstFileName+_T(" ")+strModifyTime;
	SetDlgItemText(IDC_EDIT1, finalResult);	
	//SetDlgItemText(IDC_EDIT2,  firstFileName+_T(" ")+strModifyTime);	
	//SetDlgItemText(IDC_EDIT3,  firstFileName+_T(" ")+strAccessTime);	
	/***************get file date end************************************/

	SetClipBoardData(finalResult);
}


CString CgetFilePropertyMFCvs2019Dlg::GetFileNameAndProperties(CString strFilePath, int dateType)
{
	FILETIME fileCreateDate, fileModifyDate, fileAccessDate;
	CString strModifyTime;
	SYSTEMTIME systemTimeLocal;
	CString firstFileName;
	CString finalResult;

	CString strDateFormat=_T("%04d-%02d-%02d %02d:%02d:%02d");

	firstFileName = strFilePath.Right(strFilePath.GetLength()-strFilePath.ReverseFind('\\')-1); 
	
	/***************get file date start************************************/
	HANDLE hFile = CreateFile(strFilePath, GENERIC_READ,          // open for reading
	FILE_SHARE_READ,       // share for reading
	NULL,                            // default security
	OPEN_EXISTING,          // existing file only
	FILE_FLAG_BACKUP_SEMANTICS , // normal file
	NULL);
	if (!GetFileTime(hFile, &fileCreateDate, &fileAccessDate, &fileModifyDate))
	{
		return _T("");
	}

	ZeroMemory(&systemTimeLocal, sizeof(SYSTEMTIME));
	FileTimeToSystemTime(&fileModifyDate, &systemTimeLocal);
	
	switch(dateType)
	{
		case YEAR_MONTH_DAY:
			strDateFormat=_T("%04d/%02d/%02d %02d/%02d/%02d");
			strModifyTime.Format(strDateFormat, systemTimeLocal.wYear, systemTimeLocal.wMonth, systemTimeLocal.wDay,  systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 
			break;

		case MONTH_DAY_YEAR:
			strDateFormat=_T("%02d/%02d/%04d %02d/%02d/%02d");
			strModifyTime.Format(strDateFormat,  systemTimeLocal.wMonth, systemTimeLocal.wDay, systemTimeLocal.wYear, systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 
			break;

		case DAY_MONTH_YEAR:
			strDateFormat=_T("%02d/%02d/%04d %02d/%02d/%02d");
			strModifyTime.Format(strDateFormat, systemTimeLocal.wDay, systemTimeLocal.wMonth, systemTimeLocal.wYear, systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 
			break;

		default:
			strDateFormat=_T("%02d/%02d/%04d %02d/%02d/%02d");
			strModifyTime.Format(strDateFormat, systemTimeLocal.wDay, systemTimeLocal.wMonth, systemTimeLocal.wYear, systemTimeLocal.wHour+8, systemTimeLocal.wMinute, systemTimeLocal.wSecond); 
			break;
	}	

	finalResult=firstFileName+_T(" ")+strModifyTime;
	return finalResult;
}

void CgetFilePropertyMFCvs2019Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	try
	{ 
		int i=0;
		TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, OFN_ALLOWMULTISELECT, szFilter, this);
 
		TCHAR *pBuffer = new TCHAR[MAX_PATH * 100];
		fileDlg.m_ofn.lpstrFile = pBuffer;
		fileDlg.m_ofn.nMaxFile = MAX_PATH * 100;
		fileDlg.m_ofn.lpstrFile[0] = '\0'; 
		
		CArray<CString, CString> array_filename;

		CString strFilePath; 
		CString strFileNameAndProperties;

		if (IDOK == fileDlg.DoModal())
		{
			POSITION pos_file;
			pos_file = fileDlg.GetStartPosition();
          	 
			while(pos_file != NULL)
			{
				strFilePath = fileDlg.GetNextPathName(pos_file);
				array_filename.Add(strFilePath);
				//SetDlgItemText(IDC_EDIT1,  strFilePath);				
				//SetOneFileNameAndProToClip(strFilePath);	
				 
				if(strFileNameAndProperties.IsEmpty())
				{
					strFileNameAndProperties+=(GetFileNameAndProperties(strFilePath, globalDateType));
				}
				else
				{
					strFileNameAndProperties+=(_T("\r\n")+GetFileNameAndProperties(strFilePath, globalDateType));
				}
			}//end while       
			 			
			SetDlgItemText(IDC_EDIT1, strFileNameAndProperties);	
			SetClipBoardData(strFileNameAndProperties);
		}
	}
	catch(...)
	{
		
	}
}



void CgetFilePropertyMFCvs2019Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	
	UINT nCount;
    TCHAR szPath[MAX_PATH];
 	CString strFileNameAndProperties;
    nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
    if (nCount)
    {
        for (UINT nIndex = 0; nIndex < nCount; ++nIndex)
        {
            UINT pathlenght=DragQueryFile(hDropInfo, nIndex, szPath, _countof(szPath));
		
			CString filepath(szPath, pathlenght);//change the file path to CString format
			//SetDlgItemText(IDC_EDIT1,  filepath);	
            //MessageBox(szPath, _T("WM_DROPFILES"));
			//SetOneFileNameAndProToClip(filepath);	 
			if(strFileNameAndProperties.IsEmpty())
			{
				strFileNameAndProperties+=(GetFileNameAndProperties(filepath, globalDateType));
			}
			else
			{
				strFileNameAndProperties+=(_T("\r\n")+GetFileNameAndProperties(filepath, globalDateType));
			}
        }
    }
 
	SetDlgItemText(IDC_EDIT1, strFileNameAndProperties);	
	SetClipBoardData(strFileNameAndProperties);
    DragFinish(hDropInfo);
	
	CDialogEx::OnDropFiles(hDropInfo);
}




void CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioYMD()
{
	// TODO: Add your control notification handler code here
	globalDateType=YEAR_MONTH_DAY;
}


void CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioMdy()
{
	// TODO: Add your control notification handler code here
	globalDateType=MONTH_DAY_YEAR;
}


void CgetFilePropertyMFCvs2019Dlg::OnBnClickedRadioDmy()
{
	// TODO: Add your control notification handler code here
    globalDateType=DAY_MONTH_YEAR;
}

bool CgetFilePropertyMFCvs2019Dlg::IsFileExist(CString filePath)
{
	WIN32_FIND_DATA fd = {0};
	HANDLE hFind = FindFirstFile(filePath, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
	}
	return ((hFind != INVALID_HANDLE_VALUE) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

void CgetFilePropertyMFCvs2019Dlg::ProcessGetCommand(CString cString)
{
	// TODO: Add your control notification handler code here
	if(cString.IsEmpty())
		return ;

	CString strFileNameAndProperties;
	CString filepath;
	//+5 is for length of <.exe">
	int firstDirPos=cString.Find(_T(".exe\""))+5;
	int totalLen=cString.GetLength();
	int firstSpaceOfs=0, spaceOfsNext, lastSpaceOfs=0;
		
	/*
	* the directory path is separte by space
	*/

	//find the last space
	lastSpaceOfs=cString.ReverseFind(' ');

	//find the first space
	firstSpaceOfs=cString.Find(' ', firstDirPos);
	 	
	while(firstSpaceOfs<lastSpaceOfs)
	{
		spaceOfsNext=cString.Find(' ', firstSpaceOfs+1);
		filepath=cString.Mid(firstSpaceOfs+1, spaceOfsNext-firstSpaceOfs);
		firstSpaceOfs+=filepath.GetLength();

		if(IsFileExist(filepath)==false)
		{
			strFileNameAndProperties=_T("directory is invalid, do not support space in path");
			SetClipBoardData(strFileNameAndProperties);
			globalStrFileNameAndProperties=strFileNameAndProperties;
			return ;
		}

		if(strFileNameAndProperties.IsEmpty())
		{
			strFileNameAndProperties+=(GetFileNameAndProperties(filepath, globalDateType));
		}
		else
		{
			strFileNameAndProperties+=(_T("\r\n")+GetFileNameAndProperties(filepath, globalDateType));
		}
	}
 
	//the last one
	filepath=cString.Mid(lastSpaceOfs+1, totalLen-lastSpaceOfs-1);
	
	if(strFileNameAndProperties.IsEmpty())
	{
		strFileNameAndProperties+=(GetFileNameAndProperties(filepath, globalDateType));
	}
	else
	{
		strFileNameAndProperties+=(_T("\r\n")+GetFileNameAndProperties(filepath, globalDateType));
	}
 
	//here can not call SetDlgItemText(IDC_EDIT1, strFileNameAndProperties), becase it is not working
	SetClipBoardData(strFileNameAndProperties);
	globalStrFileNameAndProperties=strFileNameAndProperties;
}

