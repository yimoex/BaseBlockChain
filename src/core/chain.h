typedef struct _Chain {
    int height;
    Block* creator;
    Block* current;
    Transaction transactionPool[TRANSACTION_SIZE];
    int transactionPoolKey;
} Chain;

void chain_push_transaction(Chain* chain);