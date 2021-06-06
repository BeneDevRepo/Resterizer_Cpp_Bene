#pragma once

#include <cstdint>

void put_pixel(uint32_t *buffer, int x, int y, uint32_t color);

void plot_line(uint32_t *buffer, int x0, int y0, int x1, int y1, uint32_t color);

void plot_triangle(uint32_t *buffer, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void clear(uint32_t *buffer, uint32_t color);
