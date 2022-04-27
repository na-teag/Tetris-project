#include "header.h"





// The following instructions create a table of 7 cells. Each cell contains a table of 4 cells (for the differents positions). Each of them contains a table of the stucture of the piece of tetris.
int*** getpieces(int I1[CTE16], int I2[CTE16], int O1[CTE16], int T1[CTE16], int T2[CTE16], int T3[CTE16], int T4[CTE16], int L1[CTE16], int L2[CTE16], int L3[CTE16], int L4[CTE16], int J1[CTE16], int J2[CTE16], int J3[CTE16], int J4[CTE16], int Z1[CTE16], int Z2[CTE16], int S1[CTE16], int S2[CTE16], int *I[CTE4], int *O[CTE4], int *T[CTE4], int *L[CTE4], int *J[CTE4], int *Z[CTE4], int *S[CTE4], int **pieces[CTE7]){
    int tabI1[CTE16] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};
    int tabI2[CTE16] = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
    int tabO1[CTE16] = {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0};
    int tabT1[CTE16] = {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0};
    int tabT2[CTE16] = {0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0};
    int tabT3[CTE16] = {0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0};
    int tabT4[CTE16] = {0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0};
    int tabL1[CTE16] = {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0};
    int tabL2[CTE16] = {0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0};
    int tabL3[CTE16] = {0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0};
    int tabL4[CTE16] = {0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0};
    int tabJ1[CTE16] = {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0};
    int tabJ2[CTE16] = {0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0};
    int tabJ3[CTE16] = {0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0};
    int tabJ4[CTE16] = {0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0};
    int tabZ1[CTE16] = {0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0};
    int tabZ2[CTE16] = {0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0};
    int tabS1[CTE16] = {0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0};
    int tabS2[CTE16] = {0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0};


    /* represent the pieces from tetris, with 4 lines of 4 columns.
    They are positionned to be at the bottom and the left of the table.
    
    Exemple :
    The first one {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1} represent the horizontal line :
    0 0 0 0
    0 0 0 0
    0 0 0 0
    1 1 1 1

    note : the order of the piece is the same that the one of wikipedia's table (https://fr.wikipedia.org/wiki/tetris#Pièces_du_jeu)

    The tables are declared again (even if there is alredy tables in parameters) to don't have to fill them cell by cell, like this :
    tab1[0] = a;
    tab1[1] = b
    ...
    tab10[5] = zza...

    */

    cpy(tabI1, I1, CTE16); //puts I1 to tabI1
    cpy(tabI2, I2, CTE16);
    cpy(tabO1, O1, CTE16);
    cpy(tabT1, T1, CTE16);
    cpy(tabT2, T2, CTE16);
    cpy(tabT3, T3, CTE16);
    cpy(tabT4, T4, CTE16);
    cpy(tabL1, L1, CTE16);
    cpy(tabL2, L2, CTE16);
    cpy(tabL3, L3, CTE16);
    cpy(tabL4, L4, CTE16);
    cpy(tabJ1, J1, CTE16);
    cpy(tabJ2, J2, CTE16);
    cpy(tabJ3, J3, CTE16);
    cpy(tabJ4, J4, CTE16);
    cpy(tabZ1, Z1, CTE16);
    cpy(tabZ2, Z2, CTE16);
    cpy(tabS1, S1, CTE16);
    cpy(tabS2, S2, CTE16);


    int *tabI[CTE4] = {I1, I2, I1, I2}; // do a table of every positions of the pieces
    int *tabO[CTE4] = {O1, O1, O1, O1};
    int *tabT[CTE4] = {T1, T2, T3, T4};
    int *tabL[CTE4] = {L1, L2, L3, L4};
    int *tabJ[CTE4] = {J1, J2, J3, J4};
    int *tabZ[CTE4] = {Z1, Z2, Z1, Z2};
    int *tabS[CTE4] = {S1, S2, S1, S2};

    cpy1(tabI, I, CTE4); //puts I to tabI
    cpy1(tabO, O, CTE4);
    cpy1(tabT, T, CTE4);
    cpy1(tabL, L, CTE4);
    cpy1(tabJ, J, CTE4);
    cpy1(tabZ, Z, CTE4);
    cpy1(tabS, S, CTE4);

    int **tabpieces[CTE7] = {I, O, T, L, J, Z, S}; // do a table of every pieces in every position
    for(int i=0; i<CTE7; i++){
        pieces[i] = tabpieces[i];
    }
    return pieces;
}