package main

import (
 "fmt"
 "math"
)

func main() {
    var Tsr float32
    var Tk float32
    var r float32
    fmt.Println("Введите температуру кофе: ")
    fmt.Scan(&Tk)
    fmt.Println("Введите температуру окружающей среды: ")
    fmt.Scan(&Tsr)
    fmt.Println("Введите коэффицент остывания: ")
    fmt.Scan(&r)
//Контейнер для хранение значений
     t:=60
    var coffee [60]float32 = cofe(Tk, Tsr, r, t)
    fmt.Println("    Таблица остывания")
    fmt.Println("________________________________________")
    fmt.Println("|     Время      |     Температура     |")
    fmt.Println("---------------------------------------")
    for i := 0; i < t; i++ {
        fmt.Printf("|     %.5f     |      ", float32(i))
		fmt.Printf("%.5f     |\n", coffee[i])
	    fmt.Println("---------------------------------------")
    }
    var a float32
    var b float32
    a = aproxA(coffee,t)
    b = aproxB(coffee,t, a)
    var kofKorrel float32
    kofKorrel = korrel(coffee)
    fmt.Println("Аппроксимирующая прямая: ")
    fmt.Printf(" y =  %.3f * x + ", a)
	fmt.Printf("%.3f  \n", b)
	fmt.Println("Коэффицент корреляции: ")
    fmt.Printf("%.3f", kofKorrel)
}
 // Функция для х и у
func cofe(Tk float32, Tsr float32, r float32, t int)[60] float32{
    var coffee [60]float32
    for i := 0; i < t; i++{
	coffee[i]=Tk
	Tk -= r * (Tk - Tsr)
}
return coffee
}
//Аппроксимирующая прямая
func aproxA(coffee [60]float32, t int)float32 {
// все x*y
var SUMxy float32 =0
// все x
var SUMx float32 =0
// все y
var SUMy float32 =0
//все х*х
var SUMxx float32 =0
for i := 0; i < len(coffee); i++ {
	SUMxy += coffee[i] * float32(i)
	SUMx += float32(i)
	SUMy += coffee[i]
	SUMxx += float32(i) * float32(i)
}
return (float32(len(coffee)) * SUMxy - SUMx * SUMy) / (float32(len(coffee)) * SUMxx - SUMx * SUMx)
}

func aproxB(coffee [60]float32, t int, a float32) float32 {
// все x
var SUMx float32 = 0
// все y
var SUMy float32 = 0
for i := 0; i < len(coffee); i++ {
	SUMx += float32(i)
	SUMy += coffee[i]
}
return ((SUMy - a * SUMx) / float32(len(coffee)))
}

func korrel(coffee [60]float32) float32 {
var Sum float32 =0
for i := 0; i < len(coffee); i++ {
	Sum += coffee[i]
}
//Среднее ариф х
var averageX float32=Sum/(float32(len(coffee)))
//Среднее ариф у
var averageY float32=((1+(float32(len(coffee))))/2)*(float32(len(coffee)))
var Sumx float32= 0
var Sumy float32= 0
var Sumxy float32= 0
for  i := 0; i < len(coffee); i++ {
	Sumxy += ((float32(i) - averageY) * (coffee[i] - averageX))
	Sumx += ((coffee[i] - averageX) * (coffee[i] - averageX))
	Sumy += ((float32(i) - averageY) * (float32(i) - averageY))
}
return (Sumxy / (float32(math.Sqrt(float64(Sumx * Sumy)))))
}
