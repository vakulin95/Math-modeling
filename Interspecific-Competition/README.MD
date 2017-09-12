# Interspecific-Competition

## [Model](https://en.wikipedia.org/wiki/Interspecific_competition)

The impacts of interspecific competition on populations have been formalized in a mathematical model called the Competitive Lotka–Volterra equations, which creates a theoretical prediction of interactions. It combines the effects of each species on the other. These effects are calculated separately for the first and second population respectively:

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/63551972a8cadc18c4b2c7ae112638039229b8e6)

![Equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/384821b0b4c530e964cdb2570e4d9cf07fa71374)

* N - population size;
* t - time;
* K - carrying capacity;
* r - intrinsic rate of increase;
* α - relative competition coefficient;
* β - relative competition coefficient.

An equivalent formulation of these models is:

![Equation1](http://library.biophys.msu.ru/LectMB/lect09.files/image002.gif)

* N - population size variable;
* a - increment rate coefficient;
* b - coefficient describing the influence of another population;
* c - coefficient describing intraspecific impact.

## Progect using

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

Change defines in `main.c` file which are listed below, to control some settings of progect.

### Сoefficients from equation:

```C
#define ALPHA_1     0.002
#define ALPHA_2     0.001

#define BETTA_1     0.004
#define BETTA_2     0.001

#define GAMMA_1     0.5
#define GAMMA_2     0.5
```

| define        | coefficient   |
| ------------- |:-------------:|
|  `ALPHA_*`    | b             |
| `BETTA_*`     | c             |
| `GAMMA_*`     | a             |

### Initial conditions:

```C
#define Y0          150.0
#define Z0          200.0
```

|define|variable   |
|:------:|:-------:|
|`Y0`|N1|
|`Z0`|N2|

### Time conditions:

```C
#define X_BEG       0.0
#define X_END       100.0
#define XDOTS_NUM   1000
#define DX          ((X_END - X_BEG) / (XDOTS_NUM - 1))
```
This defines can be used for animation setting.

## Result

![Animation](https://github.com/vakulin95/Math-modeling/blob/master/Interspecific-Competition/files/animate_phase_out.gif)
