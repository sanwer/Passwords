#include "Passwords.h"
#include <time.h>

#define TIMER_DISABLE_TIMEOUT	1001

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL);
	if(FAILED(Hr)) return 0;

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourceZip(MAKEINTRESOURCE(IDR_ZIPRES), _T("ZIPRES"));

	CPasswordsDlg* pDlg = new CPasswordsDlg();
	if(pDlg == NULL) return 0;
	pDlg->Create(NULL,_T("Passwords"),UI_WNDSTYLE_FRAME,WS_EX_APPWINDOW,0,0,800,600);
	pDlg->CenterWindow();
	pDlg->ShowModal();
	
	::CoUninitialize();

	return 0;
}

CPasswordsDlg::CPasswordsDlg()
{
	labTitle = NULL;
	editUpper = NULL;
	editLower = NULL;
	editNumber = NULL;
	editSymbol = NULL;
	chkUpper = NULL;
	chkLower = NULL;
	chkNumber = NULL;
	chkSymbol = NULL;
	labLength = NULL;
	editLength = NULL;
	labCount = NULL;
	editCount = NULL;
	editPassword = NULL;
	btnGenerator = NULL;
}

CPasswordsDlg::~CPasswordsDlg()
{
}

LPCTSTR CPasswordsDlg::GetWindowClassName() const
{
	return _T("Passwords");
}

void CPasswordsDlg::InitWindow()
{
	labTitle = static_cast<CLabelUI*>(m_Manager.FindControl(_T("labTitle")));
	editUpper = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editUpper")));
	editLower = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editLower")));
	editNumber = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editNumber")));
	editSymbol = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editSymbol")));
	chkUpper = static_cast<CCheckBoxUI*>(m_Manager.FindControl(_T("chkUpper")));
	chkLower = static_cast<CCheckBoxUI*>(m_Manager.FindControl(_T("chkLower")));
	chkNumber = static_cast<CCheckBoxUI*>(m_Manager.FindControl(_T("chkNumber")));
	chkSymbol = static_cast<CCheckBoxUI*>(m_Manager.FindControl(_T("chkSymbol")));
	labLength = static_cast<CLabelUI*>(m_Manager.FindControl(_T("labLength")));
	editLength = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editLength")));
	labCount = static_cast<CLabelUI*>(m_Manager.FindControl(_T("labCount")));
	editCount = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editCount")));
	editPassword = static_cast<CRichEditUI*>(m_Manager.FindControl(_T("editPassword")));
	btnGenerator = static_cast<CButtonUI*>(m_Manager.FindControl(_T("btnGenerator")));
	if (labTitle == NULL || editUpper == NULL|| editLower == NULL
		|| editNumber == NULL || editSymbol == NULL  || chkUpper == NULL
		|| chkLower == NULL || chkNumber == NULL || chkSymbol == NULL
		|| labLength == NULL || editLength == NULL|| labCount == NULL
		|| editCount == NULL || editPassword == NULL || btnGenerator == NULL)
	{
		MessageBox(NULL,_T("Loading resources failed!"),_T("Passwords"),MB_OK|MB_ICONERROR);
		return;
	}

	if(GetSystemDefaultLangID() == 0x0804){
		labTitle->SetText(_T("密码生成器 - Sanwer.com"));
		labLength->SetText(_T("长度"));
		labCount->SetText(_T("数量"));
		btnGenerator->SetText(_T("生成"));
		::SetWindowText(GetHWND(),_T("密码生成器"));
	}
}

void CPasswordsDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString CPasswordsDlg::GetSkinFile()
{
	return _T("Passwords.xml");
}

void CPasswordsDlg::Notify(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (_tcsicmp(msg.sType,DUI_MSGTYPE_CLICK) == 0)
	{
		if (_tcsicmp(sCtrlName,_T("btnGenerator")) == 0){
			CDuiString sTemplate,sPasswords,sLower,sUpper;
			CDuiString sNumber,sSymbol,sLength,sCount;
			btnGenerator->SetEnabled(false);
			editPassword->SetText(_T(""));
			if(chkUpper->IsSelected())
				sUpper = editUpper->GetText();
			if(chkLower->IsSelected())
				sLower = editLower->GetText();
			if(chkNumber->IsSelected())
				sNumber = editNumber->GetText();
			if(chkSymbol->IsSelected())
				sSymbol = editSymbol->GetText();
			sTemplate = sUpper + sLower + sNumber + sSymbol;
			sTemplate.Replace(_T(" "),_T(""));
			sLength = editLength->GetText();
			sCount = editCount->GetText();
			TCHAR cRandChar = 0;
			if(sTemplate.GetLength() == 0 || sLength.GetLength() == 0 || sCount.GetLength() == 0)
				return;
			int nLength = _ttoi(sLength.GetData());
			if(nLength<=0)
			{
				nLength = 6;
				editLength->SetText(_T("6"));
			}
			int nCount = _ttoi(sCount.GetData());
			if(nCount<=0)
			{
				nCount = 1;
				editCount->SetText(_T("1"));
			}

			for(int i=0;i<nCount;i++){
				if(sPasswords.GetLength()>0)
					sPasswords+=_T("\n");
				for(int j=1;j<=nLength;j++)
					sPasswords+=GetRandChar(sTemplate);
			}
			editPassword->SetText(sPasswords);
			btnGenerator->SetEnabled(true);
		}
	}
	else if (_tcsicmp(msg.sType,DUI_MSGTYPE_SELECTCHANGED) == 0)
	{
		CDuiString sBuffer;
		CCheckBoxUI* chkUI = (CCheckBoxUI*)msg.pSender;
		if(chkUpper->IsSelected())
			sBuffer += editUpper->GetText();
		if(chkLower->IsSelected())
			sBuffer += editLower->GetText();
		if(chkNumber->IsSelected())
			sBuffer += editNumber->GetText();
		if(chkSymbol->IsSelected())
			sBuffer += editSymbol->GetText();
		sBuffer.Replace(_T(" "),_T(""));
		if(sBuffer.GetLength() == 0)
			chkUI->SetCheck(!chkUI->IsSelected());
		//else
		//	sTemplate = sBuffer;
	}
	return WindowImplBase::Notify(msg);
}

TCHAR CPasswordsDlg::GetRandChar(CDuiString& sTemplate, UINT nIncrement)
{
	static UINT nRandomSeed = 0;
	UINT nTemplate = sTemplate.GetLength();
	if(nRandomSeed < nTemplate)
		srand(nRandomSeed = time(NULL));
	return sTemplate.GetAt(rand() % nTemplate);
}
