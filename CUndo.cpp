#include "stdafx.h"
#include "TextEditorDlg.h"
#include "CUndo.h"


CUndo::CUndo(){
	m_undolevels = 10;
}

CUndo::~CUndo() {
	POSITION pos = m_undolist.GetHeadPosition();
	CMemFile* nextFile = NULL;
	while (pos) {
		nextFile = (CMemFile*)m_redolist.GetNext(pos);
		delete nextFile;
	}
	m_undolist.RemoveAll();
	ClearRedoList();
}

void CUndo::Load(CMemFile* file)
{
	// TODO: 在此处添加实现代码.
	DeleteContents();
	file->SeekToBegin();
	CArchive ar(file, CArchive::load);	//CArchieve属性设为load
	CDocument::Serialize(ar);
	ar.Close();
}


void CUndo::AddUndo(CMemFile* file)
{
	// TODO: 在此处添加实现代码.
	if (m_undolist.GetCount() > m_undolevels) {
		CMemFile* pFile = (CMemFile*)m_undolist.RemoveTail();
		delete pFile;
	}
	m_undolist.AddHead(file);
}



void CUndo::ClearRedoList()
{
	// TODO: 在此处添加实现代码.
	POSITION pos = m_redolist.GetHeadPosition();	//pos为链表头记录
	CMemFile* nextFile = NULL;
	while (pos) {
		nextFile = (CMemFile*)m_redolist.GetNext(pos);
		delete nextFile;
	}
	m_redolist.RemoveAll();
}


void CUndo::CheckPoint()
{
	// TODO: 在此处添加实现代码.
	CMemFile* file = new CMemFile(50000);
	char write[50000];
	CString strText = "";
	m_Edit.GetWindowText(strText);  //获取编辑框中的内容
	strcpy(write, strText);
	file->Write(write,strText.GetLength());
	AddUndo(file);
	ClearRedoList();
}


void CUndo::Undo()
{
	// TODO: 在此处添加实现代码.
	if (m_undolist.GetCount() > 1) {
		CMemFile* pFile = (CMemFile*)m_undolist.GetHead();
		m_undolist.RemoveHead();
		m_redolist.AddHead(pFile);
		pFile = (CMemFile*)m_undolist.GetHead();
		Load(pFile);
	}
}



void CUndo::Redo()
{
	// TODO: 在此处添加实现代码.
	if (m_redolist.GetCount() > 0) {
		CMemFile* pFile = (CMemFile*)m_redolist.GetHead();
		m_redolist.RemoveHead();
		AddUndo(pFile);
		Load(pFile);
	}
}
