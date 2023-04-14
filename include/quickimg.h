// Copyright (C) Ethan Uppal 2023. All rights reserved.

#pragma once

#include <stddef.h> // size_t
#include <stdint.h> // uint16_t
#include <stdio.h> // FILE

typedef struct quickimg_t quickimg_t;
typedef uint16_t channel_t;
typedef void (*quickimg_shader_t)(quickimg_t*, size_t x, size_t y);

quickimg_t* quickimg_new(size_t width, size_t height, int max_channel);
void quickimg_destroy(quickimg_t* quickimg);

int quickimg_write(FILE* dest, quickimg_t* quickimg);

void quickimg_pix(quickimg_t* quickimg, size_t x, size_t y, channel_t r, channel_t g, channel_t b);
void quickimg_fill(quickimg_t* quickimg, quickimg_shader_t shader);
