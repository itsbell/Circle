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
#include <stdlib.h> // rand()�Լ� ���� ���̺귯��
#include <time.h> // time()�Լ� ���� ���̺귯��
#include <iostream>
int main(int argc, char* argv[]) {

	srand(time(NULL)); // �Ź� �ٸ� �õ尪 ����
	int random = 0; // ������ ���� ����
	for (int i = 0; i < 10; i++) { // 10�� �ݺ�
		random = rand() % 9; // ���� ����
		printf("%d\n", random); // ���
	}
	return 0;
}
#endif