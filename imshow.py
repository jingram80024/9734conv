import os
import argparse
import sys
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--filename", required=True)
    parser.add_argument("-w", "--width", required=True)
    parser.add_argument("-t", "--height", required=True)
    args = vars(parser.parse_args())

    filename = args["filename"]
    width = int(args["width"])
    height = int(args["height"])

    filesize=os.stat(filename).st_size
    if filesize == 1902528:
        sys.exit("file too large")
    
    imarray = np.empty(filesize,dtype=np.uint8)
    with open(filename, 'rb') as f:
        for i in range(filesize):
           imarray[i] = np.uint8(int.from_bytes(f.read(1)))

    imarray = np.reshape(imarray, (height, width))
    print(imarray.shape)
    print(imarray[0])
    im = Image.fromarray(imarray,mode="P")
    plt.imshow(im, aspect="auto")
    plt.title(filename)
    plt.show()


if __name__ == "__main__":
    main()