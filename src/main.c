#include "header.h"


int main(){
    //file part
    FILE* datafile = NULL;
    char filename[] = {"datas"};
    char path[] = {"../src/"};              //the file's name and the path are separated to use the file's name if there is an error
    char* pathtofile = add(path, filename);
    datafile = fopen(pathtofile, "r");
    if(datafile == NULL){
        printf("\n%s in %s, error %d : %s \n\n", filename, pathtofile, errno, strerror(errno));
        exit(1);
    }

    //declaration part

    srand(time(NULL));

    int end = 0;
    int game = 0;
    int gameover = 0;
    int answer = 0;
    int new_piece = 0;
    int new_orientation = 0;
    int futur_piece = 0;
    int test = 0;
    int admin = 0;
    int column = 0;
    int modif_file = 0;

        //this part is for the "tetriminos.c" file
    int I1[CTE16], I2[CTE16], O1[CTE16], T1[CTE16], T2[CTE16], T3[CTE16], T4[CTE16], L1[CTE16], L2[CTE16], L3[CTE16], L4[CTE16], J1[CTE16], J2[CTE16], J3[CTE16], J4[CTE16], Z1[CTE16], Z2[CTE16], S1[CTE16], S2[CTE16];
    int *I[CTE4], *O[CTE4], *T[CTE4], *L[CTE4], *J[CTE4], *Z[CTE4], *S[CTE4];
    int **pieces[CTE7];
    getpieces(&I1, &I2, &O1, &T1, &T2, &T3, &T4, &L1, &L2, &L3, &L4, &J1, &J2, &J3, &J4, &Z1, &Z2, &S1, &S2, &I, &O, &T, &L, &J, &Z, &S, &pieces);
    Player tab_players[10];

        //this part is for the game tables.
    char mytab[TABSIZE][TABSIZE];
    char mytab_color[TABSIZE][TABSIZE];
    char answer_txt[CTE200];
    int color[CTE7] = {36, 33, 35, 30, 34 ,31, 32};//color of the pieces. see "color.h"

    init(mytab, ' ');
    init(mytab_color, 48); // 48 = '0' (reset color)

    const char tetris[] =  {"\t _______ _______ _______ ______  _  ______ \n\t(_______|_______|_______|_____ \\| |/ _____)\n\t    _    _____      _    _____) ) ( (____  \n\t   | |  |  ___)    | |  |  __  /| |\\____ \\ \n\t   | |  | |_____   | |  | |  \\ \\| |_____) )\n\t   |_|  |_______)  |_|  |_|   |_|_(______/ \n"};
    const char endscreen[] = {"\t - GAME OVER - "};

    Setting set;
    set.language = 1;
    set.difficulty = 2;

    Player player;
    player.pseudo[0] = '\0';
    player.score = 0;
    player.level = 0;

    /* ------------------------ AFFICHAGE DE L'ECRAN D'ACCUEIL ------------------------ */

    skip_lines(50);
    printf("%s", tetris);
    skip_lines(5);

    init(mytab, '@');
    for(int i=0; i<TABSIZE; i++){
        for(int j=9; j<TABSIZE; j++){
            mytab[i][j] = ' ';
        }
    }

    
    /* --------------------------------- DEBUT DU JEU --------------------------------- */


    printf("Quelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
    scanf("%s", answer_txt);
    while(!(answer_txt[0] == '1' || answer_txt[0] == '2')){
        printf("\nVeuillez entrer uniquement 1 ou 2 comme reponse. \n\nQuelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
        scanf("%s", answer_txt);
    }
    if(answer_txt[0] == '2'){
        color[3] = 37;
    }
    skip_lines(40);
    printf("%s", tetris);
    skip_lines(4);
    printf("Si vous jouez au jeu pour la première fois, nous vous recommandons de visualiser le tutoriel.");
    skip_lines(2);
    



    
    
    // ecrire la fonction update_tab
    int i,j;
    /*
    scanf("%d", &i);
    scanf("%d", &j);
    printf("\n%d",verticalsize(i, j, pieces));*/


    /* --------------------------------- BOUCLE DE JEU --------------------------------- */

    while(end == 0){

        char* test = "test";

        game = 0;
        do{
            printf("\n\n -- Menu -- ");
            printf("\n\n 1 - Jouer");
            printf("\n 2 - Tutoriel");
            printf("\n 3 - Parametres");
            printf("\n 4 - Musique");
            printf("\n 5 - Quitter\n\n");
            scanf("%s", answer_txt);
        }while(!(answer_txt[0] == '1' || answer_txt[0] == '2' || answer_txt[0] == '3' || answer_txt[0] == '4' || answer_txt[0] == '5'));
        
        switch(answer_txt[0]){
            case '1':
                game = 1;
                break;
            case '2':
                tutorial(color[3], tetris);
                break;
            case '3':
                set = setting(set, color);
                break;
            case '4':
                music();
                break;
            case '5':
                end = 1;
                break;
            default:
                exit(1);
                break;
        }
        
        if(game == 1){
            rewind(datafile);
            for(int i=0; i<NBPLAYR; i++){
                fread(&tab_players[i], sizeof(Player), 1, datafile);
            }
            sort(tab_players, NBPLAYR);
            gameover = 0;
            player.score = 0;
            player.level = 0;
            rewind(datafile);
            futur_piece = rand()%7;
            while(gameover == 0){
                //printf("%d", game);
                new_piece = futur_piece;
                futur_piece = rand()%7;
                disptab(mytab, mytab_color, player.score, pieces, futur_piece);
                admin=ask(pieces, new_piece, &column, &new_orientation);
                if(admin == 1){
                 update_tab(pieces, mytab, mytab_color, color, column, new_orientation, new_piece, &player, &gameover);   
                }
            }
            init(mytab, ' ');
            init(mytab_color, 48);
            skip_lines(40);
            printf("%s", endscreen);
            skip_lines(3);
            printf("Best scores :");
            for(int i=0; i<10; i++){
    	        printf("\n%s : niveau %d\tscore %d", tab_players[i].pseudo, tab_players[i].level, tab_players[i].score);
            }
            if(tab_players[9].score < player.score){
                modif_file = 1;
                update_tab_player(tab_players, player);
            }
            printf("\n\nVous avez atteint le niveau %d, et votre score est de : %d points", player.level, player.score);
            skip_lines(5);

            if(player.pseudo[0] != '\0'){
                printf("Voulez vous utiliser le pseudo %s ?\n\n 0 - non\n 1 - oui\n\n", player.pseudo);
                scanf("%s", answer_txt);
                while(!(answer_txt[0] == '0' || answer_txt[0] == '1')){
                    printf("\nVeuillez entrer uniquement 0 ou 1.\nVoulez vous utiliser le pseudo %s ?\n\n 0 - non\n 1 - oui\n\n", player.pseudo);
                    scanf("%s", answer_txt);
                }
                if(answer_txt[0] == '0'){
                    printf("Veuillez entrer votre pseudo : ");
                    scanf("%s", answer_txt);
                    while(strlen(answer_txt) > 15){
                        printf("Votre pseudo doit faire 15 caractères maximum.\nVeuillez entrer votre pseudo : ");
                        scanf("%s", answer_txt);
                    }
                    strcpy(player.pseudo, answer_txt);
                }
            }else{
                printf("Veuillez entrer votre pseudo : ");
                scanf("%s", answer_txt);
                while(strlen(answer_txt) > 15){
                    printf("Votre pseudo doit faire 15 caractères maximum.\nVeuillez entrer votre pseudo : ");
                    scanf("%s", answer_txt);
                }
                strcpy(player.pseudo, answer_txt);
            }
            if(modif_file == 1){
                rewind(datafile);
                for(int i=0; i<10; i++){
    	            fwrite(&tab_players[i], sizeof(Player), 1, datafile);
                }
            }


            skip_lines(30);
            printf("%s", tetris);
        }
    }


    free(pathtofile);
    fclose(datafile);
    return 0;
}