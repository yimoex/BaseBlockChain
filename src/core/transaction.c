Transaction* transaction_make(char from[], char to[], int64_t amount, char signature[]){
    Transaction* trans = (Transaction *)malloc(sizeof(Transaction));
    strcpy(trans -> from, from);
    strcpy(trans -> to, to);
    strcpy(trans -> signature, signature);
    trans -> amount = amount;
    return trans;
}

cJSON* transaction2json(Transaction* tx){
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", tx -> id);
    cJSON_AddNumberToObject(json, "amount", tx -> amount);
    cJSON_AddStringToObject(json, "from", tx -> from);
    cJSON_AddStringToObject(json, "to", tx -> to);
    cJSON_AddStringToObject(json, "signature", tx -> signature);
    return json;
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

