# voc-quizz
A console-based app to learn vocabulary.
Written in C.

**On Windows, special characters don't work properly.**


### Compilation
A make-file is provided. Make sure you have make and GCC installed.
```bash
make
```


### Usage
```bash
./voc-quizz  db_filename  [direction]  [questions]
```

**db_filename:** path to database file

**direction:** what should be asked ?

- `-1`: random (default)
- `0`: word in language 1 told, and word in language 2 asked
- `1`: opposite

**questions:** maximum number of questions to ask.


### Database file format
```
Language 1|Language2
{number of lines below}
Word in language 1|Word in language 2
Word in language 1|Word in language 2
Word in language 1|Word in language 2
```

You can also refer to `example/english.txt`
