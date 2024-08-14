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
    char* key = file_content("private.key"); //读取私钥
    char* publicKey = file_content("public.key"); //读取公钥

    Transaction* tran = transaction_make("0x0", "0x233", 100000);
    chain_transaction_add(chain, tran, key);
    chain_block_add(chain);

    displayChainBlock(chain);
    chain_vaild(chain, publicKey); //验证区块链

    return 1;
}
