#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <curses.h>
#include "color.h"
#define TABSIZE 10
#define NBPLAYR 10 
#define CTE2 2
#define CTE3 3
#define CTE4 4
#define CTE7 7
#define CTE10 10
#define CTE16 16
#define CTE200 200

typedef struct{
    int difficulty;
    int difficulty_progressive;
    float time;
}Setting;

typedef struct{
    char pseudo[CTE16];
    int level;
    int score;
}Player;

void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE], int score, int **pieces[], int futur_piece, int color[]);
int ask(int **pieces[], int new_piece, int *column, int *line, Setting set, int color[]);
void skip_lines(int a);
unsigned long getTimeMicroSec();
void init(char mytab[TABSIZE][TABSIZE], char a);
void move_lines(char tab[TABSIZE][TABSIZE], char tab_color[TABSIZE][TABSIZE], int color[CTE7], int ligne);
char* add(char tab[], char tab2[]);
int*** getpieces();
void cpy(int tab1[], int tab2[], int size);
void cpy1(int *tab1[], int *tab2[], int size);
int changecolor(int color);
int horizontalsize(int new_piece, int orientation, int **piece[]);
void verticalsize(int new_piece, int new_orientation, int **pieces[], int tab[]);
void update_tab(int **pieces[], char mytab[TABSIZE][TABSIZE], char mytab_color[TABSIZE][TABSIZE],int color[CTE7], int column, int new_orientation, int new_piece, Player *player, int *gameover, Setting set);
int addscore(int level, int nbline, Setting set);
Setting setting(Setting set, int color[TABSIZE], const char tetris[]);
void music(const char tetris[]);
void tutorial(int color, const char tetris[]);
void setdifficulty();
void sort(Player tab_players[], int size);
void update_tab_player(Player tab_players[], Player player);
void scoring(Player tab[], const char tetris[]);
void clear_screen();
void show_rules(const char tetris[]);
void beta(const char tetris[]);