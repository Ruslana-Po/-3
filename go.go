package main

import (
 "fmt"
 "math"
)
func main() {
    fmt.Println("  Таблица значений функции")
    fmt.Println("_________________________")
    fmt.Println("|     X      |     Y     |")
    fmt.Println("--------------------------")
    y := 0.0
	for x := -4.0; x <= 6.0; x =x + 0.5 {
		if x >= -4 && x <= 0 {
			y = -x / 2
		}else if x >= 0 && x <= 2 {
			y = 2 -math.Sqrt(4 - (x * x))
		}else if (x >= 2 && x <= 4) {
			y = math.Sqrt(4 - (x-2) * (x-2))
		}else {
			y = -(x - 4) / 2
		}
		fmt.Printf("|    %.3f  |    ", x)
		fmt.Printf("%.3f  |\n", y)
		fmt.Println("--------------------------")
    }
}
