package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	"strings"
)

func main() {

	train_en_path := "data/train/en"
	train_fr_path := "data/train/fr"
	train_ge_path := "data/train/ge"
	test_path_1 := "data/test/test_file"
	test_path_2 := "data/test/test_file2"
	test_path_3 := "data/test/test_file3"

	en_data, err := ioutil.ReadFile(train_en_path)
	if err != nil {
		panic(err)
	}
	fr_data, err := ioutil.ReadFile(train_fr_path)
	if err != nil {
		panic(err)
	}
	ge_data, err := ioutil.ReadFile(train_ge_path)
	if err != nil {
		panic(err)
	}
	data_1, err := ioutil.ReadFile(test_path_1)
	if err != nil {
		panic(err)
	}
	data_2, err := ioutil.ReadFile(test_path_2)
	if err != nil {
		panic(err)
	}
	data_3, err := ioutil.ReadFile(test_path_3)
	if err != nil {
		panic(err)
	}

	train_en_data := string(en_data)
	train_fr_data := string(fr_data)
	train_ge_data := string(ge_data)
	test_data_1 := string(data_1)
	test_data_2 := string(data_2)
	test_data_3 := string(data_3)

	decorate(train_en_data, "en")
	decorate(train_fr_data, "fr")
	decorate(train_ge_data, "ge")
	decorate(test_data_1, "t1")
	decorate(test_data_2, "t2")
	decorate(test_data_3, "t3")
}

func decorate(data string, name string) {
	reg, err := regexp.Compile("[^a-zA-Z0-9]+") // a-zA-Z0-9以外の数は取り込まない
	if err != nil {
		panic(err)
	}
	data = reg.ReplaceAllString(data, "")
	data = strings.ToLower(data) // "mynameisyuyaisaka..."

	file, err := os.Create(name)
	if err != nil {
		fmt.Println(err)
	}

	defer file.Close()

	file.WriteString(data)
}
