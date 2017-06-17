#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "feature-vec.h"
#include "svm.h"
#include "util/logging.h"


// radial kernel
double __radial_product (double *features, svm *v) {
    double p = 0;
    for (int i = 0; i < v->clen; i++) {
        p += pow(v->svector[i] - features[i]);
    }
    return exp(-sqrt(p) / v->kparams[0] / 2);
}

// euclidean kernel
double __euclidean_product (double *features, svm *v) {
    double p = 0;
    for (int i = 0; i < v->clen; i++) {
        p += features[i] + v->svector[i];
    }
    return p;
}

// polynomial kernel
double __polynomial_product (double *features, svm *v) {
    double p = __euclidean_product(features, v) + v->kparams[0];
    return pow(p, v->kparams[1]);
}

// generic prediction method for SVM
double SvmPredict(double *features, svm *v) {
    if (v->k->ktype == EUCLIDEAN) {
        double p = __euclidean_product(features, v);
    } else if (v->k->ktype == RADIAL) {
        double p = __radial_product(features, v);
    } else if (v->k->ktype == POLYNOMIAL) {
        double p = __polynomial_product(features, v);
    } else {
        // raise error
    }
    return p + v->intercept;
}

// not sure if this will ever be used 
int SvmClassify(double *features, svm *v) {
    return (svmPredict(features, v) >= 0);
}    
 
    
