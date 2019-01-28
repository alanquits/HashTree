#ifndef CHASH_H
#define CHASH_H

#include <stdbool.h>

enum HashTreeEntryType { DOUBLE_ET, INTEGER_ET, STRING_ET };

union HashTreeEntry {
    char *string_value;
    double double_value;
    int integer_value;
};

struct HashTree {
    char *key;
    enum HashTreeEntryType entry_type;
    union HashTreeEntry *entry;
    struct HashTree* prev;
    struct HashTree* next;
};

// Public Functions
struct HashTree* HashTree_init(void);
void HashTree_free(struct HashTree *tree);
bool HashTree_has_key(struct HashTree *tree, char *key, struct HashTree **node);
bool HashTree_insert_string(struct HashTree **tree, char *key, char *value);
bool HashTree_insert_double(struct HashTree **tree, char *key, double value);
bool HashTree_insert_integer(struct HashTree **tree, char *key, int value);
bool HashTree_query_string(struct HashTree *tree, char *key, char **value);
bool HashTree_query_double(struct HashTree *tree, char *key, double *value);
bool HashTree_query_integer(struct HashTree *tree, char *key, int *value);

// Private Utility Functions
struct HashTree* HashTree_init_entry(char *key);
struct HashTree* HashTree_init_string_entry(char *key, char *value);

#endif // CHASH_H
