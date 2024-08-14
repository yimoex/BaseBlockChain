Transaction* transaction_make(const char* from, const char* to, int64_t amount){
    Transaction* trans = (Transaction *)malloc(sizeof(Transaction));
    strcpy(trans -> from, from);
    strcpy(trans -> to, to);
    trans -> amount = amount;
    return trans;
}

cJSON* transaction2json(Transaction* tx){
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", tx -> id);
    cJSON_AddNumberToObject(json, "amount", tx -> amount);
    cJSON_AddStringToObject(json, "from", tx -> from);
    cJSON_AddStringToObject(json, "to", tx -> to);
    return json;
}

char* transaction_serialize(Transaction* tx){
    cJSON* json = transaction2json(tx);
    char* json_string = cJSON_Print(json);
    cJSON_Delete(json);
    return json_string;
}

int transaction_signature(Transaction* transaction, const char* key, char* res){
    unsigned int signSize;
    char* buffer = char_create(HASH_LENGTH);
    char* result = char_create(HASH_LENGTH);

    char* str = transaction_serialize(transaction);

    blockchain_hash(str, buffer);
    signature_sign(key, buffer, res, &signSize);

    free(buffer);
    free(str);

    return signSize;
}

char* transaction_list_serialize(Transaction transactions[], int transactionSize){
    cJSON *json_list = cJSON_CreateArray();
    if(transactions != NULL && transactionSize != 0){
        for (int i = 0; i < transactionSize; i++) {
            cJSON *json_tx = transaction2json(&transactions[i]);
            cJSON_AddItemToArray(json_list, json_tx);
        }
    }
    char* json_string = cJSON_Print(json_list);
    cJSON_Delete(json_list);
    return json_string;
}

