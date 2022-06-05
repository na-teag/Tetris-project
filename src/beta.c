#include "header.h"


void beta(const char tetris[]){

int main1();

// game loop
clear_screen();
changecolor(34);
printf("%s", tetris);
couleur("0");
skip_lines(5);
printf("Pour diriger les pièces, utiliser les touche 8 (haut), 4 (gauche), 6 (droite), et 2 (bas) du pavé numérique.\n\n");
printf("Pour sortir de la version beta, appuyer sur la touche échap (exit)\n\napuyer sur n'importe quelle touche pour commencer.");
int c;
scanf("%c", &c);
while(getc(stdin) != '\n');

main1();

}

int main1(){

    typedef struct{
        int x;
        int y;
    }Decalage;


    void clearBuffer(){
        int c=0;
        while(c!='\n' && c!=EOF){
            c = getchar();
        }
    }

    void disptab2(char mytab[TABSIZE][TABSIZE]){
        int x=0 ,y=0;
        for(int i=0; i<TABSIZE; i++){ // the (0;0) cell is at the left corner of the bottom
            for(int j=0; j<TABSIZE; j++){
                move(10-j, 2*(i+1));
                printw("%c", mytab[i][j]);
            }
        }
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



    int check_move(char mytab[TABSIZE][TABSIZE], int **pieces_beta[], int x, int y, int new_piece, int orientation, Decalage decalage){
        int ok = 1;
        int k = 3;
        /*if(y>TABSIZE+decalage.y-1){
            return 0;
        }else if(x<decalage.x){
            return 0;
        }else if(x+horizontalsize(new_piece, orientation, pieces_beta)-1>TABSIZE-1+decalage.x){
            move(22,22);
            printw("%d+%d-1>%d-1+%d", x, horizontalsize(new_piece, orientation, pieces_beta), TABSIZE, decalage.x);
            refresh();
            sleep(10);
            return -1;
        }*/
        for(int i=0; i<4 && ok==1; i++){
            for(int j=0; j<4; j++){
                if(*(*(pieces_beta[new_piece]+orientation)+(4*k)+j) == 1 && mytab[y+j][x+i] == '@'){
                    ok=0;
                    move(23,23);
                    printw("non : pieces_beta[%d]+%d)+(4*%d)+%d) = mytab[%d][%d+%d]", new_piece, orientation, k, j, x+i, y,j);
                    refresh();
                    sleep(1);
                }
            }
            k--;
        }
        return ok;
    }






    int I1[CTE16], I2[CTE16], O1[CTE16], T1[CTE16], T2[CTE16], T3[CTE16], T4[CTE16], L1[CTE16], L2[CTE16], L3[CTE16], L4[CTE16], J1[CTE16], J2[CTE16], J3[CTE16], J4[CTE16], Z1[CTE16], Z2[CTE16], S1[CTE16], S2[CTE16];
    int *I[CTE4], *O[CTE4], *T[CTE4], *L[CTE4], *J[CTE4], *Z[CTE4], *S[CTE4];
    int **pieces_beta[CTE7];
    getpieces(I1, I2, O1, T1, T2, T3, T4, L1, L2, L3, L4, J1, J2, J3, J4, Z1, Z2, S1, S2, I, O, T, L, J, Z, S, pieces_beta);
    char mytab[TABSIZE][TABSIZE];
    init(mytab, ' ');
    // Init 'curses' library
    initscr();
    // Colors are useable
    start_color();
    // define text/background color pairs (with color index)
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // No echo for key press
    noecho();
    // no cursor displayed
    curs_set(0);
    
    // Variables (position of the player)
    int x = 5;
    int y = 2;
    
    for(int i=0; i<9; i++){
        mytab[i][4]='@';
    }
    for(int i=0; i<6; i++){
        mytab[i][3]='@';
    }
    for(int i=0; i<9; i++){
        mytab[i][2]='@';
    }
    srand(time(NULL));
    move(11,1);
    int c;
    int new_piece = 0;
    int orientation = 0;//rand()%4;
    int k = 3;
    int h_size = 1;
    int v_size = 1;
    unsigned long time1, time2;
    int turn = 1;

    time1 = getTimeMicroSec();
    y = horizontalsize(new_piece, orientation, pieces_beta);
    Decalage decalage;
    decalage.x = 1;//space between side of the screen and the table
    decalage.y=1;
        
    // Game loop
    while(c != 27){
        //usleep(1000000);
        //fflush(stdin);
        // -----------------------------------        
        // DISPLAY SCREEN DATA
        // -----------------------------------        
        clear();
        
        //usleep(2000000);
        // Draw border
        move(10,3);
        for(int y=1; y<11; y++)
        for(int x=3; x<20; x+=2){
            move(y,x);
            printw("|");
        }
        refresh();
        move(0,0);
        printw(" #");
        for(int dx=1;dx<=10;dx++){
            printw(" #");
        }
        move(11,0);
        printw(" #");
        for(int dx=1;dx<=10;dx++){
            printw(" #");
        }
        for(int dy=1;dy<=10;dy++){
            move(dy,0);
            printw(" #");
            move(dy,2*10+1);
            printw("# ");
        }
        disptab2(mytab);
        // Draw player (@) at position (x,y)
        // Set color pair 1 (defined above)
        attron(COLOR_PAIR(1));
        
        move(3,horizontalsize(new_piece, orientation, pieces_beta));
        h_size = max_verticalsize(new_piece, orientation, pieces_beta);
        v_size = horizontalsize(new_piece, orientation, pieces_beta);
        k = 3;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(*(*(pieces_beta[new_piece]+orientation)+(4*k)+j) == 1){
                    move(y-j, 2*(i+x));
                    printw("@");
                }
            }
            k--;
        }
        
        attroff(COLOR_PAIR(1));// reset color pair 0
        
        refresh();// all drawings are displayed really

        // -----------------------------------
        // Get key code from keyboard
        // -----------------------------------

        c=getch();
        if(getTimeMicroSec()-time1>=1000000 && turn==1){
            int plus = (getTimeMicroSec()-time1)/1000000;
            while(1==0&&check_move(mytab, pieces_beta, x, y+plus, new_piece, orientation, decalage)==0){
                plus--;
                move(22,22);
                printw("%d", plus);
                refresh();
                sleep(1);
                if(plus<0){
                    plus=0;
                }
            }
            if((getTimeMicroSec()-time1)/1000000>plus+1){
                turn = 0;
            }
            turn=1;//y+=plus;
            time1 = getTimeMicroSec();
        }
        
        // If there is no actual keyboard active, it returns ERR
        if(c != ERR){
            // The ESCAPE key has been pressed            
            if(turn == 1){
                // KEYPAD_2 has been pressed (down)
                if(c==50 ){
                    if(check_move(mytab, pieces_beta, x, y+1, new_piece, orientation, decalage)){
                        y++;
                        if(y>10) y=10;
                    }
                }
                // KEYPAD_4 has been pressed (left)
                if(c==52){
                    if(check_move(mytab, pieces_beta, x-1, y, new_piece, orientation, decalage)){
                        x--;
                        if(x<1) x=1;
                    }
                }
                // KEYPAD_6 has been pressed (right)
                if(c==54){
                    if(check_move(mytab, pieces_beta, x, y, new_piece, orientation, decalage)){
                        x++;
                        if(x>11-h_size) x=11-h_size;
                    }
                }
                // KEYPAD_8 has been pressed (up)
                if(c==56){

                    
                    int temp_orientation = orientation;
                    int temp_new_piece = new_piece;
                    int noplace=1;
                    int temp_x = x;
                    int i=1;
                
                    if(x+horizontalsize(temp_new_piece, temp_orientation, pieces_beta)>TABSIZE+decalage.x){
                        temp_x=TABSIZE+decalage.x-horizontalsize(temp_new_piece, temp_orientation, pieces_beta);
                        if(check_move(mytab, pieces_beta, temp_x, y, temp_new_piece, temp_orientation, decalage)){
                            x=temp_x;
                        }
                    }
                    temp_orientation++;
                    if(temp_orientation>3){
                        temp_orientation = 0;
                        temp_new_piece++;
                        if(temp_new_piece>6) temp_new_piece = 0;
                    }
                    if(check_move(mytab, pieces_beta, x, y, temp_new_piece, temp_orientation, decalage)){
                        orientation++;
                        if(orientation>3){
                            orientation = 0;
                            new_piece++;
                            if(new_piece>6) new_piece = 0;
                        }
                    }else if(check_move(mytab, pieces_beta, x, y, temp_new_piece, temp_orientation, decalage)==-1){
                        for(i=1; i<horizontalsize(temp_new_piece, temp_orientation, pieces_beta)-1; i++){
                            if(check_move(mytab, pieces_beta, x-i, y, temp_new_piece, temp_orientation, decalage)){
                                noplace=0;
                                break;
                            }
                        }
                        if(noplace == 0){
                            x-=i;
                            new_piece=temp_new_piece;
                            orientation=temp_orientation;
                        }
                    }
                }
            }
        }
    }

    // Terminate curses library use
    echo();
    endwin();
    // end of program
    return 0;
}