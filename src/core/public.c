char* int2charPtr(int val){
    char* temp = (char *)malloc(2 * sizeof(char));
    temp[0] = val;
    temp[1] = '\0';
    return temp;
}

void blockchain_hash(char* data, char* buffer){
    char temp[32] = {0};
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5, data, strlen(data));
    MD5Final(&md5, temp);
    strcpy(buffer, temp);
}

char* char_create(size_t size){
    char* t = (char *)malloc(size);
    memset(t, '\0', size);
    return t;
}

void char_clear(char* string){
    memset(string, '\0', strlen(string));
}

void hex_encode(const unsigned char* input, char* output, int length) {
    for (int i = 0; i < length; i++) {
        sprintf(&output[i * 2], "%02x", input[i]);
    }
    output[length * 2] = '\0';
}

char* file_content(const char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){
        printf("[Error]\n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char *)malloc(fileSize + 1);
    size_t rec = fread(buffer, 1, fileSize, fp);
    buffer[fileSize] = '\0';
    fclose(fp);

    return buffer;
}
