#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <Windows.h>
using namespace std;
const int t = 60;
//поиск x y
void cofe(float Tk, float Tsr, float r, vector<float>& coffee) {
	for (int i = 0; i <= t; i++) {
		coffee.push_back(Tk);
		Tk -= r * (Tk - Tsr);
	}
}
//Аппроксимирующая прямая
void aprox(vector<float>coffee, pair<float, float> &aproxAB) {
	// все x*y
	float SUMxy = 0;
	// все x
	float SUMx = 0;
	// все y
	float SUMy = 0;
	//все х*х
	float SUMxx = 0;
	for (int i = 0; i < coffee.size(); i++) {
		SUMxy += coffee[i] * i;
		SUMx += i;
		SUMy += coffee[i];
		SUMxx += i * i;
	}
	aproxAB.first = (coffee.size() * SUMxy - SUMx * SUMy) / (coffee.size() * SUMxx - SUMx * SUMx);
	aproxAB.second = (SUMy - aproxAB.first * SUMx) / coffee.size();
}
float korrel(vector<float>coffee) {
	float Sum=0;
	for (float i : coffee) {
		Sum += i;
	}
	//Среднее ариф х
	float averageX=Sum/coffee.size();
	//Среднее ариф у
	float averageY=((1+coffee.size())/2)*coffee.size();
	float Sumx = 0, Sumy = 0, Sumxy = 0;
	for (int i = 0; i < coffee.size(); i++) {
		Sumxy += ((i - averageY) * (coffee[i] - averageX));
		Sumx += ((coffee[i] - averageX) * (coffee[i] - averageX));
		Sumy += ((i - averageY) * (i - averageY));
	}
	return (Sumxy / (sqrt(Sumx * Sumy)));
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	float Tsr, Tk, r;
	cout << "Введите температуру кофе: ";
	cin >> Tk;
	cout << "Введите температуру окружающей среды: ";
	cin >> Tsr;
	cout << "Введите коэффицент остывания: ";
	cin >> r;
	//Контейнер для хранение значений
	vector<float> coffee;
	cofe(Tk, Tsr, r, coffee);
	cout << endl << setw(8) << " " << "Таблица остывания кофе" << endl;
	cout << setw(6) << " " << "_______________________________" << endl;
	cout << setw(6) << "|" << setw(3) <<"" << "время, м" << setw(4) << "|" << setw(1) << "" << "температура, С" << setw(1) << "|" << endl;
	cout << setw(5) << "" << "--------------------------------" << endl;
	for (int i = 0; i <= t; i++) {
		cout << setw(6) << "|" << setw(6) << "" << fixed << setprecision(3) << i << setw(8) << "|" << setw(5) << "";
		cout << fixed << setprecision(3) << coffee[i] << setw(5) << "|" << endl;
		cout << setw(5) << "" << "--------------------------------" << endl;
	}
	pair<float, float> aproxAB;
	aprox(coffee, aproxAB);
	float kofKorrel = korrel(coffee);
	cout << endl << "Аппроксимирующая прямая: " << "y = " << aproxAB.first<< " * x + " << aproxAB.second << endl;
	cout << "Коэффицент корреляции: " << kofKorrel << endl;
}
