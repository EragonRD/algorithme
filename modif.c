#include "image.h"
#include <limits.h>

void gris_uni(Image * i) {
  int j, size;
  GLubyte * im, val;
  val = 128;
  size = 3 * i->sizeY * i->sizeX;
  im = i->data;
  for (j = 0; j < size; j ++) {
	*im++ = val;
  }
}
void gris (Image * im) {
  int j, r, g, b, size, moy;
  GLubyte * ptr, val;

  size =  im->sizeY * im->sizeX;
  ptr = im->data;
  for (j = 0; j < size; j ++) {
	r = *ptr++ ;
	g = *ptr++ ;
	b = *ptr ;
	moy = r + g + (int) b;
	moy /= 3;
	val = (GLubyte) moy;
	ptr -= 2;
	*ptr++ = val;
	*ptr++ = val;
	*ptr++ = val;
  }
}

void printP(int x, int y) {
  //glColor3f(1,1,0);
  glBegin(GL_POINTS);
   glVertex2i(x,y);
  glEnd();
  glFlush();
}

void draw_br(int u, int v) {
  int x, y, delta, incD, incH;

  incH = v << 1;
   delta  = incH - u;
   incD   = delta - u;
   for (x = 0, y = 0; x <= u; x+=1) {
      if (delta >= 0) {
         y+=1;
         delta += incD;
      }
      else {
         delta += incH;
      }
   }
}

void draw_brVue(int u, int v) {
  int x, y, delta, incD, incH;

  incH = v << 1;
  //incH = v *2;
   delta  = incH - u;
   incD   = delta - u;
   for (x = 0, y = 0; x <= u; x+=1) {
      //affiche(x, y);
      //image[y*W+x] = color;
      printP(x, y);
      if (delta >= 0) {
         y+=1;
         delta += incD;
      }
      else {
         delta += incH;
      }
   }
}

///fonction du paterne 1
void drawP1(int *x, int *y) {
  ++*x; ++*x;
}
///fonction du paterne 2
void drawP2(int *x, int *y) {
  ++*x; ++*x; ++*y;
}
///fonction du paterne 3
void drawP3(int *x, int *y) {
  ++*x; ++*y; ++*x;
}
///fonction du paterne 4
void drawP4(int *x, int *y) {
  ++*x; ++*y; ++*x; ++*y;
}
///fonction du paterne 5
void drawP5(int *x, int *y) {
  ++*x; ++*x; ++*y; ++*x;
}
///fonction du paterne 6
void drawP6(int *x, int *y) {
  ++*x; ++*y; ++*x; ++*x; ++*y;
}

///fonction pour dessiner les pattern
void drawing(int pattern, int *x, int *y) {
  switch (pattern)
  {
  case 1:
    ++*x; printP(*x, *y); ++*x; printP(*x, *y);
    break;

  case 2:
    ++*x; printP(*x, *y); ++*x; ++*y; printP(*x, *y);
    break;

  case 3:
    ++*x; ++*y; printP(*x, *y); ++*x; printP(*x, *y);
    break;

  case 4:
    ++*x; ++*y; printP(*x, *y); ++*x; ++*y; printP(*x, *y);
    break;

  case 5:
    ++*x; printP(*x, *y); ++*x; ++*y; printP(*x, *y); ++*x; printP(*x, *y);
    break;

  case 6:
    ++*x; ++*y; printP(*x, *y); ++*x; printP(*x, *y); ++*x; ++*y; printP(*x, *y);
    break;
  }
}

///fonction pour tester l'efficacité original dans draw_line_calling
void drawing2(int pattern, int *x, int *y) {
  switch (pattern)
  {
  case 1:
  //printf("1");
    ++*x; /*printP(*x, *y);*/ ++*x; //printP(*x, *y);
    break;

  case 2:
  //printf("2");
    ++*x; /*printP(*x, *y);*/ ++*x; ++*y; //printP(*x, *y);
    break;

  case 3:
  //printf("3");
    ++*x; ++*y; /*printP(*x, *y);*/ ++*x; //printP(*x, *y);
    break;

  case 4:
  //printf("4");
    ++*x; ++*y; /*printP(*x, *y);*/ ++*x; ++*y; //printP(*x, *y);
    break;

  case 5:
  //printf("5");
    ++*x; /*printP(*x, *y);*/ ++*x; ++*y; /*printP(*x, *y);*/ ++*x; /*printP(*x, *y);*/
    break;

  case 6:
  //printf("6");
    ++*x; ++*y; /*printP(*x, *y);*/ ++*x; /*printP(*x, *y);*/ ++*x; ++*y; //printP(*x, *y);
    break;
  }
}

void draw_line_calling(int a1, int b1, int a2, int b2) {
  int dx, dy, incr1, incr2, incr3, D, x, y, xend, c;

  dx = a2 - a1, dy = b2 - b1;
  x = a1, y = b1;
  xend = a2 - 1;
  printP(x,y);
  incr2 = 4*dy - 2*dx;
  //incr2 = dy << 2 - dx <<1;

  if(incr2 <= 0) {
    c = 2 * dy;
    incr1 = 2 * c;
    incr3 = incr2 + c;
    D = incr1 - dx;
    while(x < xend) {
      if(D < 0) {
        //drawing2(1, &x, &y);
        drawP1(&x, &y);
        D += incr1;
      }
      else if(D >= c) {
        //drawing2(3, &x, &y);
        drawP3(&x, &y);
        D += incr2;
      }
      else {
        //drawing2(5, &x, &y);
        drawP5(&x, &y);
        D += incr3;
      }
    }
  }
  else {
    c = 2 *(dy - dx);
    incr1 = 2 * c;
    incr3 = incr2 + c;
    D = incr1 + dx;
    while(x < xend) {
      if(D >= 0) {
        drawP4(&x, &y);
        //drawing2(4, &x, &y);
        D += incr1;
      }
      else if(D < c) {
        drawP2(&x, &y);
        //drawing2(2, &x, &y);
        D += incr2;
      }
      else {
        drawP6(&x, &y);
        //drawing2(6, &x, &y);
        D += incr3;
      }
    }
  }
  if(x < a2) {
    //printP(x,y);
  }
}

void draw_step3Vue(int a1, int b1, int a2, int b2) {
  int dx, dy, incr1, incr2, incr3, D, x, y, xend, c;

  dx =a2 - a1, dy = b2 - b1;
  x = a1, y = b1;
  xend = a2 - 1;
  printP(x, y);
  incr2 = 4*dy - 2*dx;
  //incr2 = (dy << 2) - (dx << 1);

  if(incr2 <= 0) {
    c = 2 * dy;
    //c = dy << 1;
    incr1 = 2 * c;
    //incr1 = c << 1;
    incr3 = incr2 + c;
    D = incr1 - dx;
    while(x < xend) {
      if(D < 0) {
        ++x;
        printP(x, y);
        ++x;
        printP(x, y);
        D += incr1;
      }
      else if(D >= c) {
        ++x;
        ++y;
        printP(x, y);
        ++x;
        printP(x, y);
        D += incr2;
      }
      else {
        ++x;
        printP(x, y);
        ++x;
        ++y;
        printP(x, y);
        ++x;
        printP(x, y);
        D += incr3;
      }
    }
  }
  else {
    c = 2 *(dy - dx);
    //c = (dy - dx) << 1;
    incr1 = 2 * c;
    //incr1 = c << 1;
    incr3 = incr2 + c;
    D = incr1 + dx;
    while(x < xend) {
      if(D >= 0) {
        ++x;
        ++y;
        printP(x, y);
        ++x;
        ++y;
        printP(x, y);
        D += incr1;
      }
      else if(D < c) {
        ++x;
        printP(x, y);
        ++x;
        ++y;
        printP(x, y);
        D += incr2;
      }
      else {
        ++x;
        ++y;
        printP(x, y);

        ++x;
        printP(x, y);
        ++x;
        ++y;
        printP(x, y);
        D += incr3;
      }
    }
  }
  if(x < a2) {
    printP(a2, b2);
  }
}


void draw_step3(int a1, int b1, int a2, int b2) {
  int dx, dy, incr1, incr2, incr3, D, x, y, xend, c;

  dx =a2 - a1, dy = b2 - b1;
  x = a1, y = b1;
  xend = a2 - 1;
  incr2 = 4*dy - 2*dx;

  if(incr2 <= 0) {
    c = 2 * dy;
    incr1 = 2 * c;
    incr3 = incr2 + c;
    D = incr1 - dx;
    while(x < xend) {
      if(D < 0) {
        ++x;
        ++x;
        D += incr1;
      }
      else if(D >= c) {
        ++x;
        ++y;
        ++x;
        D += incr2;
      }
      else {
        ++x;
        ++x;
        ++y;
        ++x;
        D += incr3;
      }
    }
  }
  else {
    c = 2 *(dy - dx);
    incr1 = 2 * c;
    incr3 = incr2 + c;
    D = incr1 + dx;
    while(x < xend) {
      if(D >= 0) {
        ++x;
        ++y;
        ++x;
        ++y;
        D += incr1;
      }
      else if(D < c) {
        ++x;
        ++x;
        ++y;
        D += incr2;
      }
      else {
        ++x;
        ++y;
        ++x;
        ++x;
        ++y;
        D += incr3;
      }
    }
  }
  if(x < a2) {
  }
}

///L'algorithme améliorer pour le dessin
void draw_step3UP(int a1, int b1, int a2, int b2) {
  int dx, dy, incr1, incr2, incr3, D, D2, x, y, xend, c;
  int impaire = 0;
  if (a2%2 != 0 || b2%2 != 0) {
    impaire = 1;
  }

  dx =a2 - a1, dy = b2 - b1;
  x = a1, y = b1;
  xend = a2/2;
  printP(x,y);
  incr2 = (dy << 2) - (dx << 1);

  if(impaire == 0) {
    int xmid = (a1+a2)/2, ymid = (b1+b2)/2;
      if(incr2 <= 0) {
      //c = 2 * dy;
      c = dy << 1;
      //incr1 = 2 * c;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 - dx;
      while(x < xend) {
        if(D < 0) {
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          printP(x,y);
          D += incr1;
          printP(xmid,ymid);
        }
        else if(D >= c) {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          //image[y*W+x] = 255;
          D += incr2;
        }
        else {
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          D += incr3;
        }
      }
    }
    else {
      //c = 2 *(dy - dx);
      c = (dy - dx) << 1;
      //incr1 = 2 * c;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 + dx;
      while(x < xend) {
        if(D >= 0) {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          D += incr1;
        }
        else if(D < c) {
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          D += incr2;
        }
        else {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          //celui la
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          printP(x,y);
          printP(xmid,ymid);
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          printP(x,y);
          printP(xmid,ymid);
          D += incr3;
        }
      }
    }
  }
  else {
    int yf = b2, xf = a2;
    printP(xf,yf);
    if(incr2 <= 0) {
      //c = 2 * dy;
      c = dy << 1;
      //incr1 = 2 * c;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 - dx;
      D2 = -D;
      while(x < xend) {
        if(D < 0) {
          ++x;
          printP(x,y);
          ++x;
          printP(x,y);
          D += incr1;
        }
        else if(D >= c) {
          ++x;
          ++y;
          printP(x,y);
          ++x;
          printP(x,y);
          //printP(x,y);
          D += incr2;
        }
        else {
          ++x;
          printP(x,y);
          ++x;
          ++y;
          printP(x,y);
          ++x;
          printP(x,y);
          D += incr3;
        }

        if(D2 >= 0) {
          --xf;
          printP(xf,yf);
          --xf;
          printP(xf,yf);
          D2 -= incr1;
        }
        else if(D2 < -c) {
          --xf;
          --yf;
          printP(xf,yf);
          --xf;
          printP(xf,yf);
          D2 -= incr2;
        }
        else {
          --xf;
          printP(xf,yf);
          --xf;
          --yf;
          printP(xf,yf);
          --xf;
          printP(xf,yf);
          D2 -= incr3;
        }
      }
    }
    else {
      c = (dy - dx) << 1;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 + dx;
      D2 = -D;
      while(x < xend) {
        if(D >= 0) {
          ++x;
          ++y;
          printP(x,y);
          ++x;
          ++y;
          printP(x,y);
          D += incr1;
        }
        else if(D < c) {
          ++x;
          printP(x,y);
          ++x;
          ++y;
          printP(x,y);
          D += incr2;
        }
        else {

          ++x;
          ++y;
          printP(x,y);
          ++x;
          printP(x,y);
          ++x;
          ++y;
          printP(x,y);
          D += incr3;
        }

        if(D2 < 0) {
          --xf;
          --yf;
          printP(xf,yf);
          --xf;
          --yf;
          printP(xf,yf);
          D2 -= incr1;
        }
        else if(D2 >= -c) {
          --xf;
          printP(xf,yf);
          --xf;
          --yf;
          printP(xf,yf);
          //image[y*W+x+1] = 255;
          D2 -= incr2;
        }
        else {
          --xf;
          --yf;
          //celui la
          printP(xf,yf);
          --xf;
          printP(xf,yf);
          --xf;
          --yf;
          printP(xf,yf);
          D2 -= incr3;
        }
      }
    }
  }
}

///L'algorithme améliorer pour le test de vitesse
void draw_step3UPTEST(int a1, int b1, int a2, int b2) {
  int dx, dy, incr1, incr2, incr3, D, D2, x, y, xend, c;
  int impaire = 0;
  ///On vérifie si une des coordonnées est impaire
  if (a2%2 != 0 || b2%2 != 0) {
    impaire = 1;
  }

  dx =a2 - a1, dy = b2 - b1;
  x = a1, y = b1;
  xend = a2/2;
  incr2 = (dy << 2) - (dx << 1);

  ///si les coordonnées sont paires alors on utilise le calcule du midpoint
  if(impaire == 0) {
    int xmid = (a1+a2)/2, ymid = (b1+b2)/2;
      if(incr2 <= 0) {
      c = dy << 1;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 - dx;
      while(x < xend) {
        if(D < 0) {
          ++x;
          ++xmid;
          ++x;
          ++xmid;
          D += incr1;
        }
        else if(D >= c) {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          ++x;
          ++xmid;
          D += incr2;
        }
        else {
          ++x;
          ++xmid;
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          ++x;
          ++xmid;
          D += incr3;
        }
      }
    }
    else {
      c = (dy - dx) << 1;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 + dx;
      while(x < xend) {
        if(D >= 0) {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          D += incr1;
        }
        else if(D < c) {
          ++x;
          ++xmid;
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          D += incr2;
        }
        else {
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          ++x;
          ++xmid;
          ++x;
          ++xmid;
          ++y;
          ++ymid;
          D += incr3;
        }
      }
    }
  }

  ///Sinon si au moins une est impaire alors on utilise le endpoint
  else {
    int yf = b2, xf = a2;
    if(incr2 <= 0) {
      c = dy << 1;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 - dx;
      D2 = -D;
      while(x < xend) {
        if(D < 0) {
          ++x;
          ++x;
          D += incr1;
        }
        else if(D >= c) {
          ++x;
          ++y;
          ++x;
          D += incr2;
        }
        else {
          ++x;
          ++x;
          ++y;
          ++x;
          D += incr3;
        }

        if(D2 >= 0) {
          --xf;
          --xf;
          D2 -= incr1;
        }
        else if(D2 < -c) {
          --xf;
          --yf;
          --xf;
          D2 -= incr2;
        }
        else {
          --xf;
          --xf;
          --yf;
          --xf;
          D2 -= incr3;
        }
      }
    }
    else {
      c = (dy - dx) << 1;
      incr1 = c << 1;
      incr3 = incr2 + c;
      D = incr1 + dx;
      D2 = -D;
      while(x < xend) {
        if(D >= 0) {
          ++x;
          ++y;
          ++x;
          ++y;
          D += incr1;
        }
        else if(D < c) {
          ++x;
          ++x;
          ++y;
          D += incr2;
        }
        else {

          ++x;
          ++y;
          ++x;
          ++x;
          ++y;
          D += incr3;
        }

        if(D2 < 0) {
          --xf;
          --yf;
          --xf;
          --yf;
          D2 -= incr1;
        }
        else if(D2 >= -c) {
          --xf;
          --xf;
          --yf;
          D2 -= incr2;
        }
        else {
          --xf;
          --yf;
          --xf;
          --xf;
          --yf;
          D2 -= incr3;
        }
      }
    }
  }
}
