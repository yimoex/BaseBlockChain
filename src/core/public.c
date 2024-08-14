char* int2charPtr(int val){
    char* temp = (char *)malloc(2 * sizeof(char));
    temp[0] = val;
    temp[1] = '\0';
    return temp;
}

char* string_create(size_t size){
    char* t = (char *)malloc(size);
    memset(t, '\0', size);
    return t;
}

void string_clear(char* string){
    memset(string, '\0', strlen(string));
}
