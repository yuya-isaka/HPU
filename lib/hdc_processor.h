
#ifndef HDC_PROCESSOR_h_
#define HDC_PROCESSOR_h_

#define BUS_WIDTH 256
#define THREADS_NUM 10

volatile int *top;
volatile int *dma;
volatile uint16_t *src;
volatile int *dst;

unsigned long src_phys;
unsigned long dst_phys;

extern uint16_t hdc_assemble(const char inst_str[], uint16_t addr);

extern void hdc_setup(void);

extern void hdc_make_imem(const int RANNUM);

extern void hdc_dma_reset(void);

extern void hdc_init(const int N);

extern void hdc_start(void);

extern void hdc_compute(void);

extern void hdc_finish(void);

extern void hdc_load_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num]);

extern void hdc_wbitem_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num]);

extern void hdc_pwbitem_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num]);

extern void hdc_store_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_pstore_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_move_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_pmove_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_permute_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num);

extern void hdc_xor_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_pxor_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_wb_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_last_core(uint16_t core_num);

#endif