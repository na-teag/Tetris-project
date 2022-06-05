#include "header.h"

//this file contains all the functions that doesn't write text

void init(char tab[TABSIZE][TABSIZE], char a){ // initialize all the array's cell to a typeface 'a'
    for(int i=0; i<TABSIZE; i++){
        for(int j=0; j<TABSIZE; j++){
            tab[i][j] = a;
        }
    }
}

void move_lines(char tab[TABSIZE][TABSIZE], char tab_color[TABSIZE][TABSIZE], int color[CTE7], int ligne){ // move the lines of the game array when one is completed
    for(int i=ligne; i<TABSIZE-1; i++){
        for(int j=0; j<TABSIZE; j++){
            tab[i][j] = tab[i+1][j];
            tab_color[i][j] = tab_color[i+1][j];
        }
    }
    for(int i=0; i<TABSIZE; i++){
        tab[TABSIZE-1][i] = ' ';
        tab_color[TABSIZE-1][i] = color[0];
    }
}

unsigned long getTimeMicroSec(){// get the time
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

void cpy(int tab1[], int tab2[], int size){//copy an array
    for(int i=0; i<size; i++){
        tab2[i] = tab1[i];
    }
}
void cpy1(int *tab1[], int *tab2[], int size){//copy an array of array
    for(int i=0; i<size; i++){
        tab2[i] = tab1[i];
    }
}


int changecolor(int color){// the couleur function must have a const *char in parameters
    if(color == 30){
        couleur("30");
        return 0;
    }else if(color == 31){
        couleur("31");
        return 0;
    }else if(color == 32){
        couleur("32");
        return 0;
    }else if(color == 33){
        couleur("33");
        return 0;
    }else if(color == 34){
        couleur("34");
        return 0;
    }else if(color == 35){
        couleur("35");
        return 0;
    }else if(color == 36){
        couleur("36");
        return 0;
    }else if(color == 37){
        couleur("37");
        return 0;
    }else if(color == 48){
        couleur("0");
        return 0;
    }else{
        printf("erreur, données de couleur incorrectes (%d)\n", color);
        exit(1);
    }
    return 0;
}

int horizontalsize(int new_piece, int orientation, int **pieces[]){// calcul of the horizontal size of a piece
    int nbr = 0;
    int nbr2 = 0;
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

void verticalsize(int new_piece, int new_orientation, int **pieces[], int tab[]){// calcul of the nbr of free cell at the bottom of each comlumn
    int nbr = 0;
    for(int i=0; i<horizontalsize(new_piece, new_orientation, pieces); i++){
        for(int j=CTE3; (j>=0) && (*(*(pieces[new_piece]+new_orientation)+(4*j)+i) == 0); j--){
            nbr ++;
        }
        tab[i] = nbr;
        nbr = 0;
    }
    //printf("||");
    for(int i=0; i<CTE4; i++){
        for(int j=0; j<CTE4; j++){
            //printf("%d", *(*(pieces[new_piece]+new_orientation)+(4*i)+j));
        }
    }
    //printf("||"); 
}

int max_verticalsize(int new_piece, int orientation, int **pieces[]){// calcul of the horizontal size of a piece
    int nbr = 0;
    //orientation--;// if the player enter 1, it's equivalent to the 0th for the prgm
    while(nbr<CTE16 && *(*(pieces[new_piece]+orientation)+nbr) == 0){
        nbr++;
    }
    //printf("nbr=%d ", nbr);
    nbr = 4-(nbr/4);
    return nbr;
}

void update_tab(int **pieces[], char mytab[TABSIZE][TABSIZE], char mytab_color[TABSIZE][TABSIZE],int color[CTE7], int column, int new_orientation, int new_piece, Player *player, int *gameover, Setting set){
    new_orientation--;// if the player enter 1, it's equivalent to the 0th for the prgm
    int piece_size[CTE4] = {0,0,0,0};// the vertical size of each column of the piece (by counting only the occuped cells)
    verticalsize(new_piece, new_orientation, pieces, piece_size);
    int horizontal_size = horizontalsize(new_piece, new_orientation, pieces);
    int size[CTE4] = {0,0,0,0};
    int tabsup[CTE4];//4 lines max can be completed in one turn
    int height = 0;
    int test = 0;
    int nbline = 0;
    int k = CTE3;//variable for a loop  
    int max_vertical_size = max_verticalsize(new_piece, new_orientation, pieces);//the vertical size of the piece
    
    


    for(int i=0; i<horizontal_size; i++){
        for(int j=9; (j>=0) && (test == 0); j--){//check if the cells are free ot not, from the top to the bottom
            if(mytab[j][i+column]=='@'){
                size[i]=j+1;//as j start at 9, j is equal to the occuped cell, and not the free cell, so we need to do +1
                test=1;
                //printf("(%d;%d)", i, j);
            }else if((j==0) && (test == 0)){
                size[i] = 0;
            }
        }
        test = 0;
    }
    skip_lines(1);
    for(int i=0; i<CTE4; i++){
        //printf("%d-%d|",size[i], piece_size[i]);
        size[i] = size[i]-piece_size[i];
    }
    height = size[0];// height must be = to the higher nbr of the array
    //printf("\n|%d",size[0]);
    for(int i=0; i<horizontal_size-1; i++){
        if(size[i]<size[i+1]){
            height = size[i+1];
        }
        //printf("|%d",size[i+1]);
    }
    if(height<0){
        height = 0;
    }
    //printf("\nheight=%d,", height);
    //height = 5;
    if(height+max_vertical_size<=TABSIZE){//if there is still some place in the array
        //k = CTE4;
        for(int i=0; i<max_vertical_size; i++){
            //printf("i=%d,", i);
            for(int j=0; j<CTE4; j++){
                if(*(*(pieces[new_piece]+new_orientation)+(4*k)+j) == 1){//save the piece selected in the array
                    mytab[i+height][j+column] = '@';
                    mytab_color[i+height][j+column] = color[new_piece];
                }
                //printf("k=%d, j=%d,", k, j);
            }
            k--;
            
        }
        //printf("(%d)", new_piece);
        for(int i=0; i<TABSIZE; i++){
            int full=0;
            for(int j=0; j<TABSIZE; j++){//count the line completed
                if(mytab[i][j]=='@'){
                    full++;
                    if(full==10){
                        tabsup[nbline]=i;
                        nbline++;
                        full=0;
                    }
                }
            }
        }
        if(nbline>0){//if a line is completed
            printf("\a");
            for(int i=0; i<nbline; i++){
                move_lines(mytab, mytab_color, color, tabsup[i]-i);//move the lines   
            }
        }
        player->level++;
        player->score += addscore(player->level, nbline, set);
        //printf("\nscore=%d", player->score);

    }else{
        *gameover = 1;
    }
}





int addscore(int level, int nbline, Setting set){
    float score = 0;
    if(nbline == 1){
        score = 40;
    }else if(nbline == 2){
        score = 100;
    }else if(nbline == 3){
        score = 300;
    }else if(nbline == 4){
        score = 1200;
    }
    score += 10;
    if(set.difficulty == 0){
        score*=0.2;
    }else if(set.difficulty == 1){
        score*=0.5;
    }else if(set.difficulty == 3){
        score*=1.5;
    }
    if(set.difficulty_progressive == 1 && set.difficulty != 0){
        score*=2;
    }
    return (int)score;
}

void sort(Player tab_players[], int size){
    int decalage;
    Player temp;
    for(int step=1; step<size; step++){
        temp=tab_players[step];
        decalage=step-1;
        while(decalage >= 0 && tab_players[decalage].score < temp.score){
        	tab_players[decalage+1]=tab_players[decalage];
            decalage--;
        } 
        tab_players[decalage+1]=temp;
    }
}



void update_tab_player(Player tab_players[NBPLAYR], Player player){
    tab_players[NBPLAYR-1] = player;
    sort(tab_players, NBPLAYR);
}
