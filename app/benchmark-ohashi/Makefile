default:
	arm-linux-gnueabihf-gcc -O2 -o ohashi_random ohashi_random.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_perm ohashi_perm.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_perm_bound ohashi_perm_bound.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bind ohashi_bind.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bind_bound ohashi_bind_bound.c -lm
	arm-linux-gnueabihf-gcc -O2 -o ohashi_bound ohashi_bound.c -lm

check:
	arm-linux-gnueabihf-gcc -Wall -o ohashi_random ohashi_random.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_perm ohashi_perm.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_perm_bound ohashi_perm_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_bind ohashi_bind.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_bind_bound ohashi_bind_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -o ohashi_bound ohashi_bound.c -lm

asm:
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_random.s ohashi_random.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_perm.s ohashi_perm.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_perm_bound.s ohashi_perm_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_bind.s ohashi_bind.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_bind_bound.s ohashi_bind_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o ohashi_bound.s ohashi_bound.c -lm


clean:
	rm -f ohashi_random ohashi_perm ohashi_perm_bound ohashi_bind ohashi_bind_bound ohashi_bound

.PHONY: default check asm clean
