#include "header.h"



void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE], int score, int **pieces[], int futur_piece){
    skip_lines(40);
    for(int i=0; i<CTE16; i++){
        printf("%d", *(*(pieces[futur_piece]+0)+i));
    }
    printf("\n");
    printf("Voici votre grille :\n\t\t\t\t\t\tscore : %d\n", score);
    printf("\t A B C D E F G H I J\n\t");
    for(int i=TABSIZE-1; i>=0; i--){ // the (0;0) cell is at the left corner of the bottom
        for(int j=0; j<TABSIZE; j++){
            printf("|");
            changecolor(mytab_color[i][j]);//change the color of piece 
            printf("%c", mytab[i][j]);
            couleur("0");//reset color
        }
        printf("|i=%d", i);
        if(i == 5){//posting the futur piece
            printf("\t\tfuture piece :");
        }else if(0 <= i && i<=3){
            printf("\t\t   ");
            for(int j=0; j<CTE4; j++){
                if(*(*(pieces[futur_piece]+0)+(4*(3-i))+j) == 1){//*(*(pieces[new_piece]+orientation)+(4*line)+column)
                    printf("@ ");
                }else{
                    printf("  ");
                }
            }
        }
        printf("\n\t");
    }
    printf(" A B C D E F G H I J\n");
}


void skip_lines(int a){
    for(int i=0; i<a; i++){
        printf("\n");
    }
}

int ask(int **pieces[], int new_piece, int *column, int *orientation){
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
                    if(*(*(pieces[new_piece]+j)+(4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
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
                    if(*(*(pieces[new_piece]+j)+(4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
                        printf("@ ");
                    }else{
                        printf("  ");
                    }
                }
                printf("\t");
            }
        }else{ // if the piece is a square, we only need to print the piece once
            for(int k=0; k<CTE4; k++){
                if(*(*(pieces[new_piece])+(4*i)+k) == 1){// piece = *(*(pieces[new_piece]+orientation)+(4*line)+column)
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
        *orientation = 1; // if the piece is a square, the four recorded orientations are the same, the number doesn't matter (it still need to be 1 2 3 or 4, of course)
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
        if(answer_txt[0] == 'a' && answer_txt[1] == 'd' && answer_txt[2] == 'm' && answer_txt[3] == 'i' && answer_txt[4] == 'n'){
            return 0;
        }
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
    return 1;
}




Setting setting(Setting set, int color[TABSIZE]){
    char answer_txt[CTE200];
    int done = 0;
    while(done == 0){
    skip_lines(5);
    do{
        printf("\n\n -- Parametres -- ");
        printf("\n\n 1 - Modifier la difficulte");
        if(set.difficulty_progressive == 1){
            printf("\n 2 - desactiver la difficulte progressive");
        }else{
            printf("\n 2 - activer la difficulte progressive");
        }
        printf("\n 3 - Changer la langue");
        printf("\n 4 - Informer d'un changement de couleur d'arriere plan");
        printf("\n 5 - Retour\n\n");
        scanf("%s", answer_txt);
    }while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3' || answer_txt[0] == '4' || answer_txt[0] == '5'));
        
    
    switch(answer_txt[0]){
        case '1':
            do{
                printf("\n\nEntrez le niveau de difficulté sur une échelle de 1 a 3, ou bien 0 pour ");
                if(1 == 1){
                    printf("des"); 
                }
                printf("activer le minuteur : ");
                scanf("%s", answer_txt);
            }while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3' || answer_txt[0] == '0'));
            set.difficulty = answer_txt[0]-48;
            break;
        case '2':
            if(set.difficulty_progressive == 1){
                set.difficulty_progressive = 0;
            }else{
                set.difficulty_progressive = 1;
            }
            break;
        case '3':
            if(set.language == 1){
                set.language = 2;
            }else{
                set.language = 1;
            }
            break;
        case '4':
            printf("Quelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
            scanf("%s", answer_txt);
            while(!(answer_txt[0] == '1' || answer_txt[0] == '2')){
                printf("\nVeuillez entrer uniquement 1 ou 2 comme reponse. \n\nQuelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
                scanf("%s", answer_txt);
            }
            if(answer_txt[0] == '2'){
                color[4] = 37;
            }else{
                color[4] = 34;
            }
            break;
        case '5':
            done = 1;
            break;
        default:
            exit(1);
            break;
    }
    }
    return set;
}




void music(){
    char answer_txt[CTE200];   
    do{
        printf("\nQuelle musique souhaitez vous ouvrir dans le navigateur ?\n\n 1 - Musique Tetris original\n 2 - Musique Tetris 99\n 3 - Retour\n\n");
        scanf("%s", answer_txt);
    }while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3'));
    if(answer_txt[0] == '1'){
        system("firefox --new-tab https://www.youtube.com/watch?v=9Fv5cuYZFC0 &");
    }else if(answer_txt[0] == '2'){
        system("firefox --new-tab https://www.youtube.com/watch?v=lMJvDi0KNlM &");
    }
}

void tutoriel(){

}
