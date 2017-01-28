# Lorenz attractor

## [Model](https://en.wikipedia.org/wiki/Lorenz_system)

The Lorenz system is a system of ordinary differential equations first studied by Edward Lorenz. It is notable for having chaotic solutions for certain parameter values and initial conditions. In particular, the Lorenz attractor is a set of chaotic solutions of the Lorenz system which, when plotted, resemble a butterfly or figure eight.

In 1963, Edward Lorenz developed a simplified mathematical model for atmospheric convection. The model is a system of three ordinary differential equations now known as the Lorenz equations:

![Eq](https://vk.com/im?peers=201981150&sel=205302014&z=photo20124574_456239144%2Fmail347330)

## Progect using

In this progect was used GSL library. To install the library package, open a Terminal and type: `sudo apt-get install libgsl0ldbl`

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

### Сoefficients from equation:

```C
#define TETA_PROP   (10.0)
#define R_PROP      (28.0)
#define B_PROP      (8.0 / 3.0)
```

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

![Animation](https://github.com/vakulin95/Math-modeling/blob/master/Interspecific-Competition/files/animate_phase_out.gif)
