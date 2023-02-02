//
// Assignment 7: Author Identification
// Theodore Ikehara
// identify.c
//
// the main function is here
//

#include "ht.h"
#include "pq.h"
#include "metric.h"
#include "text.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define OPTIONS "d:n:k:l:emch"

uint32_t noiselimit = 100;

// prints the help
void help() {
    printf("SYNOPSIS\n");
    printf("   Identifies the author of some anonymous text passed through stdin.\n");
    printf("   Basically computes k-nearest neighbors, where k = 1 by default.\n");
    printf("   The number of noise words that are removed is tunable.\n");
    printf("   Uses either Euclidean, Manhattan, or cosine distance as metric.\n\n");
    printf("USAGE\n");
    printf("   ./identify [OPTIONS]\n\n");
    printf("OPTIONS\n");
    printf("   -d database     Database of authors and texts [default: lib.db]\n");
    printf("   -k matches      Set number of top matches to display [default: 5]\n");
    printf("   -n noisefile    Set file of words to ignore [default: noise.txt]\n");
    printf("   -l limit        Set noise word limit [default: 100]\n");
    printf("   -e              Set distance metric as Euclidean distance [default]\n");
    printf("   -m              Set distance metric as Manhattan distance\n");
    printf("   -c              Set distance metric as cosine distance\n");
    // printf("   -v              Enable verbose printing of program run\n");
    printf("   -h              Display program help and usage\n");
    return;
}

int main(int argc, char **argv) {

    // this is all the default values for the input
    char *database = "lib.db";
    // char *database = "small.db";
    char *noise = "noise.txt";

    int matches = 5;
    Metric m = EUCLIDEAN;

    // this is the execution of the command line options
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'd': database = optarg; break;
        case 'n': noise = optarg; break;
        case 'k': matches = atoi(optarg); break;
        case 'l': noiselimit = atoi(optarg); break;
        case 'e': m = EUCLIDEAN; break;
        case 'm': m = MANHATTAN; break;
        case 'c': m = COSINE; break;
        case 'h': help(); return 0;
        default: help(); return 0;
        }
    }
    ///////////////////////////////////////////// DEALING WITH FILES
    // This is the file that we want to identify
    // printf("needs user to input something\n");
    //
    // REMEMBER TO UNCOMMENT THIS FOR FINAL
    FILE *anonymous_text = stdin;
    // FILE *anonymous_text = fopen("test.txt", "r");
    // printf("finished inputing\n");

    // getting the noise file
    FILE *noise_file = fopen(noise, "r");
    if (noise_file == NULL) {
        printf("could not open file...\n");
        return 1;
    }
    // printf("finished loading noise file\n");

    // creates the file database
    FILE *db = fopen(database, "r");
    if (db == NULL) {
        printf("could not open file...\n");
        return 1;
    }
    // printf("finished loading database\n");
    //////////////////////////////////////////////////////////

    ////////////////////////////////////////////// CREATING TEXTS
    // creating the noise text
    Text *noise_text = text_create(noise_file, NULL);
    // printf("finished loading noise text\n");

    // This is where we create the anonymous text
    Text *anon = text_create(anonymous_text, noise_text);
    // printf("finished loading anon text\n");
    /////////////////////////////////////////////////////////////

    // printf("it gets to fgets...\n");
    // gets the number of authors and text pairs
    char line[100];
    fgets(line, sizeof(line), db);
    // creates the priority queue for the authors
    PriorityQueue *authors = pq_create(atoi(line));
    // printf("the pq cap is %d\n", pq_size(authors));

    // this keeps the values of the authors and the dist
    char *auth = "";
    double dist = 0;

    while (fgets(line, sizeof(line), db) != NULL) {
        // line[strcspn(line, "\n")] = 0;
        // auth = line;
        // // printf("%s\n", auth);
        // enqueue(authors, auth, dist);
        // dist += 1;
        // fgets(line, sizeof(line), db);

        // removing the \n char from the line
        line[strcspn(line, "\n")] = 0;
        // getting the authors name
        auth = line;
        // printf("author: %s\n", auth);

        // opens file for the auth
        fgets(line, sizeof(line), db);
        line[strcspn(line, "\n")] = 0;
        // printf("trying to open: %s\n", line);
        FILE *text = fopen(line, "r");
        if (text != NULL) {
            // printf("its coming in here\n");
            // creating text to compare
            Text *comp = text_create(text, noise_text);

            // computes the distance of the two texts
            dist = text_dist(comp, anon, m);

            // enqueues the author and the distance for the report
            enqueue(authors, auth, dist);

            fclose(text);
            text_delete(&comp);
        }
        // else {
        //     printf("could not open\n");
        //     //fgets(line, sizeof(line), db);
        // })
    }

    // prints the lowest to highest dist
    for (int i = 0; i < matches; i += 1) {
        // dequeues auth and dist
        dequeue(authors, &auth, &dist);
        printf("%d. author: %s, dist: %f\n", i, auth, dist);
    }

    // closes the files
    fclose(anonymous_text);
    fclose(noise_file);
    fclose(db);

    // deletes to prevent loss
    text_delete(&noise_text);
    text_delete(&anon);
    pq_delete(&authors);

    return 0;
}
