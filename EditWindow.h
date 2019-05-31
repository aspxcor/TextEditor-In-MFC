#if !defined(AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_)
#define AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditWindow window

class EditWindow : public CEdit
{
// Construction
public:
	EditWindow();
	CBitmap m_Bitmap;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~EditWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(EditWindow)
	afx_msg void OnChange();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);		//²»Éú³É±³¾°
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_)
