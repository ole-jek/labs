#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

extern int sort_fields[3];
extern int sort_dirs[3];
extern int sort_num;
extern const int GLOBAL_MAX_YEAR;

typedef struct {
	Book* books;
	int count;
	int capacity;
} Library;

Library* createLib();
void reserveMemory(Library* lib); // +
void addBook(Library* lib); // +
void deleteBook(Library* lib, const char* title); // +
void deleteBookAction(Library* lib); // +
void saveToFile(Library* lib, const char* filename); // +
void saveToFileAction(Library* lib); // +
void loadFromFile(Library* lib, const char* filename); // +
void loadFromFileAction(Library* lib); // +
void printLibrary(Library* lib); // +
void sortLib(Library* lib); // +
void findBookByName(Library* lib); // + 
void undo(Library* lib); // +
void changeBook(Library* lib); // +
void exitProg(Library* lib); // +
void showGenre(Library* lib); // +
void saveHistory(Library* lib);
void fprintEscaped(FILE* f, const char* str);
void readField(FILE* f, char* buffer, int maxSize);
#endif