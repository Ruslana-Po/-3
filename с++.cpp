#include <iostream>
#include <Windows.h>
#include <math.h>
#include<iomanip>
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << setw(5) << " "<< "Таблица значений функции" << endl;
	cout << setw(6) << " " << "______________________" << endl;
	cout << setw(6) << "|" << setw(5) << "X" << setw(6) << "|" << setw(5) << "Y" << setw(6) << "|" << endl;
	cout << setw(5) << "" << "-----------------------" << endl;
	float y = 0;
	for (float x = -4; x <= 6; x+=0.5) {
		if (x >= -4 && x <= 0) {
			y = -x / 2;
		}else if (x >= 0 && x <= 2) {
			y = 2 -sqrt(4 - (x * x));
		}else if (x >= 2 && x <= 4) {
			y = sqrt(4 - (x-2) * (x-2));
		}else {
			y = -(x - 4) / 2;
		}
		cout << setw(6) << "|" << setw(10) << fixed<<setprecision(3)<< x << "|" << setw(10) << y << "|"<<endl;
		cout << setw(5) << "" << "-----------------------" << endl;
	}
}
