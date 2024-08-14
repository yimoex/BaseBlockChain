#include "string.h"

StringNode* string_node_create(int id, char* data){
    size_t dataSize = data == NULL ? 0 : strlen(data);
    StringNode* node = (StringNode *)malloc(sizeof(StringNode));
    node -> id = id;
    if(dataSize != 0){
        node -> data = (char *)malloc(dataSize);
        memset(node -> data, '\0', dataSize);
        strcpy(node -> data, data);
    }
    node -> next = NULL;
    return node;
}

String* string_create(char* data){
    size_t dataSize = data == NULL ? 0 : strlen(data);
    String* string = (String *)malloc(sizeof(String));
    StringNode* node;

    string -> size = 1;
    string -> realsize = dataSize;
    node = string -> node = string_node_create(0, data);

    string -> latestNode = node;

    return string;
}

void string_append(String* string, char* data){
    size_t dataSize = strlen(data);
    StringNode* node = string -> latestNode;
    StringNode* tmp = string_node_create(string -> size, data);

    string -> size++;
    string -> realsize += dataSize;

    node -> next = tmp;
    string -> latestNode = tmp;
}

void string_clear(String* string){
    StringNode* node = string -> node;
    StringNode* tmp;
    while(node != NULL){
        free(node -> data);
        tmp = node;
        node = node -> next;
        free(tmp);
    }
    string -> size = 0;
    string -> realsize = 0;
    string -> node = NULL;
    string -> latestNode = NULL;
}

void string_print(String* string){
    StringNode* node = string -> node;
    for(int i = 0;i < string -> size;i++){
        if(node == NULL){
            printf("[Error] 字符串断裂\r\n");
            break;
        }
        printf("%s", node -> data);
        node = node -> next;
    }
    printf("\r\n");
}
