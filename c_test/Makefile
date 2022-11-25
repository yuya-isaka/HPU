
test:
	gcc test.c -o test
	./test
	rm test

overload:
	gcc test_overload.c -o test
	./test
	rm test

mp:
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib -Xpreprocessor -fopenmp test_openmp.c -lomp -o test
	./test
	rm test

simd:
	g++ -mavx2 test_simd.cpp -o test
	./test
	rm test

%: %.c
	gcc $@.c -o $@

.PHONY: test
