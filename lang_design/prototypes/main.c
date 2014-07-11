typedef unsigned int Word;

typedef enum {
    STRING
} eDataType;

typedef struct {
    Word length : 24;
    Word type   : 3;
    Word spare  : 5;
} ObjectHeader;

typedef struct {
    Word* parent;
    Word* self;
} Prototype;

typedef struct {
    ObjectHeader header;
    Prototype proto;
    Word data[1];
} Object;

int main(int argc, char** argv)
{
    return 0;
}
