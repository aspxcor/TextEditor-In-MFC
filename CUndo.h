#pragma once
#include <afxwin.h>
class CUndo :
	public CDocument,public CTextEditorDlg
{	public:
	CUndo();
	~CUndo();
	CStringList m_undolist;
	CStringList m_redolist;
	void Load(CString str);
	void AddUndo(CString str);
private:
	// ³·Ïú´ÎÊý
	int m_undolevels;
public:
	void ClearRedoList();
	void CheckPoint();
	void Undo();
	void Redo();
};

