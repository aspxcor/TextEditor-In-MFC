#if !defined(AFX_COUNTALLDLG_H__46B2F9AC_6E73_4EE7_8B00_A107804BB8A5__INCLUDED_)
#define AFX_COUNTALLDLG_H__46B2F9AC_6E73_4EE7_8B00_A107804BB8A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountDlg dialog

class CCountDlg : public CDialog
{
// Construction
public:
	void SetText(int allch,int Chinese,int English,int number,int blank);
	CCountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCountDlg)
	enum { IDD = IDD_COUNTALLBOX };
	int		m_AllChar;									//所有字符数
	int		m_BlankChar;								//空格数
	int		m_ChineseChar;								//全角字符数（中文字符数）
	int		m_EnglishChar;								//英文字母数
	int		m_NumberChar;								//数字字符数
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCountDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTALLDLG_H__46B2F9AC_6E73_4EE7_8B00_A107804BB8A5__INCLUDED_)
