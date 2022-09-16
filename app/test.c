#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

volatile int *top;
volatile int *dma;
volatile int *src;
volatile int *dst;
unsigned long src_phys;
unsigned long dst_phys;

void dma_reset(){
  dma[0x30/4] = 4;
  dma[0x00/4] = 4;
  while (dma[0x00/4] & 0x4);
}

void main() {

  int fd0,fd1,dmaf,topf;

  if ((fd0  = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY)) != -1) {
    char attr[1024];
    read(fd0, attr, 1024);
    sscanf(attr, "%lx", &src_phys);
    close(fd0);
  }
  if ((fd0  = open("/sys/class/u-dma-buf/udmabuf1/phys_addr", O_RDONLY)) != -1) {
    char attr[1024];
    read(fd0, attr, 1024);
    sscanf(attr, "%lx", &dst_phys);
    close(fd0);
  }

  if ((fd0 = open("/dev/udmabuf0", O_RDWR)) < 0) {
    perror("open");
    return;
  }
  if ((fd1 = open("/dev/udmabuf1", O_RDWR)) < 0) {
    perror("open");
    return;
  }
  if ((dmaf = open("/dev/uio0", O_RDWR | O_SYNC)) < 0) {
    perror("open");
    return;
  }
  if ((topf = open("/dev/uio1", O_RDWR | O_SYNC)) < 0) {
    perror("open");
    return;
  }

  top = (int*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, topf, 0);
  if (top == MAP_FAILED) {
    perror("mmap");
    close(topf);
    return;
  }
  dma = (int*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, dmaf, 0);
  if (dma == MAP_FAILED) {
    perror("mmap");
    close(dmaf);
    return;
  }
  src = (int*)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd0, 0);
  if (src == MAP_FAILED) {
    perror("mmap");
    close(fd0);
    return;
  }
  dst = (int*)mmap(NULL, 0x00080000, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  if (dst == MAP_FAILED) {
    perror("mmap");
    close(fd1);
    return;
  }

////////////////////// Set Matrix /////////////////////////////
  int matrix[4][8];

  printf("\n--- Set Matrix ---\n");
  for(int j=0; j<4; j++){
    for(int i=0; i<8; i++){
      matrix[j][i] = rand() & 0x000000ff;
      printf("%3d ",matrix[j][i]);
      src[(j*8+i)*2+0] = matrix[j][i];
      src[(j*8+i)*2+1] = matrix[j][i];
    }
    printf("\n");
  }

  // matw <- 1;
  top[0x00/4]=1;

  // AXI DMA transfer tx
  dma_reset();
  dma[0x00/4] = 1;
  dma[0x18/4] = src_phys;
  dma[0x28/4] = 8*4*4*2;

  // Wait for the tx to finish
  while ((dma[0x04/4] & 0x1000)!=0x1000);

  // matw <- 0;
  top[0x00/4]=0;

////////////////////// run /////////////////////////////
  // run <- 1;
  top[0x00/4]=2;

  int sample[4][8];

  printf("\n--- Sample %d Input ---\n", 0);
  for(int j=0; j<4; j++){
    for(int i=0; i<8; i++){
      sample[j][i] = rand() & 0x000000ff;
      printf("%3d ",sample[j][i]);
      src[j*8+i] = sample[j][i];
    }
    printf("\n");
  }

  // AXI DMA transfer tx
  dma_reset();
  dma[0x00/4] = 1;
  dma[0x18/4] = src_phys;
  dma[0x28/4] = 8*4*4;

  // Wait for the tx to finish
  while ((dma[0x04/4] & 0x1000)!=0x1000);

  int result[4][4];

  for(int num = 0; num < 3; num++){
    if(num!=0){
      // Wait for the rx to finish
      while ((dma[0x34/4] & 0x1000)!=0x1000) ;

      printf("\n--- Sample %d Output ---\n", num-1);
      for(int j=0; j<4; j++){
        for(int i=0; i<4; i++){
          printf("%6d ",dst[j*4+i]);
          if(dst[j*4+i] != result[j][i]){
            printf("(Error Expecetd = %6d) ",result[j][i]);
          }
        }
        printf("\n"); 
      }
    }

    // AXI DMA transfer rx
    dma_reset();
    dma[0x30/4] = 1;
    dma[0x48/4] = dst_phys;
    dma[0x58/4] = 4*4*4;


    if((num+1)!=3){
      for(int j=0; j<4; j++){
        int sum[4] = {};
        for(int k=0; k<8; k++){
          for(int i=0; i<4; i++){
            sum[i] += matrix[i][k] * sample[j][k];
          }
        }
        for(int oa=0; oa<4; oa++){
          result[j][oa] = sum[oa];
        }
      }
      printf("\n--- Sample %d Input ---\n", num+1);
      for(int j=0; j<4; j++){
        for(int i=0; i<8; i++){
          sample[j][i] = rand() & 0x000000ff;
          printf("%3d ",sample[j][i]);
          src[j*8+i] = sample[j][i];
        }
        printf("\n");
      }
      // AXI DMA transfer tx
      dma[0x00/4] = 1;
      dma[0x18/4] = src_phys;
      dma[0x28/4] = 8*4*4;

      // Wait for the tx to finish
      while ((dma[0x04/4] & 0x1000)!=0x1000);
    }else{
      // last <- 1;
      top[0x00/4]=6;
    }

  }
  // Wait for the rx to finish
  while ((dma[0x34/4] & 0x1000)!=0x1000) ;

  printf("\n--- Sample %d Output ---\n", 2);
  for(int j=0; j<4; j++){
    int sum[4] = {};
    for(int k=0; k<8; k++){
      for(int i=0; i<4; i++){
        sum[i] += matrix[i][k] * sample[j][k];
      }
    }
    for(int i=0; i<4; i++){
      printf("%6d ",dst[j*4+i]);
      if(dst[j*4+i] != sum[i]){
        printf("(Error Expecetd = %6d) ",sum[i]);
      }
    }
    printf("\n");
  }

  // run <- 0; last <- 0;
  top[0x00/4]=0;


  printf("pass\n");

  return ;
}
