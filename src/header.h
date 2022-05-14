#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include "color.h"
#define TABSIZE 10
#define CTE2 2
#define CTE3 3
#define CTE4 4
#define CTE7 7
#define CTE10 10
#define CTE16 16
#define CTE200 200



void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE]);
void ask(int **pieces[], int new_piece, int futur_piece, int *column, int *line);
void skip_lines(int a);
unsigned long getTimeMicroSec();
void init(char mytab[TABSIZE][TABSIZE], char a);
void move(char tab[TABSIZE][TABSIZE], char color[TABSIZE][TABSIZE], int ligne);
char* add(char tab[], char tab2[]);
int*** getpieces();
void cpy(int tab1[], int tab2[], int size);
void cpy1(int *tab1[], int *tab2[], int size);
int changecolor(int color);
int horizontalsize(int new_piece, int orientation, int **piece[]);
int verticalsize(int new_piece, int new_orientation, int **pieces[]);
void update_tab(int **pieces[CTE16],char mytab[TABSIZE][TABSIZE], char mytab_color[TABSIZE][TABSIZE], int column, int new_orientation, int new_piece);