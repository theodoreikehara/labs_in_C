//
// Assignment 7: Author Identification
// Theodore Ikehara
// text.c
//
// text
//

#include "text.h"
#include "bf.h"
#include "ht.h"
#include "metric.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <regex.h>

// needs to contain apostrophes and hyphins
// #define WORD "[a-zA-Z]+(('|-)[a-zA-Z]+)"
// this word definition includes a-z and hyphens and apostrophies as words
#define WORD "[a-zA-Z]+(('|-|[a-zA-z])[a-zA-Z]+)"
// uint32_t noiselimit;

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};

// creating the text data type here
Text *text_create(FILE *infile, Text *noise) {

    // 2^21 for the bloom filter size
    uint32_t bf_size = 2097152;
    // 2^19 for the hash table
    uint32_t ht_size = 524288;

    regex_t re;
    char *word = NULL;

    bool limit_not = true;

    if (regcomp(&re, WORD, REG_EXTENDED)) {
        return NULL;
    }

    // allocates memory to text
    Text *tx = (Text *) malloc(sizeof(Text));

    // if this space is allocated correctly
    if (tx != NULL) {
        tx->ht = ht_create(ht_size);
        tx->bf = bf_create(bf_size);

        // PRINT STATEMENT FOR TEST
        // printf("before loop\n");

        while ((word = next_word(infile, &re)) != NULL) {
            // PRINT STATEMENT FOR TEST
            // printf("inside loop\n");
            // lowers the case of the word
            for (int i = 0; word[i]; i++) {
                word[i] = tolower(word[i]);
            }
            // inserts the word into the hash table or bloom filter depending on
            // weather this is noise text or the actual text
            if (noise == NULL) {
                // This occurs when this is the noise text
                // loads in all the values to bloomfilter
                if (limit_not) {
                    bf_insert(tx->bf, word);
                    ht_insert(tx->ht, word);
                    tx->word_count += 1;
                    // this accounts for the noise limit
                    if (tx->word_count == noiselimit) {
                        limit_not = false;
                    }
                }
                // this occurs when the text is not noise text
            } else {
                // checking weather the noise is in the bloom filter
                // needs check bloom filter correctness
                // printf("iterating the create...\n");
                if (!bf_probe(noise->bf, word)) {
                    bf_insert(tx->bf, word);
                    ht_insert(tx->ht, word);
                    tx->word_count += 1;
                    // might be in bloom filter
                } else {
                    if (ht_lookup(noise->ht, word) == NULL) {
                        bf_insert(tx->bf, word);
                        ht_insert(tx->ht, word);
                        tx->word_count += 1;
                    }
                }
            }
        }
    }

    return tx;
}

// deletes the text data type
void text_delete(Text **text) {
    ht_delete(&(*text)->ht);
    bf_delete(&(*text)->bf);
    free(*text);
    return;
}

// calculates the euclidean distance given text
double euc_dist(Text *text1, Text *text2) {

    // creating the iterators for text 1 and 2
    HashTableIterator *hti_t1 = hti_create(text1->ht);
    HashTableIterator *hti_t2 = hti_create(text2->ht);
    // ht_print(text1->ht);

    // this keeps the values that we are calculating from the given texts
    double sum = 0.0;
    Node *n = NULL;
    double u;
    double v;
    double diff;

    // Node *node = ht_iter(hti_t1);
    // node_print(node);
    // node = ht_iter(hti_t1);
    // printf("size is %u\n", ht_size(text1->ht));

    while ((n = ht_iter(hti_t1)) != NULL) {

        // printf("%s\n", n->word);
        // getting the word normalized frequency
        u = text_frequency(text1, n->word);
        v = text_frequency(text2, n->word);

        // printf("the word is %s\n", n->word);
        // printf("u = %f\nv = %f\n", u, v);
        // getting the difference)
        diff = u - v;

        // starting euclidean formula
        diff = diff * diff;
        // this is the summation portion
        sum += diff;
    }
    while ((n = ht_iter(hti_t2)) != NULL) {
        if (!text_contains(text1, n->word)) {
            u = text_frequency(text1, n->word);
            v = text_frequency(text2, n->word);

            // printf("the word is %s\n", n->word);
            // printf("u = %f\nv = %f\n", u, v);
            // getting the difference)
            diff = u - v;

            // starting euclidean formula
            diff = diff * diff;
            // this is the summation portion
            sum += diff;
        }
    }
    double s_sum = sqrt(sum);
    // printf("this is the new sum: %f\n", s_sum);
    //
    hti_delete(&hti_t1);
    hti_delete(&hti_t2);

    return s_sum;
}

// calculates manhattan distance given text
double man_dist(Text *text1, Text *text2) {
    // creating the iterators for text 1 and 2
    HashTableIterator *hti_t1 = hti_create(text1->ht);
    HashTableIterator *hti_t2 = hti_create(text2->ht);
    // ht_print(text1->ht);

    // this keeps the values that we are calculating from the given texts
    double sum = 0.0;
    Node *n = NULL;
    double u;
    double v;
    double diff;

    // Node *node = ht_iter(hti_t1);
    // node_print(node);
    // node = ht_iter(hti_t1);
    // printf("size is %u\n", ht_size(text1->ht));

    while ((n = ht_iter(hti_t1)) != NULL) {

        // printf("%s\n", n->word);
        // getting the word normalized frequency
        u = text_frequency(text1, n->word);
        v = text_frequency(text2, n->word);

        // printf("the word is %s\n", n->word);
        // printf("u = %f\nv = %f\n", u, v);
        // getting the difference
        diff = u - v;

        // starting manhattan formula
        diff = fabs(diff);
        // this is the summation portion
        sum += diff;
    }
    while ((n = ht_iter(hti_t2)) != NULL) {
        if (!text_contains(text1, n->word)) {
            u = text_frequency(text1, n->word);
            v = text_frequency(text2, n->word);

            // printf("the word is %s\n", n->word);
            // printf("u = %f\nv = %f\n", u, v);
            // getting the difference)
            diff = u - v;

            // starting euclidean formula
            diff = fabs(diff);
            // this is the summation portion
            sum += diff;
        }
    }
    // printf("this is the new sum: %f\n", s_sum);
    hti_delete(&hti_t1);
    hti_delete(&hti_t2);
    return sum;
}

// calculates cosine distance given text
double cos_dist(Text *text1, Text *text2) {
    // creating the iterators for text 1 and 2
    HashTableIterator *hti_t1 = hti_create(text1->ht);
    HashTableIterator *hti_t2 = hti_create(text2->ht);
    // ht_print(text1->ht);

    // this keeps the values that we are calculating from the given texts
    double sum = 0.0;
    Node *n = NULL;
    double u;
    double v;
    double mult;

    // Node *node = ht_iter(hti_t1);
    // node_print(node);
    // node = ht_iter(hti_t1);
    // printf("size is %u\n", ht_size(text1->ht));

    while ((n = ht_iter(hti_t1)) != NULL) {

        // printf("%s\n", n->word);
        // getting the word normalized frequency
        u = text_frequency(text1, n->word);
        v = text_frequency(text2, n->word);

        // printf("the word is %s\n", n->word);
        // printf("u = %f\nv = %f\n", u, v);

        // starting cosine formula
        mult = u * v;

        // this is the summation portion
        sum += mult;
    }
    while ((n = ht_iter(hti_t2)) != NULL) {
        if (!text_contains(text1, n->word)) {
            u = text_frequency(text1, n->word);
            v = text_frequency(text2, n->word);

            // printf("the word is %s\n", n->word);
            // printf("u = %f\nv = %f\n", u, v);

            // starting cosine formula
            mult = u * v;

            // this is the summation portion
            sum += mult;
        }
    }
    // printf("this is the new sum: %f\n", s_sum);
    hti_delete(&hti_t1);
    hti_delete(&hti_t2);
    return 1 - sum;
}

// finds the distance of the text using one of the given formulas
double text_dist(Text *text1, Text *text2, Metric metric) {

    // need switch case to take the metric used
    switch (metric) {
    // if euclidean was selected
    case EUCLIDEAN: return euc_dist(text1, text2);

    // if manhattan was selected
    case MANHATTAN: return man_dist(text1, text2);

    // if cosine was selected
    case COSINE: return cos_dist(text1, text2);
    }

    return 0;
}

// finds the normalized frequency of the words in the text
double text_frequency(Text *text, char *word) {
    // the node for the lookedup word
    Node *h = ht_lookup(text->ht, word);
    float frequ = 0.0;

    if (h != NULL) {
        frequ = (float) (h->count) / (float) (text->word_count);
        return (double) frequ;
    }
    // if the word is not in the text
    return 0;
}

// finds wheather or not the word contains the text
bool text_contains(Text *text, char *word) {
    if (ht_lookup(text->ht, word) != NULL) {
        return true;
    }
    return false;
}

// prints the text for debugging
void text_print(Text *text) {
    // this prints the hash table
    printf("The Hashtable\n");
    ht_print(text->ht);

    // this prints the bloom filter
    // printf("The Bloomfilter\n");
    // bf_print(text->bf);

    return;
}
