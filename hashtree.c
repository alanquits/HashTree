#include "hashtree.h"
#include <stdlib.h>
#include <string.h>

struct HashTree *HashTree_init(void)
{
    struct HashTree *tree = NULL;
    return tree;
}


struct HashTree *HashTree_init_entry(char *key)
{
    struct HashTree *tree = (struct HashTree*) malloc(sizeof(struct HashTree));
    tree->key = (char*) malloc(strlen(key) + 1);
    strcpy(tree->key, key);
    tree->entry = (union HashTreeEntry*) malloc(sizeof(union HashTreeEntry));
    tree->next = NULL;
    tree->prev = NULL;

    return tree;
}

struct HashTree *HashTree_init_string_entry(char *key, char *value)
{
    struct HashTree *tree = HashTree_init_entry(key);
    tree->entry_type = STRING_ET;
    tree->entry->string_value = (char*) malloc(strlen(value) + 1);
    strcpy(tree->entry->string_value, value);

    return tree;
}

bool HashTree_has_key(struct HashTree *tree, char *key, struct HashTree **node)
{
    if (tree == NULL) {
        return false;
    }

    int order = strcmp(key, tree->key);
    if (order < 0) {
        return HashTree_has_key(tree->prev, key, node);
    } else if (order > 0) {
        return HashTree_has_key(tree->next, key, node);
    } else {
        *node = tree;
        return true;
    }

}


bool HashTree_insert_string(struct HashTree **tree, char *key, char *value)
{
    if (*tree == NULL) {
        *tree = (struct HashTree*) HashTree_init_string_entry(key, value);
        return true;
    }

    int order = strcmp(key, (*tree)->key);
    if (order < 0) {
        return HashTree_insert_string(&(*tree)->prev, key, value);
    } else if (order > 0) {
        return HashTree_insert_string(&(*tree)->next, key, value);
    } else {
        free((*tree)->entry->string_value);
        (*tree)->entry->string_value = (char*) malloc(strlen(value) + 1);
        strcpy((*tree)->entry->string_value, value);
        return true;
    }
}

bool HashTree_insert_double(struct HashTree **tree, char *key, double value)
{
    if (*tree == NULL) {
        *tree = (struct HashTree*) HashTree_init_entry(key);
        (*tree)->entry_type = DOUBLE_ET;
        (*tree)->entry->double_value = value;
        return true;
    }

    int order = strcmp(key, (*tree)->key);
    if (order < 0) {
        return HashTree_insert_double(&(*tree)->prev, key, value);
    } else if (order > 0) {
        return HashTree_insert_double(&(*tree)->next, key, value);
    } else {
        (*tree)->entry->double_value = value;
        return true;
    }
}

bool HashTree_insert_integer(struct HashTree **tree, char *key, int value)
{
    if (*tree == NULL) {
        *tree = (struct HashTree*) HashTree_init_entry(key);
        (*tree)->entry_type = INTEGER_ET;
        (*tree)->entry->integer_value = value;
        return true;
    }

    int order = strcmp(key, (*tree)->key);
    if (order < 0) {
        return HashTree_insert_integer(&(*tree)->prev, key, value);
    } else if (order > 0) {
        return HashTree_insert_integer(&(*tree)->next, key, value);
    } else {
        (*tree)->entry->integer_value = value;
        return true;
    }
}

bool HashTree_query_string(struct HashTree *tree, char *key, char **value)
{
    if (tree == NULL) {
        return false;
    }

    int order = strcmp(key, tree->key);
    if (order < 0) {
        return HashTree_query_string(tree->prev, key, value);
    } else if (order > 0) {
        return HashTree_query_string(tree->next, key, value);
    } else {
        if (tree->entry_type == STRING_ET) {
            *value = tree->entry->string_value;
            return true;
        } else {
            return false;
        }
    }
}

bool HashTree_query_double(struct HashTree *tree, char *key, double *value)
{
    struct HashTree *node;
    if (HashTree_has_key(tree, key, &node)) {
        if (node->entry_type == DOUBLE_ET) {
            *value = node->entry->double_value;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool HashTree_query_integer(struct HashTree *tree, char *key, int *value)
{
    struct HashTree *node;
    if (HashTree_has_key(tree, key, &node)) {
        if (node->entry_type == INTEGER_ET) {
            *value = node->entry->integer_value;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void HashTree_free(struct HashTree *tree)
{
    if (tree == NULL) {
        return;
    }

    HashTree_free(tree->next);
    HashTree_free(tree->prev);
    free(tree->key);
    if (tree->entry_type == STRING_ET) {
        free(tree->entry->string_value);
        free(tree->entry);
    }
}



