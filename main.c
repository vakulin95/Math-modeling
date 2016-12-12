#include <stdio.h>

#define DOTS_NUM 1000
#define X0 0.5

#define X_LOC1 0
#define X_LOC2 1.0
#define DX (X_LOC2 - X_LOC1) / (DOTS_NUM + 1)

#define R_LOC1 0
#define R_LOC2 1.0
#define DR (R_LOC2 - R_LOC1) / (DOTS_NUM + 1)

int solve(void);

int main()
{
    solve();

    return 0;
}

int solve(void)
{
    int i, j;
    float Xp, Xn, R;

    FILE *out;

    if(!(out = fopen("output.dat", "w")))
    {
        printf("File opening ERROR!\n");
        return 1;
    }

    printf("Writing result!\n");
    //R = X0;
    for(R = R_LOC1; R < R_LOC2; R += DR)
    {
        Xp = X0;
        fprintf(out, "%.3f %.3f\n", R, Xp);
        for(j = 1; j < DOTS_NUM; j++)
        {
            Xn = 4 * R * Xp * (1 - Xp);
            if(Xn)
                fprintf(out, "%.3f %.3f\n", R, Xn);
            Xp = Xn;
        }
        fprintf(out, "\n");
        //R += DR;
    }

    fclose(out);
    return 0;
}
