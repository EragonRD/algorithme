#include <unistd.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "image.h"

Image *image;
int windowWidth = 640;
int windowHeight = 480;

#define ESCAPE 27


void Keyboard(unsigned char key, int x, int y)  {
  switch(key){
  case ESCAPE :
    exit(0);
    break;
  default:
    fprintf(stderr, "Unused key\n");
  }
}

void Mouse(int button, int state, int x, int y) {

  switch(button){
  case GLUT_LEFT_BUTTON:
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  }
  glutPostRedisplay();
}

int Init(char *s) {

  image = (Image *) malloc(sizeof(Image));
  if (image == NULL) {
    fprintf(stderr, "Out of memory\n");
    return(-1);
  }
  if (ImageLoad_PPM(s, image)==-1)
	return(-1);
  printf("tailles %d %d\n",(int) image->sizeX, (int) image->sizeY);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);

  return (0);
}
int ReInit() {
  /*
  if (ImageLoad_PPM(s, image)==-1)
	return(-1);
  */
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);

  return (0);
}

void Display(void) {

  GLint w, h;

  glClear(GL_COLOR_BUFFER_BIT);

  w = glutGet(GLUT_WINDOW_WIDTH);
  h = glutGet(GLUT_WINDOW_HEIGHT);
  glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
	       image->data);

  glFlush();
}

///nouvelle fonction de display
void displayV2(void) {

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
  glColor3f(1,0,0);
}

void Reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void menuFunc(int item) {
  char s[256];
  int setWidth = windowWidth;
  int setHeight = windowHeight;
  switch(item){
  case 0:
    exit(0);
    break;
  case 1:
    //displayV2();
    glClear(GL_COLOR_BUFFER_BIT);
    //draw_brVue(setWidth,setHeight);
    break;
  case 2:
    glColor3f(0,0,1 ); // on a la couleur bleu
    draw_step3UP(0,0,setWidth, setHeight);
    //glClear(GL_COLOR_BUFFER_BIT);
    break;
  case 3:
    glColor3f(1,0,0);  // on a la couleur rouge
    draw_step3Vue(0,0,setWidth, setHeight);
    break;
  default:
    break;
  }
}

int main(int argc, char **argv) {


  if(argc == 1) {
    printf("trop peu  d'argument\n");
    return 0;
  }
  if(argc >= 2) {
    if(strcmp(argv[1], "VIT") == 0) {
      if(argc < 4) {
        printf("les coordonnées non pas été fournie\n");
        return;
      }
      printf("Mode vitesse\n");
      //int xCord = 1920, yCord = 1079;
      int xCord = atoi(argv[2]), yCord = atoi(argv[3]);
      int looping = 1000000;
      clock_t brtime = clock();
      for(int i = 0; i < looping; i++) {
        draw_br(xCord, yCord);
      }
      brtime = clock() - brtime;
      printf(" %f seconds br algo time\n", (float) brtime/CLOCKS_PER_SEC);

      clock_t steptime = clock();
      for(int i = 0; i < looping; i++) {
        draw_step3(0, 0, xCord, yCord);
      }


      clock_t upgradetime = clock();
      for(int i = 0; i < looping; i++) {
        draw_step3UPTEST(0,0,xCord,yCord);
      }
      upgradetime = clock() - upgradetime;
      printf(" %f seconds bresenham upgraded algo time\n", (float) upgradetime/CLOCKS_PER_SEC);

      clock_t PLStime = clock();
      for(int i = 0; i < looping; i++) {
        draw_line_calling(0,0, xCord, yCord);
      }


    }


    else if(strcmp(argv[1], "DRAW") == 0) {
      printf("Mode dessine\n");
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
        glutInitWindowSize(windowWidth,windowHeight);
        glutInitWindowPosition(100, 100);
        int win = glutCreateWindow("DrawLine");

        //glutDisplayFunc(displayV2);
        glutCreateMenu(menuFunc);
        glutAddMenuEntry("Quit", 0);
        glutAddMenuEntry("Clear", 1);
        glutAddMenuEntry("bresenham", 2);
        glutAddMenuEntry("upgrade", 3);

        //glutAddMenuEntry("Clear", 1)
        glutAttachMenu(GLUT_LEFT_BUTTON);
        glutDisplayFunc(displayV2);
        glutMainLoop();
    }
    else if(strcmp(argv[1], "M") == 0) {
      printf("memory mode\n");
      ptrdiff_t diff;
      char * neww, *renew;
      int looping = 10000;


      neww =(char*) malloc(sizeof(char));
      for(int i = 0; i < looping; i++) {
        draw_br(640,480);
      }
      renew =(char*) malloc(sizeof(char));
      diff = renew - neww;
      printf("%td br algo memory \n", diff);

      neww =(char*) malloc(sizeof(char));
      for(int i = 0; i < looping; i++) {
        draw_step3(0, 0, 640,480);
      }


      neww =(char*) malloc(sizeof(char));
      for(int i = 0; i < looping; i++) {
        draw_step3UPTEST(0,0,1920,1080);
      }

    }
    else {
      printf("Mode non existant\n");
      return 0;
    }
  }

  return 1;
}
