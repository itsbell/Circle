//CircleForm.cpp
#include "CircleForm.h"
#include "Circle.h"
#include "Paper.h"
#include "resource.h"
#include <ctime>

#pragma warning (disable:4996)

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
}


void CircleForm::DrawCircle(Circle* circle) {
	int nPitch = this->image->GetPitch();
	unsigned char* fm = (unsigned char*)this->image->GetBits();

	int i = 0;
	int j;
	while (i < this->image->GetHeight()) {
		j = 0;
		while (j < this->image->GetWidth()) {
			fm[i * nPitch + j] = 0;
			j++;
		}
		i++;
	}

	CRect rect(circle->GetX() - circle->GetRadius(), circle->GetY() - circle->GetRadius(),
		circle->GetX() + circle->GetRadius(), circle->GetY() + circle->GetRadius());

	int dx;
	int dy;
	i = rect.top;
	while (i < rect.bottom) {
		j = rect.left;
		while (j < rect.right) {
			if (i >= 0 && i < this->image->GetHeight() && j >= 0 && j < this->image->GetWidth()) {
				dx = j - circle->GetX();
				dy = i - circle->GetY();
				if (dx * dx + dy * dy <= circle->GetRadius() * circle->GetRadius()) {
					fm[i * nPitch + j] = GRAY;
				}
			}
			j++;
		}
		i++;
	}
}

void CircleForm::OnActionButtonClicked()
{
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);

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
		this->DrawCircle(circle);
		this->UpdateDisplay();

		dx = endX - x;
		dy = endY - y;
	}

	CString fileName;
	fileName.Format("./image/%d%d%dÀÌ¹ÌÁö.jpg", t->tm_hour, t->tm_min, t->tm_sec);
	this->image->Save(fileName);
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

	if (this->image != 0) {
		this->image->Destroy();
	}
	this->image->Create(this->paper->GetWidth(), this->paper->GetHeight(), this->paper->GetBpp());
	this->SetImageColorTable();
	this->DrawCircle(circle);
	this->UpdateDisplay();
}

BOOL CircleForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->image = new CImage();
	this->paper = new Paper();
	this->rect = new RECT();
	GetClientRect(this->rect);

	return 0;
}

void CircleForm::OnOpenButtonClicked() {

	if (this->image != 0) {
		this->image->Destroy();
	}
	this->image->Load("./image/tests.jpg");

	this->UpdateDisplay();
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

void CircleForm::SetImageColorTable() {
	if (this->paper->GetBpp() == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		this->image->SetColorTable(0, 256, rgb);
	}
}

void CircleForm::UpdateDisplay()
{
	CClientDC dc(this);
	this->image->Draw(dc, this->rect->right / 2 - this->paper->GetWidth() / 2, 220);
}