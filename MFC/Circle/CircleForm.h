//CircleForm.h
#ifndef _CIRCLEFORM_H
#define _CIRCLEFORM_H

#include "resource.h"
#include <afxwin.h>
#include <atlimage.h>

class Circle;
class ImageController;
class Paper;

class CircleForm : public CDialog {
	public:
		enum { IDD = IDD_DIALOG_CIRCLE };

	public:
		CircleForm(CWnd* parent = NULL);
		
		virtual BOOL OnInitDialog();
		BOOL PreTranslateMessage(MSG* pMsg);
		void UpdateDisplay();
		
	protected:
		afx_msg void OnDrawButtonClicked();
		afx_msg void OnActionButtonClicked();
		afx_msg void OnOpenButtonClicked();
		afx_msg void OnClose();

		DECLARE_MESSAGE_MAP()

	private:
		CImage* image;
		Paper* paper;
		RECT* rect;
		ImageController* imageController;
};

#endif //_CIRCLEFORM_H