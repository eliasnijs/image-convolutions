#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <cmath>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#define ENABLE_PRINT 1
#define ENABLE_DEBUG 1
#include "utils/utils.h"

#include "kernels.cpp"

struct Image {
	I32 w, h, c;
	U8  *data;
};


internal inline U32
indexI(Image *I, I32 x, I32 y, I32 c)
{
    x = Clamp(0, x, (I32)I->w - 1);
    y = Clamp(0, y, (I32)I->h - 1);
    return (y * I->w + x) * I->c + c;
}


internal I32
convolution(char *input, U32 kernel_id)
{
	/* load original image */
	Image I1 = {};
	I1.data = stbi_load(input, &I1.w, &I1.h, &I1.c, 0);
	if (!I1.data) {
		fprintf(stderr, "failed to load image: %s\n",
			stbi_failure_reason());
		return 1;
	}

	/* load the kernel */
	Kernel K = *KERNELS[kernel_id];
	printf("using the following kernel:\n");
	printK(K.id);

	/* do the convolution */
	Image I2 = I1;
	I2.data = (U8 *)calloc(I2.w * I2.h * I2.c, sizeof(F32));

	for (I32 y = 0; y < I1.h; ++y)
	for (I32 x = 0; x < I1.w; ++x) {
		I32 i_I2 = indexI(&I2, x, y, 0);
		F32 rgba[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		for (I32 y_local = -K.h/2; y_local <= K.h/2; ++y_local)
		for (I32 x_local = -K.w/2; x_local <= K.w/2; ++x_local)
		for (I32 c = 0; c < I1.c; ++c) {
			I32 i_I1 = indexI(&I1, x + x_local, y + y_local, c);
			I32 i_K  = indexK(&K, K.w/2 + x_local, K.h/2 + y_local, c % K.c);
			rgba[c] += (F32)I1.data[i_I1] * K.data[i_K] * K.factor;
		}
		I2.data[i_I2]     = (U8)Clamp(0, rgba[0], 255);
		I2.data[i_I2 + 1] = (U8)Clamp(0, rgba[1], 255);
		I2.data[i_I2 + 2] = (U8)Clamp(0, rgba[2], 255);
		I2.data[i_I2 + 3] = (U8)Clamp(0, rgba[3], 255);
	}

	/* save image */
	I32 s = stbi_write_png("out.png", I2.w, I2.h, I2.c, I2.data, I2.w * I2.c);
	if (!s) {
		fprintf(stderr, "failed to save image: %s\n",
			stbi_failure_reason());
		return 1;
	}

	free(I2.data);
	free(I1.data);
	return 0;
}





I32
main(I32 argc, char **argv)
{
	char *name = argv[0];
	argv = &argv[1];
	--argc;

	I32 e = 1;
	switch (argc) {
	case 1:  {
		if (strcmp(argv[0], "kernels") == 0) {
			printf("Available kernels:\n");
			for (I32 i = 1; i < KERNEL_TYPE_COUNT; ++i) {
				printK((KernelType)i);
			}
			e = 0;
		}
	} break;
	case 2: {
		U32 kernel_id = atoi(argv[1]);
		if (kernel_id <= 0 || kernel_id >= KERNEL_TYPE_COUNT) {
			fprintf(stderr, "invalid kernel id: %d\n", kernel_id);
			break;
		}
		e = convolution(argv[0], kernel_id);
	} break;
	default: {
		printf("usage: %s <input::str> <kernel_id::int>\n", name);
		printf("view available kernels with: \"%s kernels\"\n", name);
		e = 1;
	} break;
	}

	return e;
}

