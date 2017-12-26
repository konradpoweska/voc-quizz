#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wordDB.h"
#include "question.h"

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Usage:\n  %s  db_filename  [direction]  [questions]\n\n", argv[0]);
    printf("db_filename : name of the file containing the database with the words\n\n");
    printf("direction:\n  0: lang1 to lang2,\n  1: reverse\n -1: random\n\n");
    printf("questions: max. number of questions to ask\n\n");
    return 0;
  }

  WordDB* db = read_word_db_file(argv[1]);
  if(db == NULL) return 1;

  srand(time(NULL));

  short direction;
  if(
    argc < 3
    || sscanf(argv[2], "%hd", &direction) < 1
    || direction > 1
    || direction < -1
  ) direction = -1;

  unsigned int questions;
  if(
    argc < 4
    || sscanf(argv[3], "%u", &questions) < 1
    || questions > db->size
  ) questions = db->size;

  // display_word_db(db);
  // printf("Direction: %hd\nQuestions to ask: %u\n", direction, questions);

  voc_quizz(db, direction, questions);

  free_word_db(db);

  return 0;
}
