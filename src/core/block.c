Block* block_create(int id, char prevHash[]){
    Block* block = (Block *)malloc(sizeof(Block));
    block -> id = id;
    block -> transactionSize = 0;
    strcpy(block -> prevHash, prevHash);
    memset(block -> transactions, 0, sizeof(block -> transactions));
    return block;
}

void md5_hex(unsigned char* digest, char* md5_string) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&md5_string[i * 2], "%02x", digest[i]);
    }
    md5_string[MD5_DIGEST_LENGTH * 2] = '\0';
}


int block_hash(Block* block){
    char* json_string = transaction_list_serialize(block -> transactions, block -> transactionSize);
    size_t dataSize = strlen(block -> hash) + strlen(json_string) + sizeof(int);
    char* data = string_create(dataSize); //prevHash + data + nonce
    char* ptr = int2charPtr(block -> nonce);

    strcat(data, block -> hash);
    strcat(data, json_string);
    strcat(data, ptr); //Nonce

    char temp[BLOCK_HASH_SIZE] = {0};
    char temp2[BLOCK_HASH_SIZE] = {0};
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5, data, strlen(data));
    MD5Final(&md5, temp);

    md5_hex(temp, temp2);
    string_clear(block -> hash);
    strncpy(block -> hash, temp2, strlen(temp2));

    free(ptr);
    free(data);
    free(json_string);
    return 1;
}

int block_miner_check(char* value){
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
