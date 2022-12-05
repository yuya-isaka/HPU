#include <arm_neon.h>

#ifndef HYPER_VECTOR_h_
#define HYPER_VECTOR_h_

#define HV_DIM 1024
#define HV_NUM HV_DIM / 128

typedef uint32x4_t hv_t;

#ifdef OPENMP
int32x4_t **hv_bound_buff;
#else
int32x4_t *hv_bound_buff;
#endif

extern void hv_init(void);
extern void hv_finish(void);

extern hv_t *hv_make(void);
extern void hv_free(hv_t *data);

extern hv_t **hv_make_array(const uint32_t size);
extern void hv_free_array(hv_t **data, const uint32_t size);

extern hv_t **hv_make_imem(const uint32_t size);

extern void hv_copy(hv_t *dst, hv_t *src);

extern hv_t *hv_bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM]);
extern hv_t *hv_perm(hv_t origin[HV_NUM], const uint32_t perm_num);

extern void hv_bound(hv_t encoded_hv[HV_NUM]);
extern hv_t *hv_bound_result(void);
extern hv_t *hv_bound_batch(hv_t **, const uint32_t);

#endif