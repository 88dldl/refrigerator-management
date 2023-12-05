#pragma once
#include "afxdialogex.h"

// CDlgTab2 대화 상자

class CDlgTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB2 };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_listRemain;
	CListCtrl m_listRecipe;
	CString strSelectedItem;
	CString strName;
	int SelectedItem;

	virtual BOOL OnInitDialog();
//	afx_msg void OnItemchangedListCome(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonReload();
	afx_msg void OnListFood();
	afx_msg void OnClickedButtonMove();
	afx_msg void OnClickedButtonRecipe();
	afx_msg void OnClickedButtonDelete();

	afx_msg void OnItemchangedListCheck(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListCome(NMHDR* pNMHDR, LRESULT* pResult);
};
