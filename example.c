#include <stdio.h>

#include "hashtree.h"

int main()
{
    // Initialize Hash Tree
    struct HashTree *hash = HashTree_init();

    // HashTree_insert_<type> functions insert values into
    // the HashTree. The functions take three arguments:
    //   1. A reference to the HashTree pointer
    //   2. A key (char*)
    //   3. A value (char*, int, or double)
    HashTree_insert_string(&hash, "Terry", "Davis");
    HashTree_insert_double(&hash, "pi", 3.1416);
    HashTree_insert_integer(&hash, "one-hundred", 100);

    // HashTree_query_<type> functions take three arguments:
    //   1. A HashTree pointer
    //   2. A key (char*)
    //   3. A reference to (char*, int, or double)
    //
    // Returns true if key is present in HashTree AND
    //    has the correct type (double and integer are NOT
    //    interchangeable). Returns false otherwise.
    char *svalue;
    HashTree_query_string(hash, "Terry", &svalue)
            ? printf("%s\n", svalue)
            : printf("key not found\n");

    double dvalue;
    HashTree_query_double(hash, "pi", &dvalue)
            ? printf("%lf\n", dvalue)
            : printf("key not found\n");

    int ivalue;
    HashTree_query_integer(hash, "one-hundred", &ivalue)
            ? printf("%d\n", ivalue)
            : printf("key not found\n");

    // An example where key is not in the HashTree.
    HashTree_query_string(hash, "Not_A_Hash_Key", &svalue)
            ? printf("%s\n", svalue)
            : printf("key not found\n");

    // Free the HashTree.
    HashTree_free(hash);
    return 0;
}
