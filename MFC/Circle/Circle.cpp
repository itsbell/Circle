//Circle.cpp
#include "Circle.h"

Circle::Circle(int x, int y, int radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;

}

Circle::~Circle()
{
}

#if 0
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리
#include <iostream>
int main(int argc, char* argv[]) {

	srand(time(NULL)); // 매번 다른 시드값 생성
	int random = 0; // 정수형 변수 선언
	for (int i = 0; i < 10; i++) { // 10번 반복
		random = rand() % 9; // 난수 생성
		printf("%d\n", random); // 출력
	}
	return 0;
}
#endif