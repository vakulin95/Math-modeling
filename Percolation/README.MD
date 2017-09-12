# Pendulum

## [Model](https://en.wikipedia.org/wiki/Pendulum)

The differential equation which represents the motion of a simple pendulum is

![Eq](https://wikimedia.org/api/rest_v1/media/math/render/svg/36e0d601a33a7562dfb162abd7e58859a40ccff1)

* _g_ - acceleration due to gravity;
* _l_ - length of the pendulum;
* _θ_ - angular displacement.

## Progect using

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

Change defines in `main.c` file which are listed below, to control some settings of progect.

### Сoefficients from equation:

```C
#define OMEGA 		1
#define LAMBDA 		0.2
```

|define     |description    |
|:---------:|:-------------:|
|OMEGA      |g/l            |
|LAMBDA     |coefficient characterizing the power of resistance to damped pendulum               |

### Initial conditions:

```C
#define PHI0 		2
#define DPHI0 		2.4
```

Here `PHI` characterizes _θ_ which was mentioned in the previous section.

### Time conditions::

```C
#define DEFAULT_A 	0
#define DEFAULT_B 	6*PI
#define DOTS_NUM 	10000
#define STEP 		((DEFAULT_B - DEFAULT_A) / DOTS_NUM)
```
This defines can be used to control some plotting settings.

## Result

![Animation](https://github.com/vakulin95/Math-modeling/blob/master/Pendulum/files/MM_phase.pdf)
