//
// Assignment 7: Author Identification
// Theodore Ikehara
// ht.c
//
// hash table

#include "ht.h"
#include "salts.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is the struct for the HashTable
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **slots;
};

// This is the struct for the HashTableIterator
struct HashTableIterator {
    HashTable *table;
    uint32_t slot;
};

HashTable *ht_create(uint32_t size) {

    // creating the hashtable type
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));

    // defines the size
    if (ht != NULL) {
        ht->size = size;

        // defines the salts
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;

        // dynamically allocates the node to the hash table
        ht->slots = (Node **) calloc(size, sizeof(Node *));
    }

    // returns the hashtable
    return ht;
}

// deletes the nodes and the hashtable
void ht_delete(HashTable **ht) {
    // iterates through the nodes to delete them
    for (int i = 0; i < (int) (*ht)->size; i += 1) {
        node_delete(&(*ht)->slots[i]);
    }
    // deletes the slots
    free((*ht)->slots);
    // deletes the hash table
    free(*ht);
    return;
}

// returns the size of the hash table
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *word) {
    // this creates the index with the hash function
    uint32_t index = hash(ht->salt, word) % ht_size(ht);

    while (ht->slots[index] != NULL) {
        // if the index exceeds the cap
        if (index > ht_size(ht)) {
            return NULL;
        }
        if (strcmp(word, ht->slots[index]->word) == 0) {
            return ht->slots[index];
        }
        index += 1;
    }
    return NULL;
}

Node *ht_insert(HashTable *ht, char *word) {

    // This finds the index using hash
    uint32_t index = hash(ht->salt, word) % ht_size(ht);
    while (ht->slots[index] != NULL) {
        // if the index exceeds its cap
        if (index > ht_size(ht)) {
            return NULL;
        }
        // comparing the words if they are the same
        if (strcmp(word, ht->slots[index]->word) == 0) {
            // increments count if the same word is inserted
            ht->slots[index]->count += 1;
            return ht->slots[index];
        }
        // increments the index after
        index += 1;
    }

    // inserts the node here)
    ht->slots[index] = node_create(word);

    return ht->slots[index];
}

// print function for debuggi)g
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        if (ht->slots[i] != NULL) {
            node_print(ht->slots[i]);
            // printf("the slot this was found on: %u\n", i);
        }
        // else {
        //     node_print(ht->slots[i]);
        // }
    }
    return;
}

HashTableIterator *hti_create(HashTable *ht) {
    // cretes a hashtable
    HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));

    if (hti != NULL) {
        // don't need to do this portion
        //hti->table = (HashTable *) calloc(ht_size(ht), sizeof(HashTable));
        // equates the two
        hti->table = ht;
        // sets the slot location to 0
        hti->slot = 0;
    }
    return hti;
}

void hti_delete(HashTableIterator **hti) {
    //free((*hti)->table);
    free(*hti);
    return;
}

Node *ht_iter(HashTableIterator *hti) {

    Node *node = NULL;
    // ht_print(hti->table);
    for (uint32_t i = hti->slot; i < ht_size(hti->table); i += 1) {

        if (hti->table->slots[hti->slot] != NULL) {
            // creates node to return needs to increment after
            node = hti->table->slots[hti->slot];

            // printf("slot = %u\n", hti->slot);
            hti->slot += 1;
            // printf("slot = %u\n", hti->slot);

            return node;
        } else {
            hti->slot += 1;
        }
    }
    return NULL;
}
