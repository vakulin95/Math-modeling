#ifndef __META_H__

#define __META_H__

#endif

#include <math.h>
#include <stdio.h>
#include <math.h>

#define A_PROP 10.0
#define TIME_LOC1 0
#define TIME_LOC2 1.0
#define TLEN ( TIME_LOC2 - TIME_LOC1 )

#define TERMS_NUM 10

#define XDOTS_NUM 100
#define DX ( XLEN / (XDOTS_NUM - 1) )
#define TDOTS_NUM 1000
#define DT ( TLEN / (TDOTS_NUM - 1) )

#define PI 3.14159265

#define ATT_LOC1 0
#define ATT_LOC2 1.0
#define XLEN ( ATT_LOC2 - ATT_LOC1 )

double phi(double);
double phi_s(double, double);
double ksi(double);
double ksi_s(double, double);
