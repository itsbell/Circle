//Paper.h
#ifndef _PAPER_H
#define _PAPER_H

class Circle;
class Paper {
	public:
		Paper();
		~Paper();

		int Draw(int x, int y, int radius);
		void Erase();
		bool IsExistCircle();

		int GetWidth() const;
		int GetHeight() const;
		int GetBpp() const;
		Circle* GetCircle() const;


	private:
		int width;
		int height;
		int bpp;
		Circle* circle;
};

inline int Paper::GetWidth() const {
	return this->width;
}

inline int Paper::GetHeight() const {
	return this->height;
}

inline int Paper::GetBpp() const {
	return this->bpp;
}

inline Circle* Paper::GetCircle() const {
	return this->circle;
}


#endif //_PAPER_H