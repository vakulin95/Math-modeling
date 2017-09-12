# Lorenz attractor

## [Model](https://en.wikipedia.org/wiki/Lorenz_system)

The Lorenz system is a system of ordinary differential equations first studied by Edward Lorenz. It is notable for having chaotic solutions for certain parameter values and initial conditions. In particular, the Lorenz attractor is a set of chaotic solutions of the Lorenz system which, when plotted, resemble a butterfly or figure eight.

In 1963, Edward Lorenz developed a simplified mathematical model for atmospheric convection. The model is a system of three ordinary differential equations now known as the Lorenz equations:

![Eq](https://wikimedia.org/api/rest_v1/media/math/render/svg/5f993e17e16f1c3ea4ad7031353c61164a226bb8)

## Progect using

In this progect was used GSL library. To install the library package, open a Terminal and type:

`sudo apt-get install libgsl0ldbl`

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

Change defines in `main.c` file which are listed below, to control some settings of progect.

### Сoefficients from equation:

```C
#define TETA_PROP   (10.0)
#define R_PROP      (28.0)
#define B_PROP      (8.0 / 3.0)
```
Here R_PROP reflects ![](https://wikimedia.org/api/rest_v1/media/math/render/svg/1f7d439671d1289b6a816e6af7a304be40608d64) condition of equation system above.


### Initial conditions:

```C
#define INIT_X      (10.0)
#define INIT_Y      (10.0)
#define INIT_Z      (10.0)
```

### T variable settings:

```C
#define DEFAULT_T0  (0.0)
#define DEFAULT_TN  (1e+6)
#define DOTS_NUM    (1e+10)
```

## Result

![Animation](https://github.com/vakulin95/Math-modeling/blob/master/Lorenz%20attractor/files/pl_out.png)
