#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATR_DIM 10
#define PROBABILITY 0.5

void fill_m2(int M1[MATR_DIM][MATR_DIM], int M2[MATR_DIM][MATR_DIM]);
void fill_m1(int M[MATR_DIM][MATR_DIM]);
int check_cell(int M[MATR_DIM][MATR_DIM], int I, int J);
void print_m(int M[MATR_DIM][MATR_DIM]);

int main(void)
{
    int M1[MATR_DIM][MATR_DIM];
    int M2[MATR_DIM][MATR_DIM];

    srand(time(0));

    fill_m1(M1);
    fill_m2(M1, M2);
    print_m(M2);

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
            printf("%f\n", val);
            if(val >= PROBABILITY)
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

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
        {

        }
    }
}

int check_cell(int M[MATR_DIM][MATR_DIM], int I, int J)
{
    int Y = -1;

    if(!M[I][J])
        Y = 0;
    else
    {
        if((!J || !I))
        {

        }
    }

    return Y;
}

void print_m(int M[MATR_DIM][MATR_DIM])
{
    int i, j;

    FILE *out;

    if(!(out = fopen("files/out.dat", "w")))
    {
        printf("File opening ERROR in print_m()!\n");
        return;
    }

    for(i = 0; i < MATR_DIM; i++)
    {
        for(j = 0; j < MATR_DIM; j++)
            fprintf(out, "%d ", M[i][j]);
        fprintf(out, "\n");
    }
}
