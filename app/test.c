#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

unsigned long src_phys;
unsigned long dst_phys;

int main()
{
	printf("\n ------------------------------ 開始 -------------------------------- \n");

	int fd0, fd1, dmaf, topf;

	// DMAバッファの物理アドレスを取得 ------------------------------------------------------------

	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		read(fd0, attr, 1024);
		sscanf(attr, "%lx", &src_phys);
		close(fd0);
	}
	if ((fd0 = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1)
	{
		char attr[1024];
		read(fd0, attr, 1024);
		sscanf(attr, "%lx", &dst_phys);
		close(fd0);
	}

	printf("0k1");

	return 0;
}