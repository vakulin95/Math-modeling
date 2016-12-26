#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROB_BEG 0.5
#define STEP 10e-5
#define MATR_DIM 100

void fill_m1(int M[MATR_DIM][MATR_DIM], float prob);
void fill_m2(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM]);
int check_cell(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM], int I, int J, int* clN);
int hoshen_kopelman(int M[MATR_DIM][MATR_DIM]);
int correct_mark(int M[MATR_DIM][MATR_DIM], int m1, int m2);
int check_perc(int M[MATR_DIM][MATR_DIM]);
void print_m(int M[MATR_DIM][MATR_DIM], char *name);

int ulp[MATR_DIM*MATR_DIM];

int main(void)
{
    int M1[MATR_DIM][MATR_DIM];
    int M2[MATR_DIM][MATR_DIM];
    int res;
    float Probability;

    srand(time(0));

    printf("\n--------------------Percolation theory--------------------\n\n");
    Probability = PROB_BEG;
    fill_m1(M1, Probability);
    fill_m2(M1, M2);
    hoshen_kopelman(M2);
    while(!(res = check_perc(M2)) && Probability < 1.0)
    {
        Probability += STEP;
        fill_m1(M1, Probability);
        fill_m2(M1, M2);
        hoshen_kopelman(M2);
    }
    if(res)
    {
        printf("Percolation threshold: %f\n", Probability);
        print_m(M2, "result");
    }
    else
    {
        printf("No percolation threshold!\n");
    }
    printf("\n----------------------------------------------------------\n\n");

    return 0;
}

void fill_m1(int M[MATR_DIM][MATR_DIM], float prob)
{
    int i, j;
    float val;

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
        {
            val = (float)(rand() % 100) / 100;
            if(val <= prob)
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
    int Y;
    //int nona, nonl;

    for(i = 0; i < MATR_DIM*MATR_DIM; i++)
    {
        ulp[i] = 0;
    }

    Y = 0;
    for(i = 1; i < MATR_DIM; i++)
    {
        for(j = 1; j < MATR_DIM; j++)
        {
            //(i == 0) ? (nona = 1) : (nona = 0);
            //(j == 0) ? (nonl = 1) : (nonl = 0);

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

    for(i = 0; i < MATR_DIM*MATR_DIM; i++)
    {
        if(ulp[i])
        {
            correct_mark(M, i, ulp[i]);
            //printf("%d\n", correct_mark(M, i, ulp[i]));
        }
    }

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

int check_perc(int M[MATR_DIM][MATR_DIM])
{
    int i, j;
    int Y = 0, temp;

    temp = -1;
    for(i = 0; i < MATR_DIM; i++)
    {
        if(M[0][i] && M[0][i] != temp)
        {
            temp = M[0][i];

            for(j = 0; j < MATR_DIM; j++)
            {
                if(M[MATR_DIM - 1][j] == temp)
                {
                    Y = 1;
                    goto ret;
                }
            }
        }
    }

ret:
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
