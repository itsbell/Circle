//ImageController.h
#ifndef _IMAGECONTROLLER_H
#define _IMAGECONTROLLER_H

#include <afxwin.h>
#include <atlimage.h>

class Circle;
class ImageController {
	public:
		ImageController(CImage* image);
		~ImageController();

		CImage* ConvertToGrayscale8Bit();
		CImage* Create(int width, int height, int bpp);
		CImage* Destroy();
		CImage* DrawCircle(Circle* circle);
		void GetCenter(int* centerX, int* centerY);
		int GetRadius(int centerX, int centerY);
		CImage* Initialization();
		CImage* Load(CString fileName);
		CImage* Save();
		CImage* SetImageColorTable();

		CImage* GetImage() const;

	private:
		CImage* image;
};

inline CImage* ImageController::GetImage() const {
	return this->image;
}


#endif //_IMAGECONTROLLER_H