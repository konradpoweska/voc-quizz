#ifndef WORD_DB_H
#define WORD_DB_H

typedef struct _word{
  char* word1;
  char* word2;
} Word;

typedef struct _worddb {
  char* lang1;
  char* lang2;
  unsigned int size;
  Word* words;
} WordDB;


WordDB* create_word_db(unsigned int size);

void free_word_db(WordDB* db);

void end_at_newline(char* l);

WordDB* read_word_db_file(char* filename);

void display_word_db(WordDB* db);


#endif
