typedef struct _Block {
    int id;
    int nonce;
    char hash[BLOCK_HASH_SIZE];
    char prevHash[BLOCK_HASH_SIZE];
    Transaction transactions[TRANSACTION_SIZE];
    int transactionSize;
    time_t timestamp;
    struct _Block* next;
} Block;
