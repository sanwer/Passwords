#ifndef  _PASSWORDS_H_
#define  _PASSWORDS_H_
#pragma once

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include "resource.h"

#ifndef UILIB_STATIC
#define UILIB_STATIC
#endif
#include "..\DuiLib\UIlib.h"
using namespace DuiLib;

class CPasswordsDlg : public WindowImplBase
{
public:
	CPasswordsDlg();
	~CPasswordsDlg();

	TCHAR GetRandChar(CDuiString& sTemplate, UINT nIncrement=0);

public:
	LPCTSTR GetWindowClassName() const;
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
	virtual CDuiString GetSkinFile();

protected:
	void Notify(TNotifyUI& msg);

private:
	CLabelUI* labTitle;
	CRichEditUI* editUpper;
	CRichEditUI* editLower;
	CRichEditUI* editNumber;
	CRichEditUI* editSymbol;
	CCheckBoxUI* chkUpper;
	CCheckBoxUI* chkLower;
	CCheckBoxUI* chkNumber;
	CCheckBoxUI* chkSymbol;
	CRichEditUI* editLength;
	CRichEditUI* editCount;
	CRichEditUI* editPassword;
	CButtonUI* btnGenerator;
};

#endif