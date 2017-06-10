/* TO DO:
  [ ] kernel enum
  [ ] proper header setup
  [ ] constant defs
  [ ] integration
  [ ] unit tests
*/

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

// Struct for kernel and params
// (Should order be an array for other types of kerenels)?
typedef struct {
    kernelType *ktype;
    double order;
} Kernel

// all data needed for uniquely specifying and svm 
typedef struct {
    double *svector;
    double intercept;
    Kernel *k;
    int clen;
} svm; 

// functions

double __radial_product(double *features, svm *v);

double __euclidean_product(double *features, svm *v);

double __polynomial_product(double *features, svm *v);

double SvmPredict(double *features, svm *v);

double SvmClassify(double *features, svm *v);
