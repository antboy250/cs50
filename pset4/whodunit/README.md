# Questions

## What's `stdint.h`?

Header file in the C standard library

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Fixed width integer types

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 8, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

hexadecimal

## What's the difference between `bfSize` and `biSize`?

Bfsize is the size of the whole bmp file including the headers; bisize is contant and is 40 bytes representing the number of bytes that represent the BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

the bitmap is a top-down DIB with the origin at the upper left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

Bibitcount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If no file is opened for some reason, either it doesn't exist or there is an error.

## Why is the third argument to `fread` always `1` in our code?

You want to read '1' BITMAPINFOHEADER and BITMAPFILEHEADER.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

An f function in the stdio.h that moves file pointer associated with a given file to a specific position

## What is `SEEK_CUR`?

Moves pointer to given location
