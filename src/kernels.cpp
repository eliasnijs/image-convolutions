//// define a kernel with the following signature:
//// KERNEL(id, w, h, c, ...data), make sure to declare the kernel in the
//// KernelType enum and the KERNEL_TYPE_REPR_TABLE

////////////////////////////////////////////////////////////////////////////////
//// KERNELS DECLARATION
enum KernelType {
	KERNEL_TYPE_NONE,
	KERNEL_TYPE_SOBEL,
	KERNEL_TYPE_GAUSSIAN_5,
	KERNEL_TYPE_GAUSSIAN_9,
	KERNEL_TYPE_LAPLACIAN,
	KERNEL_TYPE_AVERAGE,
	KERNEL_TYPE_SHARPEN,
	KERNEL_TYPE_EMBOSS,
	KERNEL_TYPE_EDGE,
	KERNEL_TYPE_SHADOW,
	KERNEL_TYPE_OUTLINE,
	KERNEL_TYPE_COUNT
};


#include "kernel_utils.cpp"
////////////////////////////////////////////////////////////////////////////////
//// KERNELS IMPLEMENTATIONS

KERNEL(SOBEL, 3, 3, 1,
    -1,  0,  1,
    -2,  0,  2,
    -1,  0,  1
);

KERNEL(GAUSSIAN_5, 5, 5, 1,
    1,  4,  6,  4,  1,
    4, 16, 24, 16,  4,
    6, 24, 36, 24,  6,
    4, 16, 24, 16,  4,
    1,  4,  6,  4,  1
);

KERNEL(GAUSSIAN_9, 9, 9, 1,
    1,  1,  2,  2,  2,  2,  2,  1,  1,
    1,  2,  2,  4,  4,  4,  2,  2,  1,
    2,  2,  4,  4,  8,  4,  4,  2,  2,
    2,  4,  4,  8, 16,  8,  4,  4,  2,
    2,  4,  8, 16, 32, 16,  8,  4,  2,
    2,  4,  4,  8, 16,  8,  4,  4,  2,
    2,  2,  4,  4,  8,  4,  4,  2,  2,
    1,  2,  2,  4,  4,  4,  2,  2,  1,
    1,  1,  2,  2,  2,  2,  2,  1,  1
);

KERNEL(LAPLACIAN, 3, 3, 1,
    0,  1,  0,
    1, -4,  1,
    0,  1,  0
);

KERNEL(AVERAGE, 3, 3, 1,
    1/9.0f, 1/9.0f, 1/9.0f,
    1/9.0f, 1/9.0f, 1/9.0f,
    1/9.0f, 1/9.0f, 1/9.0f
);

KERNEL(SHARPEN, 3, 3, 1,
     0, -1,  0,
    -1,  5, -1,
     0, -1,  0
);

KERNEL(EMBOSS, 3, 3, 1,
    -2, -1,  0,
    -1,  1,  1,
     0,  1,  2
);

KERNEL(EDGE, 3, 3, 1,
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1
);

KERNEL(SHADOW, 3, 3, 1,
    0,  0,  0,
    0,  1,  0,
    0,  0, -1
);

KERNEL(OUTLINE, 3, 3, 1,
    0,  0,  0,
    0,  1,  0,
    0,  0,  0
);


