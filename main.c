#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define PROP_A 9.0 //4.0
#define ATT_LOC1 0
#define ATT_LOC2 3.0
#define LEN ( ATT_LOC2 - ATT_LOC1 )

#define TERMS_NUM 10
#define DOTS_NUM 300
#define DX ( LEN / DOTS_NUM )

double phi(double, double);
double ksi(double, double);
double integration(double, double, double, double(*f)(double, double));
void continuous_model(double*, double);
int write(double*, char*, double);

int main()
{
    int i = 0;
    double u[DOTS_NUM];
    double t = 0;

    for(t = 0; t <= 3; t += 0.01)
    {
        continuous_model(u, t);
        if(write(u, "cont", i) == 1)
            return 1;
        i++;
    }

    return 0;
}

double phi(double x, double k)
{
    double Y;

    // if(x >= 0 && x <= LEN / 2)
    //     Y = 0.2 * x;
    // else if(x >= LEN / 2 && x <= LEN)
    //     Y = -0.2 * (x - LEN);
    // else
    // {
    //     printf("Error in phi!\n");
    //     return 0;
    // }

    Y = 2 * sin(PI * x / LEN);

    return Y * sin(k * PI * x / LEN);
}

double ksi(double x, double k)
{
    double Y = 3;

    // if(x >= LEN/3 && x <= 2.0*LEN/3)
    //     Y = 10.0;
    // else
    //     Y = 0;

    return Y * sin(k * PI * x / LEN);
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

void continuous_model(double *u, double t)
{
    int i;
    double x, a, b, k;

    for(i = 0; i < DOTS_NUM; i++)
    {
        u[i] = 0;
        x = i * DX;
        for(k = 1; k < TERMS_NUM; k++)
        {
            a = (2.0 / LEN) * integration(ATT_LOC1, ATT_LOC2, k, phi);
            b = (2.0 / (k * PI * PROP_A)) * integration(ATT_LOC1, ATT_LOC2, k, ksi);
            // printf("%f %f\n", a, b);

            u[i] += (a * cos(k * PI * PROP_A * t / LEN) + b * sin(k * PI * PROP_A * t / LEN)) * sin(k * PI * x / LEN);
        }
    }
}

int write(double *u, char *str, double num)
{
    int i;
    double x;
    char filename[50];
    FILE *out;

    sprintf(filename, "files/data/%s_out%.0f.txt", str, num);

    if( (out = fopen(filename, "w")) == NULL )
    {
        printf("Opening file error!");
        return 1;
    }

    for(i = 0; i < DOTS_NUM; i++)
    {
        x = DX * i;
        fprintf(out, "%.3f %.3f\n", x, u[i]);
    }

    fclose(out);
    return 0;
}
