typedef struct _stringNode {
    int id;
    char* data;
    struct _stringNode* next;
} StringNode;

typedef struct _string {
    int size;
    size_t realsize;
    StringNode* node;
    StringNode* latestNode;
} String;


