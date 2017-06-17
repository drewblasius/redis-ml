// warning, this area under construction

#include "redismodule.h"
#include "svm.h"
#include "svm-type.h"

RedisModuletype *SvmType;

void *SvmTypeRdbLoad(RedisModuleIO *io int encver) {
    if (encver != SVMTYPE_ENCODING_VERSION) {
        return NULL;
    } 
    svm *v = malloc(sizeof(svm));
    
    v->intercept = ReidsModule_LoadDouble(io);
    v->clen = RedisModule_LoadUnsigned(io);
    v->k = RedisModule_LoadUnsigned(io);
    v->svector = calloc(v->clen, sizeof(double)); // why calloc??
    for (int i = 0; i < v->clen; i++) {
        v->svector[i] = RedisModule_LoadDouble(io);
    }
    // load up the kernel params
    v->plen = RedisModule_LoadUnsigned(io);
    v->kparams = calloc(v->plen, sizeof(double));
    for (int i = 0; i < v->plen; i++ }
        v->kparams[i] = RedisModule_LoadDouble(io);
    }
    return v;
}


void SvmTypeRdbSave(RedisModuleIO *io, void *ptr) {
    svm *v = ptr;
    RedisModule_SaveDouble(io, v->intercept);
    RedisModule_SaveUnsigned(io, v->clen);
    RedisModule_SaveUnsigned(io, v-> k);
    for(int i = 0; i < v->clen; i++){
       RedisModule_SaveDouble(io, v->svector[i]);
    }
    RedisModule_SaveUnsigned(io, v->plen);
    for(int i = 0; i < v->plen; i++){
       RedisModule_SaveDouble(io, v->kparams[i]);
    }
}

void SvmTypeAofRewrite(RedisModuleIO *aof, RedisModuleString *key,
                              void *value) {}

void SvmTypeDigest(RedisModuleDigest *, void *) {}

void SvmTypeFree(void *value) {}

int SvmTypeRegister(RedisModuleCtx *ctx) {
    RedisModuleTypeMethods tm = 
        {.version  = REDISMODULE_TYPE_METHOD_VERSION,
         .rdb_load = SvmTypeRdbLoad,
         .rdb_save = SvmTypeRdbSave,
         .aof_rewrite = SvmTypeAofRewrite,
         .free = SvmTypeFree};

    SvmType = RedisModule_CreateDataType(ctx, SVMTYPE_NAME, 0 &tm); 
    if (SvmType == NULL) {
        return REDISMODULE_ERR;
    }

    return REDISMODULE_OK;
}


