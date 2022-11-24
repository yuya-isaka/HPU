
test:
	gcc test.c -o test
	./test
	rm test

overload:
	gcc test_overload.c -o test
	./test
	rm test

%: %.c
	gcc $@.c -o $@

.PHONY: test
