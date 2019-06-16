#pragma once
#include <afxwin.h>
/*
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
	// 撤销次数
	int m_undolevels;
public:
	void ClearRedoList();
	void CheckPoint();
	void Undo();
	void Redo();
};
*/
// undo.h implementation
// Author - Keith Rule (keithr@europa.com)
//
// A description of this code can be found in May 1997 - Windows Tech Journal.
// Back issues can be ordered from either (800) 241-4320 or (918) 831-9557.
//
// An extended version of this class is part of the MFC Class of the week
// (http://www.weeklymfc.com/).
//
// Modified by Jiang Feng , 1998.10
//
#ifndef _UNDO_H_
#define _UNDO_H_
//------------------------------------------------------------
//  Undo/Redo for MFC By Keith Rule
class CUndo {
private:
	CObList	m_undolist;		// Stores undo states
	CObList	m_redolist;		// Stores redo states
	long	m_growsize;		// Adjust for faster saves
	long	m_undoLevels;	// Requested Undolevels 
	long	m_chkpt;

	//added by yangguichun, 2008/06/25
	BOOL	m_bUndo;
	BOOL	m_bRedo;
	//end added by yangguichun, 2008/06/25

	void AddUndo(CMemFile*);
	void AddRedo(CMemFile* pFile);
	void Load(CMemFile*);
	void Store(CMemFile*);
	void ClearRedoList();
	void ClearUndoList();
public:

	// Here are the hooks into the CDocument class
	virtual void Serialize(CArchive& ar) = 0;
	virtual void DeleteContents() = 0;

	// User accessable functions
	CUndo(long undolevels = 8, long = 32768);	// Constructor
	~CUndo();			// Destructor
	BOOL CanUndo();		// Returns TRUE if can Undo
	BOOL CanRedo();		// Returns TRUE if can Redo
	void Undo();		// Restore next Undo state
	void Redo();		// Restore next Redo state				
	void CheckPoint();	// Save current state 
	void EnableCheckPoint();
	void DisableCheckPoint();

	void SetUndolevels(int undoLevels) { m_undoLevels = undoLevels; }

	BOOL IsUndo() { return m_bUndo; };
	BOOL IsRedo() { return m_bRedo; };

	/// <summary>
	///	清除undo和redo的列表
	/// </summary>
	void Clear() {
		// Clear undo list
		ClearUndoList();

		// Clear redo list
		ClearRedoList();
	};
};

// Constructor
inline CUndo::
CUndo(long undolevels, long growsize) :
	m_growsize(growsize), m_undoLevels(undolevels),
	m_chkpt(0)
{
	m_undoLevels = 10;
	//added by yangguichun, 2008/06/25
	m_bUndo = FALSE;
	m_bRedo = FALSE;
	//end added by yangguichun, 2008/06/25
}

// Remove contents of the redo list
inline void CUndo::
ClearRedoList()
{
	// Clear redo list
	POSITION pos = m_redolist.GetHeadPosition();
	CMemFile* nextFile = NULL;
	while (pos) {
		nextFile = (CMemFile*)m_redolist.GetNext(pos);
		delete nextFile;
	}
	m_redolist.RemoveAll();
}

inline void CUndo::ClearUndoList()
{
	POSITION pos = m_undolist.GetHeadPosition();
	CMemFile* nextFile = NULL;
	while (pos) {
		nextFile = (CMemFile*)m_undolist.GetNext(pos);
		delete nextFile;
	}
	m_undolist.RemoveAll();
}
// Destructor
inline CUndo::
~CUndo()
{
	Clear();
}

// Checks undo availability, may be used to enable menus
inline BOOL CUndo::
CanUndo()
{
	return (m_undolist.GetCount() > 1);
}

// Checks redo availability, may be used to enable menus
inline BOOL CUndo::
CanRedo()
{
	return (m_redolist.GetCount() > 0);
}

// Adds state to the beginning of undo list		
inline void CUndo::
AddUndo(CMemFile* file)
{
	// Remove old state if there are more than max allowed
	if (m_undolist.GetCount() > m_undoLevels) {
		CMemFile* pFile = (CMemFile*)m_undolist.RemoveTail();
		delete pFile;
	}
	// Add new state to head of undo list
	m_undolist.AddHead(file);
}

// Saves current object into CMemFile instance
inline void CUndo::
Store(CMemFile* file)
{
	file->SeekToBegin();
	CArchive ar(file, CArchive::store);
	Serialize(ar);
	ar.Close();
}

// Loads CMemfile instance to current object
inline void CUndo::
Load(CMemFile* file)
{
	DeleteContents();
	file->SeekToBegin();
	CArchive ar(file, CArchive::load);
	Serialize(ar);
	ar.Close();
}

// Save current object state to Undo list
inline void CUndo::
CheckPoint()
{
	if (m_chkpt <= 0) {
		CMemFile* file = new CMemFile(m_growsize);
		Store(file);
		AddUndo(file);
		ClearRedoList();
	}
}

inline void CUndo::
EnableCheckPoint()
{
	if (m_chkpt > 0) {
		m_chkpt--;
	}
}

inline void CUndo::
DisableCheckPoint()
{
	m_chkpt++;
}

// Place CMemFile instnace on Redo list
inline void CUndo::
AddRedo(CMemFile* file)
{
	// Move state to head of redo list
	m_redolist.AddHead(file);
}

// Perform an Undo command
inline void CUndo::
Undo()
{
	if (CanUndo()) {
		// Remember that the head of the undo list
		// is the current state. So we just move that
		// to the Redo list and load then previous state.
		//added by yangguichun, 2008/06/25
		m_bUndo = TRUE;
		//end added by yangguichun, 2008/06/25
		CMemFile* pFile = (CMemFile*)m_undolist.GetHead();
		m_undolist.RemoveHead();
		AddRedo(pFile);
		pFile = (CMemFile*)m_undolist.GetHead();
		Load(pFile);
		//added by yangguichun, 2008/06/25
		m_bUndo = FALSE;
		//end added by yangguichun, 2008/06/25
	}
}

//Perform a Redo Command
inline void CUndo::
Redo()
{
	if (CanRedo()) {
		//added by yangguichun, 2008/06/25
		m_bRedo = TRUE;
		//end added by yangguichun, 2008/06/25
		CMemFile* pFile = (CMemFile*)m_redolist.GetHead();
		m_redolist.RemoveHead();
		AddUndo(pFile);
		Load(pFile);
		//added by yangguichun, 2008/06/25
		m_bRedo = FALSE;
		//end added by yangguichun, 2008/06/25
	}
}
#endif

