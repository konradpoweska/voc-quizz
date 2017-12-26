#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wordDB.h"

#define TMP_STR_SIZE 256

WordDB* create_word_db(unsigned int size) {
  WordDB* db = malloc(sizeof(WordDB));
  if(db == NULL) {
    fprintf(stderr, "Memory allocation error.\n");
    return NULL;
  }

  db->size = size;

  db->words = malloc(sizeof(Word)*size);
  if(db->words == NULL) {
    fprintf(stderr, "Memory allocation error.\n");
    free(db);
    return NULL;
  }

  return db;
}


void free_word_db(WordDB* db) {
  while(db->size>0) {
    db->size--;
    free(db->words[db->size].word1);
    free(db->words[db->size].word2);
  }
  free(db->words);
  free(db->lang1);
  free(db->lang2);
  free(db);
}


// READING A FILE

void end_at_newline(char* l) {
  while(*l != '\n') {
    if(*l == '\0') return;
    l++;
  }
  *l = '\0';
}

char* extract_words(char* l) {
  // returns a pointer to the second word of the line
  // transform the separator into a \0 the stop the first word
  while(*l != '|') {
    if(*l == '\0') return NULL;
    l++;
  }
  *l = '\0';
  end_at_newline(l+1);
  return l+1;
}

WordDB* read_word_db_file(char* filename) {
  FILE* f = fopen(filename, "r");
  if(f == NULL) {
    fprintf(stderr, "Can't read <%s>.\n", filename);
    return NULL;
  }
  char buffer[TMP_STR_SIZE];
  unsigned int i;

  if(!fgets(buffer, TMP_STR_SIZE, f) || !fscanf(f, "%u\n", &i)) {
    return NULL;
    fclose(f);
  }
  char* word2 = extract_words(buffer);

  WordDB* db = create_word_db(i);
  db->lang1 = strdup(buffer);
  db->lang2 = strdup(word2);

  for(i=0; i<db->size; i++) {
    if(!fgets(buffer, TMP_STR_SIZE, f)) break;
    word2 = extract_words(buffer);
    db->words[i].word1 = strdup(buffer);
    db->words[i].word2 = strdup(word2);
  }

  db->size = i; // to avoid too short databases

  fclose(f);
  return db;
}


void display_word_db(WordDB* db) {
  if(!db) return;
  printf("Languages: %s : %s\nWords:\n", db->lang1, db->lang2);

  int i;
  for(i=0; i<db->size; i++)
    printf("  %s : %s\n", db->words[i].word1, db->words[i].word2);
}
