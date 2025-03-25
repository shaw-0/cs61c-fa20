/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**                YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

Color *readPixel(FILE *fp)
{
    Color *pixel = malloc(sizeof(Color));
    if (pixel == NULL) {
        exit(-1);
    }
    fscanf(fp, "%hhu %hhu %hhu", &(pixel->R), &(pixel->G), &(pixel->B));
    return pixel;
}

//Opens a .ppm P3 image file, and constructs an Image object.
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
    //YOUR CODE HERE
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(-1);
    }
    uint32_t rows;
    uint32_t cols;
    char c[100];
    fscanf(fp, "%s", c);
    fscanf(fp, "%u %u", &cols, &rows);
    fscanf(fp, "%s", c);

    Image *pic = malloc(sizeof(Image));
    if (pic == NULL) {
        exit(-1);
    }
    pic->rows = rows;
    pic->cols = cols;
    Color **rows_of_pixel;
    rows_of_pixel = malloc(rows * sizeof(Color*));
    if (rows_of_pixel == NULL) {
        exit(-1);
    }
    for (int i = 0; i < rows; i++) {
        rows_of_pixel[i] = malloc(cols * sizeof(Color));
        Color *row_now = rows_of_pixel[i];
        if (row_now == NULL) {
            exit(-1);
        }
        for (int j = 0; j < cols; j++) {
            Color *pixel = readPixel(fp);
            *(row_now + j) = *pixel;
            free(pixel);
        }
    }
    pic->image = rows_of_pixel;

    fclose(fp);

    return pic;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
    //YOUR CODE HERE
    printf("P3\n");

    uint32_t rows = image->rows;
    uint32_t cols = image->cols;
    Color **rows_of_pixel = image->image;
    printf("%u %u\n", cols, rows);
    printf("255\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color pixel = rows_of_pixel[i][j];
            printf("%3u %3u %3u", pixel.R, pixel.G, pixel.B);
            if (j != cols - 1) {
                printf("   ");
            } else {
                printf("\n");
            }
        }
    }
}

//Frees an image
void freeImage(Image *image)
{
    //YOUR CODE HERE
    Color **rows_of_pixels = image->image;
    for (int i = 0; i < image->rows; i++) {
        free(rows_of_pixels[i]);
    }
    free(image->image);
    free(image);
}