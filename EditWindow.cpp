// EditWindow.cpp : implementation file

#include "stdafx.h"
#include "TextEditor.h"
#include "EditWindow.h"
#include "TextEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditWindow

EditWindow::EditWindow()
{
	//m_Bitmap.LoadBitmap(IDB_EditBack);
}

EditWindow::~EditWindow()
{
}


BEGIN_MESSAGE_MAP(EditWindow, CEdit)
	//{{AFX_MSG_MAP(EditWindow)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_DROPFILES()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditWindow message handlers

/*BOOL EditWindow::OnEraseBkgnd(CDC* pDC) 
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);												//创建内存设备上下文
	memDC.SelectObject(&m_Bitmap);												//将位图选入设备上下文
	BITMAP m_Bmp;																//声明位图控件
	m_Bitmap.GetBitmap(&m_Bmp);													//获得位图信息
	int x = m_Bmp.bmWidth;														//获取图片宽度
	int y = m_Bmp.bmHeight;														//获取图片高度
	CRect rect;																	//声明矩形区域对象
	GetClientRect(rect);														//获取编辑区大小矩形框
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,x,y,SRCCOPY);		//伸展铺上图片
	memDC.DeleteDC();															//释放内存设备上下文
	return TRUE;
	
	//return CEdit::OnEraseBkgnd(pDC);
}
*/

void EditWindow::OnChange() 
{
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	Invalidate();																//刷新用户界面
	
}

HBRUSH EditWindow::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);												//设置文字背景透明
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}


void EditWindow::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);								//判断滚动条是否滑动
	Invalidate();																//刷新用户界面
}

void EditWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int n1,n2;
	n1 = GetScrollPos (SB_VERT);
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	n2 = GetScrollPos (SB_VERT);
	if (n1 != n2)																//判断滚动条是否滑动
	{
		Invalidate();															//刷新用户界面
	}
}

BOOL EditWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	BOOL editS = CEdit::OnMouseWheel(nFlags, zDelta, pt);

	Invalidate();																//刷新用户界面
	
	return editS;
}

//*****************************//
//拖入文件的处理函数(编辑框)   //
//*****************************//
void EditWindow::OnDropFiles(HDROP hDropInfo) 
{
	CWnd* pWnd = AfxGetApp()->GetMainWnd();											//获得主窗口句柄
	CTextEditorDlg * pDlg;
	pDlg=(CTextEditorDlg *) pWnd;															//获得指向主窗口的指针
	EditWindow * m_EditPtr = & (pDlg->m_Edit);										//设置指针指向主窗口m_Edit控件

	char *lpszFileName=new char[512]; 
	int nFileCount,i; nFileCount=::DragQueryFile (hDropInfo,0xFFFFFFFF,NULL,512);	//记录拖入的文件				
	
	for (i=0;i<nFileCount;i++)
	{ 
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0],512); 
		CString str(&lpszFileName[0],nChars);										//获得文件路径


		//打开前对现有文本的的处理
		pDlg->isModified = m_EditPtr->GetModify();									//获取文本修改标记
	
		CString string;
		m_EditPtr->GetWindowText(string);
		if (pDlg->isNew && string.IsEmpty())										//若是新建文本且文本无内容内容
		{
			pDlg->isNew = FALSE;
		}

		else if(pDlg->isModified)													//如果文本已被修改，分情况讨论
		{
			int Choice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNO|MB_ICONQUESTION);												//弹出消息对话框询问
			if(Choice==IDYES)														//选择“是”
			{
				pDlg->OnMenuSave();													//调用保存函数保存文件
			}
		}

		CString strPath,strText="";
		strPath = str;
	
		pDlg->SavePath = str;

		int n = pDlg->SavePath.ReverseFind('.');   
		CString stl = (pDlg->SavePath).Right((pDlg->SavePath).GetLength() - n - 1);
		if (stl == "txt" || stl == "TXT" || stl == "c" || stl == "C" || stl == "cpp" || stl == "CPP"
			|| stl == "h" || stl == "H" || stl == "xml" || stl == "XML" || stl == "html" || stl == "HTML")
		{
			CFile file(str,CFile::modeReadWrite);										//以读与写方式打开文件		
		
			//拖入打开
			m_EditPtr->SetSel(0, -1);													//全部选中文本内容
			m_EditPtr->Clear();															//将所有文本删除

			char read[50000];
			file.Read(read,50000);														//读取文件内容
			for(unsigned i=0;i<file.GetLength();i++)
			{
				strText += read[i];														//把文件内容赋值给CString变量
			}		
			file.Close();																//关闭文件
			m_EditPtr->SetWindowText(strText);

			pDlg->isNew = FALSE;														//标记为打开文本
			m_EditPtr->SetModify(FALSE);												//文本修改标记设为修改
		}
		else
		{
			MessageBox ("不支持的文件类型！","打开错误");
		}
	} 
	::DragFinish (hDropInfo);															//释放内存 
	i=0;
	delete []lpszFileName; 
}

//*****************************//
//   处理鼠标运动的有关相应     //
//*****************************//

void EditWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	int n1,n2;
	n1 = GetScrollPos (SB_VERT);
	CEdit::OnMouseMove(nFlags, point);
	n2 = GetScrollPos (SB_VERT);
	if (n1 != n2)																//判断滚动条是否滑动
	{
		//Invalidate();															//刷新用户界面
		CRect rect (15,80,586,686);
		InvalidateRect(rect);													//刷新用户界面
	}
}
