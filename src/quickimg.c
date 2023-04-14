// Copyright (C) Ethan Uppal 2023. All rights reserved.

#include <stdio.h> //
#include <stdlib.h> // malloc, free
#include "quickimg.h"

#define INLINE __attribute__((always_inline))
#define CHANNELS_PER_COLOR 3

struct quickimg_t {
    size_t width;
    size_t height;
    int max_channel;
    channel_t buffer[];
};

quickimg_t* quickimg_new(size_t width, size_t height, int max_channel) {
    size_t size = width * height * CHANNELS_PER_COLOR;
    quickimg_t* qi = malloc(sizeof(*qi) + size * sizeof(*qi->buffer));
    qi->width = width;
    qi->height = height;
    qi->max_channel = max_channel;
    return qi;
}

void quickimg_destroy(quickimg_t* quickimg) {
    free(quickimg);
}

int quickimg_write(FILE* dest, quickimg_t* quickimg) {
    // ppm file header
    if (fprintf(dest, "P6\n%zu\n%zu\n%d\n",
            quickimg->width, quickimg->height, quickimg->max_channel) < 0) {
        return 1;
    }

    // write data
    size_t size = quickimg->width * quickimg->height * CHANNELS_PER_COLOR;
    if (quickimg->max_channel > 0xFF) {
        // two bytes
        for (size_t i = 0; i < size; i += CHANNELS_PER_COLOR) {
            channel_t r = quickimg->buffer[i];
            channel_t g = quickimg->buffer[i + 1];
            channel_t b = quickimg->buffer[i + 2];
            if (fprintf(dest, "%c%c%c%c%c%c", r >> 8, r, g >> 8, g, b >> 8, b) < 0) {
                return 1;
            }
        }
    } else {
        // one byte
        for (size_t i = 0; i < size; i += CHANNELS_PER_COLOR) {
            channel_t r = quickimg->buffer[i];
            channel_t g = quickimg->buffer[i + 1];
            channel_t b = quickimg->buffer[i + 2];
            if (fprintf(dest, "%c%c%c", r, g, b) < 0) {
                return 1;
            }
        }
    }

    return 0;
}

INLINE void quickimg_pix(quickimg_t* quickimg, size_t x, size_t y, channel_t r, channel_t g, channel_t b) {
    size_t i = CHANNELS_PER_COLOR * (y * quickimg->width + x);
    quickimg->buffer[i] = r;
    quickimg->buffer[i + 1] = g;
    quickimg->buffer[i + 2] = b;
}

void quickimg_fill(quickimg_t* quickimg, quickimg_shader_t shader) {
    for (size_t y = 0; y < quickimg->height; y++) {
        for (size_t x = 0; x < quickimg->width; x++) {
            shader(quickimg, x, y);
        }
    }
}
