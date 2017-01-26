#include <stdio.h>
#include <stdlib.h>

#define ALPHA_1     0.002
#define ALPHA_2     0.001

#define BETTA_1     0.004
#define BETTA_2     0.001

#define GAMMA_1     0.5
#define GAMMA_2     0.5

#define Y0          150.0
#define Z0          200.0

#define X_BEG       0.0
#define X_END       100.0
#define XDOTS_NUM   1000
#define DX          ((X_END - X_BEG) / (XDOTS_NUM - 1))

double f1(double, double, double);
double f2(double, double, double);
void RK(double*, double*, double, double, double(*f1)(double, double, double), double(*f2)(double, double, double));
int write(double*, double*, char*);
int write1(double*, double*, char*);

int main()
{
    int i, k;
    char buf[20];

    double Y[XDOTS_NUM];
    double Z[XDOTS_NUM];
    double LineX1[2];
    double LineY1[2];
    double LineX2[2];
    double LineY2[2];

    LineX1[0] = GAMMA_2 / ALPHA_1;  LineY1[0] = 0;
    LineX1[1] = 0;                  LineY1[1] = GAMMA_2 / BETTA_2;

    LineX2[0] = GAMMA_1 / BETTA_1;  LineY2[0] = 0;
    LineX2[1] = 0;                  LineY2[1] = GAMMA_1 / ALPHA_2;

    printf("\n----------------Interspecific Competition----------------\n");

    printf("X:\nGAMMA_2 / ALPHA_1: %f\nGAMMA_1 / BETTA_1: %f\n", GAMMA_2 / ALPHA_1, GAMMA_1 / BETTA_1);
    printf("\nY:\nGAMMA_2 / BETTA_2: %f\nGAMMA_1 / ALPHA_2: %f\n", GAMMA_2 / BETTA_2, GAMMA_1 / ALPHA_2);

    printf("\n---------------------------------------------------------\n");

    RK(Y, Z, Y0, Z0, f1, f2);

    write1(LineX1, LineY1, "line1");
    write1(LineX2, LineY2, "line2");

    for(i = Y0, k = 0; i < 300; i++, k++)
    {
        sprintf(buf, "1_%d", k);
        RK(Y, Z, i, Z0, f1, f2);
        write(Y, Z, buf);
    }

    for(i = Y0, k = 0; i > 0; i--, k++)
    {
        sprintf(buf, "2_%d", k);
        RK(Y, Z, i, Z0, f1, f2);
        write(Y, Z, buf);
    }

    for(i = Y0, k = 0; i < 300; i++, k++)
    {
        sprintf(buf, "3_%d", k);
        RK(Y, Z, Y0, i, f1, f2);
        write(Y, Z, buf);
    }

    for(i = Y0, k = 0; i > 0; i--, k++)
    {
        sprintf(buf, "4_%d", k);
        RK(Y, Z, Y0, i, f1, f2);
        write(Y, Z, buf);
    }

    for(i = Y0, k = 0; i < 300; i++, k++)
    {
        sprintf(buf, "5_%d", k);
        RK(Y, Z, i, i, f1, f2);
        write(Y, Z, buf);
    }

    for(i = Y0, k = 0; i > 0; i--, k++)
    {
        sprintf(buf, "6_%d", k);
        RK(Y, Z, i, i, f1, f2);
        write(Y, Z, buf);
    }

    return 0;
}

double f1(double x, double y, double z)
{
    return y * (GAMMA_1 - BETTA_1 * y - ALPHA_2 * z);
}

double f2(double x, double y, double z)
{
    return z * (GAMMA_2 - BETTA_2 * z - ALPHA_1 * y);
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

    fprintf(out,
    "# ALPHA_1 %.3f\n"
    "# ALPHA_2 %.3f\n"
    "# BETTA_1 %.3f\n"
    "# BETTA_2 %.3f\n"
    "# GAMMA_1 %.3f\n"
    "# GAMMA_2 %.3f\n"
    "# Y0 %.3f\n"
    "# Z0 %.3f\n"
    "# X_BEG %.3f\n"
    "# X_END %.3f\n"
    "# XDOTS_NUM %d\n"
    "# DX %.3f\n",
    ALPHA_1, ALPHA_2, BETTA_1, BETTA_2, GAMMA_1, GAMMA_2, m1[0], m2[0], X_BEG, X_END, XDOTS_NUM, DX);

    for(i = 0; i < XDOTS_NUM; i++)
        fprintf(out, "%7.3f %7.3f %7.3f\n", X_BEG + DX * i, m1[i], m2[i]);

    fclose(out);
    return 0;
}

int write1(double *m1, double *m2, char *str)
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

    for(i = 0; i < 2; i++)
        fprintf(out, "%7.3f %7.3f\n", m1[i], m2[i]);

    fclose(out);
    return 0;
}
