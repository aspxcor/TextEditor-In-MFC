// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TextEditor.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog


CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
	//}}AFX_DATA_INIT
}


void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
	DDX_Control(pDX, IDC_HELPFILE, m_HelpText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg message handlers

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//设置帮助内容
	CString str = "一.程序功能简介\r\n";
	str += "     1.本程序是一个用来创建简单文档的基\r\n";
	str += "        本的文本编辑器，支持查看或编辑文\r\n";
	str += "        本（.txt）文件，其他支持的文件类型\r\n";
	str += "        有cpp、h、c、html和xml（以下仅对\r\n";
	str += "        txt进行说明）\r\n";
	str += "     2.程序界面仿照记事本，另添加工具栏,\r\n";
	str += "        便于操作；\r\n";
	str += "     3.本程序支持字符（串）统计、查找、\r\n";
    str += "        替换以及对用户指定字符串的统计；\r\n";
    str += "     4.本程序支持字体设置功能，用户可对\r\n";
	str += "        字体、字形及字的大小进行设置；\r\n";
    str += "     5.统计功能说明：空格数为所有空格数\r\n";
	str += "        （中英文空格相同），英文字符数只\r\n";
	str += "        统计英文字母数（不包括半角标点符\r\n";
	str += "        号），中文字符数包括汉字和全角标\r\n";
	str += "        点符号，所有字符数包括英文、汉字\r\n";
	str += "        、全角和半角字符数以及空格数。\r\n";
	str += "\r\n";

	str += "二.程序使用简介\r\n";
    str += "     1.程序包含菜单栏、工具栏、编辑框。\r\n";
    str += "        菜单栏、工具栏可进行各种操作；编\r\n";
	str += "        辑框可进行文本编辑。\r\n";
    str += "     2.菜单栏、工具栏操作对应的快捷键为\r\n";
    str += "            新建：Ctrl+N          打开：Ctrl+O\r\n";
    str += "            保存：Ctrl+S          撤销：Ctrl+Z\r\n";
    str += "            重做：Ctrl+Y          全选：Ctrl+A\r\n";
    str += "            剪切：Ctrl+X          复制：Ctrl+C\r\n";
    str += "            粘贴：Ctrl+V   查找替换：Ctrl+F  \r\n";
    str += "            字体：Alt+F			帮助：Ctrl+H\r\n";
    str += "         各操作将在后面进行说明。\r\n";
	str += "\r\n";

	str += "三.程序运行环境\r\n";
    str += "            Windows 32位操作系统(其他操作系\r\n";
	str += "      统未作测试)。\r\n";
	str += "\r\n";

	str += "四.程序简要说明\r\n";
    str += "     1.程序版本：2.0\r\n";
    str += "     2.程序编写：TextEditor小组\r\n";
	str += "\r\n";

	str += "五.程序功能点\r\n";
    str += "     1.文件：\r\n";
    str += "     ①新建：创建一篇空白文档，从“工具\r\n";
	str += "         栏”或“文件下拉菜单”中创建\r\n";
	str += "     ②打开：打开文本（.txt）文件，从“\r\n";
	str += "         工具栏”或“文件下拉菜单”中打\r\n";
	str += "         开；或将文本（.txt）文件拖入程序\r\n";
    str += "         界面打开或应用程序TextEditor.exe图\r\n";
	str += "         标上打开；或右键单击文本文件，在\r\n";
	str += "         “打开方式”中选择本程序打开\r\n";	      
	str += "     ③保存：保存文档，从“工具栏”或“\r\n";
	str += "         文件下拉菜单”中打开\r\n";
	str += "     ④另存为：保存文件副本，在不同位置\r\n";
    str += "         或以不同文件名保存文档，从“工具\r\n";
	str += "         栏”或“文件下拉菜单”中另存\r\n";
	str += "     2.编辑：\r\n";
	str += "     ①撤销：撤销前一步所进行的操作，从\r\n";
	str += "         “编辑下拉菜单”或“右键菜单”中\r\n";
	str += "         撤销，支持多级撤销\r\n";
	str += "     ②重做：重做前一步所撤销的操作，从\r\n";
	str += "         “编辑下拉菜单”或“右键菜单”中\r\n";
	str += "         重做，支持多级重做\r\n";
	str += "     ③删除：删除当前选定字符（串），从\r\n";
	str += "         “编辑下拉菜单”或“右键菜单”中\r\n";
	str += "         删除\r\n";
	str += "     ④剪切：复制并删除选定字符（串），\r\n";
	str += "         从“编辑下拉菜单”或“右键菜单”\r\n";
	str += "         中剪切\r\n";
	str += "     ⑤复制：复制选定字符（串），从“编\r\n";
	str += "         辑下拉菜单”或“右键菜单”中复制\r\n";
	str += "     ⑥粘贴：对粘贴内容进行粘贴，从“编\r\n";
	str += "         辑下拉菜单”或“右键菜单”中粘贴\r\n";
	str += "     ⑦全选：对文本编辑框中文本全部选定\r\n";
	str += "         ，从“编辑下拉菜单”或“右键菜单\r\n";
	str += "         ”中全选\r\n";
    str += "     3.应用：\r\n";
	str += "     ①查找/替换：输入查找内容（和替换\r\n";
	str += "         内容），可从光标位置逐个查找（或\r\n";
	str += "         替换）相应内容，也可一次性全部替\r\n";
	str += "         换掉相应内容，从“工具栏”或“应\r\n";
	str += "         用下拉菜单”中执行\r\n";
	str += "     ②字体设置：设置字体、字形及字的大\r\n";
	str += "         小，从“工具栏”或“应用下拉菜单\r\n";
	str += "         ”中设置字体\r\n";
	str += "     ③统计字数：统计所有字符数、中文字\r\n";
    str += "         符数、英文字符数、数字字符数和空\r\n";
	str += "         格数，从“工具栏”或“应用下拉菜\r\n";
	str += "         单”中启动\r\n";
	str += "     4.帮助：\r\n";
	str += "     ①关于TextEditor：显示关于本程序的信息，\r\n";
	str += "         从“帮助下拉菜单”中启动\r\n";
	str += "     ②帮助：显示程序帮助文档，包括程序\r\n";
	str += "         功能、使用、简要说明等各种信息，\r\n";
	str += "         从“工具栏”或“帮助下拉菜单”中\r\n";
	str += "         启动\r\n";
	str += "     5.高级：\r\n";
	str += "     ①关联注册：向注册表添加TextEditor文件关\r\n";
	str += "         联，改变文本（.txt）文件图标，并\r\n";
	str += "         使文本（.txt）文件可单击右键后选\r\n";
	str += "         择用本程序打开(部分功能重启或注\r\n";
	str += "         销后方能生效)\r\n";
	str += "     ②还原注册：取消注册，文本（.txt）\r\n";
	str += "         文件还原为默认图标，不能右键打开\r\n";
	str += "         (部分功能重启或注销后方能生效)\r\n";

	m_HelpText.SetWindowText(str);									//显示帮助内容
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
