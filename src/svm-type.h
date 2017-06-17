#ifndef __SVM_TYPE_H__
#define __SVM_TYPE_H__

#include "redismodule.h"
#include "svm.h"

#define SVMTYPE_ENCODING_VERSION 0
#define SVMTYPE_NAME "RLML_SVM"

#define REDIS_ML_SVM_ERROR_WRONG_KERNEL_TYPE "Wrong kernel type, should be \'EUCLIDEAN\', \'POLYNOMIAL\' or \'RADIAL\'"

extern RedisModuleType *SvmType;

void *SvmTypeRdbLoad(RedisModuleIO *, int);

void SvmTypeRdbSave(RedisModuleIO *, void *);

void SvmTypeAofRewrite(RedisModuleIO *, RedisModuleString *, void *);

void SvmTypeDigest(RedisModuleDigest *, void *);

void SvmTypeFree(void *value);

int SvmTypeRegister(RedisModuleCtx *ctx);

#endif /*__SVM-TYPE_H__*/
