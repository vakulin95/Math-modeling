#include <stdio.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#define TETA_PROP   (10.0)
#define R_PROP      (28.0)
#define B_PROP      (8.0 / 3.0)

#define STEP        (1e-10)

#define INIT_X      (10.0)
#define INIT_Y      (10.0)
#define INIT_Z      (10.0)

#define DEFAULT_T0  (0.0)
#define DEFAULT_TN  (1e+6)
#define DOTS_NUM    (1e+10)

int func(double t, const double y[], double f[], void *params);
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params);

int main(void)
{
    int i, status;

    double ti;
    double t = DEFAULT_T0;
    double y[3]   = {
                        INIT_X,
                        INIT_Y,
                        INIT_Z
                    };
    double params[3];

    FILE *out;

    if(!(out = fopen("files/out.dat", "w")))
    {
        printf("ERROR! Output stream.\n");
        return -1;
    }

    params[0] = TETA_PROP;
    params[1] = R_PROP;
    params[2] = B_PROP;

    gsl_odeiv2_system ode_system;

    ode_system.function = func;
    ode_system.jacobian = jac;
    ode_system.dimension = 3;
    ode_system.params = params;

    gsl_odeiv2_driver *driver;

    driver = gsl_odeiv2_driver_alloc_y_new(&ode_system, gsl_odeiv2_step_rk8pd, STEP, 1e-6, 0.0);

    for (i = DEFAULT_T0; i < DEFAULT_TN; i++)
    {
        ti = i * (DEFAULT_TN - DEFAULT_T0) / DOTS_NUM;

        status = gsl_odeiv2_driver_apply (driver, &t, ti, y);

        if (status != GSL_SUCCESS)
        {
            printf ("error, return value = %d\n", status);
            break;
        }

        fprintf(out, "%.5lf %.5lf %.5lf\n", y[0], y[1], y[2]);
    }

    gsl_odeiv2_driver_free (driver);

    return 0;
}

int func(double t, const double y[], double f[], void *params)
{
    (void)(t);

    double teta = ((double *)params)[0];
    double r = ((double *)params)[1];
    double b = ((double *)params)[2];

    /*
        x = y[0]
        y = y[1]
        z = y[2]
    */

    f[0] = -teta * y[0] + teta * y[1];
    f[1] = -y[0] * y[2] + r * y[0] - y[1];
    f[2] = y[0] * y[1] - b * y[2];

    return GSL_SUCCESS;
}

int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t);

    double teta = ((double *)params)[0];
    double r = ((double *)params)[1];
    double b = ((double *)params)[2];

    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 3, 3);
    gsl_matrix *jacobi = &dfdy_mat.matrix;

    gsl_matrix_set (jacobi, 0, 0, -teta);
    gsl_matrix_set (jacobi, 0, 1, teta);
    gsl_matrix_set (jacobi, 0, 2, 0.0);

    gsl_matrix_set (jacobi, 1, 0, -y[2] + r);
    gsl_matrix_set (jacobi, 1, 1, -1.0);
    gsl_matrix_set (jacobi, 1, 2, -y[0]);

    gsl_matrix_set (jacobi, 2, 0, y[1]);
    gsl_matrix_set (jacobi, 2, 1, y[0]);
    gsl_matrix_set (jacobi, 2, 2, -b);

    dfdt[0] = 0.0;
    dfdt[1] = 0.0;

    return GSL_SUCCESS;
}
