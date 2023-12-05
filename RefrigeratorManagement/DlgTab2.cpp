// DlgTab2.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "DlgTab2.h"
#include "DlgTab1.h"
#include "ProjectDlg.h"
#include <iostream>
// CDlgTab2 대화 상자
IMPLEMENT_DYNAMIC(CDlgTab2, CDialogEx)

CDlgTab2::CDlgTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TAB2, pParent)
{

}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COME, m_listRemain);
	//  DDX_Control(pDX, IDC_LIST_CHECK, m_listRecipe);

	DDX_Control(pDX, IDC_LIST_CHECK, m_listRecipe);
}


BEGIN_MESSAGE_MAP(CDlgTab2, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CDlgTab2::OnClickedButtonReload)
ON_COMMAND(IDC_LIST_Food, &CDlgTab2::OnListFood)
ON_BN_CLICKED(IDC_BUTTON_MOVE, &CDlgTab2::OnClickedButtonMove)
ON_BN_CLICKED(IDC_BUTTON_RECIPE, &CDlgTab2::OnClickedButtonRecipe)
ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgTab2::OnClickedButtonDelete)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CHECK, &CDlgTab2::OnItemchangedListCheck)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_COME, &CDlgTab2::OnItemchangedListCome)
END_MESSAGE_MAP()


// CDlgTab2 메시지 처리기


void CDlgTab2::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


BOOL CDlgTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_listRemain.InsertColumn(0, _T("순번"), LVCFMT_CENTER, 60);
	m_listRemain.InsertColumn(1, _T("상품명"), LVCFMT_CENTER, 175);
	m_listRemain.InsertColumn(2, _T("개수"), LVCFMT_CENTER, 90);
	m_listRemain.InsertColumn(3, _T("남은 유통기한"), LVCFMT_CENTER, 130);

	m_listRemain.SetExtendedStyle(m_listRemain.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	m_listRecipe.InsertColumn(0, _T("이름"), LVCFMT_CENTER,300);

	m_listRecipe.SetExtendedStyle(m_listRecipe.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	((CButton*)GetDlgItem(IDC_BUTTON_MOVE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDlgTab2::OnClickedButtonReload()
{	
	if(m_listRemain.GetItemCount()>0) m_listRemain.DeleteAllItems();

	CProjectDlg* tmp = (CProjectDlg*)AfxGetMainWnd();

	int itemCount = tmp->dlg1->m_listFood.GetItemCount(); 
	CString tmpTime;
	CString strCount;
	CString strdate;
	CTime timetmp = CTime::GetCurrentTime();

	UpdateData(TRUE);


	for (int i = 0,j=0; i < itemCount; i++) {
		CString strGetTime = tmp->dlg1->OnGetListFoodDate(i);
		
		CTime ctime;
		CStringA strYear, strMonth, strDay;
		strYear = strGetTime.Left(4);
		strMonth = strGetTime.Mid(5, 2);
		strDay = strGetTime.Mid(8, 2);

		ctime = CTime(atoi(strYear), atoi(strMonth), atoi(strDay),0,0,0);

		CTimeSpan timespan = ctime - timetmp;

		if (timespan.GetDays() <=  5) {
			tmpTime.Format(_T("%d일"), timespan.GetDays());
			strCount.Format(_T("%d"), j+1);
			if (m_listRemain.GetItemData(j) == NULL) {
				m_listRemain.InsertItem(j, strCount);
			}
			else {
				m_listRemain.SetItem(j, 0, LVIF_TEXT, strCount, 0, 0, 0, 0);
			}
			m_listRemain.SetItem(j, 1, LVIF_TEXT, tmp->dlg1->OnGetListFoodName(i), 0, 0, 0, 0);
			m_listRemain.SetItem(j, 2, LVIF_TEXT, tmp->dlg1->OnGetListFoodCount(i), 0, 0, 0, 0);
			m_listRemain.SetItem(j, 3, LVIF_TEXT, tmpTime, 0, 0, 0, 0);
			j++;
			UpdateData(FALSE);
		}
		
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgTab2::OnListFood()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(FALSE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CDlgTab2::OnClickedButtonMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_listRecipe.GetItemCount();
	CString strCount;
	UpdateData(TRUE);

	if (!strName.IsEmpty()) {
		strCount.Format(_T("%d"), nCount + 1);
		m_listRecipe.InsertItem(nCount, strName);
		strName.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MOVE))->EnableWindow(FALSE);
		UpdateData(FALSE);
	}
}


void CDlgTab2::OnClickedButtonRecipe()
{
	CString search;
	search = "https://www.google.com/search?q=";
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_listRecipe.GetItemCount() == 0) {
		MessageBox(_T("레시피를 검색할 음식이 없습니다."), _T("잠깐"), MB_OK);
	}
	else {
		for (int i = 0; i < m_listRecipe.GetItemCount(); i++) {
			search += m_listRecipe.GetItemText(i, 0);
			if(i!= m_listRecipe.GetItemCount()-1) search += ",";
		}
		search += "를 활용한 레시피";
		ShellExecute(NULL, _T("OPEN"), search, NULL, NULL, SW_SHOW);
	}
}


void CDlgTab2::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SelectedItem >=0) {
		m_listRecipe.DeleteItem(SelectedItem);

		strName.Empty();
		
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);
	}

}


void CDlgTab2::OnItemchangedListCheck(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectedItem = pNMLV->iItem;

	strName = m_listRecipe.GetItemText(SelectedItem, 1);

	//m_strDate = m_listFood.GetItemText(m_nSelectedItem, 3);
	//m_datetime_picker.SetTime(sel_date);

	((CButton*)GetDlgItem(IDC_BUTTON_MOVE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	UpdateData(FALSE);
	*pResult = 0;
}


void CDlgTab2::OnItemchangedListCome(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectedItem = pNMLV->iItem;

	strName = m_listRemain.GetItemText(SelectedItem, 1);

	((CButton*)GetDlgItem(IDC_BUTTON_MOVE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

	UpdateData(FALSE);
	*pResult = 0;
}
