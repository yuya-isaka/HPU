#ifndef HYPER_VECTOR_h_
#define HYPER_VECTOR_h_

#define HV_DIM 1024
#define HV_NUM HV_DIM / 32

typedef uint32_t hv_t;

int32_t bound_buff[HV_DIM];
extern void initHV(void);
extern hv_t *makeHV(void);
extern void freeHV(hv_t *data);
extern hv_t **makeArrayHV(size_t size);
extern void freeArrayHV(hv_t **data, size_t size);
extern hv_t **makeItemMemory(size_t size);
extern void copyHV(hv_t *dst, hv_t *src);
extern hv_t *perm(hv_t origin[HV_NUM], hv_t perm_num);
extern void bound(hv_t encoded_hv[HV_NUM]);
extern hv_t *bound_extract(void);
extern hv_t *bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM]);

#endif