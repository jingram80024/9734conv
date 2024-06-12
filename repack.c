#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "repack.h"


void *__repack10_8(const void *data, int size) {
    const unsigned char *bytes;
    unsigned char *pixels;
    int size8 = size / 2;
    int p = 0;

    if (data == NULL) {//add more error handling later
        printf("RP_Error. No data");
        return NULL;
    }
    short int last_p;
    bytes = (const unsigned char *)data;
    pixels = (unsigned char *) malloc(size8);
    for (int i = 0; i < size8; i++) {
        unsigned char lsb = bytes[p++];
        unsigned char msb = bytes[p++];
        unsigned char pix8;

        int pix10_16 = (((unsigned int)msb) << 8) | (unsigned int)lsb;
        pix8 = (pix10_16 * 255) / 1023;
        pixels[i] = pix8;
    }

    return pixels;
}

void *repack10_8(const char *filename, int w, int h) {
    FILE *f = fopen(filename, "rb");
    int size, bytes_read;
    void *pixels, *data;

    if (!f) {
        printf("RP_Error opening file.\n");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    if (size <= 0 || fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        printf("RP_Error. file error");
        return NULL;
    }

    if (size != (w * h * 2)) { //2 bytes per pixel
        printf("RP_Error. File size doesn't match w * h provided.\n");
        fclose(f);
        return NULL;
    }

    data = malloc(size);
    if (!data) {
        fclose(f);
        printf("RP_Error. No data");
        return NULL;
    }

    bytes_read = fread(data, 1, size, f);
    fclose(f);
    pixels = (bytes_read != size) ? NULL : __repack10_8(data, bytes_read);
    free(data);
    return pixels;
}

int save_pixels(const char *filename, const void *data, const int w, const int h) {
    printf("Writing to %s\n",filename);
    FILE *f = fopen(filename, "wb");
    int size, err;
    size = w * h;

    if (!f) {
        printf("RP_Error. Couldn't open output file.\n");
        return 0;
    }
    if (!data) {
        printf("RP_Error. no data to write.\n");
        return 0;
    }
    
    fwrite(data, 1, size, f);
    fflush(f);
    err = ferror(f);
    fclose(f);

    return err ? 0 : size;
}