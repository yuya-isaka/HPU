#ifndef HDC_PROCESSOR_h_
#define HDC_PROCESSOR_h_

// バス幅
#define BUS_WIDTH 256

// 最大スレッド数
#define THREADS_NUM 5

extern int *dst;

extern void hdc_print(void);

extern void hdc_setup(void);

extern void hdc_dma_reset(void);

extern void hdc_init(const int N);

extern void hdc_start(void);

extern void hdc_compute(void);

extern void hdc_compute_only(void);

extern void hdc_finish(void);

extern void hdc_com_start(void);

extern void hdc_com_start_continue(void);

extern void hdc_com_gen(uint32_t num);

extern void hdc_nop(void);

extern void hdc_load_thread(uint16_t thread_num, uint16_t core_num, uint16_t addr_array[thread_num][core_num]);

extern void hdc_store_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_store_thread(void);

extern void hdc_pstore_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_pstore_thread(void);

extern void hdc_move_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_move_thread(void);

extern void hdc_pmove_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_pmove_thread(void);

extern void hdc_permute(uint16_t permute_num);

extern void hdc_permute_thread(uint16_t thread_num, uint16_t core_num, uint16_t permute_num);

extern void hdc_simd_permute_thread(uint16_t permute_num);

extern void hdc_xor_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_xor_thread(void);

extern void hdc_pxor_thread(uint16_t thread_num, uint16_t core_num);

extern void hdc_simd_pxor_thread(void);

extern void hdc_last(void);

#endif