#include "header.h"

//this file contains all the functions that write text

void disptab(char mytab[TABSIZE][TABSIZE],char mytab_color[TABSIZE][TABSIZE], int score, int **pieces[], int futur_piece, int color[]){
    clear_screen();
    printf("f:%d\n", futur_piece);
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
            printf("\t\tfuture pièce :");
        }else if(0 <= i && i<=3){
            printf("\t\t   ");
            for(int j=0; j<CTE4; j++){
                changecolor(color[futur_piece]);
                if(*(*(pieces[futur_piece]+0)+(4*(3-i))+j) == 1){//*(*(pieces[new_piece]+orientation)+(4*line)+column)
                    printf("@ ");
                }else{
                    printf("  ");
                }
                couleur("0");
            }
        }
        printf("\n\t");
    }
    printf(" A B C D E F G H I J\n");
}


void skip_lines(int a){//skip 'a' lines
    for(int i=0; i<a; i++){
        printf("\n");
    }
}

void clear_screen(){//clear the screen and write the text 10 line below
    clrscr();
    skip_lines(10);
}

int ask(int **pieces[], int new_piece, int *column, int *orientation, Setting set, int color[]){//ask for the player to write the orientation and the placement of the piece
    *orientation = 0;
    int answer1 = 0;
    int test = 0;
    int scanf_res = 0;
    int answer = 0;
    char answer_txt[CTE200];
    char answer2 = '1';
    unsigned long time, time_end;
    //new_piece = 6;
    printf("p:%d\n", new_piece);
    if(new_piece == 2 || new_piece == 3 || new_piece == 4){ // if the piece is the square for exemple, there is no need to choose the orientation
        printf("\nChoisissez l'orientation de la pièce : (%d)\n1        \t2        \t3        \t4\n", new_piece);
    }else if(new_piece == 0 || new_piece == 5 || new_piece == 6){
        printf("\nChoisissez l'orientation de la pièce :\n1        \t2\n");//segment fault
    }else{
        printf("\nVoici la piece : \n");
    }

    //this part print the differents possiblities of the orientation
    changecolor(color[new_piece]);
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
    couleur("0");
    time = getTimeMicroSec();

    //this part ask the player to chose an orientation
    if(new_piece != 1){
        scanf_res=scanf("%d", &answer);
        while(getc(stdin) != '\n');
        while(!(answer == 1 || answer == 2 || answer == 3 || answer == 4) || scanf_res == 0){
            printf("\nVeuillez entrer uniquement 1, 2, 3 ou 4 comme reponse.\nChoisissez l'orientation de la pièce : ");
            scanf_res=scanf("%d", &answer);
            while(getc(stdin) != '\n');
        }
        *orientation = answer;
    }else{
        *orientation = 1; // if the piece is a square, the four recorded orientations are the same, the number doesn't matter (it still need to be 1 2 3 or 4, of course)
    }
    printf("or=%d", *orientation);



    //this part ask the player to chose a column
    test = -1;
    while(test != 1){ //this loop check if the chosen column is OK regarding the array
        if(test == -1){
            printf("Entrez la colonne dans laquelle vous souhaitez mettre la piece : ");
        }else{
            printf("La piece est trop grande pour pouvoir être mise dans cette colonne.\nEntrez la colonne dans laquelle vous souhaitez mettre la pièce : ");
        }
        scanf_res=scanf("%s", answer_txt);
        while(getc(stdin) != '\n');
        if(answer_txt[0] == 'a' && answer_txt[1] == 'd' && answer_txt[2] == 'm' && answer_txt[3] == 'i' && answer_txt[4] == 'n'){
            return 0;
        }
        while(!(answer_txt[0] == 'A' || answer_txt[0] == 'B' || answer_txt[0] == 'C' || answer_txt[0] == 'D' || answer_txt[0] == 'E' || answer_txt[0] == 'F' || answer_txt[0] == 'G' || answer_txt[0] == 'H' || answer_txt[0] == 'I' || answer_txt[0] == 'J' || answer_txt[0] == 'a' || answer_txt[0] == 'b' || answer_txt[0] == 'c' || answer_txt[0] == 'd' || answer_txt[0] == 'e' || answer_txt[0] == 'f' || answer_txt[0] == 'g' || answer_txt[0] == 'h' || answer_txt[0] == 'i' || answer_txt[0] == 'j') || scanf_res == 0){
            printf("\nVeuillez entrer uniquement A, B, C, D, E, F, G, H ou J comme reponse.\nEntrez la colonne dans laquelle vous souhaitez faire tomber la pièce : ");
            scanf_res=scanf("%s", answer_txt);
            while(getc(stdin) != '\n');
        }
        answer1 = answer_txt[0];
        if(answer1 > 90){
            answer1 = answer1 - 97;// 97 = 'a'
        }else{
            answer1 = answer1 - 65;// 65 = 'A'
        }
        if(horizontalsize(new_piece, *orientation-1, pieces) + answer1 <= CTE10){// the column number + the size of the piece musn't be higher than the size of the array
            test = 1;
        }else{
            test = 0;
        }
        //printf("%d + %d", horizontalsize(new_piece, *orientation, pieces), answer1);
    }
    time_end = getTimeMicroSec();
    time = (time_end - time)/1000000;
    if(set.difficulty != 0){
        if((float)time>set.time){
            *orientation = 1;
            *column = 4;
            printf("\nTemps ecoulé !");
            fflush(stdout);
            sleep(4);
            return 1;
        }
    }
    *column=answer1;
    return 1;
}




Setting setting(Setting set, int color[TABSIZE], const char tetris[]){//set the parameters
    char answer_txt[CTE200];
    int answer = 0;
    int scanf_res = 0;
    int done = 0;
    while(done == 0){
    
    do{
        clear_screen();
        changecolor(34);
        printf("%s", tetris);
        couleur("0");
        printf("\n\n ----- Paramètres ----- ");
        printf("\n\n 1 - Modifier la difficulte");
        if(set.difficulty != 0){
            printf("\n 2 - Désactiver le timer");
        }else{
            printf("\n 2 - Activer le timer");
        }
        if(set.difficulty_progressive == 1){
            printf("\n 3 - Désactiver la difficulte progressive");
        }else{
            printf("\n 3 - Activer la difficulte progressive");
        }
        printf("\n 4 - Informer d'un changement de couleur d'arrière plan");
        printf("\n 5 - Retour\n\n");
        scanf_res=scanf("%d", &answer);
        while(getc(stdin) != '\n');
    }while(!(answer == 1 || answer == 2 || answer == 3 || answer == 4 || answer == 5) || scanf_res == 0);
        
    
    switch(answer){
        case 1:
            clear_screen();
            changecolor(34);
            printf("%s", tetris);
            couleur("0");
            do{
                printf("\n\nChoisissez le mode de difficulté :\n\n 1 - Facile\n 2 - Normal\n 3 - Difficile\n\n");
                scanf_res=scanf("%d", &answer);
                while(getc(stdin) != '\n');
            }while(!(answer == 1 || answer == 2 || answer == 3) || scanf_res == 0);
            set.difficulty = answer_txt[0]-48;
            set.time = 25 - set.difficulty*5;
            break;
        case 2:
                if(set.difficulty == 0){
                    set.difficulty = 1;
                }else{
                    set.difficulty = 0;
                }
            break;
        case 3:
            if(set.difficulty_progressive == 1){
                set.difficulty_progressive = 0;
            }else{
                set.difficulty_progressive = 1;
            }
            break;
        case 4:
            printf("Quelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
            scanf_res=scanf("%d", &answer);
            while(getc(stdin) != '\n');
            while(!(answer == 1 || answer == 2) || scanf_res == 0){
                printf("\nVeuillez entrer uniquement 1 ou 2 comme reponse. \n\nQuelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
                scanf_res=scanf("%d", &answer);
                while(getc(stdin) != '\n');
            }
            if(answer == 2){
                color[4] = 37;
            }else{
                color[4] = 30;
            }
            break;
        case 5:
            done = 1;
            break;
        default:
            exit(1);
            break;
    }
    }
    return set;
}




void music(const char tetris[]){// open youtube to listen tetris music
    int scanf_res = 0;
    int answer = 0;
    clear_screen();
    changecolor(34);
    printf("%s", tetris);
    couleur("0");
    skip_lines(2);
    printf(" ----- Musiques -----");
    skip_lines(2);  
    do{
        printf("\nQuelle musique souhaitez vous ouvrir dans le navigateur ?\n\n 1 - Musique Tetris original\n 2 - Musique Tetris 99\n 3 - Retour\n\n");
        scanf_res=scanf("%d", &answer);
        while(getc(stdin) != '\n');
    }while(!(answer == 1 || answer == 2 || answer == 3) || scanf_res == 0);
    if(answer == 1){
        system("firefox --new-tab https://www.youtube.com/watch?v=9Fv5cuYZFC0 &");
    }else if(answer == 2){
        system("firefox --new-tab https://www.youtube.com/watch?v=lMJvDi0KNlM &");
    }
}

void scoring(Player tab_players[], const char tetris[]){// show the scores record
    char answer[CTE200];
    clear_screen();
    changecolor(34);
    printf("%s", tetris);
    couleur("0");
    skip_lines(2);
    printf(" ----- Tableau des scores -----");
    skip_lines(2);
    for(int i=0; i<10; i++){
        printf("\n%s\t: niveau %d\tscore %d", tab_players[i].pseudo, tab_players[i].level, tab_players[i].score);
    }
    printf("\n\nAppuyez sur une touche puis Entrer pour quitter\n");
    scanf("%s", answer);
    while(getc(stdin) != '\n');
    skip_lines(10);
}

void show_rules(const char tetris[]){//show the rules of the scoring
    char answer[CTE200];
    clear_screen();
    changecolor(34);
    printf("%s", tetris);
    couleur("0");
    skip_lines(2);
    printf(" ----- Règles des scores ----- ");
    skip_lines(2);
    printf("\n  +10 points pour chaque pièce posée.");
    printf("\n  +40 points si vous terminez une ligne.");
    printf("\n  +100 points si vous terminez deux lignes en même temps.");
    printf("\n  +400 points si vous terminez trois lignes en même temps.");
    printf("\n  +1200 points si vous terminez quatre lignes en même temps.");
    printf("\n\n  Multiplicateurs de score :");
    printf("\n\n  Mode facile : x0.5");
    printf("\n  Mode normmal: x1");
    printf("\n  Mode difficile : x1.5");
    printf("\n  Mode difficulté progressive : x2");
    printf("\n  Mode temps illimité : x0.2");
    printf("\n\nAppuyez sur une touche puis Entrer pour quitter.\n");
    scanf("%s", answer);
    while(getc(stdin) != '\n');
}
