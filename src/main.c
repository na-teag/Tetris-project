#include "header.h"


int main(){
    //file part
    FILE* datafile = NULL;
    char filename[] = {"datas"};
    char path[] = {"../src/"};              //the file's name and the path are separated to use the file's name if there is an error
    char* pathtofile = add(path, filename);
    datafile = fopen(pathtofile, "rb+");
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
    int admin = 0;
    int column = 0;
    int scanf_res=0;
    int test = 0;//this one is to know if it's the first time the loop game is launched
    int modif_file = 0;

        //this part is for the "tetriminos.c" file
    int I1[CTE16], I2[CTE16], O1[CTE16], T1[CTE16], T2[CTE16], T3[CTE16], T4[CTE16], L1[CTE16], L2[CTE16], L3[CTE16], L4[CTE16], J1[CTE16], J2[CTE16], J3[CTE16], J4[CTE16], Z1[CTE16], Z2[CTE16], S1[CTE16], S2[CTE16];
    int *I[CTE4], *O[CTE4], *T[CTE4], *L[CTE4], *J[CTE4], *Z[CTE4], *S[CTE4];
    int **pieces[CTE7];
    getpieces(&I1, &I2, &O1, &T1, &T2, &T3, &T4, &L1, &L2, &L3, &L4, &J1, &J2, &J3, &J4, &Z1, &Z2, &S1, &S2, &I, &O, &T, &L, &J, &Z, &S, &pieces);
    Player tab_players[10];

        //this part is for the game arrays.
    char mytab[TABSIZE][TABSIZE];
    char mytab_color[TABSIZE][TABSIZE];
    char answer_txt[CTE200];
    int color[CTE7] = {36, 33, 35, 30, 34 ,31, 32};//color of the pieces. see "color.h"

    init(mytab, ' ');
    init(mytab_color, 48); // 48 = '0' (reset color)

    const char tetris[] =  {"\t _______ _______ _______ ______  _  ______ \n\t(_______|_______|_______|_____ \\| |/ _____)\n\t    _    _____      _    _____) ) ( (____  \n\t   | |  |  ___)    | |  |  __  /| |\\____ \\ \n\t   | |  | |_____   | |  | |  \\ \\| |_____) )\n\t   |_|  |_______)  |_|  |_|   |_|_(______/ \n"};
    const char endscreen[] = {"\t - GAME OVER - "};

    Setting set;//initialize the parameter of the game
    set.difficulty = 2;
    set.difficulty_progressive = 1;
    set.time = 15.0;

    Player player;//initialize the profile of the user
    player.pseudo[0] = '\0';
    player.score = 0;
    player.level = 0;

    /* ------------------------ WELCOME SCREEN ------------------------ */

    clear_screen();
    changecolor(34);
    printf("%s", tetris);
    couleur("0");
    skip_lines(5);


    
    /* --------------------------------- BEGINNING OF THE GAME --------------------------------- */

    fread(tab_players, sizeof(Player), 10, datafile);//read the file and
    fclose(datafile);
    printf("Quelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
    scanf_res=scanf("%d", &answer);
    while(getc(stdin) != '\n');
    while((answer != 1 && answer != 2) || scanf_res == 0){
        printf("\nVeuillez entrer uniquement 1 ou 2 comme reponse. \n\nQuelle est la couleur du fond d'ecran de votre terminal ? \n1 - Blanc \n2 - Noir \nEntrez 1 ou 2 : ");
        scanf_res=scanf("%d", &answer);
        while(getc(stdin) != '\n');
    }
    if(answer == 2){// if the background is black, put a black piece on the screen is not a good idea
        color[3] = 37;
    }


    /* --------------------------------- GAME LOOP --------------------------------- */




    while(end == 0){

        clear_screen();
        changecolor(34);
        printf("%s", tetris);
        couleur("0");
        if(test == 0){// if the program is launched for the first time
            skip_lines(2);
            printf("Si vous jouez pour la premi??re fois, nous vous recommandons de visualiser le tutoriel.");
            skip_lines(2);
            test = 1;
        }
        game = 0;//
        do{
            printf("\n\n -- Menu -- ");
            printf("\n\n 1 - Jouer");
            printf("\n 2 - Tableau des scores");
            printf("\n 3 - Tutoriel");
            printf("\n 4 - R??gles des scores");
            printf("\n 5 - Parametres");
            printf("\n 6 - Musique");
            printf("\n 7 - Version 2.0 beta (non-compl??te)");
            printf("\n 8 - Quitter\n\n");
            scanf_res=scanf("%d", &answer);
            while(getc(stdin) != '\n');
        }while((answer<0 || 9<answer) || scanf_res==0);
        
        switch(answer){
            case 1:
                game = 1;
                break;
            case 2:
                scoring(tab_players, tetris);
                break;
            case 3:
                tutorial(color[3], tetris);
                break;
            case 4:
                show_rules(tetris);
                break;
            case 5:
                set = setting(set, color, tetris);
                break;
            case 6:
                music(tetris);
                break;
            case 7:
                beta(tetris);
                break;
            case 8:
                end = 1;
                break;
            default:
                exit(1);
                break;
        }
        
        if(game == 1){
            sort(tab_players, NBPLAYR);
            gameover = 0;
            player.score = 0;
            player.level = 0;
            futur_piece = rand()%7;
            while(gameover == 0){// loop of the differents rounds
                new_piece = futur_piece;
                futur_piece = rand()%7;
                disptab(mytab, mytab_color, player.score, pieces, futur_piece, color);
                admin=ask(pieces, new_piece, &column, &new_orientation, set, color);
                if(set.difficulty_progressive == 1 && set.time>0.5){
                    set.time = set.time - 0.2;
                }
                if(admin == 1){
                 update_tab(pieces, mytab, mytab_color, color, column, new_orientation, new_piece, &player, &gameover, set);   
                }
            }
            init(mytab, ' ');
            init(mytab_color, 48);
            clear_screen();
            changecolor(31);
            printf("%s", endscreen);
            couleur("0");
            skip_lines(3);
            
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
                        printf("Votre pseudo doit faire 15 caract??res maximum.\nVeuillez entrer votre pseudo : ");
                        scanf("%s", answer_txt);
                    }
                    strcpy(player.pseudo, answer_txt);
                    player.pseudo[15] = '\0';
                }
            }else{
                printf("Veuillez entrer votre pseudo : ");
                scanf("%s", answer_txt);
                while(strlen(answer_txt) > 15){
                    printf("Votre pseudo doit faire 15 caract??res maximum.\nVeuillez entrer votre pseudo : ");
                    scanf("%s", answer_txt);
                }
                strcpy(player.pseudo, answer_txt);
                player.pseudo[15] = '\0';
            }
            if(tab_players[9].score < player.score){//if the score of the user is better than the worst one of the top-list
                modif_file = 1;
                update_tab_player(tab_players, player);//update the file
            }
            printf("\"%s\"\n" ,player.pseudo);
            skip_lines(3);
            scoring(tab_players, tetris);
            if(modif_file == 1){
                datafile = fopen(pathtofile, "w");
                if(datafile == NULL){
                    printf("\n%s file in %s, error %d : %s \n\n", filename, pathtofile, errno, strerror(errno));
                    exit(1);
                }
    	        fwrite(tab_players, sizeof(Player), 10, datafile);
                fclose(datafile);
            }
            modif_file=0;
        }
    }
    free(pathtofile);
    return 0;
}