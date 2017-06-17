#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feature-vec.h"
#include "util/thpool.h"

// enum for all of the types of kernel that we'll allow to be used in prediction
typedef enum {
    EUCLIDEAN,
    POLYNOMIAL,
    RADIAL,
} KernelType;


// kparams has the following entries

/* EUCLIDEAN:
 kparams[0] : 0 
   POLYNOMIAL:
 kparams[0] : <offset for kernel> 
 kparams[1] : <order of kernel>
   RADIAL
 kparams[0] : <sigma>  
*/

// all data needed for uniquely specifying and svm 
typedef struct {
    double *svector;
    double intercept;
    enum KernelType k;
    double *kparams; 
    int clen;
    int plen; // length of param vector
} svm; 

// functions

double __radial_product(double *features, svm *v);

double __euclidean_product(double *features, svm *v);

double __polynomial_product(double *features, svm *v);

double SvmPredict(double *features, svm *v);

double SvmClassify(double *features, svm *v);
