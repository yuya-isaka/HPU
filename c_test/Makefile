
test:
	gcc test.c -o test
	./test
	rm test

%: %.c
	gcc $@.c -o $@

.PHONY: test
