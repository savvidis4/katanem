#include "erg1.h"
#include <stdlib.h>

int *eswt_ginom_1_svc(pin_args *args, struct svc_req *rqstp) {
    static int result;
    
    result = 0;
    for (int i = 0; i < args->n; i++) {
        result += args->pina.pina_val[i] * args->pinb.pinb_val[i];
    }
    
    return &result;
}

averages_ret *averages_1_svc(pin_args *args, struct svc_req *rqstp) {
    static averages_ret result;
    double sum_a = 0, sum_b = 0;
    
    for (int i = 0; i < args->n; i++) {
        sum_a += args->pina.pina_val[i];
        sum_b += args->pinb.pinb_val[i];
    }
    
    result.avg_a = sum_a / args->n;
    result.avg_b = sum_b / args->n;
    
    return &result;
}

ginom_r_ret *ginom_r_1_svc(ginom_r_args *args, struct svc_req *rqstp) {

    static ginom_r_ret result;
    
    result.epistr.epistr_val = (double *)malloc(args->n * sizeof(double));
    result.epistr.epistr_len = args->n;
    
    for (int i = 0; i < args->n; i++) {
        result.epistr.epistr_val[i] = args->pin.pin_val[i] * args->r;
    }
    
    return &result;
}