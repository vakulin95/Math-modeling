#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define R 0.75                 //1.0
#define K 20.0                  //300.0
#define OMEGA 0.75              //1.0
#define D 5.0                 //22500.0

#define S 0.097              //1.0
#define J 0.96                  //0.9

#define Y0 1.0                //150.0
#define Z0 1.0                 //150.0

#define X_BEG 0.0
#define X_END 100.0
#define XDOTS_NUM 1000
#define DX (X_END - X_BEG) / (XDOTS_NUM - 1)

#define NFILES 300.0
#define END_VAL 25.0

double f1(double, double, double);
double f2(double, double, double);
double spec_line1(double);
double spec_line2(double);
void RK(double*, double*, double, double, double(*f1)(double, double, double), double(*f2)(double, double, double));
int write(double*, double*, char*);
int writel(double(*f1)(double), double(*f2)(double), char*);

int main()
{
    int i;
    double k;
    char buf[20];
    double Y[XDOTS_NUM];
    double Z[XDOTS_NUM];

    RK(Y, Z, Y0, Z0, f1, f2);

    write(Y, Z, "data");
    writel(spec_line1, spec_line2, "lines");

    for(i = 0, k = Z0; i < NFILES; i++, k += (END_VAL - Z0) / NFILES)
    {
        sprintf(buf, "1_%d", i);
        RK(Y, Z, k, 10*sin(k) + 10, f1, f2);
        write(Y, Z, buf);
    }

    return 0;
}

double f1(double x, double y, double z)
{
    return R * (1.0 - (y / K)) * y - ((OMEGA * y * z) / (D + y));
}

double f2(double x, double y, double z)
{
    return S * (1.0 - (J * z) / y) * z;
}

double spec_line1(double x1)
{
    return (R / OMEGA) * (1.0 - x1 / K) * (D + x1);
}

double spec_line2(double x1)
{
    return x1 / J;
}

void RK(double *y, double *z, double y0, double z0, double(*f1)(double, double, double), double(*f2)(double, double, double))
{
	int i;
	int x = X_BEG;
	double k1, k2, k3, k4, l1, l2, l3, l4;

	y[0] = y0;
	z[0] = z0;

	for (i = 1; i < XDOTS_NUM; i++)
	{
		k1 = DX * f1(x, y[i - 1], z[i - 1]);
		l1 = DX * f2(x, y[i - 1], z[i - 1]);
//if(i == 1)
//printf("%lf %lf\n", f1(x, y[i - 1], z[i - 1]), f2(x, y[i - 1], z[i - 1]));
		k2 = DX * f1(x + DX / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);
		l2 = DX * f2(x + DX / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);

		k3 = DX * f1(x + DX / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);
		l3 = DX * f2(x + DX / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);

		k4 = DX * f1(x + DX, y[i - 1] + k3, z[i - 1] + l3);
		l4 = DX * f2(x + DX, y[i - 1] + k3, z[i - 1] + l3);

		x += DX;
		y[i] = y[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		z[i] = z[i - 1] + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
	}
}

int write(double *m1, double *m2, char *str)
{
    int i;
    char filename[50];
    FILE *out;

    sprintf(filename, "files/data/%s_out.dat", str);

    if( (out = fopen(filename, "w")) == NULL )
    {
        printf("Opening file error!\n");
        return 1;
    }

    fprintf(out, "#\tX\tY\tZ\n");
    for(i = 0; i < XDOTS_NUM; i++)
        fprintf(out, "%9.5f %9.5f %9.5f\n", X_BEG + DX * i, m1[i], m2[i]);

    fclose(out);
    return 0;
}

int writel(double(*f1)(double), double(*f2)(double), char *str)
{
    double i;
    char filename[50];
    FILE *out;

    sprintf(filename, "files/data/%s_out.dat", str);

    if( (out = fopen(filename, "w")) == NULL )
    {
        printf("Opening file error!\n");
        return 1;
    }

    fprintf(out, "#\tX1\tL1(X1)\tL2(X1)\n");
    i = 0.0;
    while(i < 25.0)
    {
        fprintf(out, "%9.5f %9.5f %9.5f\n", i, f1(i), f2(i));
        i += 0.01;
    }


    fclose(out);
    return 0;
}
