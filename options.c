/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371 
 * COMP202, Semester 1, 2017.
 *****************************************************************************/
#include "options.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define GRID_START 0

/**
 * struct that defines a 'score' within our scoretable
 **/
struct score {
    int letter, score;
};

/**
 * the scores for each letter as defined for scrabble.
 **/
const struct score scoretable[] = {
                                   {'A', 1},
                                   {'E', 1},
                                   {'I', 1},
                                   {'L', 1},
                                   {'N', 1},
                                   {'O', 1},
                                   {'R', 1},
                                   {'S', 1},
                                   {'T', 1},
                                   {'U', 1},
                                   {'D', 2},
                                   {'G', 2},
                                   {'B', 3},
                                   {'C', 3},
                                   {'M', 3},
                                   {'P', 3},
                                   {'F', 4},
                                   {'H', 4},
                                   {'V', 4},
                                   {'W', 4},
                                   {'Y', 4},
                                   {'K', 5},
                                   {'J', 8},
                                   {'X', 8},
                                   {'Q', 10},
                                   {'Z', 10}
};

/**
 * in this function you calculate the score for the word passed in. It is the
 * sum of the scores for each letter.
 **/
int word_score(const char word[]) {
    char * word_copy;
    int word_score = 0;
    int iterator, iterator2;

    word_copy = strdup(word); 

    word_copy[strlen(word_copy) -1 ] = '\0';
 
     /* compare each char we are looking at with the struct array */
     for (iterator = 0; iterator < strlen(word_copy); iterator++) {
      for (iterator2 = 0; iterator2 < sizeof(scoretable) / sizeof(scoretable[0]); iterator2++) {        
        if (toupper(word_copy[iterator]) == scoretable[iterator2].letter) {
          word_score += scoretable[iterator2].score;
        }
      }
    }

    return word_score;
}

/** 
 * function to swap chars in string passed
 **/
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * recrusive function that passes in a copy of first string and the orignal second string.
 * It then creates all permutations of the first string followed by comparisons between
 * the new permutation and existing second string.
 **/
BOOLEAN permute(char * str, const char * str2, int start, int end) {
   int iterator;

   for (iterator = start; iterator <= end; iterator++) {
     /* call swap which swaps chars in incremental order */
     swap((str + start), (str + iterator));

     /* the recrusive call to pass in first string with start char incremented */
     permute(str, str2, start + 1, end);

     /* check if a permutation matches second string */
     if (strcmp(str, str2) == 0) {                                                                                   
       return TRUE;  
     }
     /* swap the chars back after creating the permutation */
     swap((str + start), (str + iterator));
   
   }
   return FALSE; 

}

#define FIRSTCHAR 0
/**
 * recursive function you need to implement to find out if two strings are
 * an anagram of each other.
 **/
BOOLEAN is_anagram(const struct anagram_pair* thepair) {
    /* initialise a new copy of anagram_pair */
    struct anagram_pair a_new_pair;
    int start;
    int end;

    /* already not an anagram if string lengths are different */  
    if (thepair->firstlen != thepair->secondlen) {
      return FALSE;
    }   
    
    /* make a copy of the first string and first string length*/ 
    strcpy(a_new_pair.firstword, thepair->firstword); 
    a_new_pair.firstlen = thepair->secondlen;

    start = FIRSTCHAR;
    end = (a_new_pair.firstlen -1);

    if (permute(a_new_pair.firstword, thepair->secondword, start, end)) {
      return TRUE;
    }

    return FALSE;
}

#define BITS 8
/**
 * function that passes in each char and prints the binary value for said char
 *
 **/
int binary_conversion(char c) {
    int binary_iterator;  
    binary_iterator = 8;

    normal_output("  ");
  
    /* while the 8 bits, print ANDED bit and increase bit order (from LSB to MSB) */
    while (binary_iterator > 0) {
      --binary_iterator;
      printf("%d", (c >> binary_iterator) & 1);
    }
    normal_output("b  ");

    return SUCCESS;
}

/**
 * you are to display a table of all the characters in an input string as the
 * letter itself, its binary, octal, decimal and hexadecimal representations.
 *
 **/
void asciitable(const char input[]) {
    char * word_copy = strdup(input);
    int iterator = 0;
    int len = strlen(word_copy);

    puts("======================================================================");
    puts("|    Ascii    |    Binary   |    Octal    |   Decimal   |     Hex     |");
    puts("|    Letter   |    Value    |    Value    |    Value    |    Value    |");
    puts("======================================================================");

    while(iterator < len) {
      normal_output("|      %c      |", word_copy[iterator]);
      normal_output("|", binary_conversion(word_copy[iterator]));
      normal_output("     %.4o    |", word_copy[iterator]);
      normal_output("     ""%.3dd""    |", word_copy[iterator]);
      normal_output("     %#x    |", word_copy[iterator]);
      normal_output("\n");
    ++iterator;    
    }
    puts("======================================================================\n"); 
}

/**
 * create the map of characters based on the map string passed in.
 * Ensure that it is a valid map as defined in the spec.
 **/
struct map create_map(int width, int height, const char map_string[]) {
    struct map themap;
    char * copy_one;
    char * copy_two;
    char * delim;
    char * buffer;
    char tokens[LINELEN + EXTRACHARS];
    int count = 0; 
    int copy_count = 0;
    int iterator; int iterator2;
    themap.isvalid = TRUE;
 
    /* make a copy of the map_string passed in */
    copy_one = strdup(map_string);
    /* strip the newline char */
    copy_two = strtok(copy_one, "\n"); 
    /* get first token */
    delim = strtok(copy_two, ",;");

    /* loop over the remaining input and tokenise */
    while (delim != NULL && themap.isvalid) {
      buffer = delim;

      /* if we are reading more than 1 char per comma seperation */     
      if (strlen(buffer) > 1) {
        error_output("%d is too long for a character!\n\n", strlen(buffer));
        themap.isvalid = FALSE; 
      }
 
      /* copy remaining chars and tokenise if we are looking at either a , || " */
      strcpy(&tokens[count], buffer);
      delim = strtok(NULL, ",;");
      ++count;
    }

    /* add tokens to the map array */
    for (iterator = 0; iterator < height; iterator++) {
      for (iterator2 = 0; iterator2 < width; iterator2++) {
        themap.themap[iterator][iterator2] = tokens[copy_count];
        copy_count++;
      }
    }

    /* assign values for the map width and map height */
    if (width <= MAXWIDTH && height <= MAXHEIGHT) {
      themap.width = width;
      themap.height = height;
    }
    else {
      error_output("Entered height or width is not within the map range. Please try again.\n\n");
      themap.isvalid = FALSE;
    }

    return themap;
}

/**
 * search the map for clusters of chars. In each location if there is not a
 * space, look at all the immediate neighbours and count up all the immediate
 * neighbours in all directions that contain the current character, including
 * the current cell.
 **/
void find_clusters(const struct map* themap) {   
    int rows = 0; int cols = 0;
    int c_width; int c_height;
    int w_copy; int h_copy;
    int startPosX; int endPosX;
    int startPosY; int endPosY;
    char c;
    int char_count = 0;
    int spaces_check = 0;

    while ((c = themap->themap[cols][rows])) {
      /* if we aren't looking at a space char */
      if (c != ' ') {
        c_width = rows; 
        c_height = cols;
        w_copy = rows; 
        h_copy = cols;
        /* ternary operations that boundary check whilst iterating the offset row/col */
        startPosX = (w_copy - 1 < GRID_START) ? GRID_START : w_copy - 1;
        endPosX = (w_copy + 1 > themap->width) ? w_copy : w_copy + 1;
        startPosY = (h_copy - 1 < GRID_START) ? GRID_START : h_copy - 1;
        endPosY = (h_copy + 1 > themap->height) ? h_copy : h_copy + 1;
  
        /** depending on the char we are looking at, we perform validity checks for inside the bounds and 
         * jump -1/+1 rows as well as checking the same row neighbours
         **/
        for (h_copy = startPosY; h_copy <= endPosY; h_copy++) { 
          for (w_copy = startPosX; w_copy <= endPosX; w_copy++) {
            if (themap->themap[h_copy][w_copy] == c) {
              char_count++;
            }      
          }
        }
        printf("Cluster count of \'%c\' at %d,%d is %d\n", c, c_height, c_width, char_count);
        char_count = 0;
      }
      /* increase` spaces_check */
      else {
        spaces_check++;
      }
      /* if spaces_check reaches total number passed in chars, user hasn't ended any cluster chars */
      if (spaces_check == (themap->width + themap->height)) {
        normal_output("There were no clusters found in the map.\n\n");
        break;
      }
      rows++; 
      /* sanity check if we are at end of row */
      if (rows == themap->width) {
        cols++; rows = 0;
      }
      /* sanity check to see if we hae exhausted the map char array */
      if (cols == themap->height) {
        break;
      }
    }   
}
