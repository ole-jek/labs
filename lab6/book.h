#ifndef BOOK_H
#define BOOK_H

#include "funcs.h"

typedef struct {
	char* author;
	char* title;
	int year;
	char* genre;
	char* summary;
} Book;

Book* createBook();
void freeBookContent(Book* b);
void freeBook(Book* b);
void inputBook(Book* b);
void printBook(Book* b);

#endif
