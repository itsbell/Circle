//Paper.cpp
#include "Paper.h"
#include "Circle.h"

Paper::Paper() {
	this->width = 500;
	this->height = 500;
	this->bpp = 8;
	this->circle = 0;
}

Paper::~Paper() {
	if (this->circle != 0) {
		delete this->circle;
	}
}

int Paper::Draw(int x, int y, int radius)
{
	this->circle = new Circle(x, y, radius);

	return this->circle->GetRadius();
}

void Paper::Erase() {
	if (this->circle != 0) {
		delete this->circle;
		this->circle = 0;
	}
}

bool Paper::IsExistCircle() {
	bool isExist = false;

	if (this->circle != 0) {
		isExist = true;
	}

	return isExist;
}