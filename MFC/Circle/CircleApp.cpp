//CircleApp.cpp
#include "CircleApp.h"
#include "CircleForm.h"

BOOL CircleApp::InitInstance() {
	CircleForm circleForm;
	this->m_pMainWnd = &circleForm;
	circleForm.DoModal();

	return TRUE;
}

CircleApp circleApp;