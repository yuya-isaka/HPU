
default:
	gcc -O2 -o bind bind.c -lm
	gcc -O2 -o bind_bound bind_bound.c -lm
	gcc -O2 -o bind_and_bound bind_and_bound.c -lm
	gcc -O2 -o random random.c -lm
	gcc -O2 -o perm perm.c -lm
	gcc -O2 -o bound bound.c -lm
	gcc -O2 -o bound2 bound2.c -lm

check:
	gcc -Wall -o bind bind.c -lm
	gcc -Wall -o bind_bound bind_bound.c -lm
	gcc -Wall -o bind_and_bound bind_and_bound.c -lm
	gcc -Wall -o random random.c -lm
	gcc -Wall -o perm perm.c -lm
	gcc -Wall -o bound bound.c -lm
	gcc -Wall -o bound2 bound2.c -lm

asm:
	gcc -Wall -O2 -S -o bind.s bind.c -lm
	gcc -Wall -O2 -S -o bind_bound bind_bound.c -lm
	gcc -Wall -O2 -S -o bind_and_bound bind_and_bound.c -lm
	gcc -Wall -O2 -S -o random.s random.c -lm
	gcc -Wall -O2 -S -o perm.s perm.c -lm
	gcc -Wall -O2 -S -o bound.s bound.c -lm
	gcc -Wall -O2 -S -o bound2.s bound2.c -lm


linux:
	arm-linux-gnueabihf-gcc -O2 -o bind_peta bind.c -lm
	arm-linux-gnueabihf-gcc -O2 -o bind_bound_peta bind_bound.c -lm
	arm-linux-gnueabihf-gcc -O2 -o bind_and_bound_peta bind_and_bound.c -lm
	arm-linux-gnueabihf-gcc -O2 -o random random.c -lm
	arm-linux-gnueabihf-gcc -O2 -o perm_peta perm.c -lm
	arm-linux-gnueabihf-gcc -O2 -o bound_peta bound.c -lm
	arm-linux-gnueabihf-gcc -O2 -o bound2_peta bound2.c -lm

linux-check:
	arm-linux-gnueabihf-gcc -Wall -o bind_peta bind.c -lm
	arm-linux-gnueabihf-gcc -Wall -o bind_bound_peta bind_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -o bind_and_bound_peta bind_and_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -o random_peta random.c -lm
	arm-linux-gnueabihf-gcc -Wall -o perm_peta perm.c -lm
	arm-linux-gnueabihf-gcc -Wall -o bound_peta bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -o bound2_peta bound2.c -lm

linux-asm:
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o bind_peta.s bind.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o bind_bound_peta.s bind_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o bind_and_bound_peta.s bind_and_bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o random_peta.s random.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o perm_peta.s perm.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o bound_peta.s bound.c -lm
	arm-linux-gnueabihf-gcc -Wall -O2 -S -o bound2_peta.s bound2.c -lm


clean:
	rm -f random perm bind bind_bound bind_and_bound bound bound2 random_peta perm_peta bind_peta bind_bound_peta bind_and_bound_peat bound_peta bound2_peta

.PHONY: default check asm linux linux-check linux-asm clean
