# String

## [Model](http://www.animations.physics.unsw.edu.au/jw/wave_equation_speed.htm)

This progect represents comparison of discrete and continuous solutions for string oscillations with fixed ends.

## Progect using

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

Change defines in `main.c` file which are listed below, to control some settings of progect.

### Сoefficient for the model:

```C
#define A_PROP 10.0
```

### Time conditions::

```C
#define TIME_LOC1 0
#define TIME_LOC2 1.0
...
#define TDOTS_NUM 1000
```
This defines can be used to control some plotting settings.

## Result

![GIF](https://github.com/vakulin95/Math-modeling/blob/master/String/files/out.gif)
