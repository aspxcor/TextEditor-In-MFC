
#include "stdafx.h"
#include "TextEditorDlg.h"
#include "CUndo.h"
/*

CUndo::CUndo(){
	m_undolevels = 10;
}

CUndo::~CUndo() {
	POSITION pos = m_undolist.GetHeadPosition();
	CString nextFile = "";
	while (pos) {
		nextFile = m_redolist.GetNext(pos);
		delete nextFile;
	}
	m_undolist.RemoveAll();
	ClearRedoList();
}

void CUndo::Load(CString str)
{
	// TODO: 在此处添加实现代码.
	m_Edit.SetWindowText(str);

}


void CUndo::AddUndo(CString str)
{
	// TODO: 在此处添加实现代码.
	if (m_undolist.GetCount() > m_undolevels) {
		m_undolist.RemoveTail();	
	}
	m_undolist.AddHead(str);
}



void CUndo::ClearRedoList()
{
	// TODO: 在此处添加实现代码.
	POSITION pos = m_redolist.GetHeadPosition();	//pos为链表头记录
	CString nextFile = "";
	while (pos) {
		nextFile = m_redolist.GetNext(pos);
		delete nextFile;
	}
	m_redolist.RemoveAll();
}


void CUndo::CheckPoint()
{
	CString strText = "";
	m_Edit.GetWindowText(strText);  //获取编辑框中的内容
	AddUndo(strText);
	ClearRedoList();
}


void CUndo::Undo()
{
	// TODO: 在此处添加实现代码.
	if (m_undolist.GetCount() > 1) {
		CString str_now=m_undolist.GetHead();
		m_undolist.RemoveHead();
		m_redolist.AddHead(str_now);
		CString str_pre =m_undolist.GetHead();
		Load(str_pre);
	}
}



void CUndo::Redo()
{
	// TODO: 在此处添加实现代码.
	if (m_redolist.GetCount() > 0) {
		CString str=m_redolist.GetHead();
		m_redolist.RemoveHead();
		AddUndo(str);
		Load(str);
	}
}
*/