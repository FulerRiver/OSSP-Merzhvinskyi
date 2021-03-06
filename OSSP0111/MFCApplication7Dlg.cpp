
// MFCApplication7Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplication7.h"
#include "MFCApplication7Dlg.h"
#include "afxdialogex.h"
#include <cstdlib>
#include <string>
#include <tchar.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMFCApplication7Dlg



CMFCApplication7Dlg::CMFCApplication7Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION7_DIALOG, pParent)
	, m_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}

BEGIN_MESSAGE_MAP(CMFCApplication7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication7Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication7Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication7Dlg

BOOL CMFCApplication7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication7Dlg::OnBnClickedButton1()
{
	UpdateData(true);// оновлення даних в елементах EditBox

	CString Text = m_str;

	CFileDialog DlgSaveAs(FALSE, _T("txt"), nullptr,

		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T(" Text Files (*.txt) |*.txt||"));

	// отображение стандартной панели выбора файла SaveAs

	// TODO: Add your control notification handler code here

	if (DlgSaveAs.DoModal() == IDOK)

	{

		CStdioFile File1(DlgSaveAs.GetPathName(), CFile::modeCreate | CFile::modeWrite);

		// Create an instance of CStdioFile and open file for writing

		File1.WriteString(Text);// write a string to file

		File1.Close();

	}
}


void CMFCApplication7Dlg::OnBnClickedButton2()
{
	UpdateData(true);// оновлення даних в елементах EditBox

	char numchar[11];
	char p[11];
	sprintf_s(numchar, "%S", (LPCTSTR)m_str);

	m_str = "";
	CFileDialog DlgOpen(TRUE, _T("txt"), nullptr, OFN_HIDEREADONLY, _T(" Text Files (*.txt) |*.txt||"));

	if (DlgOpen.DoModal() == IDOK)

	{

		// Create an instance of CStdioFile and open file for reading

		CStdioFile File2(DlgOpen.GetPathName(), CFile::modeRead);

		if (File2 != nullptr)

		{

			CString s;

			int max = atoi(numchar);

			int all = 0;

			int parn = 0;
			
			while (File2.ReadString(s)) //read a string

			{
				all++;
				if (all <= max) {
					sprintf_s(numchar, "%S", (LPCTSTR)s);
					if (atoi(numchar) % 2 == 0) { parn += 1; }
					m_str += numchar; // додавання зчитаного рядка до вмісту змінної, пов’язаної з елементом EditBox
					m_str += CString("\r\n"); // додавання переходу на новий рядок*/
				}

			}
			CString mess;
			if (all < max) {
			    mess = _T("Не знайдено необхідну кількість чисел виведено ");
				sprintf_s(p, "%d", all);
				mess += p;
				mess += _T("\nЗ усіх ");
				sprintf_s(p, "%d", all);
				mess += p;
				mess += _T("чисел , парних - ");
				sprintf_s(p, "%d", parn);
				mess += p;
				MessageBox(mess, _T("Помилка"), MB_OK);
			}
			else {
				mess += _T("\nЗ усіх ");
				sprintf_s(p, "%d", max);
				mess += p;
				mess += _T("чисел , парних - ");
				sprintf_s(p, "%d", parn);
				mess += p;
				MessageBox(mess, _T("Информация"), MB_OK);
			}
			
			File2.Close();

			UpdateData(0);// оновлення даних в елементах EditBox

		}

	}
}
