#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATR_DIM 100
#define PROBABILITY 0.7

void fill_m2(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM]);
void fill_m1(int M[MATR_DIM][MATR_DIM]);
int check_cell(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM], int I, int J, int* clN);
int fix_m(int M[MATR_DIM][MATR_DIM]);
void print_m(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM]);

int main(void)
{
    int M1[MATR_DIM][MATR_DIM];
    int M2[MATR_DIM][MATR_DIM];

    srand(time(0));

    fill_m1(M1);
    fill_m2(M1, M2);
    print_m(M1, M2);

    return 0;
}

void fill_m1(int M[MATR_DIM][MATR_DIM])
{
    int i, j;
    float val;

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
        {
            val = (float)(rand() % 100) / 100;
            //printf("%f\n", val);
            if(val <= PROBABILITY)
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

void fill_m2(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM])
{
    int i, j;
    int clastN;

    clastN = 0;
    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
        {
            M2[i][j] = check_cell(M1, M2, i, j, &clastN);
        }
    }
}

int check_cell(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM], int I, int J, int* clN)
{
    int Y, nona, nonl;

    if(I == 0)
        nona = 1;
    else
        nona = 0;

    if(J == 0)
        nonl = 1;
    else
        nonl = 0;

    Y = -1;
    if(!M1[I][J])
    {
        Y = 0;
        goto ret;
    }
    else
    {
        if((nonl && nona) || (nonl && !M2[I - 1][J]) || (nona && !M2[I][J - 1]) ||
        (!nona && !nonl && (!M2[I][J - 1] && !M2[I - 1][J])))
        {
            (*clN)++;
            //printf("%d\n", *clN);
            Y = *clN;
            goto ret;
        }
        if((nona && M2[I][J - 1]) ||
        (!nona && !nonl && (M2[I][J - 1] && !M2[I - 1][J])))
        {
            Y = M2[I][J - 1];
            goto ret;
        }
        if((nonl && M2[I - 1][J]) ||
        (!nona && !nonl && (!M2[I][J - 1] && M2[I - 1][J])))
        {
            Y = M2[I - 1][J];
            goto ret;
        }
        if(!nona && !nonl && (M2[I][J - 1] && M2[I - 1][J]))
        {
            if(M2[I][J - 1] >= M2[I - 1][J])
            {
                Y = M2[I - 1][J];
                M2[I][J - 1] = M2[I - 1][J];
                goto ret;
            }
            else
            {
                Y = M2[I][J - 1];
                M2[I - 1][J] = M2[I][J - 1];
                goto ret;
            }
        }
    }

ret:
    return Y;
}

void print_m(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM])
{
    int i, j;

    FILE *out, *pout;

    if(!(out = fopen("files/out.dat", "w")))
    {
        printf("File opening ERROR in print_m()!\n");
        return;
    }

    if(!(pout = fopen("files/pout.dat", "w")))
    {
        printf("File opening ERROR in print_m()!\n");
        return;
    }

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
            fprintf(pout, "%4d", M1[i][j]);
        fprintf(pout, "\n");
    }

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
            fprintf(out, "%5d", M2[i][j]);
        fprintf(out, "\n");
    }
}
