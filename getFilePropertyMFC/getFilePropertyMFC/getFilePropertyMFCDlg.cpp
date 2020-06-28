
// getFilePropertyMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getFilePropertyMFC.h"
#include "getFilePropertyMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgetFilePropertyMFCDlg dialog




CgetFilePropertyMFCDlg::CgetFilePropertyMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgetFilePropertyMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgetFilePropertyMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgetFilePropertyMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CgetFilePropertyMFCDlg::OnBnClickedButton1)
	ON_WM_DROPFILES()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_RADIO_Y_M_D, &CgetFilePropertyMFCDlg::OnBnClickedRadioYMD)
	ON_BN_CLICKED(IDC_RADIO_MDY, &CgetFilePropertyMFCDlg::OnBnClickedRadioMdy)
	ON_BN_CLICKED(IDC_RADIO_DMY, &CgetFilePropertyMFCDlg::OnBnClickedRadioDmy)
END_MESSAGE_MAP()


// CgetFilePropertyMFCDlg message handlers

BOOL CgetFilePropertyMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	/*CString string01=_T("使用方法：");
	CString string02=_T("1. 拖动文件");
	CString string03=_T("2. Ctrl+V ");
	CString stringReturn=_T("\r\n");
	CString initTips=string01+stringReturn+string02+stringReturn+string03;
	SetDlgItemText(IDC_EDIT1, initTips);	
	*/
	
	CheckRadioButton(IDD_GETFILEPROPERTYMFC_DIALOG,IDC_RADIO_DMY,IDC_RADIO_DMY);
	globalDateType=DAY_MONTH_YEAR;

	if(!globalStrFileNameAndProperties.IsEmpty())
	{
		SetDlgItemText(IDC_EDIT1, globalStrFileNameAndProperties);	
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgetFilePropertyMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgetFilePropertyMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CgetFilePropertyMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void  CgetFilePropertyMFCDlg::SetClipBoardData(CString cStringText)
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


void CgetFilePropertyMFCDlg::SetOneFileNameAndProToClip(CString strFilePath)
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


CString CgetFilePropertyMFCDlg::GetFileNameAndProperties(CString strFilePath, int dateType)
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

void CgetFilePropertyMFCDlg::OnBnClickedButton1()
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



void CgetFilePropertyMFCDlg::OnDropFiles(HDROP hDropInfo)
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




void CgetFilePropertyMFCDlg::OnBnClickedRadioYMD()
{
	// TODO: Add your control notification handler code here
	globalDateType=YEAR_MONTH_DAY;
}


void CgetFilePropertyMFCDlg::OnBnClickedRadioMdy()
{
	// TODO: Add your control notification handler code here
	globalDateType=MONTH_DAY_YEAR;
}


void CgetFilePropertyMFCDlg::OnBnClickedRadioDmy()
{
	// TODO: Add your control notification handler code here
    globalDateType=DAY_MONTH_YEAR;
}

void CgetFilePropertyMFCDlg::processGetCommand(CString cString)
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
	
	/***********debug start**************
	CString debugStr;
	CString strFirstDirPos;
	CString strTotalLen;
	CString strSpaceOfs;
	CString strLastSpaceOfs;
    CString strSpaceOfsNext;
	spaceOfsNext=cString.Find(' ', firstSpaceOfs+1);

	strFirstDirPos.Format(_T("%d"),firstDirPos);
	strTotalLen.Format(_T("%d"),totalLen);
	strSpaceOfs.Format(_T("%d"),firstSpaceOfs);
	strLastSpaceOfs.Format(_T("%d"),lastSpaceOfs);
	strSpaceOfsNext.Format(_T("%d"),spaceOfsNext);
	strFileNameAndProperties=cString.Mid(firstSpaceOfs, totalLen-firstSpaceOfs);

	debugStr=strFirstDirPos+_T("::total len: ")+strTotalLen+(" ::fist space: ")+strSpaceOfs+(" ::space ofs next : ")+strSpaceOfsNext+(" ::last:: ")+strLastSpaceOfs+(" ::: ")+strFileNameAndProperties+(" ##")+cString;
	SetClipBoardData(debugStr);
	***********debug end*****************/
	
	while(firstSpaceOfs<lastSpaceOfs)
	{
		spaceOfsNext=cString.Find(' ', firstSpaceOfs+1);
		filepath=cString.Mid(firstSpaceOfs+1, spaceOfsNext-firstSpaceOfs);
		firstSpaceOfs+=filepath.GetLength();

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

