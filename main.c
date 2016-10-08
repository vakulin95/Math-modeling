#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define A_PROP 10.0
#define ATT_LOC1 0
#define ATT_LOC2 1.0
#define XLEN ( ATT_LOC2 - ATT_LOC1 )
#define TIME_LOC1 0
#define TIME_LOC2 1.0
#define TLEN ( TIME_LOC2 - TIME_LOC1 )

#define TERMS_NUM 10

#define XDOTS_NUM 100
#define DX ( XLEN / (XDOTS_NUM - 1) )
#define TDOTS_NUM 1000
#define DT ( TLEN / (TDOTS_NUM - 1) )

double phi(double);
double phi_s(double, double);
double ksi(double);
double ksi_s(double, double);
double integration(double, double, double, double(*f)(double, double));
void continuous_model(double u[XDOTS_NUM][TDOTS_NUM]);
int discrete_model(double u[XDOTS_NUM][TDOTS_NUM]);
int write(double u[XDOTS_NUM][TDOTS_NUM], char*);

int main()
{
    double u[XDOTS_NUM][TDOTS_NUM];

    if((discrete_model(u) != 0) || (write(u, "discr")))
        return 0;

    continuous_model(u);
    write(u, "cont");

    return 0;
}

double phi(double x)
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

    return Y;
}

double phi_s(double x, double k)
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

double ksi(double x)
{
    double Y = 3;

    if(x >= XLEN/3 && x <= 2.0*XLEN/3)
        Y = 10.0;
    else
        Y = 0;

    return Y;
}

double ksi_s(double x, double k)
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

    return Y;
}

void continuous_model(double u[XDOTS_NUM][TDOTS_NUM])
{
    int i, j;
    double x, a, b, k, t;

    printf("Calculation of the continuous model...\n");

    for(j = 0; j < TDOTS_NUM; j++)
    {
        t = TIME_LOC1 + DT*j;

        for(i = 0; i < XDOTS_NUM; i++)
        {
            u[i][j] = 0;
            x = i * DX;
            for(k = 1; k < TERMS_NUM; k++)
            {
                a = (2.0 / XLEN) * integration(ATT_LOC1, ATT_LOC2, k, phi_s);
                b = (2.0 / (k * PI * A_PROP)) * integration(ATT_LOC1, ATT_LOC2, k, ksi_s);

                u[i][j] += (a * cos(k * PI * A_PROP * t / XLEN) + b * sin(k * PI * A_PROP * t / XLEN)) * sin(k * PI * x / XLEN);
            }
        }
    }
}

int discrete_model(double u[XDOTS_NUM][TDOTS_NUM])
{
    int i, j;
    double r, x;

    if((r = A_PROP * DT / DX) > 1)
    {
        printf("Incorrect values for discrete model!\nr = %.3f\nTry XDOTS_NUM <= %d; or A_PROP <= %d\n",
        r, (int)(XLEN / (A_PROP * DT) + 1), (int)(XLEN / ((XDOTS_NUM - 1) * DT)));
        return 1;
    }

    printf("Calculation of the discrete model...\n");

    for(i = 0; i < XDOTS_NUM; i++)
    {
        x = i * DX;
        u[i][0] = phi(x);
        u[i][1] = u[i][0] + DT * ksi(x);
    }

    for(j = 2; j < TDOTS_NUM; j++)
    {
        u[0][j] = u[XDOTS_NUM - 1][j] = 0;
        for(i = 1; i < XDOTS_NUM - 1; i++)
        {
            u[i][j] = 2 * (1 - pow(r, 2)) * u[i][j - 1] + pow(r, 2) * (u[i + 1][j - 1] + u[i - 1][j - 1]) - u[i][j - 2];
        }
    }

    return 0;
}

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

    printf("Filing \"%s\"...\n", filename);

    for(i = 0; i < XDOTS_NUM; i++)
    {
        fprintf(out, "%7.3f", DX * i);
        for(j = 0; j < TDOTS_NUM; j++)
            fprintf(out, "%7.3f", u[i][j]);
        fprintf(out, "\n");
    }

    fclose(out);
    return 0;
}
