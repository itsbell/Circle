//CircleForm.cpp
#include "CircleForm.h"
#include "Circle.h"
#include "ImageController.h"
#include "Paper.h"
#include "resource.h"

#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(CircleForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, OnDrawButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, OnActionButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnOpenButtonClicked)
	ON_WM_CLOSE()

END_MESSAGE_MAP()

CircleForm::CircleForm(CWnd* parent)
	:CDialog(CircleForm::IDD, parent) {
	this->image = 0;
	this->paper = 0;
	this->rect = 0;
	this->imageController = 0;
}

void CircleForm::OnActionButtonClicked()
{
	CString strEndX;
	CString strEndY;

	GetDlgItem(IDC_EDIT_ENDX)->GetWindowText(strEndX);
	GetDlgItem(IDC_EDIT_ENDY)->GetWindowText(strEndY);
	int endX = atoi(strEndX);
	int endY = atoi(strEndY);

	Circle* circle = this->paper->GetCircle();
	int x = circle->GetX();
	int y = circle->GetY();
	int radius = circle->GetRadius();
	
	int dx = endX - x;
	int dy = endY - y;

	while (dx != 0 || dy != 0) {
		this->paper->Erase();
		if (dx > 0) {
			x++;
		}
		else if (dx < 0) {
			x--;
		}
		if (dy > 0) {
			y++;
		}
		else if(dy<0) {
			y--;
		}
		this->paper->Draw(x, y, radius);

		circle = this->paper->GetCircle();
		this->imageController->DrawCircle(circle);
		this->UpdateDisplay();

		dx = endX - x;
		dy = endY - y;
	}

	this->imageController->Save();
}

void CircleForm::OnClose()
{
	if (this->image != 0) {
		delete this->image;
	}
	if (this->paper != 0) {
		delete this->paper;
	}
	if (this->rect != 0) {
		delete this->rect;
	}
	if (this->imageController != 0) {
		delete this->imageController;
	}

	CDialog::EndDialog(0);
}

void CircleForm::OnDrawButtonClicked()
{
	CString strStartX;
	CString strStartY;

	GetDlgItem(IDC_EDIT_STARTX)->GetWindowText(strStartX);
	GetDlgItem(IDC_EDIT_STARTY)->GetWindowText(strStartY);
	int startX = atoi(strStartX);
	int startY = atoi(strStartY);

	if (this->paper->IsExistCircle()) {
		this->paper->Erase();
	}
	int radius = rand() % 100 + 1;
	this->paper->Draw(startX, startY, radius);
	Circle* circle = this->paper->GetCircle();
	
	this->imageController->Destroy();
	this->imageController->Create(this->paper->GetWidth(), this->paper->GetHeight(), this->paper->GetBpp());
	this->imageController->SetImageColorTable();
	this->imageController->DrawCircle(circle);

	this->UpdateDisplay();
}

BOOL CircleForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->image = new CImage();
	this->paper = new Paper();
	this->rect = new RECT();
	GetClientRect(this->rect);
	this->imageController = new ImageController(this->image);

	return 0;
}

void CircleForm::OnOpenButtonClicked() {
	TCHAR szFilters[] = ("JPG Files (*.jpg)|*.jpg");
	CFileDialog fileDlg(TRUE, ("jpg"), ("*.jpg"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		this->imageController->Destroy();
		if (this->paper->IsExistCircle() == true) {
			this->paper->Erase();
		}
		this->imageController->Load(pathName);
		this->imageController->ConvertToGrayscale8Bit();
		this->image = this->imageController->GetImage();

		int centerX, centerY;
		this->imageController->GetCenter(&centerX, &centerY);
		int radius = this->imageController->GetRadius(centerX, centerY);
		this->paper->Draw(centerX, centerY, radius);
		this->UpdateDisplay();

		CClientDC dc(this);
		for (int i = -5; i <= 5; ++i) {
			// 왼쪽 상단에서 오른쪽 하단 대각선
			dc.SetPixel(centerX + this->rect->right / 2 - this->paper->GetWidth() / 2 + i, centerY + 220 + i, RGB(255, 0, 0));
			// 오른쪽 상단에서 왼쪽 하단 대각선
			dc.SetPixel(centerX + this->rect->right / 2 - this->paper->GetWidth() / 2 + i, centerY + 220 - i, RGB(255, 0, 0));
		}

		CString r;
		r.Format("radius: %d", this->paper->GetCircle()->GetRadius());
		dc.TextOut(centerX + this->rect->right / 2 - this->paper->GetWidth() / 2,
			centerY + 200, r);
	}
}

BOOL CircleForm::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN){
		if (pMsg->wParam == VK_RETURN) {
			if (GetDlgItem(IDC_EDIT_STARTX) == GetFocus() ||
				GetDlgItem(IDC_EDIT_STARTY) == GetFocus() ||
				GetDlgItem(IDC_EDIT_ENDX) == GetFocus() ||
				GetDlgItem(IDC_EDIT_ENDY) == GetFocus()) {
				return TRUE;
			}	
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CircleForm::UpdateDisplay()
{
	CClientDC dc(this);
	this->image->Draw(dc, this->rect->right / 2 - this->paper->GetWidth() / 2, 220);
}