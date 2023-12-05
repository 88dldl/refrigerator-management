// DlgTab1.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "DlgTab1.h"


// CDlgTab1 대화 상자

IMPLEMENT_DYNAMIC(CDlgTab1, CDialogEx)

CDlgTab1::CDlgTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TAB1, pParent)
	, m_strCount(_T(""))
	, m_strName(_T(""))
	, m_strSelectedItem(_T(""))
{

}

CDlgTab1::~CDlgTab1()
{
}

void CDlgTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_strCount);
	DDX_Control(pDX, IDC_LIST_Food, m_listFood);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetime_picker);
	//DDX_Text(pDX, IDC_EDIT_SELETED_ITEM, m_strSelectedItem);
	//  DDX_Control(pDX, IDC_COMBO, m_strUnit);
	DDX_Control(pDX, IDC_COMBO, m_Unit);
}


BEGIN_MESSAGE_MAP(CDlgTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDlgTab1::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_INSERT2, &CDlgTab1::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgTab1::OnClickedButtonDelete)
//	ON_EN_CHANGE(IDC_EDIT_SELECTED_ITEM, &CDlgTab1::OnChangeEditSelectedItem)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_Food, &CDlgTab1::OnItemchangedListFood)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CDlgTab1::OnDtnDatetimechangeDatetimepicker1)
ON_BN_CLICKED(IDC_BUTTON_CHOICE_DATE, &CDlgTab1::OnClickedButtonChoiceDate)
//ON_EN_CHANGE(IDC_EDIT_SELETED_ITEM, &CDlgTab1::OnEnChangeEditSeletedItem)

ON_CBN_SELCHANGE(IDC_COMBO, &CDlgTab1::OnSelchangeCombo)
END_MESSAGE_MAP()


// CDlgTab1 메시지 처리기


BOOL CDlgTab1::OnInitDialog()
{
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
	m_listFood.InsertColumn(0, _T("순번"), LVCFMT_CENTER, 60);
	m_listFood.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 170);
	m_listFood.InsertColumn(2, _T("개수"), LVCFMT_CENTER, 90);
	m_listFood.InsertColumn(3, _T("유통기한"), LVCFMT_CENTER, 130);

	m_listFood.SetExtendedStyle(m_listFood.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgTab1::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_listFood.GetItemCount();
	CString strCount;
	CString strdate;
	CTime nowTime = CTime::GetCurrentTime();
	CTime firstTime;
	firstTime= CTime(timeYear, timeMonth, timeDay, 0, 0, 0);

	UpdateData(TRUE);
	strdate.Format(_T("%d-%d-%d"), timeYear, timeMonth, timeDay);

	if (firstTime < nowTime) {
		MessageBox(_T("유효한 유통기한을 입력해주세요"), _T("잠깐"), MB_OK);
	}
	else {
		if (!m_strName.IsEmpty() && !m_strCount.IsEmpty() && !strdate.IsEmpty()) {
			strCount.Format(_T("%d"), nCount + 1);
			m_listFood.InsertItem(nCount, strCount);
			m_listFood.SetItem(nCount, 1, LVIF_TEXT, m_strName, 0, 0, 0, 0);
			m_listFood.SetItem(nCount, 2, LVIF_TEXT, m_strCount+unit, 0, 0, 0, 0);
			m_listFood.SetItem(nCount, 3, LVIF_TEXT, strdate, 0, 0, 0, 0);

			m_strName.Empty();
			m_strCount.Empty();
			unit.Empty();
			m_Unit.SetCurSel(-1);

			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			UpdateData(FALSE);
		}
		else {
			MessageBox(_T("모든 항목을 입력해주세요"), _T("잠깐"), MB_OK);
		}
	}
}

void CDlgTab1::OnClickedButtonModify()
{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strName, strCount, strdate, strIndex;
	strName = m_strName;
	strCount = m_strCount;
	strdate.Format(_T("%d-%d-%d"), timeYear, timeMonth, timeDay);

	if (m_nSelectedItem >= 0) {
		if (!m_strName.IsEmpty() && !m_strCount.IsEmpty() && !strdate.IsEmpty()) {
			strIndex.Format(_T("%d"), m_nSelectedItem + 1);
			//m_listFood.SetItem(m_nSelectedItem, 0, LVIF_TEXT, m_strName, 0, 0, 0, 0);
			m_listFood.SetItem(m_nSelectedItem, 1, LVIF_TEXT, strName, 0, 0, 0, 0);
			m_listFood.SetItem(m_nSelectedItem, 2, LVIF_TEXT, strCount + unit, 0, 0, 0, 0);
			m_listFood.SetItem(m_nSelectedItem, 3, LVIF_TEXT, strdate, 0, 0, 0, 0);

			m_strName.Empty();
			m_strCount.Empty();
			unit.Empty();

			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

			UpdateData(FALSE);
		}
		else {
			MessageBox(_T("모든 항목을 입력해주세요"), _T("잠깐"), MB_OK);
		}
	}
	else {
		MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);
	}
}



void CDlgTab1::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0) {
		m_listFood.DeleteItem(m_nSelectedItem);

		for (int i = m_nSelectedItem - 1; i < m_listFood.GetItemCount(); i++) {
			CString strIndex;

			strIndex.Format(_T("%d"), i + 1);
			m_listFood.SetItemText(i, 0, strIndex);
		}
		m_strName.Empty();
		m_strCount.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);
	}
}




void CDlgTab1::OnItemchangedListFood(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

	m_strSelectedItem.Format(_T("%d"), m_nSelectedItem + 1);

	m_strName = m_listFood.GetItemText(m_nSelectedItem, 1);
	m_strCount = m_listFood.GetItemText(m_nSelectedItem, 2);
	m_strCount= m_strCount.Left(GetNumber(m_strCount)+1);

	//m_strDate = m_listFood.GetItemText(m_nSelectedItem, 3);
	//m_datetime_picker.SetTime(sel_date);

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgTab1::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CDlgTab1::OnClickedButtonChoiceDate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTime sel_date;
	m_datetime_picker.GetTime(sel_date);
	timeYear = sel_date.GetYear();
	timeMonth = sel_date.GetMonth();
	timeDay= sel_date.GetDay();
}


void CDlgTab1::OnEnChangeEditSeletedItem()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


CString CDlgTab1::OnGetListFoodName(int num)
{
	return m_listFood.GetItemText(num,1);

}
CString CDlgTab1::OnGetListFoodCount(int num)
{
	return  m_listFood.GetItemText(num, 2);
	

}
int CDlgTab1::GetNumber(CString str)
{
	int temp;

	for (int i = 0; i < str.GetLength(); i++)
	{
		char ch = str.GetAt(i);

		if (ch >= '0' && ch <= '9')
			temp = i;
		else break;
	}

	return temp;
}

CString CDlgTab1::OnGetListFoodDate(int num)
{
	return m_listFood.GetItemText(num, 3);

}


void CDlgTab1::OnSelchangeCombo()
{
	int index = m_Unit.GetCurSel();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (index)
	{
	case 0:
		unit = _T("개");
		break;
	case 1:
		unit = _T("박스");
		break;
	case 2:
		unit = _T("조각");
		break;
	case 3:
		unit = _T("봉지");
		break;
	}
}
