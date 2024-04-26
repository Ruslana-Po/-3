package main

import (
	"fmt"
	"math/rand"
)

//решета Эратосфена
func sieveEratosthenes(numberProst *[]int) {
    //append добавленние новых элементов к массиву
	*numberProst = append(*numberProst, 2)
	for i := 3; i < 500; i++ {
		k := 0
		for j := 0; j < len(*numberProst); j++ {
			if i%(*numberProst)[j] == 0 {
				k++
			}
		}
		if k == 0 {
			*numberProst = append(*numberProst, i)
		}
	}
}
//mod
func exponentiation(number, m int) int {
	a := 1
	for i := 0; i < m; i++ {
		a *= number
		a %= (m + 1)
	}
	return a
}

func exponentiationTest(number, a, b int) int {
	s := 1
	for i := 0; i < b; i++ {
		s *= a
		s %= number
	}
	return s
}

//Общая часть тестов
func Test(numberProst []int, n int, number, dividers *[]int) int {
	m := n - 1
	i := 0
	for m > 1 {
		if m%numberProst[i] == 0 {
			*dividers = append(*dividers, numberProst[i])
			m /= numberProst[i]
		} else {
			i++
		}
	}
	//_ игнорированние переменной / пустой индификатор
	fmt.Print("Prime dividers: ")
	//range перебирает элементы 
	for _, j := range *dividers {
		fmt.Printf("%d ", j)
	}
	fmt.Println()
	t := 3
	//Рандомные числа
	for j := 0; j < t; j++ {
		*number = append(*number, rand.Intn(n))
		fmt.Printf("%d ", (*number)[j])
	}
	fmt.Println()
	//2 пункт
	for _, j := range *number {
		if exponentiation(j, n-1)%n != 1 {
			fmt.Println("n is a composite number")
			return 0
		}
	}
	return 1
}

// Тест Миллера

func Miller(numberProst []int, m int) int {
    n:=2*m+1
	dividers := []int{}
	number := []int{}
	check := Test(numberProst, n, &number, &dividers)
	if check == 0 {
		return 0
	}
	k := 0
	  //3 пункт
	for _, j := range dividers {
		for _, z := range number {
			if exponentiation(z, (n-1)/j)%n != 1 {
				k++
				break
			}
		}
	}
	if k == 0 {
		fmt.Println("n is probably a composite number")
	    return 0
	}
	fmt.Println("n is a prime number")
	return 1
}
// Тест Поклингтона
func Pocklington(numberProst []int, f int, r int) int {
    c := f
    w := r
    c1 := 0
    w1 := 0
    for ;c > 0; {
        c /= 2
        c1++
    }
    for ;w > 0; {
        w /= 2
        w1++
    }
if r >= f && c1-w1!=1 {
    return 0
}
    n :=r*f+1
	k := 0
	dividers := []int{}
	number := []int{}
	check := Test(numberProst, n, &number, &dividers)
	if check == 0 {
		return 0
	}
	  //3 пункт
	for _, z := range number {
		 for _, j := range dividers{
			if exponentiation(z, (n-1)/j)%n == 1 {
				k++
				break
			}
		}
	}
	if k == 0 {
		fmt.Println("n is a prime number")
		return 1
	}
	fmt.Println("n is probably a composite number")
	return 0
}
//степень
func Stepen(a, b int) int {
	s := 1
	for i := 0; i < b; i++ {
		s = s * a
	}
	return s
}
//ГОСТ Р 34.10 - 94.
func GOST(t, q int){
    if q != t / 2 {
    return
    }
	f := false
	p := 0
	for {
	    //Пункт 1
		N := Stepen(2, t-1)/q
		if N%2 == 1 {
			N++
		}
		//Пункт 2
		u := 0
		for {
		    //Пункт 3
			p = (N+u)*q + 1
			//Пункт 4
			if Stepen(2, t) < p {
				break
			}
			//Пункт 5
			if Stepen(2, p-1)%p == 1 && Stepen(2, N+u)%p != 1 {
				f = true
				break
			}
			//Пункт 6
			u = u + 2
		}
		//Пункт вывод
		if f {
			fmt.Println("GOST:")
			fmt.Printf("%d - prime\n", p)
			return
		}
	}
}
//Тест вер
func probabilityTest(number int) int {
	if number == 2 || number == 3 {
		return 1
	}
	if number < 2 || number%2 == 0 {
		return 0
	}
// представим n − 1 в виде (2^s)·t, t-нечет
	d := number - 1
	s := 0
	for d%2 == 0 {
		d /= 2
		s++
	}
	 //случайное число в отрезке [2, n − 1]
	a := rand.Intn(number-4) + 2
	x := exponentiationTest(number, a, d)
	y := 0
	for i := 0; i < s; i++ {
		y = (x * x) % number
		if y == 1 && x != 1 && x != number-1 {
			return 0
		}
		x = y
	}
	if y != 1 {
		return 0
	}
	return 1
}

func main() {
	numberProst := []int{}
	//решета Эратосфена
	sieveEratosthenes(&numberProst)
	fmt.Println("Prime numbers table 1-500:")
	//вывод таблицы
	for _, i := range numberProst {
		fmt.Printf("%d ", i)
	}
	fmt.Println()
	//ГОСТ
    GOST(3, 2)
      //полученные 10 чисел
	quantity := []int{}
	// Вектор отвергнутых чисел
	reject := []int{}
	examination := 0
	k := 0
	for len(quantity) < 10 {
	   m:=1
	   f:=1
	    for i := 0; i < 2; i++ {
		    m=m*numberProst[rand.Intn(len(numberProst)/8)]
		    f=f*numberProst[rand.Intn(len(numberProst)/8)]
	    }
	    //Prost[rand.Next(Prost.Count)]
		r := 2*rand.Intn(64)
		fmt.Println()
		fmt.Println("Miller Test:")
		mil := Miller(numberProst, m)
		fmt.Println("Pocklington Test:")
		pock := Pocklington(numberProst, f, r)
		if mil == 1 {
			quantity = append(quantity, 2*m+1)
			reject = append(reject, examination)
			examination = 0
		} else {
		    //Сколько чисел не пройдет
			examination += probabilityTest(2*m+1)
		}
		if pock == 1 {
			quantity = append(quantity, f*r+1)
			reject = append(reject, examination)
			examination = 0
		} else {
		    //Сколько чисел не пройдет
			examination += probabilityTest(f*r+1)
		}
		k++
	}
	fmt.Println("Number of rejected numbers that turned out to be prime:")
	for _, i := range reject {
		fmt.Printf("%d ", i)
	}
	examination = 0
	fmt.Println()
	fmt.Printf("Total numbers checked: %d\n", k)
	fmt.Println("10 resulting numbers:")
	//10 простых чисел с помощью полученной процедуры
	for _, i := range quantity {
		fmt.Printf("%d ", i)
		examination = probabilityTest(i)
		 //Тест
		if examination == 1 {
			fmt.Print(" + ")
		} else {
			fmt.Print(" - ")
		}
	}
}
