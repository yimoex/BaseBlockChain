Block* block_create(int id, char prevHash[]){
    Block* block = (Block *)malloc(sizeof(Block));
    block -> id = id;
    block -> transactionSize = 0;
    strcpy(block -> prevHash, prevHash);
    memset(block -> transactions, 0, sizeof(block -> transactions));
    return block;
}

int block_hash(Block* block){
    char* json_string = transaction_list_serialize(block -> transactions, block -> transactionSize);
    size_t dataSize = strlen(block -> hash) + strlen(json_string) + sizeof(int);
    char* data = char_create(dataSize); //prevHash + data + nonce
    char* ptr = int2charPtr(block -> nonce);

    strcat(data, block -> hash);
    strcat(data, json_string);
    strcat(data, ptr); //Nonce

    char* buffer = char_create(HASH_LENGTH);
    blockchain_hash(data, buffer);
    MD5_hex(buffer, block -> hash);

    free(buffer);
    free(ptr);
    free(data);
    free(json_string);
    return 1;
}

int block_miner_check(const char* value){
    for(int i = 0;i < CHAIN_DIFFICULTY;i++){
        if(value[i] != '0'){
            return 0;
        }
    }
    return 1;
}

//挖矿
void block_miner(Block* block){
    int nonce = 0;
    do {
        block_hash(block);
        nonce++;
    } while(!block_miner_check(block -> hash));
    //printf("[Chain] 已找到目标Nonce: %d\n", nonce);
}
