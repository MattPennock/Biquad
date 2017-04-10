#include <math.h>
#include <stdio.h>
#include "biquad.h"

const float pi = 3.141592654;

/*
 *          Prototypes
 */
void CONFIG_BandPass(biquad_t *bq, float center_freq, float bandwidth);

/*
 *            Code
 */
int main(void)
{
    biquad_t bq;
    BQ_init(&bq);
    CONFIG_BandPass(&bq, 0.5*pi, 0.1*pi);

    printf("Numerator Ring: \r\n");
    RB3_print(&(bq.num_coeff));

    printf("Denominator Ring: \r\n");
    RB3_print(&(bq.den_coeff));
}

void CONFIG_BandPass(biquad_t *bq, float center_freq, float bandwidth)
{
    float beta = cosf(center_freq);
    float inv_beta = 1.0f / beta;
    float det = sqrtf((inv_beta*inv_beta) - 1.0f);
    float alpha = inv_beta - det;

    float a1 = beta * (1-alpha);
    float a2 = alpha;
    
    float num = (1.0f - alpha) / 2.0f;

    BQ_setDen(bq, a1, a2);
    BQ_setNum(bq, num, 0.0f, num);
}
