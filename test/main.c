#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "libs/loader.h" //依赖库加载器

#include "core/config.h"
#include "core/public.c"

#include "core/transaction.h"
#include "core/block.h"
#include "core/chain.h"

#include "core/signature.c"
#include "core/transaction.c"
#include "core/block.c"
#include "core/chain.c"

#include "debuger.c"

typedef struct {
    int id;
    char name[64];
} Book;

int main(){
    
    Chain* chain = chain_create();
    srand((unsigned int)time(NULL));

    randBlock(chain); //随机生成区块

    displayChainBlock(chain); //展示所有区块链
    chain_vaild(chain); //验证区块链

    return 1;
}
