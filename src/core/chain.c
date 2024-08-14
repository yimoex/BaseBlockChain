Chain* chain_create(){
    Chain* chain = (Chain *)malloc(sizeof(Chain));
    chain -> height = 1;
    chain -> transactionPoolKey = 0;
    Block* first = block_create(0, "");

    chain -> creator = first;
    chain -> current = first;
    memset(chain -> transactionPool, '0', sizeof(chain -> transactionPool));
    
    block_hash(first);
    return chain;
}

int chain_block_add(Chain* chain){
    int id = chain -> height;
    chain -> height++;

    Block* block = chain -> current;
    block -> next = block_create(id, block -> hash);
    chain -> current = block -> next;
    chain_push_transaction(chain);
    block_miner(chain -> current);
    chain -> current -> next = NULL;
    return 1;
}

int chain_vaild(Chain* chain, const char* publicKey){
    Block* ptr = chain -> creator; //获取创世区块
    char* vailder, *str;
    char* hash = char_create(HASH_LENGTH);
    char* signature;
    Transaction transactionVailder;

    do {
        vailder = ptr -> hash;
        block_hash(ptr);
        if(ptr -> hash != vailder){
            printf("[Chain]: ID(%d)的区块数据可能被篡改!\n", ptr -> id);
            return 0;
        }
        printf("[Chain]: 已验证ID(%d)的区块\n", ptr -> id);
        //验证transaction
        for(int index = 0;index < ptr -> transactionSize;index++){
            transactionVailder = ptr -> transactions[index];
            str = transaction_serialize(&transactionVailder);
            blockchain_hash(str, hash);
            if(signature_verify(publicKey, hash, transactionVailder.signature, SIGNATURE_SIZE) == 0){
                printf("[Chain - Transaction]: ID(%d)的区块,ID(%d)的交易可能被篡改!\n", ptr -> id, transactionVailder.id);
                return 0;
            }
        }
    } while((ptr = ptr -> next) != NULL);
    return 1;
}

void chain_push_transaction(Chain* chain){
    Block* current = chain -> current;
    int key = chain -> transactionPoolKey;
    size_t length = sizeof(Transaction) * TRANSACTION_SIZE;
    
    memcpy(current -> transactions, chain -> transactionPool, length);
    current -> transactionSize = key;
    memset(chain -> transactionPool, 0, sizeof(chain -> transactionPool));
    chain -> transactionPoolKey = 0;
}


void chain_transaction_add(Chain* chain, Transaction* transaction, const char* skey){
    int key = chain -> transactionPoolKey;

    Transaction* trans = &(chain -> transactionPool[key]);
    strcpy(trans -> from, transaction -> from);
    strcpy(trans -> to, transaction -> to);
    strcpy(trans -> signature, transaction -> signature);
    trans -> id = key;
    trans -> amount = transaction -> amount;
    //开始
    transaction_signature(transaction, skey, trans -> signature);
    chain -> transactionPoolKey++;
}
