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
#define CTE4 4
#define CTE7 7
#define CTE16 16



void disptab(char mytab[TABSIZE][TABSIZE]);
void skip_lines(int a);
unsigned long getTimeMicroSec();
void init(char mytab[TABSIZE][TABSIZE], char a);
void move(char mytab[TABSIZE][TABSIZE], int ligne);
char* add(char tab[], char tab2[]);
int*** getpieces();
void cpy(int tab1[], int tab2[], int size);
void cpy1(int *tab1[], int *tab2[], int size);