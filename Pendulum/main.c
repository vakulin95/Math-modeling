#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 			3.14159265

#define OMEGA 		1
#define LAMBDA 		0.2

#define PHI0 		2
#define DPHI0 		2.4

#define DEFAULT_A 	0
#define DEFAULT_B 	6*PI
#define DOTS_NUM 	10000
#define STEP 		((DEFAULT_B - DEFAULT_A) / DOTS_NUM)

double f1(double x, double y, double z);
double f2(double x, double y, double z);
double f3(double x, double y, double z);
double f4(double x, double y, double z);
void RK(double *y, double *z, double(*f1)(double, double, double), double(*f2)(double, double, double), int cas);
void write(double *x, double *y, char *s);

int main()
{
	double Phi[DOTS_NUM];
	double dPhi[DOTS_NUM];

	RK(Phi, dPhi, f1, f2, 1);		//exact solution
	write(Phi, dPhi, "_exact1");
	RK(Phi, dPhi, f1, f2, 0);
	write(Phi, dPhi, "_exact0");

	RK(Phi, dPhi, f1, f3, 1);		//stable equilibrium solution
	write(Phi, dPhi, "_stable");

	RK(Phi, dPhi, f1, f4, 1);		//unstable equilibrium
	write(Phi, dPhi, "_unstable1");
	RK(Phi, dPhi, f1, f4, 0);
	write(Phi, dPhi, "_unstable0");

	return 0;
}

double f1(double x, double y, double z)
{
	return z;
}

//exact
double f2(double x, double y, double z)
{
	return -OMEGA * sin(y) - LAMBDA * z;
}

//stable
double f3(double x, double y, double z)
{
	return -OMEGA * y - LAMBDA * z;
}

//unstable
double f4(double x, double y, double z)
{
	return (OMEGA * y - PI) - LAMBDA * z;
}

void RK(double *y, double *z, double(*f1)(double, double, double), double(*f2)(double, double, double), int cas)
{
	int i;
	int x = DEFAULT_A;
	double k1, k2, k3, k4, l1, l2, l3, l4, hr;

	if (cas == 1)
		hr = STEP;
	else
		hr = -STEP;

	y[0] = PHI0;
	z[0] = DPHI0;

	for (i = 1; i < DOTS_NUM; i++)
	{
		k1 = hr * f1(x, y[i - 1], z[i - 1]);
		l1 = hr * f2(x, y[i - 1], z[i - 1]);

		k2 = hr * f1(x + hr / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);
		l2 = hr * f2(x + hr / 2, y[i - 1] + k1 / 2, z[i - 1] + l1 / 2);

		k3 = hr * f1(x + hr / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);
		l3 = hr * f2(x + hr / 2, y[i - 1] + k2 / 2, z[i - 1] + l2 / 2);

		k4 = hr * f1(x + hr, y[i - 1] + k3, z[i - 1] + l3);
		l4 = hr * f2(x + hr, y[i - 1] + k3, z[i - 1] + l3);

		x += hr;
		y[i] = y[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		z[i] = z[i - 1] + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
	}
}

void write(double *x, double *y, char *s)
{
	int i;
	double t = DEFAULT_A;
	FILE *out_File;
	char buff[50];

	sprintf(buff, "files/output%s.dat", s);
	out_File = fopen(buff, "w");

	for (i = 0; i < DOTS_NUM; i++)
	{
		fprintf(out_File, "%f  %f  %f\n", t, x[i], y[i]);
		t += STEP;
	}

	fclose(out_File);
}
