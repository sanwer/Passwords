#include "Passwords.h"
#include <time.h>

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
	editPassword = NULL;
	btnGenerator = NULL;
	cRandChar = 0;
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
	labTitle = static_cast<CLabelUI*>(m_pm.FindControl(_T("labTitle")));
	editUpper = static_cast<CRichEditUI*>(m_pm.FindControl(_T("editUpper")));
	editLower = static_cast<CRichEditUI*>(m_pm.FindControl(_T("editLower")));
	editNumber = static_cast<CRichEditUI*>(m_pm.FindControl(_T("editNumber")));
	editSymbol = static_cast<CRichEditUI*>(m_pm.FindControl(_T("editSymbol")));
	chkUpper = static_cast<CCheckBoxUI*>(m_pm.FindControl(_T("chkUpper")));
	chkLower = static_cast<CCheckBoxUI*>(m_pm.FindControl(_T("chkLower")));
	chkNumber = static_cast<CCheckBoxUI*>(m_pm.FindControl(_T("chkNumber")));
	chkSymbol = static_cast<CCheckBoxUI*>(m_pm.FindControl(_T("chkSymbol")));
	editPassword = static_cast<CRichEditUI*>(m_pm.FindControl(_T("editPassword")));
	btnGenerator = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnGenerator")));
	if (labTitle == NULL || editUpper == NULL|| editLower == NULL
		|| editNumber == NULL || editSymbol == NULL  || chkUpper == NULL
		|| chkLower == NULL || chkNumber == NULL || chkSymbol == NULL
		|| editPassword == NULL || btnGenerator == NULL)
	{
		MessageBox(NULL,_T("Loading resources failed!"),_T("Passwords"),MB_OK|MB_ICONERROR);
		return;
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
			CDuiString sTemplate,sPasswords,sLower,sUpper,sNumber,sSymbol;
			if(chkUpper->IsSelected()){
				sUpper = editUpper->GetText();
			}
			if(chkLower->IsSelected()){
				sLower = editLower->GetText();
			}
			if(chkNumber->IsSelected()){
				sNumber = editNumber->GetText();
			}
			if(chkSymbol->IsSelected()){
				sSymbol = editSymbol->GetText();
			}
			sTemplate = sUpper + sLower + sNumber + sSymbol;
			sTemplate.Replace(_T(" "),_T(""));
			int nLength = sTemplate.GetLength();
			srand((unsigned)time(NULL));
			for(int i=200;i>0;i--){
				srand((unsigned)i+cRandChar+time(NULL));
				cRandChar = sTemplate.GetAt((i+rand()) % nLength);
				sPasswords+=sTemplate.GetAt((i+cRandChar+rand()) % nLength);
			}
			editPassword->SetText(sPasswords);
			return;
		}
	}
	else if (_tcsicmp(msg.sType,DUI_MSGTYPE_SELECTCHANGED) == 0)
	{
		if (_tcsicmp(sCtrlName,_T("chkUpper")) == 0){
		}
		else if (_tcsicmp(sCtrlName,_T("chkLower")) == 0){
		}
		else if (_tcsicmp(sCtrlName,_T("chkNumber")) == 0){
		}
		else if (_tcsicmp(sCtrlName,_T("chkSymbol")) == 0){
		}
	}
	return WindowImplBase::Notify(msg);
}
