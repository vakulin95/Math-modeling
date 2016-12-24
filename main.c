#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATR_DIM 500
#define PROBABILITY 0.7

void fill_m2(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM]);
void fill_m1(int M[MATR_DIM][MATR_DIM]);
int check_cell(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM], int I, int J, int* clN);
int hoshen_kopelman(int M[MATR_DIM][MATR_DIM]);
int correct_mark(int M[MATR_DIM][MATR_DIM], int m1, int m2);
void print_m(int M[MATR_DIM][MATR_DIM], char *name);

int main(void)
{
    int M1[MATR_DIM][MATR_DIM];
    int M2[MATR_DIM][MATR_DIM];

    srand(time(0));

    fill_m1(M1);
    //print_m(M1, "M1");

    fill_m2(M1, M2);
    //print_m(M2, "M2");

    hoshen_kopelman(M2);
    print_m(M2, "result");

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

    (I == 0) ? (nona = 1) : (nona = 0);
    (J == 0) ? (nonl = 1) : (nonl = 0);

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

int hoshen_kopelman(int M[MATR_DIM][MATR_DIM])
{
    int i, j;
    int Y, max, nona, nonl;
    int *ulp;

    max = M[0][0];
    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 1; j < MATR_DIM; j++)
        {
            if(M[i][j] > max)
            {
                max = M[i][j];
            }
        }
    }

    ulp = (int*)calloc(sizeof(int), max);

    Y = 0;
    for(i = 1; i < MATR_DIM; i++)
    {
        for(j = 1; j < MATR_DIM; j++)
        {
            (i == 0) ? (nona = 1) : (nona = 0);
            (j == 0) ? (nonl = 1) : (nonl = 0);

            if(M[i][j])
            {
                if(M[i - 1][j] > M[i][j])
                {
                    ulp[M[i - 1][j]] = M[i][j];
                }
                if(M[i][j - 1] > M[i][j])
                {
                    ulp[M[i][j - 1]] = M[i][j];
                }
            }
        }
    }

    for(i = 0; i < max; i++)
    {
        if(ulp[i])
        {
            correct_mark(M, i, ulp[i]);
            //printf("%d\n", correct_mark(M, i, ulp[i]));
        }
    }

    free(ulp);
    return Y;
}

int correct_mark(int M[MATR_DIM][MATR_DIM], int m1, int m2)
{
    int i, j;
    int Y = 0;

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
        {
            if(M[i][j] == m1)
            {
                M[i][j] = m2;
                Y++;
            }
        }
    }

    return Y;
}

void print_m(int M[MATR_DIM][MATR_DIM], char *name)
{
    int i, j;
    char path[50];

    FILE *out;

    sprintf(path, "files/%s_out.dat", name);

    if(!(out = fopen(path, "w")))
    {
        printf("File opening ERROR in print_m()!\n");
        return;
    }

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
            fprintf(out, "%10d", M[i][j]);
        fprintf(out, "\n");
    }
}
