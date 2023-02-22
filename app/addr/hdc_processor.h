#ifndef HDC_PROCESSOR_h_
#define HDC_PROCESSOR_h_

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

extern void hdc_load_1(uint32_t thread_num, uint32_t addr_array[thread_num]);

extern void hdc_xor_121(uint32_t thread_num);

extern void hdc_xor_p21(uint32_t thread_num);

extern void hdc_xor_p11(uint32_t thread_num);

extern void hdc_move_21(uint32_t thread_num);

extern void hdc_move_p1(uint32_t thread_num);

extern void hdc_load_2(uint32_t thread_num, uint32_t addr_array[thread_num]);

extern void hdc_xor_122(uint32_t thread_num);

extern void hdc_xor_p22(uint32_t thread_num);

extern void hdc_xor_p12(uint32_t thread_num);

extern void hdc_move_12(uint32_t thread_num);

extern void hdc_move_p2(uint32_t thread_num);

extern void hdc_permute_2(uint32_t thread_num, uint32_t permute_num);

extern void hdc_permute_1(uint32_t thread_num, uint32_t permute_num);

extern void hdc_permute_2_unit(uint32_t permute_num);

extern void hdc_permute_1_unit(uint32_t permute_num);

extern void hdc_store_2(uint32_t thread_num);

extern void hdc_store_1(uint32_t thread_num);

extern void hdc_store_p(uint32_t thread_num);

extern void hdc_last(void);

#endif