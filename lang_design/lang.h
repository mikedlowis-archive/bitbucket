
typedef struct {
    long type: 8;
    long size: 24;
} type_header_t;

typedef struct {
    type_header_t header;
    char data[4];
} object_t;

typedef object_t* var_t;

// Atomic types
typedef long char_t;

typedef double num_t;

// Collections
typedef struct {
    type_header_t header;
    char_t* data;
} symbol_t;

typedef struct {
    type_header_t header;
    char_t* data;
} string_t;

typedef struct {
    type_header_t header;
    var_t* data;
} vector_t;

typedef struct {
    type_header_t header;
    var_t head;
    var_t tail;
} list_t;

// Other
typedef struct {
    type_header_t header;
    var_t context;
    var_t (*fn)(var_t args);
} func_t;

typedef struct {
    type_header_t header;
    char* data;
} port_t;

#define MACRO(name) void name(var_t args) {
#define END_MACRO   }

#define FUNC(name)  var_t name(var_t args) {
#define END_FUNC    }

#define PACKAGE()   void* init_package()
#define END_PACKAGE }

#define REGISTER(name,val) register_val( intern(#name), val )

MACRO(genname_1)
END_MACRO

FUNC(genname_2)
END_FUNC

PACKAGE()
    REGISTER(some_macro, genname_1);
    REGISTER(some_func, genname_2);
END_PACKAGE

