//CircleForm.h
#ifndef _CIRCLEFORM_H
#define _CIRCLEFORM_H

#include "resource.h"
#include <afxwin.h>
#include <atlimage.h>

class Circle;
class Paper;

class CircleForm : public CDialog {
	public:
		enum { IDD = IDD_DIALOG_CIRCLE };

	public:
		CircleForm(CWnd* parent = NULL);
		
		void DrawCircle(Circle* circle);
		virtual BOOL OnInitDialog();
		BOOL PreTranslateMessage(MSG* pMsg);
		void SetImageColorTable();
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

};

#endif //_CIRCLEFORM_H