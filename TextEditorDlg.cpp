// TextEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TextEditor.h"
#include "TextEditorDlg.h"
//#include "CountStringDlg.h"
#include "splash.h"
#include "CountDlg.h"
#include "HelpDlg.h"
#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT WM_FINDMESSAGE = RegisterWindowMessage(FINDMSGSTRING);   //定义“查找/替换”消息

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditorDlg dialog

CTextEditorDlg::CTextEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextEditorDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hAccel=::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR1));//根据所创建的加速键表加载加速键  
}

void CTextEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextEditorDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CTextEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_SAVEAS, OnMenuSaveas)
	ON_COMMAND(ID_MENU_FIND_REPLACE, OnMenuFindReplace)
	ON_REGISTERED_MESSAGE(WM_FINDMESSAGE, OnFindReplace)
	ON_COMMAND(ID_MENU_FONT, OnMenuFont)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_COPY, OnMenuCopy)
	ON_COMMAND(ID_MENU_PASTE, OnMenuPaste)
	ON_COMMAND(ID_MENU_CUT, OnMenuCut)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	//ON_COMMAND(ID_MENU_COUNT_STRING, OnMenuCountString)
	ON_COMMAND(ID_MENU_COUNT_ALL, OnMenuCountAll)
	ON_COMMAND(ID_MENU_HELP, OnMenuHelp)
	ON_COMMAND(ID_MENU_REG, OnMenuReg)
	ON_COMMAND(ID_MENU_BACKUP, OnMenuBackUp)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditorDlg message handlers

//*****************************//
//对话框的初始化函数           //
//*****************************//
BOOL CTextEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	//创建菜单
	m_Menu.CreateMenu();					//创建菜单窗口
   
	//“文件”菜单
	CMenu m_PopMenu1;						//定义菜单对象	
	m_PopMenu1.CreatePopupMenu();			//创建弹出菜单窗口
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu1.m_hMenu,"文件(&F)");     //插入菜单
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_NEW,"新建(&N)   Ctrl+N");    //插入子菜单
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_OPEN,"打开(&O)   Ctrl+O");   //插入子菜单
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVE,"保存(&S)   Ctrl+S");   //插入子菜单
    m_PopMenu1.AppendMenu(MF_SEPARATOR);                                 //插入分隔线
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVEAS,"另存为(&A)");        //插入子菜单
	
	//“编辑”菜单
	CMenu m_PopMenu2;
	m_PopMenu2.CreatePopupMenu();                                  
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu2.m_hMenu,"编辑(&E)");     
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_UNDO,"撤销(&U)   Ctrl+Z");
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_REDO, "重做(&R)   Ctrl+Y");
    m_PopMenu2.AppendMenu(MF_SEPARATOR);
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_SELECT_ALL,"全选(&A)   Ctrl+A");
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_CUT,"剪切(&T)   Ctrl+X");		  
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_COPY,"复制(&C)   Ctrl+C");         
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_PASTE,"粘贴(&V)   Ctrl+V");        
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_DELETE, "删除(&D)");
	m_PopMenu2.AppendMenu(MF_SEPARATOR);
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_FIND_REPLACE, "查找与替换(&F)     Ctrl+F");

	//“应用”菜单
	CMenu m_PopMenu3;
	m_PopMenu3.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu3.m_hMenu,"应用(&A)");
	//m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FIND_REPLACE,"查找/替换(&F)     Ctrl+F");
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FONT,"字体(&S)          Alt+F");
	m_PopMenu3.AppendMenu(MF_SEPARATOR); 
	m_PopMenu3.AppendMenu(MF_STRING, ID_MENU_REG, "关联注册(&R)");
	m_PopMenu3.AppendMenu(MF_STRING, ID_MENU_BACKUP, "还原注册(&B)");
	//m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_COUNT_STRING,"统计字符串(&C)");
	m_PopMenu3.AppendMenu(MF_SEPARATOR);
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_COUNT_ALL,"字数统计(&C)");	

	//“帮助”菜单
	CMenu m_PopMenu4;
	m_PopMenu4.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu4.m_hMenu,"帮助(&H)");
	m_PopMenu4.AppendMenu(MF_STRING, ID_MENU_HELP, "查看帮助(&H)   Ctrl+H");
	m_PopMenu4.AppendMenu(MF_STRING,ID_MENU_ABOUT,"关于TextEditor(&A)");

	//“高级”菜单
	/*
	CMenu m_PopMenu5;
	m_PopMenu5.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu5.m_hMenu,"高级(&H)");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_REG,"关联注册(&R)");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_BACKUP,"还原注册(&B)");
    */

	//分离菜单句柄
	m_PopMenu1.Detach();
	m_PopMenu2.Detach();
	m_PopMenu3.Detach();
	m_PopMenu4.Detach();
	//m_PopMenu5.Detach();
	SetMenu(&m_Menu); //将菜单和窗口进行关联
	
	//不创建工具栏
	/*if (!TextEditor_ToolBar.CreateEx (this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC))
	{
		return FALSE;
	}
	CImageList ImageList;																	//声明图像列表对象
	ImageList.Create(32,32,ILC_COLOR32|ILC_MASK,10,10);										//创建图像列表
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));										//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON9));										//设置图标
	TextEditor_ToolBar.GetToolBarCtrl().SetImageList(&ImageList);									//关联图像列表
	ImageList.Detach();																		//释放图像列表
	TextEditor_ToolBar.SetButtons(NULL,9);															//设置工具栏按钮

	TextEditor_ToolBar.SetButtonInfo(0,ID_MENU_NEW,TBSTYLE_BUTTON,0);								//设置工具栏信息
	TextEditor_ToolBar.SetButtonText(0,"新建文件");												//设置工具栏文本
	TextEditor_ToolBar.SetButtonInfo(1,ID_MENU_OPEN,TBSTYLE_BUTTON,1);
	TextEditor_ToolBar.SetButtonText(1,"打开文件");
	TextEditor_ToolBar.SetButtonInfo(2,ID_MENU_SAVE,TBSTYLE_BUTTON,2);
	TextEditor_ToolBar.SetButtonText(2,"保存文件");
	TextEditor_ToolBar.SetButtonInfo(3,ID_MENU_SAVEAS,TBSTYLE_BUTTON,3);
	TextEditor_ToolBar.SetButtonText(3,"另存文件");
	TextEditor_ToolBar.SetButtonInfo(4,ID_MENU_FIND_REPLACE,TBSTYLE_BUTTON,4);
	TextEditor_ToolBar.SetButtonText(4,"查找替换");
	TextEditor_ToolBar.SetButtonInfo(5,ID_MENU_FONT,TBSTYLE_BUTTON,5);
	TextEditor_ToolBar.SetButtonText(5,"字体设置");
	TextEditor_ToolBar.SetButtonInfo(6,ID_MENU_COUNT_STRING,TBSTYLE_BUTTON,6);
	TextEditor_ToolBar.SetButtonText(6,"统计字串");
	TextEditor_ToolBar.SetButtonInfo(7,ID_MENU_COUNT_ALL,TBSTYLE_BUTTON,7);
	TextEditor_ToolBar.SetButtonText(7,"统计字数");
	TextEditor_ToolBar.SetButtonInfo(8,ID_MENU_HELP,TBSTYLE_BUTTON,8);
	TextEditor_ToolBar.SetButtonText(8,"帮助提示"); 

	TextEditor_ToolBar.SetSizes(CSize(60,60),CSize(32,32));										//设置按钮大小
	TextEditor_ReBar.Create(this);																	//创建容器
	TextEditor_ReBar.AddBar(&TextEditor_ToolBar);															//设置目标工具栏
    TextEditor_ReBar.RedrawWindow();																//刷新窗口
	REBARBANDINFO info;																		
	info.cbSize = sizeof(info);																//设置结构大小
	info.fMask = RBBIM_BACKGROUND;															//设置标记
	TextEditor_ToolBar.ModifyStyle(0,TBSTYLE_TRANSPARENT);											//设置工具栏风格
	TextEditor_ReBar.GetReBarCtrl().SetBandInfo(0,&info);											//访问工具栏
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);						//显示工具栏
	*/
	OpenFile();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTextEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTextEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTextEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//*****************************//
//“打开”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuOpen()
{
    // TODO: Add your control notification handler code here
	//打开前对现有文本的的处理
	isModified = m_Edit.GetModify();									//获取文本修改标记

    CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())										//若是新建文本且文本无内容
	{
		;
	}

	else if(isModified)													//如果文本已被修改，分情况讨论
	{
	    int Choice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNO|MB_ICONQUESTION);									//弹出消息对话框询问
	    if(Choice==IDYES)												//选择“是”
		{
			OnMenuSave();												//调用保存函数保存文件
		}
	}
    
	//打开
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||",AfxGetMainWnd());					//构造“文件打开”对话框
	CString strPath,strText="";
	if(dlg.DoModal() == IDOK)											//判断按下“打开”
	{
		strPath = SavePath = dlg.GetPathName();							//获取文件打开路径
		CFile file(strPath,CFile::modeReadWrite);						//以读与写方式打开文件
		char read[50000];
		file.Read(read,50000);											//读取文件内容
		for(unsigned i=0;i<file.GetLength();i++)
		{
			strText += read[i];											//把文件内容赋值给CString变量
		}		
		file.Close();													//关闭文件
		m_Edit.SetWindowText(strText);									//在编辑框中显示文件内容
		m_Edit.SetModify(FALSE);										//文本修改标记设为未修改
		isNew = FALSE;													//不是新建的文本
	}
}

//*****************************//
//“新建”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuNew()
{
	//新建前对现有文本的的处理
	isModified = m_Edit.GetModify();									//获取文本修改标记
	
	CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())										//若是新建文本且文本无内容内容
	{
		;
	}

	else if(isModified)													//如果文本已被修改，分情况讨论
	{
	    int Choice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNO|MB_ICONQUESTION);									//弹出消息对话框询问
	    if(Choice==IDYES)												//选择“是”
		{
			OnMenuSave();												//调用保存函数保存文件
		}
	}
    
	//新建
	m_Edit.SetSel(0, -1);												//全部选中文本内容
	m_Edit.Clear();														//将所有文本删除
	isNew = TRUE;														//标记为新建文本
	m_Edit.SetModify(FALSE);											//文本修改标记设为未修改
}

//*****************************//
//“保存”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuSave()
{
    if (isNew)											//对新建且未保存的文本调用“另存为”进行保存
	{
		OnMenuSaveas();									//新建文本已保存
	}
	else												//对打开的文件修改后进行保存
	{            
		CString strText="";
		char write[50000];		
		CFile file(_T(SavePath),CFile::modeCreate|CFile::modeReadWrite);//以读与写方式创建文件
		m_Edit.GetWindowText(strText);                  //获取编辑框中的内容
		strcpy(write,strText);                          //将编辑框中的内容赋值给字符串数组
		file.Write(write,strText.GetLength());          //把编辑框中的内容写入文件
		file.Close();									//关闭文件
		m_Edit.SetModify(FALSE);						//设置修改标记为未修改
	}
	m_Edit.SetSel(0,0);
}

//*****************************//
//“另存为”的处理函数         //
//*****************************//
void CTextEditorDlg::OnMenuSaveas()
{
	CFileStatus fs;										//文件存在状态 

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.txt)|*.txt||",AfxGetMainWnd());    //构造“文件另存为”对话框
	CString strPath,strText="";
	char write[50000];
	if(dlg.DoModal() == IDOK)                           //判断按下“另存为”
	{
		strPath = dlg.GetPathName();                    //获取文件另存为路径
		if(strPath.Right(4) != ".txt")
		{
			strPath += ".txt";                          //设置文件扩展名为txt
		}

		if(CFile::GetStatus(_T(strPath),fs))			//如果文件存在
		{   
			CString info = strPath;
			info += " 已存在。\r\n要替换它吗？";
			int nChoice = MessageBox (info,"另存为",MB_ICONWARNING|MB_YESNO);	//弹出确认替换消息
			if (nChoice == IDYES)												//如果确认替换
			{
				
				SavePath = strPath;												//获取保存新建文本的路径
		
				CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);		//以只写方式创建文件
				m_Edit.GetWindowText(strText);									//获取编辑框中的内容
				strcpy(write,strText);											//将编辑框中的内容赋值给字符串数组
				file.Write(write,strText.GetLength());							//把编辑框中的内容写入文件
				file.Close();													//关闭文件
				isNew = FALSE;
				m_Edit.SetModify(FALSE);
			}
			else																//不替换
			{
				OnMenuSaveas();													//弹出另存对话框
			}
		}
		else																	//如果文件不存在
		{
			SavePath = strPath;													//获取保存新建文本的路径

			CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);			//以只写方式创建文件
			m_Edit.GetWindowText(strText);										//获取编辑框中的内容
			strcpy(write,strText);												//将编辑框中的内容赋值给字符串数组
			file.Write(write,strText.GetLength());								//把编辑框中的内容写入文件
			file.Close();
			isNew = FALSE;
			m_Edit.SetModify(FALSE);
		}									
	}
	m_Edit.SetSel(0,0);
	
	CRect rect (15,80,586,686);
	InvalidateRect(rect);														//刷新用户界面
}

//*****************************//
//“查找/替换”的菜单响应函数  //
//*****************************//
void CTextEditorDlg::OnMenuFindReplace()
{
	// TODO: Add your control notification handler code here
	nindex = 0;
	degree = FALSE;
	index = 0;
	dlg = new CFindReplaceDialog;									//声明“查找/替换”对话框指针
	dlg->Create(FALSE,NULL);										//创建“替换”对话框
	dlg->ShowWindow(SW_SHOW);										//显示“替换”对话框
}

//*****************************//
//“查找/替换”的处理函数      //
//*****************************//
long CTextEditorDlg::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
	CString strText,repText;										//声明字符串变量
	strText = dlg->GetFindString();									//获得查找字符串
	CString str;													//声明字符串变量
	m_Edit.GetWindowText(str);										//获得编辑框中是文本

	int len;

	if(dlg->ReplaceAll())											//判断是否全部替换
	{
		strText = dlg->GetFindString();								//获得查找字符串
		repText = dlg->GetReplaceString();							//获得替换字符串
		len = repText.GetLength();									//获得替换字符串长度
		str.Replace(strText,repText);								//使用替换字符串替换查找字符串
		m_Edit.SetWindowText(str);									//将替换后的字符串显示在编辑框中
		nindex =0;													//设置查找位置为初始
		m_Edit.SetModify(TRUE);		             					//文本修改标记设为修改
		m_Edit.SetSel(0,-1);

		CRect rect (15,80,586,686);
		InvalidateRect(rect);										//刷新界面
	}
	
	if(dlg->ReplaceCurrent())										//替换
		find = FALSE;												//进行替换
	else
	{
		find = TRUE;												//进行查找
	}
    																//声明整型变量
	
	if(find)														//判断是查找还是替换
	{
		len = strText.GetLength();									//获得要查找字符串的长度
	}
	else
	{
		CString left,right;											//声明字符串变量
		int num   = strText.GetLength();							//获得查找字符串的长度
		int strnum = str.GetLength();								//获得编辑框中文本长度	
		
		if(!degree)													//判断为第一次替换
			index = str.Find(strText,nindex);						//获得查找字符串在编辑框文本中的位置

		if(index < 0)
		{
			nindex = 0;
			degree = FALSE;
			return 1;
		}		

		left = str.Left(index);										//获得替换字符串左侧的字符串
		right = str.Right(strnum-index-num);						//获得替换字符串右侧的字符串
		repText = dlg->GetReplaceString();							//获得替换字符串
		len = repText.GetLength();									//获得替换字符串长度
		str = left + repText + right;								//组合成新的字符串
		m_Edit.SetWindowText(str);									//在编辑框中显示新的字符串
		m_Edit.SetModify(TRUE);		             					//文本修改标记设为修改
	}
	
	strText = dlg->GetFindString();									//获得查找字符串
	m_Edit.GetWindowText(str);										//获得编辑框中是文本

	index = str.Find (strText,nindex);								//获得查找字符串在编辑框文本中的位置
	
	m_Edit.SetSel(index,index+strText.GetLength());					//选中查找或替换的字符串
	nindex = index+len;												//设置起始查找位置
	if (index >= 0)
	{
		degree = TRUE;
	}
	else
	{
		degree = FALSE;
		nindex = 0;
	}
	m_Edit.SetFocus();												//编辑框获得焦点

	CRect rect1 (15,80,586,686);
	InvalidateRect(rect1);											//刷新界面

	return 0;
}

//*****************************//
//“字体”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuFont()
{
	// TODO: Add your control notification handler code here
	CFont* TempFont = m_Edit.GetFont();             //获取编辑框当前字体
	LOGFONT LogFont;
	TempFont->GetLogFont(&LogFont);					//获取字体信息
	CFontDialog dlg(&LogFont);						//初始化字体信息
	if(dlg.DoModal()==IDOK)
	{
		m_Font.Detach();                            //分离字体
		LOGFONT temp;
		dlg.GetCurrentFont(&temp);					//获取当前字体信息
		m_Font.CreateFontIndirect(&temp);			//直接创建字体
		m_Edit.SetFont(&m_Font);					//设置字体
	}
}

//*****************************//
//“关于TextEditor”的处理函数        //
//*****************************//
void CTextEditorDlg::OnMenuAbout()
{
	CAboutDlg dlg;       //声明系统关于对话框类对象
	dlg.DoModal();		 //显示对话框
}

//*****************************//
//“复制”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuCopy()
{
	m_Edit.Copy();       //将编辑框中的当前选中文本拷贝到剪贴板中
}

//*****************************//
//“粘贴”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuPaste()
{
	m_Edit.Paste();      //在当前光标位置插入剪贴板内的文本
}

//*****************************//
//“剪切”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuCut()
{
	m_Edit.Cut();        //删除编辑控件中当前选中的文本，并将删除的文本拷贝到剪贴板中
}

//*****************************//
//“删除”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuDelete()
{
	m_Edit.Clear();      //删除编辑框中当前选中的文本
}

//*****************************//
//“全选”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuSelectAll()
{
	m_Edit.SetSel(0, -1);//全部选中文本内容
}

//*****************************//
//“撤销”的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuUndo()
{
	m_Edit.Undo();       //撤销上一次的编辑框中的操作（单级撤销）
}

//*****************************//
//退出程序的处理函数           //
//*****************************//
void CTextEditorDlg::OnClose() 
{
	isModified = m_Edit.GetModify();				//获取文本修改标记
	CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())					//若是新建文本且文本无内容内容
	{
		CDialog::OnClose();							//退出程序
	}
	else if(isModified)								//如果文本已被修改，分情况讨论
	{
	    int QuitChoice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNOCANCEL|MB_ICONQUESTION);		//弹出消息对话框询问
	    if(QuitChoice==IDYES)						//选择“是”
		{
			OnMenuSave();							//调用保存函数保存文件
			if (isModified = FALSE)
				CDialog::OnClose();					//退出程序
		}
		else if(QuitChoice==IDNO)					//选择“否”
		{
			CDialog::OnClose();						//退出程序
		}
		else
		{
		    return;									//选择“取消”时不退出
		}
	}
	else
	{
	    CDialog::OnClose();							//如果文本未被修改则直接退出程序
	}
}

//*****************************//
//统计字符串的处理函数         //
//*****************************//
/*
void CTextEditorDlg::OnMenuCountString()
{
	CString str;
	m_Edit.GetWindowText(str);						//获取编辑框文本
	//CCountStringDlg dlg;							//声明统计字符串对话框类对象
    //dlg.SetText(str);
	//dlg.DoModal();									//显示对话框

}
*/

//*****************************//
//统计字符的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuCountAll()
{
	
	int nTotalLenth = 0;					//总共字数 
	int nCLenth = 0;						//中文   
	int nELenth = 0;						//英文  
	int nNLenth = 0;						//数字
	int nBLenth = 0;						//空格
	int nEnLenth = 0;						//半角字符
	int nEnterLenth = 0;					//回车
	
	CString strText;
	m_Edit.GetWindowText(strText);
	int Lenth = strText.GetLength();

	for(int i=0;i<Lenth;i++)    
	{    
       
		char c = strText.GetAt(i);			//获取当前字符   
       
		//中文字符     
		if(c<0||c>255)    
			continue;
		
		//英文字符   
		else    
		{
			if(c == '\r')					//回车符
			{
				i ++;						//跳过"\n"
				nEnterLenth ++;				//回车符计数加1
			}
			else
			{
				nEnLenth ++;
				if (c == ' ')				//空格数加1
					nBLenth ++;
				else if (c>='0' && c<='9')	//数字字符加1
					nNLenth ++;
				else if ((c>='a'&&c<='z')||(c>='A' && c <= 'Z'))
					nELenth ++;				//英文字符数加1
			}
		}
  
	}    
	//计算中文字符数   
	nCLenth = (Lenth-nEnLenth)/2-nEnterLenth;
	nTotalLenth = nCLenth + nEnLenth; 

	CCountDlg dlg;	   //声明统计字数对话框类对象
	dlg.SetText(nTotalLenth,nCLenth,nELenth,nNLenth,nBLenth);
	dlg.DoModal();		   //显示对话框  
}

//*****************************//
//帮助的处理函数   			   //
//*****************************//
void CTextEditorDlg::OnMenuHelp()
{
    CHelpDlg dlg;          //声明帮助对话框类对象
	dlg.DoModal();		   //显示对话框
}

//*****************************//
//函数功能：加载加速键         //
//*****************************//
BOOL CTextEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_hAccel!=NULL)   
	if(::TranslateAccelerator(m_hWnd,m_hAccel,pMsg))   //翻译加速键表
	return TRUE;  
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CTextEditorDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

//*****************************//
//启动画面的处理函数           //
//*****************************//
int CTextEditorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CSplashWnd::ShowSplashScreen(this);							//显示启动画面
	Sleep(2000);												//设置启动画面显示时间

	

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DragAcceptFiles(TRUE);

	return 0;
}


//*****************************//
//拖入文件的处理函数(对话框)   //
//*****************************//
void CTextEditorDlg::OnDropFiles(HDROP hDropInfo)     
{ 
	
	char *lpszFileName=new char[512]; 
	int nFileCount,i; nFileCount=::DragQueryFile (hDropInfo,0xFFFFFFFF,NULL,512); 

	for (i=0;i<nFileCount;i++)
	{ 
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0],512); 
		CString str(&lpszFileName[0],nChars);								//获得文件路径


		//打开前对现有文本的的处理
		isModified = m_Edit.GetModify();									//获取文本修改标记
	
		CString string;
		m_Edit.GetWindowText(string);
		if (isNew && string.IsEmpty())										//若是新建文本且文本无内容内容
		{
			;
		}

		else if(isModified)													//如果文本已被修改，分情况讨论
		{
			int Choice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNO|MB_ICONQUESTION);										//弹出消息对话框询问
			if(Choice==IDYES)												//选择“是”
			{
				OnMenuSave();												//调用保存函数保存文件
			}
		}

		CString strText="";
		SavePath = str;

		int n = SavePath.ReverseFind('.');   
		CString stl = SavePath.Right(SavePath.GetLength() - n - 1);
		if (stl == "txt" || stl == "TXT" || stl == "c" || stl == "C" || stl == "cpp" || stl == "CPP"
			|| stl == "h" || stl == "H" || stl == "xml" || stl == "XML" || stl == "html" || stl == "HTML")
		{
			CFile file(str,CFile::modeReadWrite);								//以读与写方式打开文件		
		
			//拖入打开
			m_Edit.SetSel(0, -1);												//全部选中文本内容
			m_Edit.Clear();														//将所有文本删除

			char read[50000];
			file.Read(read,50000);												//读取文件内容
			for(unsigned i=0;i<file.GetLength();i++)
			{
				strText += read[i];												//把文件内容赋值给CString变量
			}		
			file.Close();														//关闭文件
			m_Edit.SetWindowText(strText);
			isNew = FALSE;														//标记为打开文本
			m_Edit.SetModify(FALSE);											//文本修改标记设为修改
		}
		else
		{
			MessageBox ("不支持的文件类型！","打开错误");
		}
	} 
	::DragFinish (hDropInfo); //释放内存 
	i=0;
	delete []lpszFileName; 
}

//**********************************//
//拖在程序图标上打开文件的处理函数  //
//**********************************//
void CTextEditorDlg::OpenFile()
{
	CString strCmdLine = GetCommandLine();

	int totalLen = strCmdLine.GetLength();
	int i = 0;
	int index = 0;
	//循环统计字符个数
	for (i = 0,index = 0; i < 3; i++,index ++)
	{
		index = strCmdLine.Find("\"", index);											//查找字符串
	}
	if (index != 0)
	{
		for (i = index;i < totalLen - 1;i ++)
			SavePath += strCmdLine.GetAt(i);
		
		int n = SavePath.ReverseFind('.');   
		CString stl = SavePath.Right(SavePath.GetLength() - n - 1);
		if (stl == "txt" || stl == "TXT" || stl == "c" || stl == "C" || stl == "cpp" || stl == "CPP"
			|| stl == "h" || stl == "H" || stl == "xml" || stl == "XML" || stl == "html" || stl == "HTML")
		{
			CString strText;
			CFile file(SavePath,CFile::modeReadWrite);									//以读与写方式打开文件
			char read[50000];
			file.Read(read,50000);														//读取文件内容
			for(unsigned i=0;i<file.GetLength();i++)
			{
				strText += read[i];														//把文件内容赋值给CString变量
			}		
			file.Close();																//关闭文件
			m_Edit.SetWindowText(strText);												//在编辑框中显示文件内容
			m_Edit.SetModify(FALSE);													//文本修改标记设为未修改
			isNew = FALSE;
			Invalidate();
		}
		else
		{
			MessageBox ("不支持的文件类型！","打开错误");
			m_Edit.SetModify(FALSE);													//文本修改标记设为未修改
			isNew = TRUE;
		}
	}
	else
	{
		m_Edit.SetModify(FALSE);														//文本修改标记设为未修改
		isNew = TRUE;
	}
	m_Edit.SetSel(0,0);
}

//*****************************//
//写注册表的处理函数           //
//*****************************//
void CTextEditorDlg::OnMenuReg()
{
	int nChoice = MessageBox ("即将将此程序的信息写入系统注册表。\r\n确定要写入吗？","程序注册",MB_ICONWARNING|MB_YESNO);
	if(nChoice == IDYES)
	{
		HKEY hresult;   
		CString str1,str2;   
		long value;   
    
		LPCTSTR dataset1 = "txtfile\\shell\\OPEN";									//打开方式子键
		LPCTSTR dataset2 = "txtfile\\shell\\OPEN\\command";							//启用程序路径子键   
		LPCTSTR dataset3Icon = "txtfile\\DefaultIcon";								//关联图标子键   
    
		//获得三个子键要设置的内容
		str1="用TextEditor miniword打开";  
		
		char buffModulPath[MAX_PATH];   
		GetModuleFileName(GetModuleHandle(NULL),buffModulPath,MAX_PATH);   
    
		str2.Format("%s",(LPCTSTR)buffModulPath);
		str2 = "\"" + str2 + "\" ";
		CString str3 = str2;   
		str2 += "\"%1\"";
		CString CTextName = "TextEditor.exe,10";											//关联后显示你的图标  
		

		for (int nPathEnd = strlen(buffModulPath) - 1; nPathEnd >= 0; nPathEnd --)	//获得程序路径
		{   
			if (buffModulPath[nPathEnd]=='\\')   
			{     
				buffModulPath[nPathEnd+1]='\0';   
  				strcat(buffModulPath,CTextName);   
    
  				break;   
			}   
		}   
		str3.Format("%s",(LPCTSTR)buffModulPath);   
    
		DWORD dwPos;   
    
		//创建“TextEditorminiword应用程序”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset1,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“用TextEditorminiword打开”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str1,str1.GetLength());   
		//创建“command”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset2,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为TextEditor应用程序的路径   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str2,str2.GetLength());   
    
		//创建Default项。   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset3Icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“TextEditor图标”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str3,str3.GetLength());   
    
		::RegCloseKey(hresult);  

		MessageBox ("已将信息写入注册表，系统重启后生效。","系统提示");
	}
}

//*****************************//
//还原注册表的处理函数         //
//*****************************//
void CTextEditorDlg::OnMenuBackUp()
{
	int nChoice = MessageBox ("即将还原系统注册表。\r\n确定要还原吗？","还原信息",MB_ICONWARNING|MB_YESNO);
	CString str1,str2,str3;

	if(nChoice == IDYES)
	{
		HKEY hresult;  
		long value;   
    
		LPCTSTR dataset1 = "txtfile\\shell\\OPEN";									//打开方式子键
		LPCTSTR dataset2 = "txtfile\\shell\\OPEN\\command";							//启用程序路径子键   
		LPCTSTR dataset3Icon = "txtfile\\DefaultIcon";								//关联图标子键   
		
		//获得三个子键默认的内容
		str1="用记事本打开"; 
		str2 = "%SystemRoot%\\NotePad.exe\" \"%1\"";
		str3 = "%SystemRoot%\\system32\\shell32.dll,-152";

		DWORD dwPos;   
    
		//创建“我的应用程序”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset1,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“用记事本打开”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str1,str1.GetLength());   
		//创建“command”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset2,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为记事本程序的路径   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str2,str2.GetLength());   
    
		//创建Default项。   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset3Icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“记事本关联图标”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str3,str3.GetLength());   
    
		::RegCloseKey(hresult);  

		MessageBox ("已还原注册表信息，系统重启后生效。","系统提示");
	}
}