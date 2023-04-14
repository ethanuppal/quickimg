// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h>
#include "quickimg.h"

#define MAX_CHANNEL 255
#define BLACK 0, 0, 0
#define PURPLE 255, 0, 255

#define WIDTH 500
#define HEIGHT 500
#define N 50

void shader(quickimg_t* qi, size_t x, size_t y) {
    if (((x * N / WIDTH) % 2 == 0) ^ ((y * N / WIDTH) % 2 == 0)) {
        quickimg_pix(qi, x, y, BLACK);
    } else {
        quickimg_pix(qi, x, y, PURPLE);
    }
}

int main() {
    quickimg_t* qi = quickimg_new(WIDTH, HEIGHT, MAX_CHANNEL);
    quickimg_fill(qi, shader);
    FILE* f = fopen("bin/out.ppm", "w");
    quickimg_write(f, qi);
    fclose(f);
    quickimg_destroy(qi);
    return 0;
}
