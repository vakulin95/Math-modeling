#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define PROP_A 20.0
#define ATT_LOC1 0
#define ATT_LOC2 3.0
#define XLEN ( ATT_LOC2 - ATT_LOC1 )
#define TIME_LOC1 0
#define TIME_LOC2 3.0
#define TLEN ( TIME_LOC2 - TIME_LOC1 )

#define TERMS_NUM 10

#define XDOTS_NUM 300
#define DX ( XLEN / (XDOTS_NUM - 1) )
#define TDOTS_NUM 300
#define DT ( TLEN / (TDOTS_NUM - 1) )

double phi(double, double);
double ksi(double, double);
double integration(double, double, double, double(*f)(double, double));
//void continuous_model(double*, double);
void continuous_model(double u[XDOTS_NUM][TDOTS_NUM]);
//int write(double*, char*, double);
int write(double u[XDOTS_NUM][TDOTS_NUM], char*);

int main()
{
    int i = 0;
    double u[XDOTS_NUM][TDOTS_NUM];

    continuous_model(u);
    write(u, "cont");

    //double t = 0;

    // for(t = 0; t <= 3; t += 0.01)
    // {
    //     continuous_model(u, t);
    //     if(write(u, "cont", i) == 1)
    //         return 1;
    //     i++;
    // }

    return 0;
}

double phi(double x, double k)
{
    double Y;

    // if(x >= 0 && x <= XLEN / 2)
    //     Y = 0.2 * x;
    // else if(x >= XLEN / 2 && x <= XLEN)
    //     Y = -0.2 * (x - XLEN);
    // else
    // {
    //     printf("Error in phi!\n");
    //     return 0;
    // }

    Y = 2 * sin(PI * x / XLEN);

    return Y * sin(k * PI * x / XLEN);
}

double ksi(double x, double k)
{
    double Y = 3;

    if(x >= XLEN/3 && x <= 2.0*XLEN/3)
        Y = 10.0;
    else
        Y = 0;

    return Y * sin(k * PI * x / XLEN);
}

double integration(double a, double b, double k, double(*f)(double, double))
{
    int i;
    double Y;

    int N = 100;
    double h = ( b - a ) / ( 2 * N );
    double S = 0;

    for(i = 1; i <= 2*N - 1; i++)
    {
        if(i % 2 == 0)
            S += 2 * f(a + i * h, k);
        else
            S += 4 * f(a + i * h, k);
    }

    Y = h / 3 * ( f(a, k) + f(b, k) + S);
    //printf("%f\n", Y);
    return Y;
}

// void continuous_model(double *u, double t)
// {
//     int i;
//     double x, a, b, k;
//
//     for(i = 0; i < XDOTS_NUM; i++)
//     {
//         u[i] = 0;
//         x = i * DX;
//         for(k = 1; k < TERMS_NUM; k++)
//         {
//             a = (2.0 / XLEN) * integration(ATT_LOC1, ATT_LOC2, k, phi);
//             b = (2.0 / (k * PI * PROP_A)) * integration(ATT_LOC1, ATT_LOC2, k, ksi);
//             // printf("%f %f\n", a, b);
//
//             u[i] += (a * cos(k * PI * PROP_A * t / XLEN) + b * sin(k * PI * PROP_A * t / XLEN)) * sin(k * PI * x / XLEN);
//         }
//     }
// }

void continuous_model(double u[XDOTS_NUM][TDOTS_NUM])
{
    int i, j;
    double x, a, b, k, t;

    for(j = 0; j < TDOTS_NUM; j++)
    {
        t = TIME_LOC1 + DT*j;

        for(i = 0; i < XDOTS_NUM; i++)
        {
            u[i][j] = 0;
            x = i * DX;
            for(k = 1; k < TERMS_NUM; k++)
            {
                a = (2.0 / XLEN) * integration(ATT_LOC1, ATT_LOC2, k, phi);
                b = (2.0 / (k * PI * PROP_A)) * integration(ATT_LOC1, ATT_LOC2, k, ksi);
                // printf("%f %f\n", a, b);

                u[i][j] += (a * cos(k * PI * PROP_A * t / XLEN) + b * sin(k * PI * PROP_A * t / XLEN)) * sin(k * PI * x / XLEN);
            }
        }
    }
}

// int write(double *u, char *str, double num)
// {
//     int i;
//     double x;
//     char filename[50];
//     FILE *out;
//
//     sprintf(filename, "files/data/%s_out%.0f.txt", str, num);
//
//     if( (out = fopen(filename, "w")) == NULL )
//     {
//         printf("Opening file error!");
//         return 1;
//     }
//
//     for(i = 0; i < XDOTS_NUM; i++)
//     {
//         x = DX * i;
//         fprintf(out, "%.3f %.3f\n", x, u[i]);
//     }
//
//     fclose(out);
//     return 0;
// }

int write(double u[XDOTS_NUM][TDOTS_NUM], char *str)
{
    int i, j;
    char filename[50];
    FILE *out;

    sprintf(filename, "files/%s_out.txt", str);

    if( (out = fopen(filename, "w")) == NULL )
    {
        printf("Opening file error!");
        return 1;
    }

    for(i = 0; i < XDOTS_NUM; i++)
    {
        fprintf(out, "%6.2f", DX * i);
        for(j = 0; j < TDOTS_NUM; j++)
            fprintf(out, "%6.2f", u[i][j]);
        fprintf(out, "\n");
    }

    fclose(out);
    return 0;
}
