# Converts a PPM file to a C-header

This is a simple tool that converts an image file encoded in in the PPM
format to a C-header with an array containing the image data.

This tool requires the 'netpbm' package to convert an image to PPM.

* works and tested in linux...

```
$ sudo apt-get install netpbm
$ make
$ ./jpeg-to-c.sh image.jpeg image.h
```
