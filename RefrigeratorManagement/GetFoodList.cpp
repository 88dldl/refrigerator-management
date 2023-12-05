// GetFoodList.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "GetFoodList.h"


// GetFoodList 대화 상자

IMPLEMENT_DYNAMIC(GetFoodList, CDialogEx)

GetFoodList::GetFoodList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TAB1, pParent)
{

}

GetFoodList::~GetFoodList()
{
}

void GetFoodList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GetFoodList, CDialogEx)
END_MESSAGE_MAP()


// GetFoodList 메시지 처리기
