# Holling Tanner model

## Model

Biology considered a model that describes the interaction between predator and prey populations.

* x1 - number of victims
* x2 - the number of predators

In the absence of predators population of victims can be described with logistic equation. Availability
predators leads to the appearance of the term in the equation OMEGA \* x1 \* X2 / (D + X1). This term describes the decrease in the number of victims due to the hunting of predators.

![Equatations](http://old.exponenta.ru/educat/class/courses/ode/theme17/images/t15.gif)

## Progect using

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

Change defines in `main.c` file which are listed below, to control some settings of progect.

### Сoefficients from equation:

```C
#define R           0.75
#define K           20.0
#define OMEGA       0.75
#define D           5.0

#define S           0.097
#define J           0.96
```

### Initial conditions:

```C
#define Y0          1.0
#define Z0          1.0
```
Here Y0 reflects initial value of x1 and Z0 such value of x2 variabels.

### Time conditions:

```C
#define X_BEG       0.0
#define X_END       100.0
#define XDOTS_NUM   1000
#define DX          (X_END - X_BEG) / (XDOTS_NUM - 1)
```
This defines can be used for animation setting.

## Result

![Animation](https://github.com/vakulin95/Math-modeling/blob/master/Holling-Tanner/files/animate_phase_out.gif)
