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

extern void hdc_load_1(uint32_t addr_array[THREADS_NUM]);

extern void hdc_load_1_thread(uint32_t thread_num, uint32_t addr_array[thread_num]);

extern void hdc_bind_121(void);

extern void hdc_bind_121_thread(uint32_t thread_num);

extern void hdc_bind_p21(void);

extern void hdc_bind_p21_thread(uint32_t thread_num);

extern void hdc_bind_p11(void);

extern void hdc_bind_p11_thread(uint32_t thread_num);

extern void hdc_move_21(void);

extern void hdc_move_21_thread(uint32_t thread_num);

extern void hdc_move_p1(void);

extern void hdc_move_p1_thread(uint32_t thread_num);

extern void hdc_load_2(uint32_t addr_array[THREADS_NUM]);

extern void hdc_load_2_thread(uint32_t thread_num, uint32_t addr_array[thread_num]);

extern void hdc_bind_122(void);

extern void hdc_bind_122_thread(uint32_t thread_num);

extern void hdc_bind_p22(void);

extern void hdc_bind_p22_thread(uint32_t thread_num);

extern void hdc_bind_p12(void);

extern void hdc_bind_p12_thread(uint32_t thread_num);

extern void hdc_move_12(void);

extern void hdc_move_12_thread(uint32_t thread_num);

extern void hdc_move_p2(void);

extern void hdc_move_p2_thread(uint32_t thread_num);

extern void hdc_permute_2(uint32_t permute_num);

extern void hdc_permute_2_thread(uint32_t thread_num, uint32_t permute_num);

extern void hdc_permute_1(uint32_t permute_num);

extern void hdc_permute_1_thread(uint32_t thread_num, uint32_t permute_num);

extern void hdc_permute_2_unit(uint32_t permute_num);

extern void hdc_permute_1_unit(uint32_t permute_num);

extern void hdc_bound_2(void);

extern void hdc_bound_2_thread(uint32_t thread_num);

extern void hdc_bound_1(void);

extern void hdc_bound_1_thread(uint32_t thread_num);

extern void hdc_bound_p(void);

extern void hdc_bound_p_thread(uint32_t thread_num);

extern void hdc_last(void);

#endif