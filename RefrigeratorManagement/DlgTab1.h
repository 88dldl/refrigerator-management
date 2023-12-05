#pragma once
#include "afxdialogex.h"


// CDlgTab1 대화 상자

class CDlgTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB1 };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strName;
	CString m_strCount;
	CListCtrl m_listFood;
	CString m_strSelectedItem;
	int m_nSelectedItem;
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonDelete();
//	afx_msg void OnChangeEditSelectedItem();
	afx_msg void OnItemchangedListFood(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonChoiceDate();
	CDateTimeCtrl m_datetime_picker;
	int timeYear;
	int timeMonth;
	int timeDay;
	afx_msg void OnEnChangeEditSeletedItem();
	afx_msg CString OnGetListFoodName(int num);
	afx_msg CString OnGetListFoodDate(int num);
	afx_msg CString OnGetListFoodCount(int num);
	afx_msg int GetNumber(CString str);
//	CString m_strUnit;
	CComboBox m_Unit;
	CString unit;
	afx_msg void OnSelchangeCombo();
};
