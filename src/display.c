#include "header.h"



void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE], char color[], int **pieces[], int new_piece, int futur_piece, int new_orientation, int futur_orientation){
    int num = 0;
    
    printf("Voici votre grille :\n\n");
    printf(" A B C D E F G H I J\n");
    for(int i=0; i<TABSIZE; i++){
        for(int j=0; j<TABSIZE; j++){
            printf("|");
            //couleur("%d", color[i][j]);//change the color of piece 
            printf("%c", mytab[i][j]);
            couleur("0");//reset color
        }
        printf("|\n");
    }
}

void skip_lines(int a){
    for(int i=0; i<a; i++){
        printf("\n");
    }
}

// *(*(pieces[new_piece]+new_orientation)+nbr)