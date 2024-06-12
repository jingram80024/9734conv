# conv9734

Utilty to convert ov9734 captured raw image from v4l2-ctl from 10-bit bayer to 8-bit format. I used this for debugging and development of the ov9734 driver/dts.

Run `make` to build.

Usage: `./conv9734 <infile> <outfile> <width> <height>`

Example: `./conv9734 input.raw output.raw 1280 720`

im.png is not a good image because optics were not used with the image sensor.
