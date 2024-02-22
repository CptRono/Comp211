#include <stdio.h>

int main(void)
{
    double r, K, d, p_low, p_high, step, Th, a, prey, pred, t_steps;
    double f;
    /* read from file */
    FILE* file;
    file = fopen("rates.txt", "r");
    fscanf(file, "Prey birth rate: %lf\n", &r);
    fscanf(file, "Prey carrying capacity: %lf\n", &K);
    fscanf(file, "Predator death rate: %lf\n", &d);
    fscanf(file, "Low kill rate: %lf\n", &p_low);
    fscanf(file, "High kill rate: %lf\n", &p_high);
    fscanf(file, "Kill step: %lf\n", &step);
    fscanf(file, "Handling time: %lf\n", &Th);
    fscanf(file, "Conversion rate: %lf\n", &a);
    fscanf(file, "Initial prey population: %lf\n", &prey);
    fscanf(file, "Initial predator population: %lf\n", &pred);
    fscanf(file, "Time steps: %lf\n", &t_steps);
    
    // printf("Kill rate %lf \n", p_low);
    // printf("Kill rate %lf \n", p_high);
    printf("prey are %lf \n", prey);
    // printf("preditors are %lf \n\n", pred);

    for( ; p_low < p_high; p_low += 0.000500)
    {
        printf("Now Kill rate is %lf \n", p_low);
        for(float i = 0; i <= t_steps; i++)
        {
            
            printf("BEGIN: %lf    %lf \n", pred, prey);

            f = p_low * (prey * prey)/(1 + p_low * Th * prey * prey);
            pred = pred + a * f * pred - d * pred;
            prey = prey + r * prey * (1 - prey / K) - f * pred;
            
            /* round down to zero if either is 0 point something */
            if (prey < 1.0){prey = 0.0;};
            if (pred < 1.0){pred = 0.0;};
            
            if (prey == 0 || pred == 0)
            {
                printf("%lf    %lf Kill rate %lf is unstable\n\n", pred, prey, p_low);
                break;
            }

            if (i == t_steps && prey != 0 && pred != 0)
            /* stable if program runs 100 times without getting a 0 */
            {
                printf("%lf    %lf Kill rate %lf is stable\n", pred, prey, p_low);
            };
            /*
            if (pred || prey == 0)
            printf("%lf        %lf\n", pred, prey);
            */
        };
        //printf("Kill rate %lf is stable\n", p_low);
    }
    return 0;
}