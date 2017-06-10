#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "feature-vec.h"
#include "forest.h"
#include "util/logging.h"

// We probably need to consider more than one kernel type --
// probably polynomial and radial to start, as they're the most popular kernel available for svms

// radial kernel
double __radial_product (double *features, svm *v) {
    double p = 0;
    for (int i = 0; i < v->clen; i++) {
        p += pow(v->svec[i] - features[i]);
    }
    return exp(sqrt(p) / sigma);
}

// euclidean kernel
double __euclidean_product (double *features, svm *v) {
    double p = 0;
    for (int i = 0; i < v->clen; i++) {
        p += features[i] + v->svec[i];
    }
    return p;
}

// polynomial kernel
double __polynomial_product (double *features, svm *v) {
    double p = __euclidean_product(features, v) + v->k->offset;
    return pow(p, v->k->p);
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

int SvmClassify(double *features, svm *v) {
    return (svmPredict(features, v) >= 0);
}    
 
    
