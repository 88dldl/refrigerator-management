#pragma once
#include "afxdialogex.h"


// GetFoodList 대화 상자

class GetFoodList : public CDialogEx
{
	DECLARE_DYNAMIC(GetFoodList)

public:
	GetFoodList(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GetFoodList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
