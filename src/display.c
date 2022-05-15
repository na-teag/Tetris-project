#include "header.h"



void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE]){
    skip_lines(40);
    printf("Voici votre grille :\n\n");
    printf("\t A B C D E F G H I J\n\t");
    for(int i=TABSIZE-1; i>=0; i--){ // the (0;0) cell is at the left corner of the bottom
        for(int j=0; j<TABSIZE; j++){
            printf("|");
            changecolor(mytab_color[i][j]);//change the color of piece 
            printf("%c", mytab[i][j]);
            couleur("0");//reset color
        }
        printf("|i=%d\n\t", i);
    }
    printf(" A B C D E F G H I J\n");
}

void ask(int **pieces[], int new_piece, int futur_piece, int *column, int *orientation){
    *orientation = 0;
    int answer1 = 0;
    int test = 0;
    char answer_txt[CTE200];
    char answer2 = '1';

    printf("%d", new_piece);

    if(new_piece == 2 || new_piece == 3 || new_piece == 4){ // if the piece is the square for exemple, there is no need to choose the orientation
        printf("\nChoisissez l'orientation de la piece : (%d)\n1        \t2        \t3        \t4\n", new_piece);
    }else if(new_piece == 0 || new_piece == 5 || new_piece == 6){
        printf("\nChoisissez l'orientation de la piece :\n1        \t2\n");
    }else{
        printf("\nVoici la piece : \n");
    }

    //this part print the differents possiblities of the orientation 
    for(int i=0; i<CTE4; i++){
        if(new_piece == 2 || new_piece == 3 || new_piece == 4){
            for(int j=0; j<CTE4; j++){
                for(int k=0; k<CTE4; k++){
                    if(*(*(pieces[new_piece]+j)+(CTE4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
                        printf("@ ");
                    }else{
                        printf("  ");
                    }
                }
                printf("\t");
            }
        }else if(new_piece == 0 || new_piece == 5 || new_piece == 6){ // if the piece is the stick there is only two possible choice, so we do it in an other printf
            for(int j=0; j<CTE2; j++){
                for(int k=0; k<CTE4; k++){
                    if(*(*(pieces[new_piece]+j)+(CTE4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
                        printf("@ ");
                    }else{
                        printf("  ");
                    }
                }
                printf("\t");
            }
        }else{ // if the piece is a square, we only need to print the piece once
            for(int k=0; k<CTE4; k++){
                if(*(*(pieces[new_piece])+(CTE4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
                        printf("@ ");
                    }else{
                        printf("  ");
                    }
            }
        }
        printf("\n");
    }


    //this part ask the player to chose an orientation
    if(new_piece != 1){
        scanf("%s", answer_txt);
        while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3' || answer_txt[0] == '4')){
            printf("\nVeuillez entrer uniquement 1, 2, 3 ou 4 comme reponse.\nChoisissez l'orientation de la piece : ");
            scanf("%s", answer_txt);
        }
        answer2 = answer_txt[0];
        *orientation = answer2 - 48;// 48 = '1'
    }else{
        *orientation = 0; // if the piece is a square, the four recorded orientations are the same, the number doesn't matter (it still need to be 1 2 3 or 4, of course)
    }
    printf("or=%d", *orientation);



    //this part ask the player to chose a column
    test = -1;
    while(test != 1){ //this loop check if the chosen column is OK regarding the table
        if(test == -1){
            printf("Entrez la colonne dans laquelle vous souhaitez mettre la piece : ");
        }else{
            printf("La piece est trop grande pour pouvoir etre mise dans cette colonne.\nEntrez la colonne dans laquelle vous souhaitez mettre la piece : ");
        }
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
        if(horizontalsize(new_piece, *orientation-1, pieces) + answer1 <= CTE10){// the column number + the size of the piece musn't be higher than the size of the table
            test = 1;
        }else{
            test = 0;
        }
        //printf("%d + %d", horizontalsize(new_piece, *orientation, pieces), answer1);
    }
    *column=answer1;
}

void skip_lines(int a){
    for(int i=0; i<a; i++){
        printf("\n");
    }
}
