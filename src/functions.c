#include "header.h"

void init(char tab[TABSIZE][TABSIZE], char a){ // initialize all the table's cell to a typeface 'a'
    for(int i=0; i<TABSIZE; i++){
        for(int j=0; j<TABSIZE; j++){
            tab[i][j] = a;
        }
    }
}

void move(char tab[TABSIZE][TABSIZE], char color[TABSIZE][TABSIZE], int ligne){ // move the lines of the game table when one is completed
    for(int i=ligne; i<TABSIZE-1; i++){
        for(int j=0; j<TABSIZE; j++){
            tab[i][j] = tab[i+1][j];
            color[i][j] = color[i+1][j];
        }
    }
    for(int i=0; i<TABSIZE; i++){
        tab[TABSIZE][i] = ' ';
        color[TABSIZE][i] = 0;
    }
}

unsigned long getTimeMicroSec(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec) + tv.tv_usec;
}

char* add(char tab[], char tab2[]){ // put two character strings together
    char* tab3 = NULL;
    tab3 = malloc(strlen(tab)*sizeof(char)+strlen(tab2)*sizeof(char)+1);
    if(tab3 == NULL){
        printf("erreur d'allocution");
        exit(1);
    }
    for(int i=0; i<strlen(tab); i++){
        tab3[i] = tab[i];
    }
    for(int i=0; i<strlen(tab2); i++){
        tab3[i+strlen(tab)] = tab2[i];
    }
    tab3[strlen(tab)+strlen(tab2)+1] = '\0';
    return tab3;
}

void cpy(int tab1[], int tab2[], int size){
    for(int i=0; i<size; i++){
        tab2[i] = tab1[i];
    }
}
void cpy1(int *tab1[], int *tab2[], int size){
    for(int i=0; i<size; i++){
        tab2[i] = tab1[i];
    }
}
