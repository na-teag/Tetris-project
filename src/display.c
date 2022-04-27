#include "header.h"



void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE], char color[], int **pieces[], int new_piece, int futur_piece){
    int orientation = 0;
    int answer1 = 0;
    char answer_txt[CTE200];
    char answer2 = '1';
    skip_lines(40);
    printf("Voici votre grille :\n\n");
    printf(" A B C D E F G H I J\n");
    for(int i=0; i<TABSIZE; i++){
        for(int j=0; j<TABSIZE; j++){
            printf("|");
            changecolor(mytab_color[i][j]);//change the color of piece 
            printf("%c", mytab[i][j]);
            couleur("0");//reset color
        }
        printf("\n");
    }
    printf("|\n A B C D E F G H I J\n");
    if(new_piece != 1){ // if the piece is the square, there is no need to choose the orientation
        printf("\nChoisissez l'orientation de la piece :\n1    \t2    \t3    \t4\n");
    }else{
        printf("Voici la piece :\n");
    }
    for(int i=0; i<CTE4; i++){
        if(new_piece != 0 && new_piece != 1){
            for(int j=0; j<CTE4; j++){
                for(int k=0; k<CTE4; k++){
                    printf("%c", *(*(pieces[new_piece]+j)+(CTE4*i)+k)); // piece[line][column] = *(*(pieces[new_piece]+new_orientation)+(4*line)+column)
                }
                printf("\t");
            }
        }else if(new_piece == 1){ // if the piece is the stick there is only two possible choice, so we do it in an other printf
            for(int j=0; j<CTE2; j++){
                for(int k=0; k<CTE4; k++){
                    printf("%c", *(*(pieces[new_piece]+j)+(CTE4*i)+k)); // piece[line][column] = *(*(pieces[new_piece]+new_orientation)+(4*line)+column)
                }
                printf("\t");
            }
        }else{ // if the piece is a square, we only need to print the piece once
            for(int k=0; k<CTE4; k++){
                printf("%c", *(*(pieces[new_piece])+(CTE4*i)+k)); // piece[line][column] = *(*(pieces[new_piece]+new_orientation)+(4*line)+column)
            }
        }
        printf("\n");
    }
    if(new_piece != 1){
        scanf("%s", answer_txt);
        while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3' || answer_txt[0] == '4')){
            printf("\nVeuillez entrer uniquement 1, 2, 3 ou 4 comme reponse.\nChoisissez l'orientation de la piece : ");
            scanf("%s", answer_txt);
        }
        answer2 = answer_txt[0];
        printf("%c %d %d ", answer2, atoi(&answer2), atoi("4"));
        orientation = (atoi(&answer2)%10)%5;
    }else{
        orientation = 0; // if the piece is a square, the four recorded orientations are the same, the number doesn't matter (it still need to be 1 2 3 or 4, of course)
    }
    printf("%d", orientation);
    printf("Entrez la colonne dans laquelle vous souhaitez faire tomber la piece : ");
    scanf("%s", answer_txt);
    while(!(answer_txt[0] == 'A' || answer_txt[0] == 'B' || answer_txt[0] == 'C' || answer_txt[0] == 'D' || answer_txt[0] == 'E' || answer_txt[0] == 'F' || answer_txt[0] == 'G' || answer_txt[0] == 'H' || answer_txt[0] == 'I' || answer_txt[0] == 'J' || answer_txt[0] == 'a' || answer_txt[0] == 'b' || answer_txt[0] == 'c' || answer_txt[0] == 'd' || answer_txt[0] == 'e' || answer_txt[0] == 'f' || answer_txt[0] == 'g' || answer_txt[0] == 'h' || answer_txt[0] == 'i' || answer_txt[0] == 'j')){
        printf("\nVeuillez entrer uniquement A, B, C, D, E, F, G, H ou J comme reponse.\nEntrez la colonne dans laquelle vous souhaitez faire tomber la piece : ");
        scanf("%s", answer_txt);
    }
    answer1 = answer_txt[0];
    if(answer1 > 90){
        answer1 = answer1 - 97;// 97 = 'a'
    }else{
        answer1 = answer1 - 65;// 65 = 'A'
    }
    //printf("%d", answer1);
}

void skip_lines(int a){
    for(int i=0; i<a; i++){
        printf("\n");
    }
}

