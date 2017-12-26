#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordDB.h"
#include "question.h"
#define TMP_STR_SIZE 256


Word* switch_random_with_last(Word* tab, unsigned int size) {
  unsigned int r = rand() % size;
  Word temp = tab[r];
  size--;
  tab[r] = tab[size];
  tab[size] = temp;
  return tab+size;
}


void tell_directions(short direction, WordDB* db) {
  if(direction == 0) printf("From %s to %s.\n", db->lang1, db->lang2);
  else if(direction == 1) printf("From %s to %s.\n", db->lang2, db->lang1);
}


unsigned int voc_quizz(WordDB* db, short direction, unsigned int number_of_questions) {
  unsigned int questionNo, score = 0;
  char buffer[TMP_STR_SIZE];
  short q_dir = direction; // question-specific asking direction

  // start message
  printf("%u QUESTIONS\n", number_of_questions);
  tell_directions(direction, db);

  for(questionNo = 0; questionNo < number_of_questions; questionNo++) {
    printf("\n#%u: ", questionNo+1);

    // if direction random, choose & print direction for every question
    if(direction == -1) {
      q_dir = rand() % 2;
      tell_directions(q_dir, db);
    }

    // randomly choose a word from DB
    Word* w = switch_random_with_last(db->words, db->size - questionNo);

    // ask
    printf("%s -> ", q_dir ? w->word2 : w->word1);

    // prompt
    fgets(buffer, TMP_STR_SIZE, stdin);
    end_at_newline(buffer);

    // compare and print if correct
    if(strcoll(buffer, q_dir ? w->word1 : w->word2)==0) {
      printf("Correct\n");
      score++;
    } else printf("Wrong (%s)\n", q_dir ? w->word1 : w->word2);
  }

  printf("\nScore: %u/%u\n", score, number_of_questions);
  return score;
}
