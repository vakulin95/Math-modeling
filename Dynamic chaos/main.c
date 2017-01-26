#include <stdio.h>
#include <math.h>

#define DOTS_NUM1       10000
#define DOTS_NUM2       1000
#define X0              0.5
#define EPS             0.001

#define X_LOC1          0
#define X_LOC2          1.0

#define R_LOC1          0
#define R_LOC2          1.0
#define DR              0.00001
#define R_DOTS_NUM      (int)((R_LOC2 - R_LOC1) / DR)

#define NUM_OF_DELTAS   7

int solve(void);
int calc_delta(float*, int);
int deg_of_2(int);

int main()
{
    printf("\n----------------DYNAMIC CHAOS----------------\n");
    solve();
    printf("\n---------------------------------------------\n");

    return 0;
}

int solve(void)
{
    int i, j, k, m, fl, kmax, r;
    float Xp, Xn, R, temp;
    float X[DOTS_NUM2], Rmas[R_DOTS_NUM];

    FILE *out;

    if(!(out = fopen("files/output.dat", "w")))
    {
        printf("File opening ERROR in solve()!\n");
        return 1;
    }

    fl = 0;
    r = 0;
    kmax = 1;
    for(R = R_LOC1, i = 0; R < R_LOC2; R += DR, i++)
    {
        Xp = X0;
        for(j = 1; j < DOTS_NUM1; j++)
        {
            Xn = 4 * R * Xp * (1 - Xp);
            Xp = Xn;
        }

        fl = 0;
        temp = Xp;
        X[0] = Xn;
        for(j = 1, k = 1; j < DOTS_NUM2; j++)
        {
            Xn = 4 * R * Xp * (1 - Xp);
            if(fabsf(Xn - temp) > EPS)
            {
                // Repetition control
                for(m = 0; m < k; m++)
                {
                    if(fabs(Xn - X[m]) < 0.001)
                    {
                        fl = 1;
                        break;
                    }
                }

                if(!fl)
                {
                    X[k] = Xn;
                    k++;
                }
                else
                    fl = 0;

                temp = Xn;
            }
            Xp = Xn;
        }

        // Writing "X" values for current "R"
        for(m = 0; m < k; m++)
            fprintf(out, "%.4f %.4f\n", R, X[m]);
        fprintf(out, "\n");

        // "k" changing control
        if(k > kmax && !(k % 2) && deg_of_2(k))
        {
            Rmas[r] = R;
            r++;
            kmax = k;
        }
        else if(k < kmax)
            kmax = k;
    }

    // Delta calculation
    if(calc_delta(Rmas, NUM_OF_DELTAS))
        return -1;

    fclose(out);
    return 0;
}

int calc_delta(float *R, int N)
{
    int i;
    float delta;

    FILE *out_r;

    if(N < 3)
    {
        printf("ERROR in calc_del() func!\n Mass R too small\n");
        return 1;
    }

    if(!(out_r = fopen("files/out_r.dat", "w")))
    {
        printf("File opening ERROR in clac_delta()!\n");
        return -1;
    }

    for(i = 0; i < N - 2; i++)
    {
        delta = (R[i + 1] - R[i]) / (R[i + 2] - R[i + 1]);
        fprintf(out_r, "R[%d]\t%f\tdelta\t%f\n", i,  R[i], delta);
        printf("R[%d]\t%f\tdelta\t%f\n", i,  R[i], delta);
    }

    fclose(out_r);
    return 0;
}

int deg_of_2(int x)
{
    return (x <= 0) ? 0 : (x & (x-1)) == 0;
}
