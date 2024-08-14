void displayChainBlock(Chain* chain){
    Block* temp;
    temp = chain -> creator;
    size_t size = sizeof(Block);
    do {
        printf("Block ID: %d\n", temp -> id);
        printf("Block Hash: %s\n", temp -> hash);
        printf("Block PrevHash: %s\n", temp -> prevHash);
        printf("Block TransactionSize: %d\n", temp -> transactionSize);
        printf("==================\n");
    } while((temp = temp -> next) != NULL);
}

void generateRandomString(char *str, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    size_t charset_size = sizeof(charset) - 1;

    if(length > 0){
        srand(time(NULL));
        for (size_t i = 0; i < length; i++) {
            int key = rand() % charset_size;
            str[i] = charset[key];
        }
        str[length] = '\0';
    }
}

void randTransaction(Chain* chain, const char* key){
    Transaction* trans = (Transaction *)malloc(sizeof(Transaction));
    char address[32] = {0};
    char addressTo[32] = {0};
    generateRandomString(address, 32);
    generateRandomString(addressTo, 32);

    strcat(trans -> from, "0x");
    strcat(trans -> from, address);
    strcat(trans -> to, "0x");
    strcat(trans -> to, addressTo);
    strcpy(trans -> signature, "hello debugger");
    trans -> amount = rand();
    /*
    printf("[DEBUG]: 已生成随机Transaction\n");
    printf("FROM: 0x%s\n", address);
    printf("TO: 0x%s\n", addressTo);
    printf("amount: %ld\n", trans -> amount);
    printf("+++++++++++++++\n");
    */
    chain_transaction_add(chain, trans, key);
    free(trans);
}

void randBlock(Chain* chain, const char* key){
    int counts = rand() % 9;
    for(int i = 0;i < counts;i++){
        randTransaction(chain, key);
    }
    chain_block_add(chain);
}


