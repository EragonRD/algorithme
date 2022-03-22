#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define __OSX__
#ifndef __OSX__
/* pour Bocal */
#include <GL/gl.h>
#else
/* pour mac */
#include <GL/glut.h>
#endif


struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *);
void gris_uniforme (Image *);
void gris (Image *);
void affichePixel(int x, int y);
void draw_br(int u, int v);
void draw_brVue(int u, int v);
void drawing(int pattern, int *x, int *y);
void drawing2(int pattern, int *x, int *y);
void draw_line_calling(int a1, int b1, int a2, int b2);
void draw_step3Vue(int a1, int b1, int a2, int b2);
void draw_step3(int a1, int b1, int a2, int b2);
void draw_step3UP(int a1, int b1, int a2, int b2);
void draw_step3UPTEST(int a1, int b1, int a2, int b2);
