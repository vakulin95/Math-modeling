#include "meta.h"

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
