/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371
 * COMP202, Semester 1, 2017.
*****************************************************************************/
#include <stdarg.h>
#include "shared.h"
#ifndef IO_H
#define IO_H
#define EXTRACHARS 2
#define LINELEN 80
/* the number of choices in the program */
#define NUM_MENU_CHOICES 5

/**
 * constants for the different options for the menu system
 **/
enum menu_choice {
    MNU_WD_SCR = 1,
    MNU_ASC_TBL,
    MNU_ANAG,
    MNU_CLST,
    MNU_QUIT,
    MNU_EOF,
    MNU_INVALID = -1
};

/**
 * data type for the i/o functions to return. These give the possible outcomes
 * of an i/o operation.
 **/
enum input_result {
    IR_FAILURE,
    IR_SUCCESS,
    IR_EOF
};

/**
 * put here all declaratioins of user input functions
 **/
enum input_result get_int_input(const char[], int*);
enum input_result get_string_input(const char[], char[], long);
BOOLEAN long_from_string(const char[], long*);
void display_menu();
enum menu_choice get_menu_choice();
enum input_result get_wordscore_input(char[]);
enum input_result get_asciitable_input(char[]);
enum input_result get_cluster_input();
enum input_result get_anagram_input();

/**
 * the input and output functions that you should call outside of this module
 **/
int normal_output(const char[], ...);
int error_output(const char[], ...);
#endif

