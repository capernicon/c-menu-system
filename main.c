/******************************************************************************
 * Student Name  : Matthew Ablott
 * MQ ID : 44649371
 * COMP202, Semester 1, 2017.
*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "helpers.h"
#include "io.h"
#include "options.h"

int main(void) {
    enum menu_choice the_choice;

    do {
      /* get choice from the user */
      the_choice = get_menu_choice();      

      switch(the_choice) { 
        enum input_result input_result; 
        char input_buffer[LINELEN + EXTRACHARS];        

        case MNU_WD_SCR: {
          int score;
          input_result = get_wordscore_input(input_buffer);
          if (input_result == IR_EOF) {
            continue;
          }
          score = word_score(input_buffer);
          normal_output("the score for \"%s\" is %d\n", input_buffer, score);
          break;
        }
           
        case MNU_ASC_TBL: {
          input_result = get_asciitable_input(input_buffer);
          if (input_result == IR_EOF) {
            continue;
          }
          asciitable(input_buffer);
          break;
        }

        case MNU_ANAG: {
          struct anagram_pair the_pair;
          input_result = get_anagram_input(&the_pair);

          if (input_result == IR_EOF) {
            continue;
          }
        
          if (is_anagram(&the_pair)) {
            normal_output("%s and %s are anagrams.\n", the_pair.firstword, the_pair.secondword);
          }
          else {
            normal_output("%s and %s are not anagrams.\n", the_pair.firstword, the_pair.secondword);
          }
          break;      
        }

        case MNU_CLST: {
          struct map_input cluster_input;
          struct map themap;
          BOOLEAN valid_map;

          do {
            valid_map = FALSE;
            input_result = get_cluster_input(&cluster_input);
           
            if (input_result == IR_EOF) {
              break;
            }
            themap = create_map(cluster_input.x, cluster_input.y, cluster_input.cluster_text);
         
            if (!themap.isvalid) { 
              continue;
            }
            valid_map = TRUE;
  
          } while (!valid_map);

          if (input_result == IR_EOF) {
            break;
          }
 
          find_clusters(&themap);
          break;
        }

        default: {
          if (the_choice != MNU_QUIT && the_choice != MNU_EOF) {
            return MNU_INVALID;
          }
        }
      }
    }
    while (the_choice != MNU_QUIT && the_choice != MNU_EOF);  
    return EXIT_SUCCESS;
}

