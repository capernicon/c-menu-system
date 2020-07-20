/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371
 * COMP202, Semester 1, 2017.
*****************************************************************************/
#include "io.h"
#include "options.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCLUSTERINPUT 100

/**
 * function provided to clear the input buffer whenever you detect buffer
 * overflow. It just reads the leftover bytes and throws them away, resetting
 * the error state
 **/
static void clear_buffer(void) {
    int ch;
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
        ;
    clearerr(stdin);
}

/**
 * function that retrieves a user entered string from stdin
 **/
enum input_result get_string_input(const char input[], char output[], long len) {
    char buf[LINELEN + EXTRACHARS];
     
    /* display the menu prompt message */
    normal_output(input);

    /* You don't want to play...? */  
    if (fgets(buf, len, stdin) == NULL) {
      error_output("You have exited the program.\n\n");
      return IR_FAILURE;
    }

    /* naughty...naughty */
    if (buf[strlen(buf) -1] != '\n') {
      error_output("Line too long!\n\n");
      clear_buffer();
      return IR_EOF;
    }
    /* add null term */
    buf[strlen(buf)-1] = '\0';
    strcpy(output, buf);
  
   return IR_SUCCESS;
}

#define STRTOL 10

/**
 * function that passes in the string and converts to an int
 **/
enum input_result get_int_input(const char input[], int * output) {           
    char input_buffer[LINELEN + EXTRACHARS];
    char * long_ptr;
    int r; 

    normal_output(input);
  
    /* if string, pass in and convert to a long */ 
    if (get_string_input("", input_buffer, LINELEN + EXTRACHARS) != IR_FAILURE || IR_EOF) {
      r = strtol(input_buffer, &long_ptr, STRTOL);
      *output = r;
      return IR_SUCCESS;
    }

    return IR_FAILURE;
}

/**
 * Actually display the menu
 **/
void display_the_menu() {
    int menu_list;
    char * menu_heading = "Welcome to the menu system";
 
    /* menu list */
    char * the_menu_list[] = {
      "Word score",
      "Ascii table",
      "Check if two words are anagrams",
      "Find clusters",
      "Quit"
    };

    /* print the menu heading */
    puts(menu_heading);
    normal_output("=================================\n");

    /* print the menu */
    for (menu_list = 0; menu_list < NUM_MENU_CHOICES; ++menu_list) { 
      printf("%d) %s\n", menu_list + 1, the_menu_list[menu_list]);
    }	
}

/**
 * display the menu and then get the choice from the user. Please note that
 * you should implement this in such a way that it is easy to maintain and
 * extend.
 **/
enum menu_choice get_menu_choice(void) {   
    enum input_result input_result;
    int choice;

    /* display menu */
    display_the_menu();
        
    if (input_result = get_int_input("Please enter your choice: ", &choice), input_result == IR_FAILURE) {
      return MNU_INVALID;
    }

    if (input_result == IR_EOF) {
      return MNU_EOF;
    }

    if (choice < 0 || choice > MNU_QUIT) {
      error_output("%d is not a valid menu choice. Please try again.\n\n", choice);
      return MNU_INVALID;
    }

    return choice;
}

/**
 * word_score function that validates input from stdin and returns the word
 **/
enum input_result get_wordscore_input(char word[]) {
    enum input_result input_result;
    char * wordscore_heading = "Word score";
    puts(wordscore_heading);
    puts("========");

    if (input_result = get_string_input("Please enter a word to get a score on (less than 80 chars): ", 
      word, LINELEN + EXTRACHARS), input_result == IR_FAILURE) {
        error_output("Invalid input. Please try again.\n\n");
    }

    return input_result;
}

/**
 * asciitable function that validates input from stdin and passes it to the ascii table
 **/
enum input_result get_asciitable_input(char input[]) {
    enum input_result input_result;
    char * ascii_heading = "Ascii table";
    puts(ascii_heading);
    puts("===========");

    if (input_result = get_string_input("Please enter a phrase to display in the ascii table (less than 80 chars): ", 
      input, LINELEN + EXTRACHARS), input_result == IR_FAILURE) {
        error_output("Invalid input. Please try again.\n\n");
        return MNU_INVALID;
    }
    
    return input_result;
}

/**
 * anagram_pair function that validates input from stdin and returns the two strings
 **/
enum input_result get_anagram_input(struct anagram_pair* pair_input) {
    enum input_result input_result;
    char input_buff[LINELEN + EXTRACHARS];
    char * anagram_heading = "Anagram check";
    puts(anagram_heading);
    puts("=============");

    /* first word */
    if (input_result = get_string_input("Please enter the first word:  ", 
      input_buff, LINELEN + EXTRACHARS), input_result == IR_FAILURE) {
        error_output("Invalid input. Please try again.\n\n");
        return MNU_INVALID;
    }

    if (input_result == IR_EOF) {
      return MNU_EOF;
    }
    strcpy(pair_input->firstword, input_buff);
    pair_input->firstlen = strlen(pair_input->firstword);


    /* second word */
    if (input_result = get_string_input("Please enter the second word: ", 
      input_buff, LINELEN + EXTRACHARS), input_result == IR_FAILURE) {
        error_output("Invalid input. Please try again.\n\n");
        return MNU_INVALID;
    }

    if (input_result == IR_EOF) {
      return MNU_EOF;
    }
    strcpy(pair_input->secondword, input_buff);
    pair_input->secondlen = strlen(pair_input->secondword);

    return input_result;
}

/**
 * cluster_map function that validates map details from stdin and returns the word
 **/
enum input_result get_cluster_input(struct map_input * input) {
    enum input_result input_result;
    char input_text[MAXCLUSTERINPUT + EXTRACHARS];
    char * clusters_heading = "Find clusters";
    puts(clusters_heading);
    puts("=============");

    /* cluster x */    
    if (input_result = get_int_input("Please enter a value for the width of the map: ", &input->x), input_result == IR_FAILURE) {
      return MNU_INVALID;
    }

    if (input_result == IR_EOF) {
      return MNU_EOF;
    }


    /* cluster y */
    if (input_result = get_int_input("Please enter a value for the height of the map: ", &input->y), input_result == IR_FAILURE) {
      return MNU_INVALID;
    }
    
    if (input_result == IR_EOF) {
      return MNU_EOF;
    }


    /* cluster text */    
    if (input_result = get_string_input("Please enter a string that defines the mao to be processed to: ", input_text, LINELEN + EXTRACHARS), 
      input_result == IR_FAILURE) {
      return MNU_EOF;
    }
    
    if (input_result == IR_EOF) {
      return MNU_EOF;
    }
    strcpy(input->cluster_text, input_text);

    return input_result;
}

/**
 * prints out normal output to stdout - you call this function EXACTLY like
 * you call printf. There is no difference in its use.
 **/
int normal_output(const char format[], ...) {
    int count = 0;
    va_list vlist;
    va_start(vlist, format);
    count += vprintf(format, vlist);
    va_end(vlist);
    return count;
}

/**
 * use this function to print out errors. We will test that you are doing
 *separate output to stderr for errors.
 **/
int error_output(const char format[], ...) {
    int count = 0;
    va_list vlist;
    va_start(vlist, format);
    count += fprintf(stderr, "Error: ");
    count += vfprintf(stderr, format, vlist);
    va_end(vlist);
    return count;
}

