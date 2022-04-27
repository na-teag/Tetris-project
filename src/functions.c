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


int changecolor(int color){
    if(color == 30){
        couleur("30");
        return 0;
    }
    if(color == 31){
        couleur("31");
        return 0;
    }
    if(color == 32){
        couleur("32");
        return 0;
    }
    if(color == 33){
        couleur("33");
        return 0;
    }
    if(color == 34){
        couleur("34");
        return 0;
    }
    if(color == 35){
        couleur("35");
        return 0;
    }
    if(color == 36){
        couleur("36");
        return 0;
    }
    if(color == 37){
        couleur("37");
        return 0;
    }
    return 0;
}

int horizontalsize(int new_piece, int orientation, int **pieces[]){// calcul of the horizontal size of a piece
    int nbr = 0;
    int nbr2 = 0;
    orientation--;// if the player enter 1, it's equivalent to the 0th for the prgm
    for(int i=0; i<CTE4; i++){
        nbr = 0;
        for(int j=0; j<CTE4; j++){
            nbr += *(*(pieces[new_piece]+orientation)+(4*j)+i);// check each column, to see if they contain something
        }
        if(nbr != 0){
            nbr2++;
        }
    }
    return nbr2;
}

void update_tab(int **pieces[CTE7],char mytab[TABSIZE][TABSIZE], char mytab_color[TABSIZE][TABSIZE], int new_piece, int new_orientation){

}