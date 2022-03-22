#  Makefile
#  Auteur : Debbah Rabah
#  Email  : debbah.rabah.amir@gmail.comments
#  Date   : 4 janvier 2022


#  Université Paris VIII

SHELL = /bin/sh
#definition des commandes utilisees
CC = gcc
MACHINE= $(shell uname -s)
#declaration des options du compilateur
#PG_FLAGS = -DOPENGL_1_5

ifeq ($(MACHINE), Darwin)
GL_LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
else
GL_LDFLAGS = -lGL -lglut -lGLU
endif

CFLAGS = -Wall
LDFLAGS = -lm $(GL_LDFLAGS)
#definition des fichiers et dossiers
PROGNAME = test
HEADERS = image.h
SOURCES = main.c Print.c modif.c

OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*
