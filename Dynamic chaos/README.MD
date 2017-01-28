# Dynamic chaos

## [Model](https://en.wikipedia.org/wiki/Period-doubling_bifurcation)

In mathematics, a period doubling bifurcation in a discrete dynamical system is a bifurcation in which a slight change in a parameter value in the system's equations leads to the system switching to a new behavior with twice the period of the original system. With the doubled period, it takes twice as many iterations as before for the numerical values visited by the system to repeat themselves.

Consider the following simple dynamics:
![Alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/b84673eee90dff3113ee6263cc20a628979cc11d) where ![Alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/7c5ea190699149306d242b70439e663559e3ffbe), the value of ![Alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/87f9e315fd7e2ba406057a97300593c4802b53e4) at time ![Alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/a601995d55609f2d9f5e233e36fbe9ea26011b3b), lies in the [0,1] interval and changes over time according to the parameter ![Alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/95233b14c983dc586ede442328058442616db86c). This classic example is a simplified version of the logistic map.

## Progect using

* Run `make` to launch the project
* Run `make plot` to plot result without launching the program

### Model settings:

```C
#define DOTS_NUM1       10000
#define DOTS_NUM2       1000
#define X0              0.5
#define EPS             0.001
```

### Calculation bounds:

```C
#define X_LOC1          0
#define X_LOC2          1.0

#define R_LOC1          0
#define R_LOC2          1.0
```

### Number of dots:

```C
#define DR              0.00001
#define R_DOTS_NUM      (int)((R_LOC2 - R_LOC1) / DR)
```

## Result

![Alt text](https://github.com/vakulin95/Math-modeling/blob/master/Dynamic%20chaos/files/pl_out.png)
