//ImageController.cpp
#include "ImageController.h"
#include "Circle.h"
#include "resource.h"

#include <ctime>
#pragma warning (disable:4996)

ImageController::ImageController(CImage* image)
{
	this->image = image;
}

ImageController::~ImageController()
{
}

CImage* ImageController::ConvertToGrayscale8Bit()
{
	// 24��Ʈ �̹����� �ε��� ��, 8��Ʈ�� ��ȯ�ϱ� ���� �� �̹����� ����
	int width = this->image->GetWidth();
	int height = this->image->GetHeight();
	int nPitch = this->image->GetPitch();
	unsigned char* fm = (unsigned char*)this->image->GetBits();

	CImage* tempImage = new CImage;
	tempImage->Create(width, height, 8);

	// ȸ���� �ȷ�Ʈ ���� (0~255�� ȸ��)
	RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++) {
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	}
	tempImage->SetColorTable(0, 256, rgb);  // ȸ���� �ȷ�Ʈ ����

	unsigned char* fmTemp = (unsigned char*)tempImage->GetBits();

	// 24��Ʈ �̹����� 8��Ʈ �׷��̽����Ϸ� ��ȯ
	int i = 0;
	int j = 0;
	while (i < height) {
		j = 0;
		while (j < width) {
			// 24��Ʈ �̹������� R, G, B ä�ΰ� ����
			unsigned char r = fm[i * nPitch + j * 3];
			unsigned char g = fm[i * nPitch + j * 3 + 1];
			unsigned char b = fm[i * nPitch + j * 3 + 2];

			// �׷��̽����� �� ��� (���⼭�� �Ϲ����� ���� ��� ��� ���)
			unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
			fmTemp[i * tempImage->GetPitch() + j] = gray;

			j++;
		}
		i++;
	}

	if (this->image != 0) {
		this->image->Destroy();
		delete this->image;
	}
	this->image = tempImage;

	return this->image;
}

CImage* ImageController::Create(int width, int height, int bpp)
{
	this->image->Create(width, height, bpp);
	return this->image;
}

CImage* ImageController::Destroy()
{
	this->image->Destroy();
	return this->image;
}

CImage* ImageController::DrawCircle(Circle* circle)
{
	this->Initialization();

	int i = 0;
	int j;
	int dx;
	int dy;

	int nPitch = this->image->GetPitch();
	unsigned char* fm = (unsigned char*)this->image->GetBits();

	CRect rect(circle->GetX() - circle->GetRadius(), circle->GetY() - circle->GetRadius(),
		circle->GetX() + circle->GetRadius(), circle->GetY() + circle->GetRadius());

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

	return this->image;
}

void ImageController::GetCenter(int* centerX, int* centerY)
{
	int nPitch = this->image->GetPitch();
	unsigned char* fm = (unsigned char*)this->image->GetBits();

	int i = 0;
	int j;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	while (i < this->image->GetHeight()) {
		j = 0;
		while (j < this->image->GetWidth()) {
			if (fm[i * nPitch + j] >= 5) {
				nSumX += j;
				nSumY += i;
				nCount++;
			}
			j++;
		}
		i++;
	}

	*centerX = nSumX / nCount;
	*centerY = nSumY / nCount;
}

int ImageController::GetRadius(int centerX, int centerY)
{
	int i = centerY;
	int j = centerX;
	int nCount = 0;
	int nPitch = this->image->GetPitch();
	unsigned char* fm = (unsigned char*)this->image->GetBits();

	while (i >= 0 && fm[i * nPitch + j] >= 5) {
		nCount++;
		i--;
	}

	return nCount;
}

CImage* ImageController::Initialization()
{
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

	return this->image;
}

CImage* ImageController::Load(CString fileName)
{
	this->image->Load(fileName);
	return this->image;
}

CImage* ImageController::Save()
{
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);

	CString fileName;
	fileName.Format("./image/%d%d%d�̹���.jpg", t->tm_hour, t->tm_min, t->tm_sec);
	this->image->Save(fileName);

	return this->image;
}

CImage* ImageController::SetImageColorTable()
{
	if (this->image->GetBPP() == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		this->image->SetColorTable(0, 256, rgb);
	}

	return this->image;
}
