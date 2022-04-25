#include "header.h"

int main(){
    FILE* datafile = NULL;
    char filename[] = {"datas.txt"};
    char path[] = {"../src/"};              //the file's name and the path are separated to use the file's name if there is an error
    char* pathtofile = add(path, filename);
    datafile = fopen(pathtofile, "r");
    if(datafile == NULL){
        printf("\n%s in %s, error %d : %s \n\n", filename, pathtofile, errno, strerror(errno));
        exit(1);
    }

    int end = 0;
    int gameover = 0;
    int answer = 0;

    //this part go with "tetriminos.c"
    int I1[CTE16], I2[CTE16], O1[CTE16], T1[CTE16], T2[CTE16], T3[CTE16], T4[CTE16], L1[CTE16], L2[CTE16], L3[CTE16], L4[CTE16], J1[CTE16], J2[CTE16], J3[CTE16], J4[CTE16], Z1[CTE16], Z2[CTE16], S1[CTE16], S2[CTE16];
    int *I[CTE4], *O[CTE4], *T[CTE4], *L[CTE4], *J[CTE4], *Z[CTE4], *S[CTE4];
    int **pieces[CTE7];
    getpieces(&I1, &I2, &O1, &T1, &T2, &T3, &T4, &L1, &L2, &L3, &L4, &J1, &J2, &J3, &J4, &Z1, &Z2, &S1, &S2, &I, &O, &T, &L, &J, &Z, &S, &pieces);

    char mytab[TABSIZE][TABSIZE];
    char mytab_color[TABSIZE][TABSIZE];
    char color[] = {36, 33, 35, 30, 34 ,31, 32};//color of the pieces according to wikipedia. see "color.h"

    init(mytab, ' ');
    init(mytab_color, 48); // 48 = '0' (reset color)

    const char tetris[] =  {"\t _______ _______ _______ ______  _  ______ \n\t(_______|_______|_______|_____ \\| |/ _____)\n\t    _    _____      _    _____) ) ( (____  \n\t   | |  |  ___)    | |  |  __  /| |\\____ \\ \n\t   | |  | |_____   | |  | |  \\ \\| |_____) )\n\t   |_|  |_______)  |_|  |_|   |_|_(______/ \n"};
    

    /* ------------------------ AFFICHAGE DE L'ECRAN D'ACCUEIL ------------------------ */

    skip_lines(50);
    printf("%s", tetris);
    skip_lines(5);
    
    /* --------------------------------- DEBUT DU JEU --------------------------------- */


    printf("Quelle est la couleur du fond d'ecran de votre terminal ?\n1 - Blanc\n2 - Noir\nEntrez 1 ou 2 :");
    do{
        scanf("%d", &answer);
    }while(answer!=1 && answer!=2);
    if(answer == 2){
        color[4] =  37;
    }

    disptab(mytab);

    


    /* --------------------------------- BOUCLE DE JEU --------------------------------- */

    while(end == 0){
        while(gameover == 0){
            gameover = 1;
        }
        end =1;
    }


    free(pathtofile);
    fclose(datafile);
    return 0;
}
