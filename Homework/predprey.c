#include <stdio.h>

int main(void)
{
    double r, K, d, p, Th, a, prey, pred, t_steps;
    double f;
    /* read from file */
    FILE* file;
    file = fopen("params.txt", "r");
    fscanf(file, "Prey birth rate: %lf\n", &r);
    fscanf(file, "Prey carrying capacity: %lf\n", &K);
    fscanf(file, "Predator death rate: %lf\n", &d);
    fscanf(file, "Kill rate: %lf\n", &p);
    fscanf(file, "Handling time: %lf\n", &Th);
    fscanf(file, "Conversion rate: %lf\n", &a);
    fscanf(file, "Initial prey population: %lf\n", &prey);
    fscanf(file, "Initial predator population: %lf\n", &pred);
    fscanf(file, "Time steps: %lf\n", &t_steps);

    for(float i = 0; i <= t_steps; i++)
    {
        f = p*(prey * prey)/(1 + p * Th * prey * prey);
        pred = pred + a * f * pred - d * pred;
        prey = prey + r * prey * (1 - prey / K) - f * pred;
        printf("%lf        %lf\n", pred, prey);
    };
    return 0;
}