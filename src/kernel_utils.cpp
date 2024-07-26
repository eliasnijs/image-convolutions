struct Kernel {
    KernelType  id;
    I32  w, h, c;
    F32  *data;
};

global_variable Kernel *KERNELS[KERNEL_TYPE_COUNT] = {};
global_variable char *KERNEL_TYPE_REPR_TABLE[KERNEL_TYPE_COUNT] = {};

#define KERNEL(id, w, h, c, ...) \
    global_variable F32 kernel_##id##_data[] = { __VA_ARGS__ }; \
    global_variable Kernel id##_KERNEL = { KERNEL_TYPE_##id, w, h, c, kernel_##id##_data }; \
    global_variable Kernel *id##_KERNEL_PTR = &id##_KERNEL; \
    Kernel *_init_##id() { \
	    KERNELS[KERNEL_TYPE_##id] = id##_KERNEL_PTR; \
	    KERNEL_TYPE_REPR_TABLE[KERNEL_TYPE_##id] = #id; \
	    return id##_KERNEL_PTR; \
    } \
    global_variable Kernel *_##id##_init = _init_##id();


internal inline U32
indexK(Kernel *K, I32 x, I32 y, I32 c)
{
    return (y * K->w + x) * K->c + c;
}

internal void
printK(KernelType id) {
	Kernel *K = KERNELS[id];
	printf("%d. %s:", id, KERNEL_TYPE_REPR_TABLE[id]);
	if (K == 0x0) {
		printf("\tKernel not implemented\n");
		return;
	}
	printf("\n");
	for (I32 y = 0; y < K->h; ++y) {
		printf("\t[");
		for (I32 x = 0; x < K->w; ++x) {
			for (I32 c = 0; c < K->c; ++c) {
				printf("%4.0f ", K->data[indexK(K, x, y, c)]);
			}
		}
		printf("]\n");
	}
}
