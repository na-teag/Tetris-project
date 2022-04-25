#include "header.h"



void disptab(char mytab[TABSIZE][TABSIZE]){
    printf("Voici votre grille :\n\n");
    printf(" A B C D E F G H I J\n");
    for(int i=0; i<TABSIZE; i++){
        for(int j=0; j<TABSIZE; j++){
            printf("|");
            printf("%c", mytab[i][j]);
        }
        printf("|\n");
        //if(i == )
    }
}

void skip_lines(int a){
    for(int i=0; i<a; i++){
        printf("\n");
    }
}
