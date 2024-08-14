typedef struct _Transaction {
    int id;
    char from[ADDRESS_SIZE];
    char to[ADDRESS_SIZE];
    int64_t amount;
    char signature[SIGNATURE_SIZE];
} Transaction;

