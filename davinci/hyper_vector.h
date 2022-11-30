#ifndef HYPER_VECTOR_h_
#define HYPER_VECTOR_h_

#define HV_DIM 1024
#define HV_NUM HV_DIM / 32

typedef uint32_t hv_t;

int32_t bound_buff[HV_DIM];

extern void hv_init(void);

extern hv_t *hv_make(void);
extern void hv_free(hv_t *data);

extern hv_t **hv_make_array(const uint32_t size);
extern void hv_free_array(hv_t **data, const uint32_t size);

extern hv_t **hv_make_imem(const uint32_t size);

extern void hv_copy(hv_t *dst, hv_t *src);

extern hv_t *bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM]);
extern hv_t *perm(hv_t origin[HV_NUM], const uint32_t perm_num);
extern void bound(hv_t encoded_hv[HV_NUM]);
extern hv_t *bound_result(void);

#endif