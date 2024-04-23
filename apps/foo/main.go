package main

import "fmt"

func foo() {
	fmt.Println("hello world")
}

func main() {
	x := 1
	if x == 1 {
		foo()
	}
}
