/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371
 * COMP202, Semester 1, 2017. 
*****************************************************************************/
#include "helpers.h"
#include "shared.h"
#include "io.h"
#ifndef OPTIONS_H
#define OPTIONS_H

/* the maximum height and width for the map */
#define MAXHEIGHT 10
#define MAXWIDTH 10

/**
 * the map type used with the clusters option.
 **/
struct map {
    /* the array of chars that make up the map */
    int themap[MAXHEIGHT][MAXWIDTH];
    /* the width and heigh of the map */
    int width;
    int height;
    /* whether the char data that has been processed was
     * a valid map
     */
    BOOLEAN isvalid;
};

/**
 * struct that represents the inputs needed for the clusters implementation
 **/
struct map_input {
    int x, y;
    char cluster_text[LINELEN + 1];
};

/**
 * the pair of words to check if they are an anagram. Please note that I
 * have provided the length of the two words as well - this means that you
 * only need to call strlen() on these once.
 **/
struct anagram_pair {
    char firstword[LINELEN + 1];
    long firstlen;
    char secondword[LINELEN + 1];
    long secondlen;
};

/**
 * The function prototypes for the options you need to implement
 **/
BOOLEAN permute(char*, const char*, int, int);
void swap(char*, char*);
BOOLEAN is_anagram(const struct anagram_pair *);
int binary_conversion(char);
void asciitable(const char[]);
int word_score(const char[]);
struct map create_map(int, int, const char[]);
void find_clusters(const struct map *);

#endif

