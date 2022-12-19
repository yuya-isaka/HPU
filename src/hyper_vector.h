
#ifndef HYPER_VECTOR_h_
#define HYPER_VECTOR_h_

// 次元数可変
#define HV_DIM 2048
#define HV_NUM HV_DIM / ELEMENT_SIZE

#ifdef HV64
#define ELEMENT_SIZE 64
typedef uint64_t hv_t;
#else
#define ELEMENT_SIZE 32
typedef uint32_t hv_t;
#endif

typedef int32_t hv_int_t;

#ifdef OPENMP
hv_int_t **hv_bound_buff;
#else
hv_int_t *hv_bound_buff;
#endif

extern void hv_init(void);
extern void hv_finish(void);

extern hv_t *hv_make(void);
extern void hv_free(hv_t *data);

extern hv_t **hv_make_imem(const uint32_t size);

extern void hv_copy(hv_t *dst, hv_t *src);

extern hv_t *hv_bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM]);
extern hv_t *hv_perm(hv_t origin[HV_NUM], const uint32_t perm_num);

extern void hv_bound(hv_t encoded_hv[HV_NUM]);
extern hv_t *hv_bound_result(void);

extern void hv_print(hv_t print_data[HV_NUM]);

// batch
extern hv_t **hv_make_array(const uint32_t size);
extern void hv_free_array(hv_t **data, const uint32_t size);

// batch
extern hv_t *hv_bound_batch(hv_t **, const uint32_t);

#endif