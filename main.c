#include <stdio.h>
#include <math.h>

#define DOTS_NUM1 1000
#define DOTS_NUM2 100
#define X0 0.5
#define EPS 0.01

#define X_LOC1 0
#define X_LOC2 1.0

#define R_LOC1 0.7
#define R_LOC2 0.8
#define DR 0.001 //(R_LOC2 - R_LOC1) / (DOTS_NUM2 + 1)

int solve(void);
float clac_del();

int main()
{
    solve();

    return 0;
}

int solve(void)
{
    int i, j;
    float Xp, Xn, R, temp;

    FILE *out;

    if(!(out = fopen("files/output.dat", "w")))
    {
        printf("File opening ERROR!\n");
        return 1;
    }

    temp = X0;
    for(R = R_LOC1, i = 0; R < R_LOC2; R += DR, i++)
    {
        Xp = X0;
        for(j = 1; j < DOTS_NUM1; j++)
        {
            Xn = 4 * R * Xp * (1 - Xp);
            Xp = Xn;
        }


        for(j = 1; j < DOTS_NUM2; j++)
        {
            Xn = 4 * R * Xp * (1 - Xp);
            //fprintf(out, "%f\n", Xn - temp);
            if(fabsf(Xn - temp) > EPS)
            {
                fprintf(out, "%.3f %.3f\n", R, Xn);
                temp = Xn;
            }
            Xp = Xn;
        }
        //fprintf(out, "\n");
    }

    fclose(out);
    return 0;
}
