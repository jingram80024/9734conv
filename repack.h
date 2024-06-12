#pragma once

/* Unpacks 10bit raw sensor data and compresses it into 8bits per pixel

The original data must be 10-bit color depth spread across 2 bytes ("unpacked").
The Bayer filter layout does not matter, all pixels are treated the same regardless of color. */

void *repack10_8(const char *filename, int w, int h);

/* helper function for repack10_8 */

void *__repack10_8(const void *data, int size);

/* save a pixel byte stream to file */

int save_pixels(const char *filename, const void *data, const int w, const int h);