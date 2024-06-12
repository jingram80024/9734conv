#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "repack.h"

#define STR_ENDS_WITH(S, E) (strcmp(S + strlen(S) - (sizeof(E)-1), E) == 0)
#define DEBUG_GBD 0

// main
int main(int argc, char **argv) {
    if (argc < (5 + DEBUG_GBD)) {
        puts("Usage: conv9734 <infile> <outfile> <width> <height>");
        puts("Example:");
        puts("    conv9734 input.raw output.raw 1280 720");
        exit(1);
    } //  todo add debayering format arg

    if (!(STR_ENDS_WITH(argv[1+DEBUG_GBD], ".raw") && STR_ENDS_WITH(argv[2+DEBUG_GBD], ".raw"))) {
        printf("Error. Filetypes must be .raw");
        exit(1);
    }
    
    // TODO: add w & h error handling and debayer format eventually

    // import pixel data
    void *pixels = NULL;
    int w = atoi(argv[3+DEBUG_GBD]);
    int h = atoi(argv[4+DEBUG_GBD]);
    // TODO: add debayering arg capture
    
    // repack10_8(const char *filename, w, h)
    pixels = repack10_8(argv[1+DEBUG_GBD], w, h);//my example here should be qoi_read

    if (pixels == NULL) {
        printf("9734_Error. Could not unpack.\n");
        exit(1);
    }

    // save output to file
    int saved = 0;

    saved = save_pixels(argv[2+DEBUG_GBD], pixels, w, h);

    if (!saved) {
        printf("9734_Error. Could not save to file.\n");
        exit(1);
    }

    free(pixels);
    return 0;
}