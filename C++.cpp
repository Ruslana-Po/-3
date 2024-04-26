#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <Windows.h>
using namespace std;
//решета Эратосфена
void sieveEratosthenes(vector<int> &numberProst) {
    numberProst.push_back(2);
    for (int i = 3; i < 500; i++)
    {
        int k = 0;
        for (int j = 0; j < numberProst.size(); j++) {
            if ((i % numberProst[j]) == 0) k++;
        }
        if (k == 0) {
            numberProst.push_back(i);
        }
    }
}
//mod
int exponentiation(int number, int m) {
    int a = 1;
    for (int i = 0; i < m; i++) {
        a *= number;
        a %= (m + 1);
    }
    return a;
}
//mod
int exponentiationTest(int number, int a, int b) {
    int s = 1;
    for (int i = 0; i < b; i++) {
        s *= a;
        s %= number;
    }
    return s;
}

//Общая часть тестов
int Test(vector<int> numberProst, int n, vector<int> &number, vector<int> &dividers) {
    int m = n - 1;
    int i = 0;
    //Находим из каких простых чисел состоит
    while (m > 1) {
        if (m % numberProst[i] == 0) {
            dividers.push_back(numberProst[i]);
            m /= numberProst[i];
        }
        else {
            i++;
        }
    }
    cout << "На какие простые числа раскладывается: ";
    for (int j : dividers) cout << j << " ";
    cout << endl;
    int t = 3;
    //рандомное т
    for (int j = 0; j < t; j++) {
        number.push_back(rand() % (n));
        cout << number[j] << " ";
    }
    cout << endl;
    //2 пункт
    for (int j : number) {
        if ((exponentiation(j, n - 1) % n) != 1) {
            cout << "n – составное число" << endl;
            return 0;
        }
    }
    return 1;
}

// Тест Миллера
int Miller(vector<int> numberProst, int m) {
    vector<int> dividers;
    vector<int> number;
    int n = 2*m + 1;
    int check = Test(numberProst, n, number, dividers);
    if (check == 0)return 0;
    int k = 0;
    //3 пункт
    for (int j : dividers) {
        for (int z : number) {
            if ((exponentiation(z, (n-1) / j) % n) != 1) {
                k++;
                break;
            }
        }
    }
    if (k == 0) {
        cout << "вероятно, n – составное число" << endl;
        return 0;
    }
    cout << "n – простое число" << endl;
    return 1;
}
// Тест Поклингтона
int Pocklington(vector<int> numberProst, int f, int r) {
    int c = f;
    int w = r;
    int c1 = 0;
    int w1 = 0;
    while (c > 0) {
        c /= 2;
        c1++;
    }
    while (w > 0) {
        w /= 2;
        w1++;
    }
    if (r >= f && c1-w1!=1) {
        return 0;
    }
    int n = f * r + 1;
    //получаем n
    int k = 0;
    vector<int> dividers;
    vector<int> number;
    int check = Test(numberProst, n, number, dividers);
    if (check == 0)return 0;
    //3 пункт
    for (int z : number) {
        for (int j : dividers) {
            if ((exponentiation(z, (n - 1) / j) % n) == 1) {
                k++;
                break;
            }
        }
    }
    if (k == 0) {
        cout << "n – простое число" << endl;
        return 1;
    }
    cout << "вероятно, n – составное число" << endl;
    return 0;
  
}
//степень для гост
long long Stepen(int a, int b) {
    long long s = 1;
    for (int i = 0; i < b; i++) {
        s = s * a;
    }
    return s;

}
//ГОСТ Р 34.10 - 94.
int GOST(int t, int q) {
    if (q == t / 2) {
        return 0;
    }
    bool f = false;
    int p = 0;
    while (true) {
        //Пункт 1
        int N = Stepen(2, t - 1)/ q;
        if (N % 2 == 1)N++;
        //Пункт 2
        int u = 0; 
        while (true) {
            //Пункт 3
            p = (N + u) * q + 1; 
            //Пункт 4
            if (Stepen(2, t) < p) { 
                break;
            }
            //Пункт 5
            if ((Stepen(2, p - 1) % p == 1) && (Stepen(2, N + u) % p != 1)) {
                f = true;
                break;
            }
            //Пункт 6
            u = u + 2;
        }
        //Выход
        if (f) {
            cout << "    ГОСТ: " << endl;
            cout << p << " - простое" << endl;
            return p;
        }
    }
}
int probabilityTest(int number) {
    if (number == 2 || number == 3)
    {
        return 1;
    }
    if (number < 2 || number % 2 == 0)
    {
        return 0;
    }
    // представим n − 1 в виде (2^s)·t, t-нечет
    int d = number - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s += 1;
    }
    //случайное число в отрезке [2, n − 1]
    int a = rand() % (number - 4) + 2;
    int x = exponentiationTest(number,a,d);
    int y = 0;
    for (int i = 0; i < s; i++) {
        y = (x * x) % number;
        if (y == 1 && x != 1 && x != (number - 1)) {
            return 0;
        }
        x = y;
    }
    
    if (y != 1) {
        return 0;
    }
    return 1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<int> numberProst;
    //решета Эратосфена
    sieveEratosthenes(numberProst);
    cout << " Таблица простых чисел  1-500: " << endl;
    //вывод таблицы
    for (int i : numberProst) {
        cout << i << " ";
    }
    cout  << endl;
    int number = GOST(3, 2);
    //полученные 10 чисел
    vector<int> quantity;
    // Вектор отвергнутых чисел 
    vector<int> reject;
    // 
    // C помощью тестов записывает 10 чисел
   int examination = 0;
   int k = 0;
  while(quantity.size()<10){
      int m = 1, f = 1;
      for (int i = 0; i < 2; i++) {
          m*= numberProst[rand() % (numberProst.size()/8)];
          f*= numberProst[rand() % (numberProst.size()/8)];
      }
       int r = 2 * (rand()%64);
       cout << endl;
       cout << "    m = " << m << " "<<f << endl;
       cout << "    Тест Миллера: " << endl;
       int mil = Miller(numberProst, m);
       cout << "   Тест Поклингтона: " << endl;
       int pock = Pocklington(numberProst, f,r);
       if (mil==1) {
           quantity.push_back(2*m+1);
           reject.push_back(examination);
           examination = 0;
       }else {
           //Сколько чисел не пройдет
           examination += probabilityTest(2*m+1);
       }
       if (pock) {
           quantity.push_back(2 * m + 1);
           reject.push_back(examination);
           examination = 0;
       }else {
           //Сколько чисел не пройдет
           examination += probabilityTest(r*f + 1);
       }
       
       k++;
  }
  cout << "           Сколько отвергнутых чисел в итоге подтвердили простоту: " << endl;
  for (int i : reject) {
      cout << i << " ";
  }
  examination = 0;
  cout << endl;
  cout << " Всего перебрали "<<k<<" чисел" << endl;
  //10 простых чисел с помощью полученной процедуры
  cout << "           10 Получившихся чисел: " << endl;
  for (int i : quantity) {
      cout << i << " ";
      //Тест
      examination = probabilityTest(i);
      if (examination == 1) {
          cout << " +  ";
      }else {
          cout << " -  ";
      }
  }
}

