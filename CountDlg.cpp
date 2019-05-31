// CountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TextEditor.h"
#include "CountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountDlg dialog


CCountDlg::CCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountDlg)
	m_AllChar = 0;
	m_ChineseChar = 0;
	m_EnglishChar = 0;
	m_NumberChar = 0;
	m_BlankChar = 0;
	//}}AFX_DATA_INIT
}


void CCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountDlg)
	DDX_Text(pDX, IDC_ALLCH, m_AllChar);
	DDV_MinMaxInt(pDX, m_AllChar, 0, 50000);
	DDX_Text(pDX, IDC_BLKCH, m_BlankChar);
	DDV_MinMaxInt(pDX, m_BlankChar, 0, 50000);
	DDX_Text(pDX, IDC_CHNCH, m_ChineseChar);
	DDV_MinMaxInt(pDX, m_ChineseChar, 0, 50000);
	DDX_Text(pDX, IDC_ENGCH, m_EnglishChar);
	DDV_MinMaxInt(pDX, m_EnglishChar, 0, 50000);
	DDX_Text(pDX, IDC_NUMCH, m_NumberChar);
	DDV_MinMaxInt(pDX, m_NumberChar, 0, 50000);
	//}}AFX_DATA_MAP
}

//*****************************//
//显示统计结果的处理函数       //
//*****************************//
void CCountDlg::SetText(int allch,int Chinese,int English,int number,int blank)
{
	m_AllChar = allch;
	m_ChineseChar = Chinese;
	m_EnglishChar = English;
	m_NumberChar = number;
	m_BlankChar = blank;
}

BEGIN_MESSAGE_MAP(CCountDlg, CDialog)
	//{{AFX_MSG_MAP(CCountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountDlg message handlers

BOOL CCountDlg::OnInitDialog() 
//指定对话框是否对它的一个控件设置输入焦点
//如果OnInitDialog返回非零值，Windows将输入焦点设在对话框的第一个控件上，
//只有在对话框明确将输入焦点设在某控件上，应用返回0。
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


